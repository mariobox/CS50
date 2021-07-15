import os
import time

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)


# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd


# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stockWorth = 0
    zeroCounter = 0
    port = db.execute(
        "SELECT Symbol, Name, SUM(Shares), Price, Total FROM transactions WHERE id = :id GROUP BY Symbol", id=session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
    # assign total cash on hand to variable
    cashLeft = cash[0]["cash"]
    portLength = len(port)
    for i in range(len(port)):
        # calculate current prices of stocks owned
        port[i]["Price"] = lookup(port[i]["Symbol"])["price"]
        # calculate total dollar value of shares owned
        port[i]["Total"] = port[i]["SUM(Shares)"] * port[i]["Price"]
        # calculate the total dollar value of stock portfolio
        stockWorth += port[i]["Total"]
    # calculate net worth
    netWorth = stockWorth + cashLeft
    return render_template("index.html", port=port, portLength=portLength, cashLeft=cashLeft, netWorth=netWorth)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    if request.method == "POST":
        # get stock symbol from the form
        symbol = request.form.get("symbol")

        # validate company symbol
        quote = lookup(symbol)
        if symbol == "":
            return apology("You must enter a stock symbol")
        elif not type(quote) is dict:
            return apology("Invalid symbol")
        # get quantity to buy from the form
        qty = request.form.get("shares")

        # validate quantity to buy
        # make sure quantity is not empty
        if qty == '':
            return apology("Input number of shares")
        # make sure quantity is an integer
        while True:
            try:
                qty = int(request.form.get("shares"))
            except ValueError:
                return apology("input a positive integer")
                continue
            else:
                break
        # make sure integer quantity is positive
        if qty < 0:
            return apology("# of shares must be positive")

        # create and set variables to use in query
        quote = lookup(symbol)
        prc = quote["price"]
        tot = prc * qty
        usid = session["user_id"]
        nm = quote["name"]

        # verify if there is enough cash to buy the stocks
        cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])

        # if there is enough cash buy stocks and update cash amount on database
        if cash[0]["cash"] >= tot:
            db.execute("INSERT INTO transactions (Symbol, Trans, Name, Shares, Price, Total, id) VALUES (:symbol, :trans, :nm, :qty, :prc, :tot, :usid)",
                       symbol=symbol, trans='Buy', nm=nm, qty=qty, prc=prc, tot=tot, usid=usid)
            newCash = cash[0]["cash"] - tot

            # pass info to the template
            db.execute("UPDATE users SET cash = :newCash WHERE id = :usid", newCash=newCash, usid=usid)
            return redirect("/")

        # if there is not enough cash return apology
        else:
            return apology("Not enough cash")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    hist = db.execute("SELECT Symbol, Shares, Price, Date FROM transactions WHERE id = :id", id=session["user_id"])
    return render_template("history.html", hist=hist)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout/")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    if request.method == "POST":

        # get stock symbol from the form
        symbol = request.form.get("symbol")
        quote = lookup(symbol)

        # validate stock symbol
        if symbol == "":
            return apology("You must enter a stock symbol")
        elif not type(quote) is dict:
            return apology("Invalid symbol")

        # if stock is valid pass info to the template
        else:
            return render_template("quoted.html", name=quote["name"], symbol=symbol, price=quote["price"])


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # Ensure password doesn't contain any typos
        elif not request.form.get("password") == request.form.get("confirmation"):
            return apology("your passwords don't match")

        hash = generate_password_hash(request.form.get("password"))

        result = db.execute("INSERT INTO users (username, hash) VALUES(:username, :hash)",
                            username=request.form.get("username"), hash=hash)

        if not result:
            return apology("The username is already taken")

        # Log new user in automatically
        rows = db.execute("SELECT id FROM users WHERE username = :username", username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "GET":

        # get symbols of available stocks to sell
        stocksToSell = db.execute("SELECT Symbol FROM transactions WHERE id = :id GROUP BY Symbol", id=session["user_id"])

        # pass info to the template
        return render_template("sell.html", stocksToSell=stocksToSell)

    if request.method == "POST":

        # initialize helper variables
        totalSharesBought = 0
        totalSharesSold = 0
        totalShares = 0

        # get information from form
        symbol = request.form.get("symbol")
        qty = int(request.form.get("shares"))

        # define and set variables to pass to template
        quote = lookup(symbol)
        prc = quote["price"]
        tot = prc * qty
        usid = session["user_id"]
        nm = quote["name"]
        sellThisBought = db.execute("SELECT Shares FROM transactions WHERE Symbol = :symbol AND Trans = :trans",
                                    symbol=request.form.get("symbol"), trans="Buy")
        sellThisSold = db.execute("SELECT Shares FROM transactions WHERE Symbol = :symbol AND Trans = :trans",
                                  symbol=request.form.get("symbol"), trans="Sell")

        # calculate how many shares of the selected symbol are available to sell
        for i in range(0, len(sellThisBought)):
            totalSharesBought += sellThisBought[i]["Shares"]
        for i in range(0, len(sellThisSold)):
            totalSharesSold += sellThisSold[i]["Shares"]
        totalShares = totalSharesBought + totalSharesSold

        # if there are enough shares of that symbol to sell, then sell them
        if totalShares >= qty:
            db.execute("INSERT INTO transactions (Symbol, Trans, Name, Shares, Price, Total, id) VALUES (:symbol, :trans, :nm, :qty, :prc, :tot, :usid)",
                       symbol=symbol, trans='Sell', nm=nm, qty=(-1)*qty, prc=prc, tot=tot, usid=usid)
            cash = db.execute("SELECT cash FROM users WHERE id = :id", id=session["user_id"])
            newCash = cash[0]["cash"] + tot
            db.execute("UPDATE users SET cash = :newCash WHERE id = :usid", newCash=newCash, usid=usid)
            return redirect("/")

        # if not enough shares of that symbol to sell return apology
        else:
            return apology("You don't have enough shares")
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)

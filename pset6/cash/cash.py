from cs50 import get_float


def main():
    # While statements
    num = get_float("How much change do I owe you?: ")
    while num < 0:
        num = get_float("How much change do I owe you?: ")

    # Transform to cents in int form with two decimals to avoid rounding errors
    num = int(round(num * 100, 2))

    # Calculate number or coins
    quarters = num // 25
    num = num % 25

    dimes = num // 10
    num = num % 10

    nickels = num // 5
    num = num % 5

    pennies = num

    totalCoins = quarters + dimes + nickels + pennies

    # Print total minimum number of coins
    print("The minimum number of coins is: {}".format(totalCoins))


if __name__ == "__main__":
    main()

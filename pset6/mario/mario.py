from cs50 import get_int


def main():
    # While statements
    num = get_int("Give me an int between 0 and 23: ")
    while num < 0 or num > 23:
        num = get_int("Give me an int between 0 and 23: ")

    # Print pyramid
    for i in range(num):
        print(" " * (num - (i + 1)), end="")
        print("#" * (i + 1), end="")
        print("  ", end="")
        print("#" * (i + 1))


if __name__ == "__main__":
    main()
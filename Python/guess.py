import random


def guess():
    num = random.randint(1, 100)
    print("Welcome to the guessing game!")
    while True:
        guess = int(input("Enter a number from 1 - 100: "))
        if guess == 69:
            print("The random number is: ", num)
            print("Do you want to continue? (y/n)")
            answer = input()
            if answer == "n":
                break
        elif guess == num:
            print("You got it!")
            break
        elif guess < num:
            print("Too low!")
        else:
            print("Too high!")


guess()


while True:
    print("Do you want to play again? (y/n)")
    answer = input()
    if answer == "n":
        break
    else:
        print("\n")
        guess()

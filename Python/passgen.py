import random
import string


def generate_password(
    length=12,
    include_lowercase=True,
    include_uppercase=True,
    include_digits=True,
    include_special=True,
):
    """Generates a random password based on user-specified criteria."""

    characters = ""
    if include_lowercase:
        characters += string.ascii_lowercase
    if include_uppercase:
        characters += string.ascii_uppercase
    if include_digits:
        characters += string.digits
    if include_special:
        characters += string.punctuation

    # Ensure at least one character from each selected type
    password = [
        random.choice(chars)
        for chars in (
            string.ascii_lowercase,
            string.ascii_uppercase,
            string.digits,
            string.punctuation,
        )
        if chars in characters
    ]

    # Fill remaining length with random characters
    password += [random.choice(characters) for _ in range(length - len(password))]

    # Shuffle to increase randomness
    random.shuffle(password)

    return "".join(password)


# Get user input for password criteria
while True:
    try:
        length = int(input("Enter desired password length (minimum 8): "))
        if length < 8:
            raise ValueError
        break
    except ValueError:
        print("Invalid input. Please enter a number greater than or equal to 8.")

include_lowercase = input("Include lowercase letters? (y/n): ").lower() == "y"
include_uppercase = input("Include uppercase letters? (y/n): ").lower() == "y"
include_digits = input("Include digits? (y/n): ").lower() == "y"
include_special = input("Include special characters? (y/n): ").lower() == "y"

# Generate and print the password
password = generate_password(
    length, include_lowercase, include_uppercase, include_digits, include_special
)
print("Generated password:", password)

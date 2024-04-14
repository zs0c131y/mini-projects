import qrcode

def switch_case(argument):
    switcher = {
        1: "URL",
        2: "Text",
    }
    return switcher.get(argument, "Invalid type")

def main():
    # Switch case for the type of QR code
    print("Enter the type of QR code you want to generate:\n1. URL\n2. Text\n")
    argument = int(input("Enter your choice: "))

    # Validate the input
    if argument not in [1, 2]:
        print("Invalid choice!")
        return

    # Taking the URL or text as input
    if argument == 1:
        data = input("Enter the URL: ")
    else:
        data = input("Enter the text: ")

    qr = qrcode.QRCode(version=1, error_correction=qrcode.constants.ERROR_CORRECT_L, box_size=10, border=4)
    qr.add_data(data)
    qr.make(fit=True)

    # Converting into an image
    img = qr.make_image(fill_color="black", back_color="white")
    name = input("Enter the name of the file: ")
    img.save(name + ".png")

    print("QR Code generated successfully!")
    print("File saved as " + name + ".png")

if __name__ == "__main__":
    main()

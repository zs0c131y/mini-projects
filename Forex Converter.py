from forex_python.converter import CurrencyRates, CurrencyCodes
from requests.exceptions import ConnectionError
import sys

converter = CurrencyRates()
codes = CurrencyCodes()

def parse_arguments():
    if len(sys.argv) < 3:
        raise ValueError("Insufficient arguments")

    amount = 1.0  # Default amount
    if len(sys.argv) >= 2:
        try:
            amount = float(sys.argv[1])
        except ValueError:
            pass  # Use default amount if parsing fails

    if len(sys.argv) < 4 or sys.argv[2] != 'to':
        raise ValueError("Invalid arguments")

    return amount, sys.argv[1].upper(), sys.argv[3].upper()

def convert_currency(amount, base, dest):
    try:
        base_symbol = codes.get_symbol(base)
        dest_symbol = codes.get_symbol(dest)

        if not base_symbol:
            raise ValueError(f'Currency {base} is invalid')
        if not dest_symbol:
            raise ValueError(f'Currency {dest} is invalid')

        result = converter.convert(base_cur=base, dest_cur=dest, amount=amount)
        result = round(result, 3)

        print(f'{amount} {base_symbol} equals {result} {dest_symbol}')

    except ConnectionError:
        print('Connection error')
        sys.exit(1)

    except ValueError as e:
        print(f'Error: {e}')
        sys.exit(1)

def main():
    print("Choose how you want to input data:")
    print("1. Command Line")
    print("2. Direct Initialization")
    
    choice = input("Enter your choice (1 or 2): ")
    
    if choice == '1':
        usage = '[<amount>] <BASE> to <DESTINATION>'
        try:
            amount, base, dest = parse_arguments()
        except ValueError as e:
            print(f'Error: {e}')
            print('Usage:')
            print(usage)
            sys.exit(1)

        convert_currency(amount, base, dest)
        
    elif choice == '2':
        amount = float(input("Enter the amount: "))
        base = input("Enter the base currency: ").upper()
        dest = input("Enter the destination currency: ").upper()
        
        convert_currency(amount, base, dest)
        
    else:
        print("Invalid choice. Please enter either 1 or 2.")
        sys.exit(1)

if __name__ == "__main__":
    main()

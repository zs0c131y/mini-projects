from googletrans import Translator

def translate_text(text, target_language='en'):
    translator = Translator()
    translation = translator.translate(text, dest=target_language)
    return translation.text

def main():
    print("Welcome to the Python Translator!")
    while True:
        text = input("Enter text to translate (or 'q' to quit): ")
        if text.lower() == 'q':
            print("Thank you for using the translator. Goodbye!")
            break
        target_language = input("Enter target language (e.g., 'fr' for French, 'es' for Spanish): ")
        translated_text = translate_text(text, target_language)
        print("Translated text:", translated_text)

if __name__ == "__main__":
    main()

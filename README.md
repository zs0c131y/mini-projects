
# Mini Projects

This repository contains mini projects that I have worked on, which are helpful but not so significant to get an entire repo for them. This README file will list projects that I have created in different languages, but mainly Python, JavaScript, C.

## DupeDelete - Delete .json and duplicates

Might be the silliest idea so far, but I got this idea from a problem I encountered. Having 60 GB+ for Takeout files, they're merged with JSON files and have duplicates in most of the cases. I downloaded my entire cloud data to store offline (and store new things on cloud). When I unzipped my files, they had JSON for every normal file and in most cases these files were repeated. Very painful. More so when you have to delete duplicates. Deleting JSON files wasn't a big deal, just search for it, select all and delete but still a tedious task.

So to get rid and automate the process, I developed a Python program that takes the location of the current working directly and scans through the files. It finds all JSON files and deletes them, permanently. It takes the non-JSON file names and stores them in a new .txt file with their hashes. When running in different folder or as such, it checks the non-JSON files and their hashes which will delete the duplicate files.

## QR Code Generator

I generally made QR codes online, but the options are overwhelming - contacts, links, texts, and what not. I never had the use of so many sources at all. So to serve my purpose, I created a QR Code Generator using the "qrcode" package in Python to achieve the goal. This app takes links and texts to generate a QR Code -- much rather in the same way sans confusion.

## Translator using "googletrans"

A simple but effective translator that uses the "googletrans" py library to translate text into your target languages. A list of all target codes are available here: <https://pypi.org/project/googletrans/>

## Forex Currency Converter

This simple Python script allows you to convert currencies using the forex_python library. You can input the amount, base currency, and destination currency either through the command line or directly initialize the values in the script.

Command line input: `python currency_converter.py [<amount>] <BASE> to <DESTINATION>`

#### Direct Initialization:

    1. Run the script.
    2. Choose the option for direct initialization.
    3. Enter the amount, base currency, and destination currency when prompted.

#### Dependencies

    1. forex_python
    2. requests

#### How to Run

    1. Clone this repository to your local machine.
    2. Install dependencies using pip install forex-python.
    3. Run the script using python currency_converter.py.

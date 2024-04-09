# Mini Projects
This repository contains mini projects that I have worked on, which are helpful but not so significant to get an entire repo for them. This README file will list projects that I have created in different languages, but mainly Python, JavaScript, C. 

## DupeDelete - Delete .json and duplicates
Might be the silliest idea so far, but I got this idea from a problem I encountered. Having 60 GB+ for Takeout files, they're merged with JSON files and have duplicates in most of the cases. I downloaded my entire cloud data to store offline (and store new things on cloud). When I unzipped my files, they had JSON for every normal file and in most cases these files were repeated. Very painful. More so when you have to delete duplicates. Deleting JSON files wasn't a big deal, just search for it, select all and delete but still a tedious task. 

So to get rid and automate the process, I developed a Python program that takes the location of the current working directly and scans through the files. It finds all JSON files and deletes them, permanently. It takes the non-JSON file names and stores them in a new .txt file with their hashes. When running in different folder or as such, it checks the non-JSON files and their hashes which will delete the duplicate files. 

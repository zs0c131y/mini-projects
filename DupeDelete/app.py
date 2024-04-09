import os
import hashlib

def delete_json_files(folder_path):
    try:
        files = os.listdir(folder_path)
        non_json_files = []     
        for file in files:
            if file.endswith('.json'):
                file_path = os.path.join(folder_path, file)
                os.remove(file_path)
                print(f"Deleted: {file}")
            else:
                non_json_files.append(file)
        with open('non_json_files.txt', 'a') as f:
            for file_name in non_json_files:
                f.write(file_name + '\n')
        print("Deletion completed successfully.")
    except Exception as e:
        print(f"An error occurred: {e}")

def delete_duplicates(folder_path):
    try:
        with open('non_json_files.txt', 'r') as f:
            non_json_files = f.read().splitlines()
        files = os.listdir(folder_path)
        for file in files:
            if file not in non_json_files:
                file_path = os.path.join(folder_path, file)
                with open(file_path, 'rb') as f:
                    file_hash = hashlib.md5(f.read()).hexdigest()
                if file_hash in hashes:
                    os.remove(file_path)
                    print(f"Deleted duplicate: {file}")
                else:
                    hashes.add(file_hash)
        print("Duplicate deletion completed successfully.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == "__main__":
    current_folder = os.getcwd()
    delete_json_files(current_folder)
    hashes = set()
    delete_duplicates(current_folder)

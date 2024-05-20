# Projects in this folder -

## HashIt - Text and File Hashing Tool

HashIt is a simple hashing tool developed in JavaScript/Node.js that facilitates the hashing of text and files using various hashing algorithms such as MD5, SHA-1, and SHA-256. This tool provides a command-line interface for convenient usage.

### Features

- Hashing of both text and files
- Supports MD5, SHA-1, and SHA-256 algorithms
- Simple and intuitive command-line interface

### Usage

1. **Hash a String**: Enter `1` when prompted and provide the string you want to hash.
2. **Hash a File**: Enter `2` when prompted and specify the filename of the file you want to hash.

### Dependencies

- Node.js
- crypto module (built-in)
- fs module (built-in)
- readline module (built-in)

### How to Run

1. Clone this repository to your local machine.
2. Navigate to the project directory.
3. Run `node hashit.js` in your terminal.

### Note

Ensure Node.js is installed on your system before running the script.

For any issues or suggestions, feel free to create an issue or submit a pull request. Happy hashing! 🔒

## MapScan

MapScan is a simple, hobbyist-level port scanner written in JavaScript. It uses Node.js to scan specified ports on a target host and reports which ports are open. This tool is intended for educational purposes and is not as advanced as professional tools like Nmap.

### Features

- Scans a range of ports on a specified host.
- Lists open ports found within the specified range.
- Uses asynchronous operations to perform scans in parallel, improving scan speed.

### Limitations

- Due to the simplicity of the implementation, there may be issues with large scans where some ports might be missed.
- For example, scanning a range of 1-100 will show all open ports, but scanning a range of 1-1000 might miss some open ports.
- Since this tool runs on Node.js, it faces a myriad of limitations and a few well-known ports like 21 are not displayed in result if opened because of this reason as the target server in some cases might prevent scanning of such ports without a bypass.

### Requirements

- Node.js (v12 or higher)

### Installation

 Clone the repository:
   ```
   git clone https://github.com/zs0c131y/mini-projects/blob/main/JavaScript/mapscan.js
   cd mapscan
   npm install (the required dependencies)
   ```
### Usage

1. Run the script: `node mapscan.js`
2. Follow the prompts and enter the data.
3. The script will run and return the results. I would suggest using nmap as well to cross-check.

### Contribution

This project is intended for learning and hobbyist purposes. Feel free to fork the repository and submit pull requests with improvements or bug fixes.

### Note

Please note that unauthorized port scanning can be illegal and unethical. Always obtain proper authorization before scanning any network or host.

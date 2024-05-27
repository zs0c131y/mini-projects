# C Projects

## 1. Mapscan

- **Description**: The port scanner is a multi-threaded application that scans a specified range of ports on a given IP address to check if they are open. A similar program is in this repository that is implemented using JavaScript.

- **Tech Stack**: C

### Usage

- **Description**: To compile the port scanner, you need to have a C compiler installed. On Windows, you can use GCC provided by MinGW or any other compatible compiler. This is an accurate port scanner than the one I made in JavaScript and gives all open ports on that particular IP.

- **Compile**: `gcc mapscan.c -o mapscan -lws2_32`

- **Run**: `mapscan <IP> <start_port> <end_port>` after a successful compilation in command line. Make sure that your includePath and libPath are correctly configured in system environment path variable.

- **Example**: `mapscan 127.0.0.1 1 65535`

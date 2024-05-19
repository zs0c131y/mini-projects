// import libraries
const crypto = require("crypto");
const fs = require("fs");
const readline = require("readline");

// create readline interface
const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

// compute functions
function computeMD5(input) {
  return crypto.createHash("md5").update(input).digest("hex");
}

function computeSHA1(input) {
  return crypto.createHash("sha1").update(input).digest("hex");
}

function computeSHA256(input) {
  return crypto.createHash("sha256").update(input).digest("hex");
}

// hash functions
function hashString(input) {
  console.log(`Input String: ${input}`);
  console.log(`MD5 Hash: ${computeMD5(input)}`);
  console.log(`SHA-1 Hash: ${computeSHA1(input)}`);
  console.log(`SHA-256 Hash: ${computeSHA256(input)}`);
}

function hashFile(filename) {
  fs.readFile(filename, (err, data) => {
    if (err) {
      console.error("Error reading file:", err);
      return;
    }

    console.log(`Input File: ${filename}`);
    console.log(`MD5 Hash: ${computeMD5(data)}`);
    console.log(`SHA-1 Hash: ${computeSHA1(data)}`);
    console.log(`SHA-256 Hash: ${computeSHA256(data)}`);
  });
}

// main
rl.question(
  "1. Hash a string\n2. Hash a file\nEnter your choice: ",
  (choice) => {
    if (choice === "1") {
      rl.question("Enter the string to hash: ", (input) => {
        hashString(input);
        rl.close();
      });
    } else if (choice === "2") {
      rl.question("Enter the filename to hash: ", (filename) => {
        hashFile(filename);
        rl.close();
      });
    } else {
      console.log("Invalid choice");
      rl.close();
    }
  }
);

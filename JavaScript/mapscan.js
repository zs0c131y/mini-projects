const net = require("net");
const readline = require("readline");
const { exec } = require("child_process"); // Import child_process for executing shell commands

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

// Function to scan a single port
const scanPort = (host, port, timeout) => {
  return new Promise((resolve, reject) => {
    const socket = new net.Socket();
    let status = "closed";

    socket.setTimeout(timeout);
    socket.on("connect", () => {
      status = "open";
      socket.end();
    });

    socket.on("timeout", () => {
      status = "closed";
      socket.destroy();
    });

    socket.on("error", () => {
      status = "closed";
    });

    socket.on("close", () => {
      resolve({ host, port, status });
    });

    socket.connect(port, host);
  });
};

// Function to scan multiple ports in parallel
const scanPorts = async (host, startPort, endPort, timeout = 2000) => {
  const portPromises = Array.from({ length: endPort - startPort + 1 }, (_, i) =>
    scanPort(host, startPort + i, timeout)
  );

  // Use Promise.all to wait for all scans to complete
  const portResults = await Promise.all(portPromises);
  return portResults;
};

const askDetails = (question) => {
  return new Promise((resolve) => rl.question(question, resolve));
};

// Function to ping a host
const pingHost = (host) => {
  return new Promise((resolve, reject) => {
    const platform = process.platform;
    const pingCommand =
      platform === "win32" ? `ping -n 4 ${host}` : `ping -c 4 ${host}`;

    exec(pingCommand, (error, stdout, stderr) => {
      if (error) {
        console.error(`Ping error: ${error.message}`);
        return reject(error);
      }
      if (stderr) {
        console.error(`Ping stderr: ${stderr}`);
        return reject(new Error(stderr));
      }
      console.log(stdout);
      resolve(stdout);
    });
  });
};

(async () => {
  try {
    const host = await askDetails("Enter the host: ");
    const startPort = parseInt(await askDetails("Enter the start port: "), 10);
    const endPort = parseInt(await askDetails("Enter the end port: "), 10);

    if (
      isNaN(startPort) ||
      isNaN(endPort) ||
      startPort < 1 ||
      endPort > 65535 ||
      startPort > endPort
    ) {
      console.error(
        "Invalid port range. Please enter valid numbers between 1 and 65535 with start port less than or equal to end port."
      );
    } else {
      const startTime = Date.now(); // Record the start time
      const results = await scanPorts(host, startPort, endPort);
      const endTime = Date.now(); // Record the end time
      const elapsedTime = endTime - startTime; // Calculate elapsed time in milliseconds
      console.log(`Scanning took ${elapsedTime}ms`);

      const openPorts = results.filter((result) => result.status === "open");
      if (openPorts.length === 0) {
        console.log("No open ports found.");
      } else {
        openPorts.forEach((result) => {
          console.log(`Port ${result.port} is ${result.status}`);
        });
      }

      // Ping the host
      //   await pingHost(host);
    }
  } catch (err) {
    console.error(`Error: ${err.message}`);
  } finally {
    rl.close();
  }
})();

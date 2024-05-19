const net = require("net");
const readline = require("readline");

const rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

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

const scanPorts = async (host, startPort, endPort, timeout = 2000) => {
  const portStatus = [];
  for (let port = startPort; port <= endPort; port++) {
    try {
      const result = await scanPort(host, port, timeout);
      portStatus.push(result);
    } catch (err) {
      console.error(`Error scanning port ${port}: ${err.message}`);
    }
  }
  return portStatus;
};

const askDetails = (question) => {
  return new Promise((resolve) => rl.question(question, resolve));
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
      const results = await scanPorts(host, startPort, endPort);
      const openPorts = results.filter((result) => result.status === "open");
      if (openPorts.length === 0) {
        console.log("No open ports found.");
      } else {
        openPorts.forEach((result) => {
          console.log(`Port ${result.port} is ${result.status}`);
        });
      }
    }
  } catch (err) {
    console.error(`Error: ${err.message}`);
  } finally {
    rl.close();
  }
})();

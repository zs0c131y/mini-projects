const endpoints = [
  {
    id: 1,
    name: "DC1 - MIA, Miami FL, USA",
    url: "149.154.175.50",
  },
  {
    id: 2,
    name: "DC2 - AMS, Amsterdam, NL",
    url: "149.154.167.50",
  },
  {
    id: 3,
    name: "DC3 - MIA, Miami FL, USA",
    url: "149.154.175.100",
  },
  {
    id: 4,
    name: "DC4 - AMS, Amsterdam, NL",
    url: "149.154.167.91",
  },
  {
    id: 5,
    name: "DC5 - SIN, Singapore, SG",
    url: "91.108.56.100",
  },
];

const statusContainer = document.getElementById("status-container");

function updateStatus() {
  statusContainer.innerHTML = ""; // Clear existing status

  endpoints.forEach((endpoint) => {
    const statusItem = document.createElement("div");
    statusItem.className = "status-item available";
    statusItem.id = `status-${endpoint.id}`;
    statusItem.innerHTML = `
              <span>${endpoint.name}</span>
              <span class="ping" id="ping-${endpoint.id}">Ping: --ms</span>
          `;
    statusContainer.appendChild(statusItem);

    pingEndpoint(endpoint);
  });
}

function pingEndpoint(endpoint) {
  const start = Date.now();

  fetch(endpoint.url)
    .then(() => {
      const ping = Date.now() - start;
      document.getElementById(
        `ping-${endpoint.id}`
      ).innerText = `Ping: ${ping}ms`;
    })
    .catch(() => {
      document.getElementById(`ping-${endpoint.id}`).innerText = `Ping: --ms`;
    });
}

document.addEventListener("DOMContentLoaded", () => {
  setInterval(updateStatus, 5000);
  updateStatus(); // Initial call on page load
});

#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

#define THREAD_POOL_SIZE 100

typedef struct
{
    const char *ip;
    int port;
} ScanParams;

DWORD WINAPI scan_port(LPVOID param)
{
    ScanParams *params = (ScanParams *)param;
    const char *ip = params->ip;
    int port = params->port;

    WSADATA wsa;
    SOCKET sock;
    struct sockaddr_in addr;

    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        printf("WSAStartup failed. Error Code: %d\n", WSAGetLastError());
        return 1;
    }

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET)
    {
        printf("Socket creation failed with error code: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) == 0)
    {
        printf("Port %d is open\n", port);
    }

    closesocket(sock);
    WSACleanup();
    free(params);
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <IP> <start_port> <end_port>\n", argv[0]);
        return 1;
    }

    const char *ip = argv[1];
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);

    if (start_port < 1 || end_port > 65535 || start_port > end_port)
    {
        fprintf(stderr, "Invalid port range\n");
        return 1;
    }

    HANDLE threads[THREAD_POOL_SIZE];
    int current_thread = 0;

    for (int port = start_port; port <= end_port; port++)
    {
        ScanParams *params = (ScanParams *)malloc(sizeof(ScanParams));
        params->ip = ip;
        params->port = port;

        threads[current_thread] = CreateThread(NULL, 0, scan_port, params, 0, NULL);
        current_thread++;

        if (current_thread >= THREAD_POOL_SIZE)
        {
            WaitForMultipleObjects(THREAD_POOL_SIZE, threads, TRUE, INFINITE);
            current_thread = 0;
        }
    }

    // Wait for remaining threads
    if (current_thread > 0)
    {
        WaitForMultipleObjects(current_thread, threads, TRUE, INFINITE);
    }

    return 0;
}

#include "server.h"
#include <WinSock2.h>

#ifdef _WIN32

void startNetworking() {
    WSADATA ws = {0};
    int iResult = WSAStartup(MAKEWORD(2, 2), &ws);
    if (iResult != 0) {
        printf("Error: WSAStartup failed: %d\n", iResult);
        exit(1);
    }
}

void cleanupNetworking(MySocket ConnectSocket) {
    closesocket(ConnectSocket);
    WSACleanup();
}

#else

void startNetworking() {
    // No initialization needed on Linux
}

void cleanupNetworking(MySocket ConnectSocket) {
    close(ConnectSocket);
}

#endif


MySocket connectSocket(char *host, char *port) {
    MySocket ConnectSocket = INVALID_SOCKET;
    int iResult = 0;
    
    struct addrinfo hints, *result, *ptr;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(host, port, &hints, &result);
    if (iResult != 0) {
        printf("Error: getaddrinfo failed with error: %d\n", iResult);
        return INVALID_SOCKET;
    }

    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            continue;
        }

        iResult = connect(ConnectSocket, ptr->ai_addr, ptr->ai_addrlen);
        if (iResult == -1) {
            #ifdef _WIN32
                closesocket(ConnectSocket);
            #else
                close(ConnectSocket);
            #endif

            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }
    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error: Unable to connect to server!\n");
        return INVALID_SOCKET;
    }

    return ConnectSocket;
}

void sendRequest(MySocket ConnectSocket, char *command) {
    int iResult = send(ConnectSocket, command, strlen(command), 0);
    if (iResult == -1) {
        printf("Error: send failed\n");
        cleanupNetworking(ConnectSocket);
        exit(1);
    }

    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == -1) {
        printf("Error: shutdown failed\n");
        cleanupNetworking(ConnectSocket);
        exit(1);
    }
}

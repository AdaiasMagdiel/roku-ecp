#include "server.h"

WSADATA startWSA() {
    WSADATA ws = {0};

    // Initialize Winsock
    int iResult = WSAStartup(MAKEWORD(2, 2), &ws);
    if (iResult != 0) {
        printf("Error: WSAStartup failed: %d\n", iResult);
        exit(1);
    }

    return ws;
}

SOCKET connectSocket(char *host, char *port) {
    SOCKET ConnectSocket = INVALID_SOCKET;

    int iResult = 0;
    
    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *ptr;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(host, port, &hints, &result);
    if (iResult != 0) {
        printf("Error: getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL; ptr=ptr->ai_next) {
        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %d\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }

        break;
    }
    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Error: Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    return ConnectSocket;
}
    
void sendRequest(SOCKET ConnectSocket, char *command) {
    // Send the command
    int iResult = send(ConnectSocket, command, (int)strlen(command), 0);
    if (iResult == SOCKET_ERROR) {
        printf("Error: send failed with error: %d\n", WSAGetLastError());
        
        closesocket(ConnectSocket);
        WSACleanup();
        
        exit(1);
    }

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        
        closesocket(ConnectSocket);
        WSACleanup();
        
        exit(1);
    }
}

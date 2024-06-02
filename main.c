#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#define HOST "192.168.1.3"
#define PORT "8060"

int main(int argc, char **argv) {
    int keysCount = 28;
    char *keys[] = {
        "Home",
        "Rev",
        "Fwd",
        "Play",
        "Select",
        "Left",
        "Right",
        "Down",
        "Up",
        "Back",
        "InstantReplay",
        "Info",
        "Backspace",
        "Search",
        "Enter",
        "VolumeDown",
        "VolumeMute",
        "VolumeUp",
        "PowerOff",
        "PowerOn",
        "ChannelUp",
        "ChannelDown",
        "InputTuner",
        "InputHDMI1",
        "InputHDMI2",
        "InputHDMI3",
        "InputHDMI4",
        "InputAV1",
    };

    if (argc == 1) {
        printf("Usage: rokuecp [key]\n\n");

        printf("Keys:\n");
        for (int i=0; i<keysCount; i++) {
            printf("    %s\n", keys[i]);
        }

        return 1;
    }

    char *key = argv[1];

    int iResult = 0;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo hints;
    struct addrinfo *result;
    struct addrinfo *ptr;

    // Initialize Winsock
    WSADATA ws = {0};
    iResult = WSAStartup(MAKEWORD(2, 2), &ws);
    if (iResult != 0) {
        printf("Error: WSAStartup failed: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(HOST, PORT, &hints, &result);
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

    // Send an initial buffer
    char buffer[1024];
    sprintf(buffer, "POST /keypress/%s HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n", key);

    iResult = send(ConnectSocket, buffer, (int)strlen(buffer), 0);
    if (iResult == SOCKET_ERROR) {
        printf("Error: send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}

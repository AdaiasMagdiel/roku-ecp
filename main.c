#include <stdio.h>
#include "src/server.h"

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

    char buffer[1024];
    sprintf(buffer, "POST /keypress/%s HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n", key);

    startWSA();
    SOCKET ConnectSocket = connectSocket(HOST, PORT);

    sendRequest(ConnectSocket, buffer);

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}

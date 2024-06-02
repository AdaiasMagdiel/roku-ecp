#ifndef MGDL_ECP
#define MGDL_ECP

#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

WSADATA startWSA();
SOCKET connectSocket(char *host, char *port);
void sendRequest(SOCKET ConnectSocket, char *command);

#endif  // MGDL_ECP

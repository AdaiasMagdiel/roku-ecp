#ifndef MGDL_ECP
#define MGDL_ECP

#include <stdio.h>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
typedef SOCKET MySocket;
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
typedef int MySocket;
#endif

void startNetworking();
MySocket connectSocket(char *host, char *port);
void sendRequest(MySocket ConnectSocket, char *command);
void cleanupNetworking(MySocket ConnectSocket);

#endif  // MGDL_ECP

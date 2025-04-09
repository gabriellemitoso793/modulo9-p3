#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib,"ws2_32.lib") // Biblioteca do Winsock

#define PORT "8080"
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL, hints;
    char buffer[BUFFER_SIZE];
    int iResult;

    WSAStartup(MAKEWORD(2,2), &wsaData);

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    getaddrinfo(NULL, PORT, &hints, &result);

    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    listen(ListenSocket, SOMAXCONN);
    printf("Servidor ouvindo na porta %s...\n", PORT);

    ClientSocket = accept(ListenSocket, NULL, NULL);
    printf("Cliente conectado.\n\n");

    do {
        iResult = recv(ClientSocket, buffer, BUFFER_SIZE-1, 0);
        if (iResult > 0) {
            buffer[iResult] = '\0';
            printf("%s", buffer);
        }
    } while (iResult > 0);

    printf("\nRecepção concluída.\n");

    closesocket(ClientSocket);
    closesocket(ListenSocket);
    WSACleanup();

    return 0;
}
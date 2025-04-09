#include <stdio.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

#define PORT "8080"
#define BUFFER_SIZE 1024

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;
    struct addrinfo *result = NULL, hints;
    FILE *file;
    char buffer[BUFFER_SIZE];

    // Inicializa Winsock
    WSAStartup(MAKEWORD(2,2), &wsaData);

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    getaddrinfo("127.0.0.1", PORT, &hints, &result);

    // Cria o socket
    sock = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

    // Conecta ao servidor
    connect(sock, result->ai_addr, (int)result->ai_addrlen);

    file = fopen(argv[1], "rb");
    if (file == NULL) {
        perror("Erro ao abrir arquivo");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Envia conteúdo do arquivo
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(sock, buffer, bytes_read, 0);
    }

    printf("Arquivo enviado com sucesso!\n");

    // Finalização
    fclose(file);
    closesocket(sock);
    WSACleanup();

    return 0;
}
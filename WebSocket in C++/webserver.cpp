/* ============================================================================
    Esse projeto se trata de um Servidor WebSocket. Se você chegou até aqui é 
    porque você precisa urgente arrumar alguma coisa neste código BOA SORTE, 
    pois quando ele foi feito apenas duas pessoas sabiam como ele funcionava 
    (Deus e Eu), agora somente ele sabe.
    
    Autor: Lukas Lujan Moreira
    Data: 22/08/2024
============================================================================ */

/* --- Cabeçalhos importados --- */

#include "webserver.hpp"

/* ========================================================================= */
/* --- Função Principal --- */

#define PORT 8080  // Porta para o servidor escutar

int main() {
    #ifdef _WIN32 // Código específico para Windows
    WSADATA wsaData;
    SOCKET server_sock = INVALID_SOCKET, client_sock = INVALID_SOCKET;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_size = sizeof(client_addr);

    // Inicializa o Winsock
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl; // Equivalente ao print
        return 1;
    }

    // Cria um socket
    server_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_sock == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl; // Equivalente ao print
        WSACleanup();
        return 1;
    }

    // Define o endereço e a porta do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Vincula o socket ao endereço e porta especificados
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl; // Equivalente ao print
        closesocket(server_sock);
        WSACleanup();
        return 1;
    }

    // Obtém e imprime o endereço IP e a porta do socket do servidor
    struct sockaddr_in local_addr;
    int local_addr_size = sizeof(local_addr);
    if (getsockname(server_sock, (struct sockaddr*)&local_addr, &local_addr_size) == 0) {
        char* local_ip = inet_ntoa(local_addr.sin_addr);  // Usando inet_ntoa para Windows
        std::cout << "Endereco do servidor: " << local_ip << ":" << ntohs(local_addr.sin_port) << std::endl; // Equivalente ao print
    } else {
        std::cerr << "Erro ao obter o endereço do socket: " << WSAGetLastError() << std::endl; // Equivalente ao print
    }

    // Escuta por conexões
    if (listen(server_sock, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl; // Equivalente ao print
        closesocket(server_sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Aguardando conexoes no Windows na porta " << PORT << "..." << std::endl; // Equivalente ao print

    // Aceita uma conexão de cliente
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
    if (client_sock == INVALID_SOCKET) {
        std::cerr << "Accept failed: " << WSAGetLastError() << std::endl; // Equivalente ao print
        closesocket(server_sock);
        WSACleanup();
        return 1;
    }

    // Imprime o endereço IP do cliente
    char* client_ip = inet_ntoa(client_addr.sin_addr);
    std::cout << "Conexão recebida de: " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl; // Equivalente ao print

    // Fecha os sockets
    closesocket(client_sock);
    closesocket(server_sock);
    WSACleanup();

    #elif defined(__linux__) // Código específico para Linux
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    // Cria um socket
    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        std::cerr << "Error at socket(): " << strerror(errno) << std::endl; // Equivalente ao print
        return 1;
    }

    // Define o endereço e a porta do servidor
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Vincula o socket ao endereço e porta especificados
    if (bind(server_sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Bind failed: " << strerror(errno) << std::endl; // Equivalente ao print
        close(server_sock);
        return 1;
    }

    // Obtém e imprime o endereço IP e a porta do socket do servidor
    struct sockaddr_in local_addr;
    socklen_t local_addr_size = sizeof(local_addr);
    if (getsockname(server_sock, (struct sockaddr*)&local_addr, &local_addr_size) == 0) {
        char local_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &local_addr.sin_addr, local_ip, INET_ADDRSTRLEN);
        std::cout << "Endereço do servidor: " << local_ip << ":" << ntohs(local_addr.sin_port) << std::endl; // Equivalente ao print
    } else {
        std::cerr << "Erro ao obter o endereço do socket: " << strerror(errno) << std::endl; // Equivalente ao print
    }

    // Escuta por conexões
    if (listen(server_sock, 3) < 0) {
        std::cerr << "Listen failed: " << strerror(errno) << std::endl;
        close(server_sock);
        return 1;
    }

    std::cout << "Aguardando conexões no Linux na porta " << PORT << "..." << std::endl;

    // Aceita uma conexão de cliente
    client_sock = accept(server_sock, (struct sockaddr*)&client_addr, &client_addr_size);
    if (client_sock < 0) {
        std::cerr << "Accept failed: " << strerror(errno) << std::endl;
        close(server_sock);
        return 1;
    }

    // Imprime o endereço IP do cliente
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    std::cout << "Conexão recebida de: " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;

    // Fecha os sockets
    close(client_sock);
    close(server_sock);
    #endif

    return 0;
}

/* ============================================================================  
                                                              
                                       _                      
                                      / \                     
                                     |oo >                    
                                     _\=/_                    
                    ___         #   /  _  \   #               
                   /<> \         \\//|/.\|\\//                
                 _|_____|_        \/  \_/  \/                 
                | | === | |          |\ /|                    
                |_|  0  |_|          \_ _/                    
                 ||  0  ||           | | |                    
                 ||__*__||           | | |                    
                |* \___/ *|          []|[]                    
                /=\ /=\ /=\          | | |                    
________________[_]_[_]_[_]_________/_]_[_\_______________________________
                                                              
                                                              
============================================================================ */
/* --- Final do Programa --- */

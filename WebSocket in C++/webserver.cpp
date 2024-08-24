/* ============================================================================

    Esse projeto se trata de um Servidor WebSocket. Se você chegou até aqui é 
    porque você precisa urgente arrumar alguma coisa neste código BOA SORTE, 
    pois quando ele foi feito apenas duas pessoas sabiam como ele funcionava 
    (Deus e Eu), agora somente ele sabe.
    
    Autor: Lukas Lujan Moreira
    Data: 22/08/2024

============================================================================ */

/* --- Cabeçalhos importados --- */
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>


/* ========================================================================= */
/* --- Função Principal --- */

int main() {
    WSADATA wsaData;
    SOCKET sock = INVALID_SOCKET;

    // Inicializa o Winsock
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    // Cria um socket
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    std::cout << "Socket criado com sucesso!" << std::endl;

    // Fecha o socket
    closesocket(sock);
    WSACleanup();
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

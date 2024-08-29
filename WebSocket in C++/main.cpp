/* ============================================================================
    Esse projeto se trata de um Servidor WebSocket. Se você chegou até aqui é 
    porque você precisa urgente arrumar alguma coisa neste código BOA SORTE, 
    pois quando ele foi feito apenas duas pessoas sabiam como ele funcionava 
    (Deus e Eu), agora somente ele sabe.
    
    Autor: Lukas Lujan Moreira
    Data: 22/08/2024
============================================================================ */

/* --- Cabeçalhos importados --- */

#include "webserver.cpp"

/* ========================================================================= */
/* --- Função Principal --- */

#ifdef _WIN32
SocketWin socketwin;
WSADATA wsaData;
SOCKET server_sock = INVALID_SOCKET, client_sock = INVALID_SOCKET;

#elif defined(__linux__)
int server_sock;
SocketUbu socketubu;

#endif

int main() {
    #ifdef _WIN32 // Código específico para Windows

    socketwin.InitSocket(wsaData);
    socketwin.CreateSocket(server_sock);

    #elif defined(__linux__) // Código específico para Linux

    socketubu.CreateSocket(server_sock);

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

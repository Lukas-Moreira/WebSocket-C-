/* --- Cabeçalhos importados --- */

#ifdef _WIN32 // Verifica se está em um sistema Windows
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <winerror.h> 
#include <iphlpapi.h> 
#elif defined(__linux__) // Verifica se está em um sistema Linux
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cerrno>
#include <ifaddrs.h>
#include <netdb.h>
#endif

#include <iostream>

/* --- Classes e suas definições --- */

#define PORT 3001

#ifdef _WIN32
class SocketWin
{
    private:
        struct sockaddr_in server_addr, client_addr;
        int client_addr_size = sizeof(client_addr);

    public:
        void InitSocket (WSADATA wsaData);

        void CreateSocket (SOCKET server_sock);

        void getIPAddress(std::string& ipAddress);

        void BindSocket (SOCKET socket);

        void GetSocket (SOCKET socket);

        void ListenSocket (SOCKET socket);

        void AcceptDevices (SOCKET socket);

        void CloseSocket (SOCKET socket);
};

#elif defined(__linux__) 

class SocketUbu {
    private:
        struct sockaddr_in server_addr, client_addr;
        socklen_t client_addr_size = sizeof(client_addr);

    public:
        void CreateSocket (int socket_server);

        void getIPAddress(std::string& ipAddress);

        void BindSocket (int socket_server);

        void GetSocket (int socket_server);

        void ListenSocket (int socket_server);

        void AcceptSocket (int socket_server);

        void CloseSocket (int socket_server);
};


#endif
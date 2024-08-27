/* --- Cabeçalhos importados --- */

#ifdef _WIN32 // Verifica se está em um sistema Windows
#include <winsock2.h>
#include <ws2tcpip.h>
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
        void InitSocket (WSADATA wsaData){
            int result = WSAStartup(MAKEWORD(2,2), &wsaData);
            if (result !=0 ){
                std::cerr << "Falha na Inicialização do Winsock: " << result << std::endl;
            }
        };

        void CreateSocket (SOCKET server_sock){
            server_sock = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
            if (server_sock == INVALID_SOCKET){
                std::cerr << "Erro ao criar o socket: " << WSAGetLastError() << std::endl;
                WSACleanup();
            }
            else {
                std::cout << "\n==========================================" << std::endl;
                std::cout << "Socket criado com sucesso" << std::endl;

                std::string ipAddress;
                getIPAddress(ipAddress);  // Obtém o IP do dispositivo

                server_addr.sin_family = AF_INET;
                server_addr.sin_addr.s_addr = inet_addr(ipAddress.c_str());
                server_addr.sin_port = htons(PORT);
                BindSocket(server_sock);
                GetSocket(server_sock);
                ListenSocket(server_sock);
                AcceptDevices(server_sock);
                std::cout << "\nAguardando conexoes no Windows na porta " << PORT << "...\n" << std::endl;
            };
        }

        void getIPAddress(std::string& ipAddress) {
            PIP_ADAPTER_INFO pAdapterInfo;
            PIP_ADAPTER_INFO pAdapter = NULL;
            DWORD dwRetVal = 0;

            ULONG ulOutBufLen = sizeof(IP_ADAPTER_INFO);
            pAdapterInfo = (IP_ADAPTER_INFO *) malloc(sizeof(IP_ADAPTER_INFO));
            if (pAdapterInfo == NULL) {
                std::cerr << "Erro ao alocar memória para adapter info" << std::endl;
                return;
            }

            if (GetAdaptersInfo(pAdapterInfo, &ulOutBufLen) == ERROR_BUFFER_OVERFLOW) {
                free(pAdapterInfo);
                pAdapterInfo = (IP_ADAPTER_INFO *) malloc(ulOutBufLen);
                if (pAdapterInfo == NULL) {
                    std::cerr << "Erro ao alocar memória para adapter info" << std::endl;
                    return;
                }
            }

            if ((dwRetVal = GetAdaptersInfo(pAdapterInfo, &ulOutBufLen)) == NO_ERROR) {
                pAdapter = pAdapterInfo;
                while (pAdapter) {
                    ipAddress = pAdapter->IpAddressList.IpAddress.String;
                    pAdapter = pAdapter->Next;
                }
            } else {
                std::cerr << "GetAdaptersInfo falhou com erro: " << dwRetVal << std::endl;
            }

            if (pAdapterInfo)
                free(pAdapterInfo);
        }

        void BindSocket (SOCKET socket){
            int result = bind(socket, (struct sockaddr*)&server_addr,sizeof(server_addr));
            if (result == SOCKET_ERROR){
                std::cerr << "Falha na vinculacao: " << WSAGetLastError() << std::endl;
            }
        }

        void GetSocket (SOCKET socket){
            struct sockaddr_in local_addr;
            int local_addr_size = sizeof(local_addr);
            int result = getsockname(socket, (struct sockaddr*)&local_addr,&local_addr_size);

            if (result == 0) {
                char* local_ip = inet_ntoa(local_addr.sin_addr);
                std::cout << "\nEndereco do servidor: " << local_ip << ":" << ntohs(local_addr.sin_port) << "\n" << std::endl;
            } else {
                std::cerr << "Erro ao obter o endereco do socket: " << WSAGetLastError() << std::endl;
            }
        }

        void ListenSocket (SOCKET socket){
            if(listen(socket,3) == SOCKET_ERROR){
                std::cerr << "\nFalha na escuta do socket: " << WSAGetLastError() << std::endl;
                closesocket(socket);
                WSACleanup();
            }
        }

        void AcceptDevices (SOCKET socket){
            SOCKET client_sock = accept(socket, (struct sockaddr*)&client_addr, &client_addr_size);
            if (client_sock == INVALID_SOCKET){
                std::cerr << "\nNao foi possivel aceitar dispositivos: " << GetLastError() << std::endl;
                closesocket(socket);
                WSACleanup();
            } else{
                char* client_ip = inet_ntoa(client_addr.sin_addr);
                std:: cout << "\nConexão estabelecida com o dispositivo: " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;
            }

        }

        void CloseSocket (SOCKET socket){
            std::cout << "Fechando servidor" << std::endl;
            closesocket(socket);
            WSACleanup();
        }
};

#elif defined(__linux__) 

class SocketUbu {
    private:
        struct sockaddr_in server_addr, client_addr;
        socklen_t client_addr_size = sizeof(client_addr);

    public:
        void CreateSocket (int socket_server){
            socket_server = socket(AF_INET,SOCK_STREAM,0);
            if (socket_server < 0) {
                std::cerr << "Erro ao criar o socket: " << strerror(errno) << std::endl;
            } else {
                std::cout << "\n=============================================" << std::endl;
                std::cout << "Socket criado com sucesso" << std::endl;

                std::string ipAddress;
                getIPAddress(ipAddress);

                server_addr.sin_family = AF_INET;
                inet_pton(AF_INET, ipAddress.c_str(), &server_addr.sin_addr);
                server_addr.sin_port = htons(PORT);
                
                BindSocket(socket_server);
                GetSocket(socket_server);
                ListenSocket(socket_server);
                AcceptSocket(socket_server);

            }
        }

        void getIPAddress(std::string& ipAddress) {
            struct ifaddrs *ifaddr, *ifa;
            int family, s;
            char host[NI_MAXHOST];

            if (getifaddrs(&ifaddr) == -1) {
                perror("getifaddrs");
                return;
            }

            for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
                if (ifa->ifa_addr == NULL) continue;

                family = ifa->ifa_addr->sa_family;
                if (family == AF_INET) {
                    s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in), host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
                    if (s != 0) {
                        std::cerr << "getnameinfo() failed: " << gai_strerror(s) << std::endl;
                        continue;
                    }

                    if (std::string(host) != "127.0.0.1") { // Ignorar endereço localhost
                        ipAddress = host;
                        break;
                    }
                }
            }

            freeifaddrs(ifaddr);
        }

        void BindSocket (int socket_server){
            int result  = bind(socket_server, (struct sockaddr*)&server_addr, sizeof(server_addr));
            if (result < 0){
                std::cerr << "\nFalha ao vincular o socket: " << strerror(errno) << std::endl;
                CloseSocket(socket_server);
            } else {
                std::cout << "\nAguardando conexões no Linux na porta " << PORT << "..." << std::endl;
            }
        }

        void GetSocket (int socket_server){
            struct sockaddr_in local_addr;
            socklen_t local_addr_size = sizeof(local_addr);
            int result = getsockname(socket_server, (struct sockaddr*)&local_addr, &local_addr_size);
            if (result == 0){
                char local_ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &local_addr.sin_addr, local_ip, INET_ADDRSTRLEN);
                std::cout << "\nEndereço do servidor: " << local_ip << ":" << ntohs(local_addr.sin_port) << "\n" << std::endl; 
            } else {
                std::cerr << "\nErro ao obter o endereço do socket: " << strerror(errno) << std::endl;
            }
        }

        void ListenSocket (int socket_server){
            int result = listen(socket_server,3);
            if (result < 0){
                std::cerr << "\nFalha ao escutar os dispositivos: " << strerror(errno) << std::endl;
                CloseSocket(socket_server);
            }
        }

        void AcceptSocket (int socket_server){
            int client_sock = accept(socket_server, (struct sockaddr*)&client_addr, &client_addr_size);
            if (client_sock < 0) {
                std::cerr << "\nNao foi possivel aceitar os dispositivos: " << strerror(errno) << std::endl;
                CloseSocket(socket_server);
            } else {
                char client_ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
                std::cout << "\nConexão recebida de: " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;
            }
        }

        void CloseSocket (int socket_server){
            close(socket_server);
        }
};


#endif
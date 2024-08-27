/* --- Cabeçalhos importados --- */

#ifdef _WIN32 // Verifica se está em um sistema Windows
#include <winsock2.h>
#include <ws2tcpip.h>
#elif defined(__linux__) // Verifica se está em um sistema Linux
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <cerrno>
#endif

#include <iostream>

/* --- Classes e suas definições --- */

#define PORT 3001

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
                server_addr.sin_family = AF_INET;
                server_addr.sin_addr.s_addr = INADDR_ANY;
                server_addr.sin_port = htons(PORT);
                BindSocket(server_sock);
                GetSocket(server_sock);
                AcceptDevices(server_sock);
                ListenSocket(server_sock);
                std::cout << "\nAguardando conexoes no Windows na porta " << PORT << "...\n" << std::endl;
            };
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
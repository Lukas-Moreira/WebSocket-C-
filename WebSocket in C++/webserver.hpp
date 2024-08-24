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
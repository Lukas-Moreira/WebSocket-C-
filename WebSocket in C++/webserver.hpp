/* ============================================================================

    Esse projeto se trata de um Servidor WebSocket feito para ARTHI. Se você che
    gou até aqui é porque você precisa urgente arrumar alguma coisa neste código
    BOA SORTE, pois quando ele foi feito apenas duas pessoas sabiam como ele fun-
    cionava (Deus e Eu), agora somente ele sabe.
    
    Autor: Lukas Lujan Moreira
    Data: 22/08/2024

============================================================================ */

/* --- Bibliotecas --- */
#ifndef WebServer_ARTHI
#define WebServer_ARTHI

#include <stdio.h>

#define __WINx64__

/* Verifica se o sistema é compatível com Windows ou Linux (Coletor) */
#ifdef __WINx64__
#include <winsock.h>
#else 
#include <sys/socket.h>
#endif 
/* Final da verificação */

/* ========================================================================= */
/* --- Funções e Suas definições --- */

namespace WS {
    class ARTHI_Server_Socket {
        private:
            int connection;
        public:
            ARTHI_Server_Socket(int domain, int services, int protocol);
        };
}



#endif /* WebServer_ARTHI */
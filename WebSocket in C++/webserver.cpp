/* ============================================================================

    Esse projeto se trata de um Servidor WebSocket feito para ARTHI. Se você che
    gou até aqui é porque você precisa urgente arrumar alguma coisa neste código
    BOA SORTE, pois quando ele foi feito apenas duas pessoas sabiam como ele fun-
    cionava (Deus e Eu), agora somente ele sabe.
    
    Autor: Lukas Lujan Moreira
    Data: 22/08/2024

============================================================================ */

/* --- Cabeçalhos importados --- */
#include "webserver.hpp"


/* ========================================================================= */
/* --- Função Principal --- */

WS::ARTHI_Server_Socket::ARTHI_Server_Socket(int domain,int service,int protocol){
  int connection = socket(domain,service,protocol);
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

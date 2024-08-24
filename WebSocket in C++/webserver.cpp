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

void do_session(tcp::socket socket)
{
    try
    {
        // Este buffer é usado para ler e escrever mensagens.
        beast::flat_buffer buffer;

        // Cria o stream WebSocket que 'tomará' conta da conexão.
        websocket::stream<tcp::socket> ws{std::move(socket)};

        // Faz o handshake do WebSocket (aceita a conexão).
        ws.accept();

        for(;;)
        {
            // Lê uma mensagem
            ws.read(buffer);

            // Ecoa de volta a mensagem recebida.
            ws.text(ws.got_text());
            ws.write(buffer.data());

            // Limpa o buffer para a próxima mensagem
            buffer.consume(buffer.size());
        }
    }
    catch(beast::system_error const& se)
    {
        // Handle close or any other error
        if(se.code() != websocket::error::closed)
            std::cerr << "Error: " << se.code().message() << "\n";
    }
}

int main()
{
    try
    {
        // Criando o contexto IO.
        net::io_context ioc;

        // Objeto aceitando conexões.
        tcp::acceptor acceptor{ioc, tcp::endpoint{tcp::v4(), 8080}};

        for(;;)
        {
            // Aceita uma nova conexão.
            tcp::socket socket{ioc};
            acceptor.accept(socket);

            // Inicia uma nova sessão para cada cliente conectado.
            std::thread{std::bind(&do_session, std::move(socket))}.detach();
        }
    }
    catch(std::exception const& e)
    {
        std::cerr << "Error: " << e.what() << "\n";
        return EXIT_FAILURE;
    }
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

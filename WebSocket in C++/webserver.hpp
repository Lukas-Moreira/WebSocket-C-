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

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/version.hpp>
#include <iostream>
#include <memory>
#include <string>

/* Final da verificação */

/* ========================================================================= */
/* --- Funções e Suas definições --- */

namespace beast = boost::beast;     // from <boost/beast.hpp>
namespace http = beast::http;       // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;        // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;   // from <boost/asio/ip/tcp.hpp>

#endif /* WebServer_ARTHI */
/*
 * Copyright (C) 2013-2016, The OpenFlint Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS-IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <boost/asio/io_service.hpp>
#include <boost/log/trivial.hpp>
#include <ws/WsServer.h>

#include "http/HttpServer.h"

void onHttpRequest(flint::HttpSession *httpSession);

void onWebsocketConnect(flint::WsSession *wsSession);

int main(void) {
    BOOST_LOG_TRIVIAL(debug) << "Hello, WebSocket Message Exchanger!\n";

    // test http server
//    boost::asio::io_service *ioService = new boost::asio::io_service();
//    flint::HttpServer *server = new flint::HttpServer(ioService, 9527);
//    flint::HttpServer *server = new flint::HttpServer(9527);
//    server->HttpRequest.connect(boost::bind(&onHttpRequest, ::_1));
//    server->start();
//    ioService->run();

    // test ws server
    flint::WsServer *server = new flint::WsServer(9527);
    server->WebsocketConnect.connect(boost::bind(&onWebsocketConnect, ::_1));
    server->start();
    return 0;
}

void onHttpRequest(flint::HttpSession *httpSession) {
    std::string path = httpSession->getResource();
    BOOST_LOG_TRIVIAL(debug) << "received HTTP request [" << path << "]";
    httpSession->response(websocketpp::http::status_code::ok, "hello, manson!");
}

void onWebsocketConnect(flint::WsSession *wsSession) {
    std::string path = wsSession->getResource();
    BOOST_LOG_TRIVIAL(debug) << "received WS connect [" << path << "]";
    wsSession->sendText("Hello, manson!");
    wsSession->close();
}

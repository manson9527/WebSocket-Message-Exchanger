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

#ifndef WEBSOCKET_MESSAGE_EXCHANGER_HTTPSERVER_H
#define WEBSOCKET_MESSAGE_EXCHANGER_HTTPSERVER_H

#include <boost/signals2.hpp>
#include <boost/asio.hpp>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

#include "base/IServer.h"
#include "http/HttpSession.h"
#include "http/HttpServer.h"

namespace flint {

    typedef websocketpp::server<websocketpp::config::asio> http_server;

    class HttpServer : public IServer {
    public:
        HttpServer(int port);

        HttpServer(boost::asio::io_service *ioService, int port);

        virtual ~HttpServer();

    public:
        boost::signals2::signal<void(HttpSession *)> HttpRequest;

    protected:
        virtual void onStart();

        virtual void onStop();

        // return true means that this session has been processed and it wouldn't be transfer to another component
        virtual bool onHttpRequest(HttpSession *session);

    private:
        void internalHttpHandler(websocketpp::connection_hdl hdl);

    protected:
        boost::asio::io_service *ioService_;
        http_server server_;
        int port_;

    private:
        bool standalone_;
    };

}
#endif //WEBSOCKET_MESSAGE_EXCHANGER_HTTPSERVER_H

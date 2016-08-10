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

#include <boost/algorithm/string.hpp>
#include <boost/xpressive/xpressive_dynamic.hpp>

#include "WsServer.h"

namespace flint {

    WsServer::WsServer(boost::asio::io_service *ioService, int port, bool enableHttp) :
            HttpServer(ioService, port), enableHttp_(enableHttp) {
        // TODO Auto-generated constructor stub
    }

    WsServer::WsServer(int port, bool enableHttp) :
            HttpServer(port), enableHttp_(enableHttp) {
        // TODO Auto-generated constructor stub
    }

    WsServer::~WsServer() {
        // TODO Auto-generated destructor stub
    }

    void WsServer::onStart() {
        BOOST_LOG_TRIVIAL(debug) << "WsServer start! " << port_;
        server_.init_asio(ioService_);
        server_.set_reuse_addr(true);

        server_.set_open_handler(
                boost::bind(&WsServer::internalWsHandler, this, ::_1));

        server_.listen(boost::asio::ip::tcp::v4(), port_);
        server_.start_accept();
        if (standalone_) {
            ioService_->run();
        }
    }

    void WsServer::internalWsHandler(websocketpp::connection_hdl hdl) {
        WsSession *session = new WsSession(&server_, hdl);
        WebsocketConnect(session);
    }

} /* namespace flint */

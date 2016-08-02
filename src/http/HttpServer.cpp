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

#include <boost/log/trivial.hpp>
#include <boost/bind.hpp>

#include "HttpServer.h"

namespace flint {

    HttpServer::HttpServer(boost::asio::io_service &ioService, int port) :
            IServer(), ioService_(ioService), port_(port) {
    }

    HttpServer::~HttpServer() {
    }

    void HttpServer::onStart() {
        BOOST_LOG_TRIVIAL(debug) << "HttpServer start! " << port_;
        server_.init_asio(&ioService_);
        server_.set_reuse_addr(true);

        // handle HTTP request
        server_.set_http_handler(
                boost::bind(&HttpServer::internalHttpHandler, this, ::_1));

        server_.listen(boost::asio::ip::tcp::v4(), port_);
        server_.start_accept();
    }

    void HttpServer::onStop() {
        BOOST_LOG_TRIVIAL(debug) << "HttpServer stop! " << port_;
        server_.stop();
    }

    bool HttpServer::onHttpRequest(HttpSession *session) {
        session->response(websocketpp::http::status_code::ok);
        return false;
    }

    void HttpServer::internalHttpHandler(websocketpp::connection_hdl hdl) {
        HttpSession *session = new HttpSession(&server_, hdl);
        if (!onHttpRequest(session)) {
            HttpRequest(session);
        }
        delete session;
    }

}

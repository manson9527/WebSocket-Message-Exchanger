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

#ifndef WEBSOCKET_MESSAGE_EXCHANGER_HTTPSESSION_H
#define WEBSOCKET_MESSAGE_EXCHANGER_HTTPSESSION_H

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

namespace flint {

    typedef websocketpp::server<websocketpp::config::asio> http_server;

    class HttpSession {
    public:
        HttpSession(http_server *server, websocketpp::connection_hdl hdl);

        virtual ~HttpSession();

        std::string const &getSrcAddr();

        std::string const &getUrl();

        std::string const &getResource();

        std::string const &getMethod();

        std::string const &getBody();

        std::string const &getHost();

        std::string const &getQuery();

        std::string const &getHeader(const std::string &key);

        void setHeader(const std::string &headerKey,
                       const std::string &headerValue);

        void setStatus(websocketpp::http::status_code::value code,
                       const std::string &msg = "");

        void setBody(const std::string &body);

    protected:
        http_server *httpServer_;
        http_server::connection_ptr conn_;
    };

}

#endif //WEBSOCKET_MESSAGE_EXCHANGER_HTTPSESSION_H

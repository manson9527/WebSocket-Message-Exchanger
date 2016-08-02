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

#include "HttpSession.h"

namespace flint {

    HttpSession::HttpSession(http_server *server,
                             websocketpp::connection_hdl hdl) :
            httpServer_(server) {
        conn_ = httpServer_->get_con_from_hdl(hdl);
    }

    HttpSession::~HttpSession() {
        BOOST_LOG_TRIVIAL(debug) << "~HttpSession\n";
    }

    std::string const &HttpSession::getSrcAddr() {
        return conn_->get_remote_endpoint();
    }

    std::string const &HttpSession::getUrl() {
        return conn_->get_uri()->str();
    }

    std::string const &HttpSession::getResource() {
        return conn_->get_uri()->get_resource();
    }

    std::string const &HttpSession::getMethod() {
        return conn_->get_request().get_method();
    }

    std::string const &HttpSession::getBody() {
        return conn_->get_request().get_body();
    }

    std::string const &HttpSession::getHost() {
        return conn_->get_host();
    }

    std::string const &HttpSession::getQuery() {
        return conn_->get_uri()->get_query();
    }

    std::string const &HttpSession::getHeader(const std::string &key) {
        return conn_->get_request_header(key);
    }

    void HttpSession::setHeader(const std::string &headerKey,
                                const std::string &headerValue) {
        conn_->replace_header(headerKey, headerValue);
    }

    void HttpSession::setStatus(websocketpp::http::status_code::value code,
                                const std::string &msg) {
        conn_->set_status(code, msg);
    }

    void HttpSession::setBody(const std::string &body) {
        conn_->set_body(body);
    }

    void HttpSession::response(websocketpp::http::status_code::value statusCode,
                               const std::string &body) {
        setStatus(statusCode);
        setBody(body);
    }

    void HttpSession::response(websocketpp::http::status_code::value statusCode,
                               std::map<std::string, std::string> &headers,
                               const std::string &body) {
        setStatus(statusCode);
        std::map<std::string, std::string>::iterator it;
        for (it = headers.begin(); it != headers.end(); ++it) {
            setHeader(it->first, it->second);
        }
        setBody(body);
    }
}

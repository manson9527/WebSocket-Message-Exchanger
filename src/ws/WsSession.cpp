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


#include "base/base.h"
#include "WsSession.h"

namespace flint {
    WsSession::WsSession(http_server *server,
                         websocketpp::connection_hdl hdl) :
            HttpSession(server, hdl) {
        // set close hander
        conn_->set_close_handler(
                boost::bind(&WsSession::onClose, this, ::_1));
        // set fail hander
        conn_->set_fail_handler(boost::bind(&WsSession::onFail, this, ::_1));
        // set interrupt hander
        conn_->set_interrupt_handler(
                boost::bind(&WsSession::onInterrupt, this, ::_1));
        // set message hander
        conn_->set_message_handler(
                boost::bind(&WsSession::onMessage, this, ::_1, ::_2));
    }

    WsSession::~WsSession() {
        BOOST_LOG_TRIVIAL(debug) << "~WsSession\n";
    }

    void WsSession::sendText(const std::string &message) {
        try {
            BOOST_LOG_TRIVIAL(debug) << "WsSession::send:" << message;
            conn_->send(message.data(), message.size(),
                        websocketpp::frame::opcode::TEXT);
        } catch (std::exception &e) {
            BOOST_LOG_TRIVIAL(error) << "WsSession::send exception:" << e.what();
        }
    }

    void WsSession::close() {
        closeInternal();
    }

    void WsSession::closeInternal() {
        BOOST_LOG_TRIVIAL(debug) << "WsSession closeInternal: " << getResource();
        conn_->close(websocketpp::close::status::normal, "");
    }

    void WsSession::onMessage(websocketpp::connection_hdl hdl,
                              websocketpp::server<websocketpp::config::asio>::message_ptr msg) {
        const std::string &message = msg->get_payload();
        Message(message);
        BOOST_LOG_TRIVIAL(debug) << "WsSession onMessage: " << message;
    }

    void WsSession::onClose(websocketpp::connection_hdl hdl) {
        BOOST_LOG_TRIVIAL(debug) << "WsSession onClose: " << getResource();
        clear();
    }

    void WsSession::onFail(websocketpp::connection_hdl hdl) {
        BOOST_LOG_TRIVIAL(debug) << "WsSession onFail: " << getResource();
        clear();
    }

    void WsSession::onInterrupt(websocketpp::connection_hdl hdl) {
        BOOST_LOG_TRIVIAL(debug) << "WsSession onInterrupt: " << getResource();
        clear();
    }

    void WsSession::clear() {
        Close();
        BOOST_LOG_TRIVIAL(debug) << "WsSession clear: " << getResource();
        delete this;
    }

}

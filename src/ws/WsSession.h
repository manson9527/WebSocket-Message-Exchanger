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


#ifndef WEBSOCKET_MESSAGE_EXCHANGER_WSSESSION_H
#define WEBSOCKET_MESSAGE_EXCHANGER_WSSESSION_H

#include "http/HttpSession.h"

namespace flint {

    class WsSession : public HttpSession {
    public:
        WsSession(http_server *server, websocketpp::connection_hdl hdl);

        virtual ~WsSession();
    };
}

#endif //WEBSOCKET_MESSAGE_EXCHANGER_WSSESSION_H

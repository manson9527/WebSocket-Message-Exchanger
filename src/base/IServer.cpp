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

#include <boost/thread/mutex.hpp>
#include <boost/log/trivial.hpp>

#include "IServer.h"

namespace flint {

    IServer::IServer() :
            isRunning_(false) {
        // TODO Auto-generated constructor stub

    }

    IServer::~IServer() {
        // TODO Auto-generated destructor stub
    }

    void IServer::start() {
        boost::mutex lock_;
        lock_.lock();
        if (isRunning_) {
            BOOST_LOG_TRIVIAL(warning) << "Server is already running!!!\n";
            return;
        } else {
            isRunning_ = true;
            onStart();
        }
        lock_.unlock();
    }

    void IServer::stop() {
        boost::mutex lock_;
        lock_.lock();
        if (!isRunning_) {
            BOOST_LOG_TRIVIAL(warning) << "Server not running skip stop!!!\n";
            return;
        } else {
            isRunning_ = false;
            onStop();
        }
        lock_.unlock();
    }

    bool IServer::isRunning() {
        return isRunning_;
    }

} /* namespace flint */

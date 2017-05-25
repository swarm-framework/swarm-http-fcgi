/*
 * Copyright 2017 Dami <contact@damiengiron.me>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef SWARM_HTTP_FCGI_FCGISESSION_HXX
#define SWARM_HTTP_FCGI_FCGISESSION_HXX

#include <swarm/http/server/HTTPSession.hxx>

namespace swarm {
    namespace http {
        namespace fastcgi {
            
            /// \brief Class FCGISession
            class FCGISession : public HTTPSession {

              private:
                /// \brief Swarm http request
                std::shared_ptr<HTTPRequest> httpRequest_;

            public:
                
                /// \brief Constructor with fast CGI and swarm request
                /// \param httpRequest HTTP request
                FCGISession(std::shared_ptr<HTTPRequest> httpRequest);
                
                // Destructor
                ~FCGISession();
                
              public:
                /// \return Retrieve session request
                virtual HTTPRequest & request() override {
                    return * httpRequest_;
                }
            };
        }
    }
}

#endif // SWARM_HTTP_FCGI_FCGISESSION_HXX

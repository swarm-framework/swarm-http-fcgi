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

#ifndef SWARM_HTTP_FASTCGI_FASTCGISERVERDELEGATE_HXX
#define SWARM_HTTP_FASTCGI_FASTCGISERVERDELEGATE_HXX

#include <swarm/http/server/HTTPServerDelegate.hxx>
#include <swarm/http/message/request/HTTPRequest.hxx>
#include <cxx-log/Logger.hxx>
#include <fcgiapp.h>

namespace swarm {
    namespace http {
        namespace fastcgi {
            
            class FCGIRequest {
                
            private:
                // Create fast cgi request
                FCGX_Request fcgxRequest;
                
            public:
                FCGIRequest() {
                    
                }
                
                void init(int sock) {
                    FCGX_InitRequest(&fcgxRequest, sock, 0);
                }
                
                void accept() {
                    FCGX_Accept_r(&fcgxRequest);
                }
                
                FCGX_Request* request() {
                    return &fcgxRequest;
                }
                
                FCGX_Stream * out() {
                    return fcgxRequest.out;
                }
                
                /// \brief Decode FCGI request to swarm request
                std::shared_ptr<HTTPRequest> decode();
            };
            
            /// \brief Class FastCGIServerDelegate
            class FastCGIServerDelegate : public HTTPServerDelegate {

            private:
                
                /// \brief Define delegate logger
                static const cxxlog::Logger LOGGER_;
                
                /// \brief FCGI request wrapper
                FCGIRequest request_;
                
                /// \brief FCGI socket
                int sock;
                
              public:
                /// \brief Constructor
                FastCGIServerDelegate();

                /// \brief Init and start the HTTP server
                /// \param server Server containing informations
                virtual void init(HTTPServer &server) override;

                /// \brief Stop the server
                /// \param server HTTP server
                virtual void stop(HTTPServer &server) override;

                /// \brief Listen a connection
                /// \param server Server object
                virtual std::shared_ptr<HTTPSession> listening(HTTPServer &server) override;

                /// \brief Send response
                /// \param server Server object
                /// \param session Session previously accepted
                /// \param response Response to send
                virtual void send(HTTPServer &server, std::shared_ptr<HTTPSession> session,
                                  HTTPResponse &response) override;
            };
        }
    }
}

#endif // SWARM_HTTP_FASTCGI_FASTCGISERVERDELEGATE_HXX

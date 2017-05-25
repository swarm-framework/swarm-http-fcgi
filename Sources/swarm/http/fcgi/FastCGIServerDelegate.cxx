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

#include "FastCGIServerDelegate.hxx"

#include "FastCGISession.hxx"
#include "FastCGIRequestDecoder.hxx"
#include <fcgio.h>
#include <swarm/http/server/HTTPServer.hxx>
#include <swarm/http/message/request/HTTPRequest.hxx>
#include <swarm/http/message/response/HTTPResponse.hxx>
#include <swarm/http/message/body/HTTPBody.hxx>
#include <swarm/http/stream/HTTPStream.hxx>

namespace swarm {
    namespace http {
        namespace fastcgi {
            
            // Init loger
            const cxxlog::Logger FastCGIServerDelegate::LOGGER_ = LOGGER(FastCGIServerDelegate);
            
            // Deocde fcgi request
            std::shared_ptr<HTTPRequest> FCGIRequest::decode() {
                
                HTTPRequestBuilder builder{};
                
                // Read request
                FastCGIRequestDecoder::updateBuilder(builder, fcgxRequest);
                
                return builder.build();
            }
            
            // Constructor
            FastCGIServerDelegate::FastCGIServerDelegate() {
                
                // Init loger
                LOGGER_.log(cxxlog::Level::INFO, "Init Fast CGI sub-system");
                FCGX_Init();
            }
            
            // Init and start the HTTP server
            void FastCGIServerDelegate::init(HTTPServer &server) {
                
                // Create stream request
                std::stringstream ss;
                
                // Create sokect request
                ss << ':' << server.port();
                
                LOGGER_.log(cxxlog::Level::INFO, "Init Fast CGI delegate at '%1%'", ss.str());
                
                // Open socket
                sock = FCGX_OpenSocket(ss.str().c_str(), 50);
                if (sock < 0) {
                    throw SwarmException{"Unable to start HTTP server (FastCGI) on port %1%", server.port()};
                }
                
                // Init request
                request_.init(sock);
            }

            // Stop the server
            void FastCGIServerDelegate::stop(HTTPServer &server) {
                
            }

            // Listen a connection
            std::shared_ptr<HTTPSession> FastCGIServerDelegate::listening(HTTPServer &server) {
                
                LOGGER_.log(cxxlog::Level::INFO, "Listening requests");
                
                
                // Waiting connection
                request_.accept();
                
                LOGGER_.log(cxxlog::Level::INFO, "Request accepted");
                
                return std::shared_ptr<HTTPSession>{
                    new FCGISession{request_.decode()}
                };
            }

            // Send response
            void FastCGIServerDelegate::send(HTTPServer &server, std::shared_ptr<HTTPSession> session, HTTPResponse &httpResponse) {
                
                LOGGER_.log(cxxlog::Level::INFO, "Send response");
                
                // Create fast cgi stream buf
                fcgi_streambuf cout_fcgi_streambuf(request_.out());
                
                // Create fcgi stream
                std::ostream fout(&cout_fcgi_streambuf);
                
                // Retrieve status
                const HTTPResponseStatus & status = httpResponse.status();
                
                // Write HTTP status line
                fout << "Status: " << status.code() << " " << status.reason() << "\r\n";
                
                // Add all headers
                for (auto header : httpResponse.headers()) {
                    fout << header.first.key() << ": " << header.second << "\r\n";
                }
                
                // Find body
                auto body = httpResponse.body();
                
                if (body) {
                    // FXIME Vérifier que le content-type n'est pas déjà envoyé
                    fout << "Content-type: " << body->mediaType().str() << "\r\n";
                }
                
                fout << "\r\n";
                if (body) {
                    static const int LENGTH = 1024;
                    char buffer[LENGTH] {};
                    int size = 0;
                    
                    while ((size = body->stream().read(buffer, LENGTH)) > 0) {
                        fout.write(buffer, size);
                    }
                }
            }
        }
    }
}

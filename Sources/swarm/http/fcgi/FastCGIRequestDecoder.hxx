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

#ifndef SWARM_HTTP_FASTCGIREQUESTDECODER_HXX
#define SWARM_HTTP_FASTCGIREQUESTDECODER_HXX

#include <swarm/http/message/request/HTTPRequestBuilder.hxx>
#include <fcgiapp.h>

namespace swarm {
    namespace http {
        namespace fastcgi {

            
            /// \brief Class FastCGIRequestDecoder
            struct FastCGIRequestDecoder {
                
                /// \brief Update builder form FastCGI data
                /// \param builder Request builder
                /// \param fcgxRequest FastCGI request
                static void updateBuilder(HTTPRequestBuilder &builder, FCGX_Request& fcgxRequest);
                
            private:
                
                /// \brief Read query parameters
                /// \param builder HTTP request builder
                /// \param query HTTP query
                static void updateQueryParameters(HTTPRequestBuilder &builder, const std::string & query);
            };
        }
    }
}

#endif // SWARM_HTTP_FASTCGIREQUESTDECODER_HXX

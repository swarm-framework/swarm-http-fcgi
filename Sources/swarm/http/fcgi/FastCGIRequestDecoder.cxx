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

#include "FastCGIRequestDecoder.hxx"

#include <cxxlog/Logger.hxx>
#include <map>
#include <memory>
#include <sstream>
#include <swarm/http/message/commons/HTTPVersion.hxx>
#include <swarm/http/message/header/HTTPHeader.hxx>
#include <swarm/http/message/header/HTTPHeaders.hxx>
#include <swarm/http/message/header/HTTPHeaders.hxx>
#include <swarm/http/message/commons/HTTPParam.hxx>

#define DEBUG 1

namespace swarm {
    namespace http {
        namespace fastcgi {
            // Update builder form FastCGI data
            void FastCGIRequestDecoder::updateBuilder(HTTPRequestBuilder &builder, FCGX_Request &fcgxRequest) {

                static auto logger = LOGGER(FastCGIRequestDecoder);

                // Options
                std::map<std::string, std::string> options_;

                // Header profix
                static char HEADER_PREFIX[] = "HTTP_";

                // Browse all FastCGI parameters
                char **envp = fcgxRequest.envp;
                for (; *envp; ++envp) {

                    // is an HTTP header
                    bool header = true;

                    std::stringstream ssKey{};
                    char *c = *envp;

                    // Read key (and detect HTTP header)
                    for (int i = 0; *c != '\0'; ++c, ++i) {

                        if (i < 5) {
                            header = header && *c == HEADER_PREFIX[i];
                        } else if (i == 5 && header) {
                            ssKey = std::stringstream{};
                        }

                        if (*c == '=') {
                            ++c;
                            break;
                        }
                        ssKey << *c;
                    }

                    // Read value
                    std::stringstream ssValue{};
                    for (; *c != '\0'; ++c) {
                        ssValue << *c;
                    }

                    // logger.log(cxxlog::Level::INFO, [&](std::ostream & os) { os << "arg: " << ssKey.str() << ":" <<
                    // ssValue.str(); });

                    if (header) {

                        // Find header
                        auto header = HTTPHeaders::get(ssKey.str());

                        // Add header to builder
                        builder.addHeaderParam(*header, ssValue.str());

                    } else {
                        // Add to options_
                        options_[ssKey.str()] = ssValue.str();
                    }
                }

                try {
                    // Read version
                    builder.version(HTTPVersions::get(options_.at("SERVER_PROTOCOL")));
                } catch (...) {
                    logger.log(cxxlog::Level::SEVERE, "Unable to decode HTTP version");
                }

                try {
                    // Read path
                    builder.path(options_.at("PATH_INFO"));
                } catch (...) {
                    logger.log(cxxlog::Level::SEVERE, "Unable to get HTTP path");
                }

                try {
                    // Read uri
                    builder.uri(options_.at("REQUEST_URI"));
                } catch (...) {
                    logger.log(cxxlog::Level::SEVERE, "Unable to get HTTP uri");
                }
                
                try {
                    // Read method
                    builder.method(HTTPMethod::get(options_.at("REQUEST_METHOD")));
                } catch (...) {
                    logger.log(cxxlog::Level::SEVERE, "Unable to decode HTTP method");
                }
                
                try {
                    
                    // Find query string
                    std::string query = options_.at("QUERY_STRING");
                    
                    // Read method
                    builder.addQueryString(query);
                    
                    // Add query
                    updateQueryParameters(builder, query);
                    
                } catch (...) {
                    logger.log(cxxlog::Level::SEVERE, "Unable to decode HTTP method");
                }
                
#if DEBUG > 0
for (auto entry : options_) {
    logger.log(cxxlog::Level::SEVERE, "%1%:%2%", entry.first, entry.second);
}
#endif
            }
            
            // Read query parameters
            void FastCGIRequestDecoder::updateQueryParameters(HTTPRequestBuilder &builder, const std::string & query) {
                
                std::stringstream ssKey{};
                std::stringstream ssValue{};
                
                bool key = true;
                for (auto c : query) {
                    
                    if (key) {
                        if (c == '=') {
                            key = false;
                            continue;
                        }
                        if (c == '&') {
                            key = false;
                        } else {
                            ssKey << c;
                        }
                    }
                    
                    if (!key) {
                        if (c == '&') {
                            key = true;
                                
                            // Add query param
                            builder.addQueryParam(HTTPParam::fromValue(ssKey.str(), ssValue.str()));
                            
                            ssKey = std::stringstream{};
                            ssValue = std::stringstream{};
                        } else {
                            ssValue << c;
                        }
                    }
                }
                
                auto lastKey = ssKey.str();
                if (!lastKey.empty()) {
                    
                    // Add query param
                    builder.addQueryParam(HTTPParam::fromValue(lastKey, ssValue.str()));
                }
            }
        }
    }
}

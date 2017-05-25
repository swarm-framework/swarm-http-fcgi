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

#include "swarm/http/fcgi/FastCGIServerDelegate.hxx"
#include <swarm/http/server/HTTPServer.hxx>
#include <swarm/http/router/HTTPRouter.hxx>

int main(int arc, char *argv[]) {
    
    auto logger = LOGGER(Main);
    
    logger.log(cxxlog::Level::INFO, "Create router");
    
    // Router
    std::shared_ptr<swarm::http::HTTPRouter> router;
    
    logger.log(cxxlog::Level::INFO, "Create delegate");
    
    // Create fast cgi delegate
    auto delegate = std::make_shared<swarm::http::fastcgi::FastCGIServerDelegate>();
    
    logger.log(cxxlog::Level::INFO, "Create server");
    
    // Create server
    swarm::http::HTTPServer server{delegate, 9090, router};
    
    logger.log(cxxlog::Level::INFO, "Start server");
    
    // Process launch
    server.process();
    
    logger.log(cxxlog::Level::INFO, "Stop server");
}

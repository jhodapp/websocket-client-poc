// main.cpp
// websocket client POC

#include "websocket_client_poc.h"

#include "oatpp/network/client/SimpleTCPConnectionProvider.hpp"

#include <iostream>
#include <thread>

namespace {

    const char* TAG = "websocket-client-poc";

}

void run() {
    OATPP_LOGI(TAG, "Application Started");
}

int main()
{
    std::cout << "WebsocketClientPoc" << std::endl;

    oatpp::base::Environment::init();
    run();
    oatpp::base::Environment::destroy();

    return 0;
}

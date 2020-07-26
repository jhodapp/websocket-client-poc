// main.cpp
// websocket client POC

#include "websocket_client_poc.h"

#include "WSListener.hpp"

#include <oatpp-websocket/WebSocket.hpp>
#include <oatpp-websocket/Connector.hpp>

#include <oatpp/network/client/SimpleTCPConnectionProvider.hpp>

#include <iostream>
#include <thread>

namespace {

    const char* TAG = "websocket-client-poc";

     bool finished = false;

     void socketTask(const std::shared_ptr<oatpp::websocket::WebSocket>& websocket) {
         websocket->listen();
         OATPP_LOGD(TAG, "SOCKET CLOSED!!!");
         finished = true;
     }

}

void run() {
    OATPP_LOGI(TAG, "Application Started");

    //auto connectionProvider = oatpp::network::client::SimpleTCPConnectionProvider::createShared("echo.websocket.org", 80);
    auto connectionProvider = oatpp::network::client::SimpleTCPConnectionProvider::createShared("localhost", 8080);

    auto connector = oatpp::websocket::Connector::createShared(connectionProvider);

    auto connection = connector->connect("/");

    OATPP_LOGI(TAG, "Connected");

    auto socket = oatpp::websocket::WebSocket::createShared(connection, true /* maskOutgoingMessages must be true for clients */);

    std::mutex socketWriteMutex;

    socket->setListener(std::make_shared<WSListener>(socketWriteMutex));

    std::thread thread(socketTask, socket);

    while(!finished) {
	    {
		    OATPP_LOGD(TAG, "sending message...");
		    std::lock_guard<std::mutex> lock(socketWriteMutex);
		    socket->sendOneFrameText("hello from C++ Websocket_Client_Poc");
	    }
	    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    thread.join();
}

int main()
{
    std::cout << "WebsocketClientPoc starting up..." << std::endl;

    oatpp::base::Environment::init();
    run();
    oatpp::base::Environment::destroy();

    return 0;
}

// main.cpp
// websocket client POC

#include "websocket_client_poc.h"

#include "WSListener.hpp"

#include <oatpp-websocket/WebSocket.hpp>
#include <oatpp-websocket/Connector.hpp>

#include <oatpp/network/client/SimpleTCPConnectionProvider.hpp>

#include <iostream>
#include <signal.h>
#include <thread>

using namespace std;

namespace {

    const char* TAG = "websocket-client-poc";

    shared_ptr<oatpp::websocket::WebSocket> socket;

    bool finished = false;

    void socketTask(const std::shared_ptr<oatpp::websocket::WebSocket>& websocket) {
        websocket->listen();
        OATPP_LOGD(TAG, "SOCKET CLOSED!!!");
        finished = true;
    }

}

// Define the function to be called when ctrl-c (SIGINT) is sent to process
void signal_callback_handler(int signum) {
    cout << "Caught signal " << signum << endl;
    switch (signum)
    {
        case SIGINT:
            OATPP_LOGD(TAG, "Sending close to server");
	    socket->sendClose();
	    break;
    }
    // Terminate program
    exit(signum);
}

void run() {
    OATPP_LOGI(TAG, "Application Started");

    //auto connectionProvider = oatpp::network::client::SimpleTCPConnectionProvider::createShared("echo.websocket.org", 80);
    auto connectionProvider = oatpp::network::client::SimpleTCPConnectionProvider::createShared("localhost", 8080);

    auto connector = oatpp::websocket::Connector::createShared(connectionProvider);

    auto connection = connector->connect("/");

    OATPP_LOGI(TAG, "Connected");

    socket = oatpp::websocket::WebSocket::createShared(connection, true /* maskOutgoingMessages must be true for clients */);

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
    cout << "WebsocketClientPoc starting up..." << endl;

    // Register signal and signal handler
    signal(SIGINT, signal_callback_handler);

    oatpp::base::Environment::init();
    run();
    oatpp::base::Environment::destroy();

    return 0;
}

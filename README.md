# Simple C++ websocket client with simple Node.js websocket server

This example uses the [oatpp](https://github.com/oatpp/oatpp) and [oatpp-websocket](https://github.com/oatpp/oatpp-websocket) libraries for the C++ websocket client and the [Node.js module ws](https://github.com/websockets/ws) for the websocket server.


## Prerequisites
Follow the instructions for oatpp and oatpp-websocket to compile and install the required C++ libraries for the client (see links above).

`npm install ws` to install the Node.js ws library

## Running server
`cd src`
`node server.js`

## Running client
`./websocket_client_poc`

You should see active console output on both the client and server sides.

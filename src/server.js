// Simple websocket server written in Node.JS

const WebSocket = require('ws');

const wss = new WebSocket.Server({ port: 8080 });

wss.on('connection', function connection(ws, req) {
  ws.on('message', function incoming(message) {
    console.log('received from %s: %s', req.socket.remoteAddress, message);
  });

wss.on('close', function close(code, reason) {
    console.log('client closed connection to server (code: %d, reason: %s)', code, reason);
  });

  ws.send('something');
});

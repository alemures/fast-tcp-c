'use strict';

var net = require('net');

net.createServer((socket) => {
  console.log('Socket connected');

  socket.setEncoding('utf8');
  socket.on('data', (data) => socket.write(data.trim().toUpperCase()));
  socket.on('close', () => console.log('Socket closed'));
}).listen(5000, () => console.log('Tcp server listening at port 5000'));

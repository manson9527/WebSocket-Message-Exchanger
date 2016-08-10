var WebSocket = require('ws');

var ws = new WebSocket('ws://127.0.0.1:9527/ws/test');
ws.on('open', function open() {
    console.log('open!!!');
    ws.send('from sender1');
});
ws.on('message', function (data, flags) {
    console.log('received: ', data);
});
ws.on('close', function close() {
    console.warn('close!!!');
});

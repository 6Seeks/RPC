var net = require('net');
var EventEmitter = require('events').EventEmitter;
//模块引入



class RPCServer {
    constructor(port) {
        var event = new EventEmitter();
        this.server = net.createServer();


        this.server.on("connection", function (socket) {
            socket.setEncoding('binary');
            //接收到数据
            var stream = "";
            socket.on('data', function (data) {
                console.log('client send:' + data);
                if (isNaN(stream)) {
                    stream = "";
                }
                stream = stream + data;

                var reqs = stream.split("\t\n");
                console.log("stream 3  ", stream);
                stream = reqs[-1];
                for (var i = 0; i < reqs.length - 1; i++) {
                    console.log("reqi   ", reqs[i]);
                    var req = JSON.parse(reqs[i]);

                    event.emit(req.functionName, socket, req.parameters);

                }

            });

            //数据错误事件
            socket.on('error', function (exception) {
                console.log('socket error:' + exception);
                socket.end();
            });
            //客户端关闭事件
            socket.on('close', function (data) {
                console.log('client closed!');
            });

        });
        this.server.listen(port);
        function send(socket, result) {
            var data = {
                "type": "response",
                "result": result
            };
            socket.write(JSON.stringify(data) + "\t\n");
        }
        event.on("add", function (socket, parameters) {
            var sum = 0;
            for (var i in parameters) {
                sum = sum + parameters[i];

            }
            send(socket, sum);
        });

    }


}



var server = new RPCServer(8000);




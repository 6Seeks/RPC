var net = require('net');
var port = 8000;
var host = '127.0.0.1';
var client = new net.Socket();
//创建socket客户端
client.setEncoding('binary');
//连接到服务端
client.setNoDelay(true);
client.connect(port, host, function () {
    console.log("连接成功");

    for (var i = 0; i < 100; i++) {
        data = {
            "type": "request",
            "functionName": "add",
            "parameters": [i, 0]
        };
        client.write(JSON.stringify(data) + "\t\n",function(){
            console.log("send",JSON.stringify(data));
        });

    }

    //向端口写入数据到达服务端
});
var stream = "";
client.on('data', function (data) {
    if (isNaN(stream)) {
        stream = "";
    }
    stream = stream + data;
    var resp = stream.split("\t\n");
    stream = resp[-1];
    for (var i = 0; i < resp.length - 1; i++) {
        console.log('from server:' + resp[i]);
    }
  
    //得到服务端返回来的数据
});
client.on('error', function (error) {
    //错误出现之后关闭连接
    console.log('error:' + error);
    client.destory();
});
client.on('close', function () {
    //正常关闭连接
    console.log('Connection closed');
});



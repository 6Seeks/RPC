
from socket import *
import time
import json


class RPCClient():
    def __init__(self, ip, port):

        self.tcp_client = socket(AF_INET, SOCK_STREAM)
        self.tcp_client.connect((ip, port))

    def call(self, functionName, parameters):
        data = {
            "type": "request",
            "async":True,
            "functionName": functionName,
            "parameters": parameters
        }
        msg = json.dumps(data)
        self.tcp_client.sendall(msg.encode("utf-8"))
        # result = self.tcp_client.recv(1024).decode("utf-8")
        # print("服务器命令执行的结果是:", result)
        # return result


if __name__ == "__main__":
    c = RPCClient("127.0.0.1",8000)
    i=0
    while True:
        c.call("add",[i,0])
        time.sleep(0.5)


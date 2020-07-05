import socketserver
import json
import uuid


import time
import threading

class RPCServer(socketserver.BaseRequestHandler):
    def real_solve(self, req):
        print("ADDSDsd")

        if not hasattr(self, req["functionName"]):
            msg = json.dumps({
                "type": "response",
                "result": "illegal function"
            })
            self.request.sendall(msg.encode("utf-8"))
        else:
            result = str(getattr(self, req["functionName"])(req["parameters"]))

            msg = json.dumps({"type": "response", "result": result})
            self.request.sendall(msg.encode("utf-8"))

        print("thread over")

    def handle(self):

        print("conn is :", self.request)  # conn
        print("addr is :", self.client_address)  # addr
        while True:
            try:
                # 收消息
                print("new ready")
                data = self.request.recv(1024)
                print("receive!")
                if not data:
                    break
                print("收到客户端的消息是", data.decode("utf-8"))
                req = json.loads(data.decode("utf-8"))
                t = threading.Thread(target=self.real_solve, args=(req,))
                t.start()
                print("process start")
            except Exception as e:
                print(e)
                break


class MyServer(RPCServer):
    def add(self, parameters):
        print("add")
        time.sleep(10)
        result = 0
        for i in range(len(parameters)):
            result = result + parameters[i]
        print("add over")
        return result


if __name__ == "__main__":
    ip_port = ("127.0.0.1", 8000)
    s = socketserver.ThreadingTCPServer(ip_port, MyServer)
    s.serve_forever()

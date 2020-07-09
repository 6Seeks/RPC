# RPC
一个RPC的小的实现
使用C++实现了RFC的客户端，在进行远程调用时只需提供方法名和参数即可，具有比较好的灵活性。在进行数据传输时，利用rapidjson将数据封装成json格式进行传输，实现了跨语言调用。接收服务端发来的返回结果，利用rapidjson解析出方法的返回值，最后返回给方法的调用者。

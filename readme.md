# 一个小型的RPC框架

## 组成

主体采用python3，IDL编译器使用python。为了体现跨语言特性，将会使用java，javascript和python等语言进行远程过程调用

## IDL语法

IDL语法初步采用json数据格式。

```json
{
    "type":,//"request" or "response"
    "functionName":, //string
    "parameters":{
        "parametersName":"parametersValue"
    }
}
```

## 
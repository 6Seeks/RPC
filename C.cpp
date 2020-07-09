#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <windows.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#pragma comment(lib, "ws2_32.lib")

using namespace std;

class RPCClient{
	private:
		SOCKET sclient;
		sockaddr_in serAddr;
	
	public:
		
		int init(string ip, int port){
			sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			if (sclient == INVALID_SOCKET)
	        {
	            printf("invalid socket!");
	            return 0;
	        }
	        serAddr.sin_family = AF_INET;
	        serAddr.sin_port = htons(port);
	        serAddr.sin_addr.S_un.S_addr = inet_addr(ip.c_str());
	        if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	        {
	            printf("connect error !");
	            closesocket(sclient);
	            return 0;
	        }
	        return 1;
		}
		
		string call(string func, vector<int> parameters){
			string type = "request";
			bool async = true;
			string functionName = func;
			rapidjson::StringBuffer s;
			rapidjson::Writer<rapidjson::StringBuffer> writer(s);
            //create json
			writer.StartObject();
			writer.Key("type");
			writer.String(type.c_str());
			writer.Key("sync");
			writer.Bool(true);
			writer.Key("functionName");
			writer.String(func.c_str());
			writer.Key("parameters");
			writer.StartArray();
			vector<int>::iterator iter;
			for(iter = parameters.begin(); iter != parameters.end(); iter++){
				writer.Int(*iter);
			}
			writer.EndArray();
	  		writer.EndObject();
			string sendData = s.GetString();
	        send(sclient, sendData.c_str(), strlen(sendData.c_str()), 0);
			cout << "send:" << sendData << endl;
	        char tem[1024];
	        int ret = recv(sclient, tem, 1024, 0);
			string recData(tem);
	        cout << "receive:" << recData << endl;
	        closesocket(sclient);
	        //read json
	        rapidjson::Document document;
  			document.Parse(recData.c_str());
	        rapidjson::Value::ConstMemberIterator iter2 = document.FindMember("result");
	        string res;
			if(iter2 != document.MemberEnd()){
				res = iter2->value.GetString();
			}
	        return res;
		}
};

int main()
{
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    if (WSAStartup(sockVersion, &data) != 0) return 0;

	for(int i = 0; i < 5; i++){
		RPCClient client;
		if(client.init("127.0.0.1", 8000) == 0){
			return 0;
		}
		vector<int> para;
		para.push_back(i);
		para.push_back(i + 1);
		string res = client.call("add", para);
		cout << "result:" << res << endl;
	}
    WSACleanup();
    return 0;
}

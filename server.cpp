#include<iostream>
#include<WinSock2.h>
#include<WS2tcpip.h>
#include<tchar.h>
#include<thread>
#include<vector>
#include<algorithm>
#pragma comment(lib,"ws2_32.lib")

using namespace std;
bool Intialize(){
	WSADATA data;
	return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}

void InteractWithClient(SOCKET clientSocket, vector<SOCKET>& clients) {
	// send/recv client
	cout << "Client connected" << endl;
	char buffer[4096];
	while (1) {
		int bytesrecv = recv(clientSocket, buffer, sizeof(buffer), 0); // we can say data receiving.
		if (bytesrecv <= 0) {
			cout << "Client disconnected" << endl;
			break;
		}
		string message(buffer, bytesrecv);
		cout << "message frome client : " << message << endl;
		for (auto client : clients) {
			if (client != clientSocket) {
				send(client, message.c_str(), message.length(), 0);
			}
		}
	}
	auto it = find(clients.begin(), clients.end(), clientSocket);
	if (it != clients.end()) {
		clients.erase(it);
	}
	closesocket(clientSocket);
}

int main(){
	if(!Intialize()){
		cout << " winsock intialization has been failed" << endl;
		return 1;
	}
	/* 
		// first intialize winsack libary
	   //  create the socket
	   // get ip and port
	   // bind the ip and port with the socket
	*/
	SOCKET listenSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET) {
		cout << "Socket creation failed" << endl;
		return 1;
	}

	// crreate address structure
	int port = 12345;
	sockaddr_in serveraddr;
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(port);

	// convert the ipaddress(0.0.0.0) put it in sin_family in binary form
	if (InetPton(AF_INET, _T("0.0.0.0"), &serveraddr.sin_addr) != 1) {
		cout << "setting adress failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// bind them
	if (bind(listenSocket, reinterpret_cast<sockaddr*>(&serveraddr), sizeof(serveraddr)) == SOCKET_ERROR) {
		cout << "Bind failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	// listen
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		cout << "listen failed" << endl;
		closesocket(listenSocket);
		WSACleanup();
		return 1;
	}

	cout << "now server port has started to listen: " << port << endl;
	vector<SOCKET>clients;
	while (1) {
		//accept
		SOCKET clientSocket = accept(listenSocket, nullptr, nullptr);
		if (clientSocket == INVALID_SOCKET) {
			cout << "invalid client socket" << endl;
		}
		clients.push_back(clientSocket);
		thread t1(InteractWithClient, clientSocket, std::ref(clients));
		t1.detach();
	}
	closesocket(listenSocket);

	WSACleanup();
	cout << "Hi I am Gp" << endl;
	return 0;
}
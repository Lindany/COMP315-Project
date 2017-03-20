#include <iostream>
#include <string>
#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

using namespace std;

void main(){

	//initialise winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsock = WSAStartup(ver, &wsData);
	if (wsock != 0){
		cerr << "can't initialize winsock! Quiting" << endl;
		return;
	}

	//create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET){
		cerr << "Can;t create a socket! Quiting" << endl;
		return;
	}

	//Bind socket to a IP address
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // could also use inet_pton ....

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	//Tell winsock the socket is for listerning
	listen(listening, SOMAXCONN);

	//wait for a connection
	sockaddr_in client;
	int clientsize = sizeof(client);

	SOCKET clientSocket = accept(listening, (sockaddr*)&client, &clientsize); //return random address
	if (clientSocket == INVALID_SOCKET){
		cerr << "Invalid Socket! Quiting" << endl;

	}

	char host[NI_MAXHOST]; // Client's remote name
	char service[NI_MAXHOST]; // Service (i.e. port)  the client ics connect on

	ZeroMemory(host, NI_MAXHOST); // same as meset(host, 0, NI_MAXHOST)
	ZeroMemory(service, NI_MAXHOST);

					//check to see if we can get the host name else display the IP address//
	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXHOST, 0) == 0){
		cout << host << " connected on port " << service << endl;
	}
	else{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		cout << host << "conncted on host" << ntohs(client.sin_port) << endl;
	}

	//close listerning socket
	closesocket(listening); // what if you want to accept other clients?
	//while loo: accept and echo message back to client
	char buf[4096];

	while (true){
		ZeroMemory(buf, 4096);
		// wait for client to send data
		int byteReceived = recv(clientSocket, buf, 4096, 0);
		if (byteReceived == SOCKET_ERROR){
			cerr << "Error in recv(). Quiting" << endl;
			break;
		}

		if (byteReceived == 0){
			cout << "Client disconnected " << endl;
			break;
		}

		cout << string(buf, 0, byteReceived) << endl;

		//Echo message back to client
		send(clientSocket, buf, byteReceived + 1, 0);
	}
	//close the socket
	closesocket(clientSocket);
	//shutdown winsock
	WSACleanup();
}
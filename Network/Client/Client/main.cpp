#include <iostream>
#include <WS2tcpip.h>
#include <string>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

void main(){
	string ipAddress = "127.0.0.1";  // IP Address of the server
	int port = 54000;				 // listening port on the server

	// initialize winSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data); // 0-true no erro
	if (wsResult != 0){
		cerr << "Can't start winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET){
		cerr << "cant create socket, Err #" << WSAGetLastError() << endl;
		return;
	}
	// Fill to server
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// connect to a socket
	int connectResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connectResult == SOCKET_ERROR){
		cerr << "cant connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	
	// Do-while loop to send and receive data
	char buf[4096];
	string userInput;

	do{
		// Prompt the user for some text
		cout << " >";
		getline(cin, userInput);

		//send the text
		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0); // plus carrige return size

		//check if user typed something
		if (userInput.size() > 0){
			// send the text
			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR){
				//wait for response
				ZeroMemory(buf, 4096);
				int byteReceived = recv(sock, buf, 4096, 0);
				if (byteReceived > 0){
					// Echo response to console
					cout << "SERVDER>" << string(buf, 0, byteReceived) << endl;
				}
			}
		}
	} while (userInput.size() > 0);
		// Gracelly close down everything
		closesocket(sock);
		WSACleanup();

}

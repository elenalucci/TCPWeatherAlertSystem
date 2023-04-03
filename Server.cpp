#include <iostream>
#include <cstring>
#include <string>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <vector>

#define PORTNUM 60002

using namespace std;

int main(){

	//Server Vars
	char serverBuffer[2048];
	int serverSocket;
	struct sockaddr_in serverAddress;

	string message = "";

	string fileName;
	ifstream input;

	serverSocket = socket(AF_INET, SOCK_STREAM,0);
	if(serverSocket <0){
		cerr << "Error opening server socket\n";
	}

	bzero((char*) &serverAddress, sizeof(serverAddress));

	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(PORTNUM);

	if(bind(serverSocket,(struct sockaddr*) &serverAddress, sizeof(serverAddress)) <0){
		cerr << "Binding Failed\n"; 
		exit(1);
	}
	else{
		cout << "\nServer is started and ready\n";
	}

	if(listen(serverSocket,5)<0){
		cerr << "\nServer is not listening\n";
		exit(1);
	}
	else{
		cout<<"\nServer is listening and waiting for client\n";
	}

	if(pthread_mutex_init(&lock, NULL) != 0) {
		cerr << "mutex init failed";
		exit(1);
	}

	//Client Vars
	socklen_t clientSocket;
	struct sockaddr_in clientAddress;
	int newSocket;

	clientSocket = sizeof(clientAddress);

	while(true) {
		newSocket = accept(serverSocket,(struct sockaddr*) &clientAddress, &clientSocket);	
	
		if(newSocket <0){
			cerr<<"Server did not accept Client connection";
			exit(1);
		}
		
		else{
			cout << "Client Connection Accepted\n";
		}

	}
	
	pthread_t thread;
	int* clientThread = new int;
	*clientThread = newSocket;

		while(1){

		int messageNum, n;

		bzero(serverBuffer,2048);
		
		n = read(newSocket, serverBuffer, 2048);
		
		if(n < 0) {

			cout << "Error on read" << endl;

		}	

		cout << "File Requested From Client: " << serverBuffer << endl;


		fileName = serverBuffer;

		input.open(fileName, ios::in);
		

		if(!input.is_open()) {
			cerr << "Error: could not open file " << fileName << endl;
                	exit(1);
        	}
        	
		string line;

        	while(getline(input, line)) {

                	message += line;

        	}

        	input.close();
		
		cout << "Sending file: " << serverBuffer << endl << endl;
		int sendMessage = send(newSocket,message.c_str(),strlen(message.c_str()),0);
		if(sendMessage < 0) {

			cout << "Error on send" << endl;
		}

	}

	close(newSocket);
	close(serverSocket);


	return 0;
}

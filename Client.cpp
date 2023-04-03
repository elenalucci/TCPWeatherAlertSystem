#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cstdlib>
#include <string>
#include <unistd.h>

using namespace std;

#define BUFFER_SIZE 2048
#define PORTNUM 60002

int main() {

	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	char clientBuffer[2048];
	struct hostent *server;
	
	string fileName;

	if(serverSocket < 0) {
		cerr<< "Error: cannot open socket";
		return 1;
	}

	server = gethostbyname("127.0.0.1");

	struct sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(60002);

	if(connect(serverSocket, (struct sockaddr*) &serverAddress, sizeof(serverAddress))<0){
		cerr<< "Client could not connect to server\n";
		exit(1);
	}

	int serverMessage;
	while(1){

		cout << endl << endl;

		bzero(clientBuffer,2048);
		
		while(1){

		}

		if(serverMessage <0){
			cerr<< "Error on Send\n";
		}

		bzero(clientBuffer,2048);
		serverMessage = recv(serverSocket,clientBuffer,sizeof(clientBuffer), 0);

		if(serverMessage <0){
			cerr << "Error on Receive\n";
		}
		
		cout << "Receieved File Content: \n\n" << clientBuffer << "\n\n";
	}

	close(serverSocket);


	return 0;

}

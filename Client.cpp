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
	else{
		cout << "Connected\n\n";
	}

	int serverMessage;
	bool userExists = false;
	int selection;
	std::string username;
	std::string password;
	while(1){

		bzero(clientBuffer,2048);
		if (userExists) {
		// The client credentials are valid, so propose the available options
    			cout << "Welcome, !\n";
    			cout << "Available options:\n";
    			cout << "1. Subscribe to a location\n";
    			cout << "2. Unsubscribe from a location\n";
    			cout << "3. See the online users\n";
    			cout << "4. Send a message to a user\n";
    			cout << "5. Send a group message to a location\n";
    			cout << "6. See all the locations that you have subscribed to\n";
    			cout << "7. See the last 10 messages received\n";
    			cout << "8. Change password\n";
    			cout << "9. Logout\n";
			
			cout << "Selection: ";
			cin >> selection;
			cout << endl;
	
			switch(selection){
				case(1):
					break;
				case(2):
					break;
				case(3):
					break;
				case(4):
					break;
				case(5):
					break;
				case(6):
					break;
				case(7):
					break;
				case(8):
					break;
				case(9):
					break;

			}

		} else {
    		// The client credentials are invalid, so re-propose the login options
    			//cout << "Invalid username or password.\n";
    			cout << "Please choose an option:\n";
    			cout << "1. Login\n";
    			cout << "2. Register\n";
    			cout << "3. Quit\n";

			cout << "Selection: ";
			cin >> selection;
			cout << endl;

			switch(selection){
				case(1):
					cout << "Enter username: ";
					cin >> username;
					cout << "\nEnter password: ";
					cin >> password;
					cout << endl;
					break;
		
				case(2):
					cout << "Enter username: ";
                                        cin >> username;
                                        cout << "\nEnter password: ";
                                        cin >> password;
                                        cout << endl;
                                        break;
				case(3):
					exit(0);
					break;
			}
		}		
		

			
	}

	close(serverSocket);


	return 0;

}

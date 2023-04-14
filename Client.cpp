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
#include <sstream>

#include "User.hpp"

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
	std::string location;
	std::string selectionMessage;

	while(1){	

		bzero(clientBuffer,2048);
		if (userExists) {
		// The client credentials are valid, so propose the available options
    			cout << "Welcome, " << username << "!\n";
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
		
			while(1){	
				cout << "Selection: ";
				cin >> selection;
				cout << endl;
			
				if(selection == 1){
					string location;
               	 			cout << "Enter the location you want to subscribe to: ";
                			cin >> location;
					cout << endl;
				
					selectionMessage = "addLocation " + location;
                                	strcpy(clientBuffer,selectionMessage.c_str());
                                	serverMessage = send(serverSocket,clientBuffer,strlen(clientBuffer),0);

					break;
				}
				else if(selection ==2){
					string location;
                			cout << "Enter the location you want to unsubscribe to: ";

					break;
				}
				else if(selection == 3){
					break;
				}
				else if(selection == 4){
					break;
				}
				else if(selection == 5){
					break;
				}
				else if(selection == 6){
					cout << "Subscribed Locations:\n";
					
					break;
				}
				else if(selection == 7){
					break;
				}
				else if(selection == 8){
					string oldPassword, newPassword;
					cout << "Enter old password: ";

					cout << "Enter new password: ";
					
					break;
				}
				else if(selection == 9){
					exit(1);
					break;
				}
				else{
					cout << "Invalid Option" << endl;
                                	selectionMessage = "Invalid";
                                	strcpy(clientBuffer,selectionMessage.c_str());
                                	serverMessage = send(serverSocket,clientBuffer,strlen(clientBuffer),0);
					break;
				}
				
				break;	
			
			}

		} 
		else {
    		// The client credentials are invalid, so re-propose the login options
    			while(1){
				cout << "Please choose an option:\n";
    				cout << "1. Login\n";
    				cout << "2. Register\n";
    				cout << "3. Quit\n";
		
		
				cout << "Selection: ";
				cin >> selection;
				cout << endl;
		
				if(selection==1) {
					cout << "Enter username: ";
					cin >> username;
					cout << "\nEnter password: ";
					cin >> password;
					cout << endl;
					selectionMessage = "Login," + username + "," + password;
					selectionMessage = "Login " + username + " " + password;
					strcpy(clientBuffer,selectionMessage.c_str());
					serverMessage = send(serverSocket,clientBuffer,strlen(clientBuffer),0);
					

					break;
				}
				else if(selection == 2){
					cout << "Enter username: ";
                                        cin >> username;
                                        cout << "\nEnter password: ";
                                        cin >> password;
                                        cout << endl;
					selectionMessage = "Register " + username + " " + password;
                                        strcpy(clientBuffer,selectionMessage.c_str());
                                        serverMessage = send(serverSocket,clientBuffer,strlen(clientBuffer),0);
                                        break;
				}
				else if (selection == 3){
					exit(0);
					break;
				}
				else{
					cout << "Invalid Option" << endl;
					selectionMessage = "Invalid";
                                        strcpy(clientBuffer,selectionMessage.c_str());
					serverMessage = send(serverSocket,clientBuffer,strlen(clientBuffer),0);
					break;
				}	
			}
		}
		bzero(clientBuffer,2048);
		serverMessage = recv(serverSocket,clientBuffer,sizeof(clientBuffer), 0);
		cout << clientBuffer << endl;	
		std::string tempString;
                
		for(int i=0;i<2048;i++){
                        if(clientBuffer[i] == NULL){
                                break;
                        }

                        tempString += clientBuffer[i];
                }

		std::string tempArr[10];
                std::stringstream s(tempString);
                std::string command;
                int count = 0;
                while(s >> command){
                        tempArr[count] = command;
                        count ++;
                }
		
		if(tempArr[0] == "Login" && tempArr[1] == "true"){
			cout << "Login Successful!" << endl;
			userExists = true;

		}
		else if(tempArr[0] == "Login" && tempArr[1] == "false"){
			cout << "Login attempt failed" << endl;
			userExists = false;
		}		
		
		
	}

	close(serverSocket);


	return 0;

}

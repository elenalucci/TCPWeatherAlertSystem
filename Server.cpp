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
		cout<<"\nServer is listening and waiting for client\n\n";
	}

	//Client Vars
	socklen_t clientSocket;
	struct sockaddr_in clientAddress;
	int newSocket;

	clientSocket = sizeof(clientAddress);

	newSocket = accept(serverSocket,(struct sockaddr*) &clientAddress, &clientSocket);	
	
	if(newSocket <0){
		cerr<<"Server did not accept Client connection";
		exit(1);
	}
	else{
		cout << "Client Connection Accepted\n";
	}

		while(1){

		int  n;

		bzero(serverBuffer,2048);
		
		n = read(newSocket, serverBuffer, 2048);
		
		if(n < 0) {

			cout << "Error on read" << endl;

		}

		std::string tempString;
		for(int i=0;i<2048;i++){
			if(serverBuffer[i] == '\0'){
				break;
			}

			tempString += serverBuffer[i];
		}
		
		std::string tempArr[10];
		std::stringstream s(tempString);
		std::string command;
		int count = 0;
		while(s >> command){
			tempArr[count] = command;
			count ++;
		}

		string message = "";

		if(tempArr[0] == "Login"){
			bool foundUser = false;
			ifstream in;
			in.open("usernames.txt");
			string line;
			int pos;
			string s1,s2;
			while(getline(in,line)){
				pos = line.find(',');
				s1 = line.substr(0,pos);
				s2 = line.substr((pos+1),line.length());
				if(s1 == tempArr[1] && s2 == tempArr[2]){
					foundUser = true;
					cout << endl;
					cout << "Username found!" << endl;
					message = "Login true";
				}
			}
			if(!foundUser){
				cout << endl;
				cout << "Username was not found." << endl;
				message = "Login false";
			}
			in.close();

		}
		else if(tempArr[0] == "Register"){
			bool foundUser = false;
			ifstream in;
			in.open("usernames.txt");
                        string line;
                        int pos;
                        string s1,s2;
                        while(getline(in,line)){
                                pos = line.find(',');
                                s1 = line.substr(0,pos);
                                if(s1 == tempArr[1]){
					foundUser = true;
					message = "Registration was not successful.\n";	
					break;
				}
			}
			in.close();
			if(!foundUser){
                        	ofstream out("usernames.txt",ios::app);
                        	out <<tempArr[1] << "," << tempArr[2] << endl;
                        	out.close();
                        	message = "Registrations was successful!\n";
			}
                        
		}
		else if(tempArr[0] == "Invalid"){
			message = "Invalid";
		}
		else if(tempArr[0] == "addLocation"){
			cout << endl;
			cout << "Subscribing to location: " << tempArr[1] << endl;
			
			ifstream in("locations.txt");
			string line;
			bool locationExists = false;

			while(getline(in, line)) {
				if(line == tempArr[1]) {
					locationExists = true;
					break;
				}
			}

			in.close();
			
			if(locationExists) {
				cout << endl;
				cout << "You are already subscribed to that location." << endl;
				message = "Location has already been subscribed to.\n";
			} else {

				ofstream out("locations.txt", ios::app);
				out << tempArr[1] << endl;
				out.close();

				message = "Added location.\n";
			}
		}

		else if(tempArr[0] == "removeLocation") {
			cout << endl;
			cout << "Unsubscribing from location: " << tempArr[1] << endl;
			bool foundLocation = false;
			ifstream in("locations.txt");
			ofstream tempOut("temp.txt");

			string line;
			
			while(getline(in, line)) {
				if(line == tempArr[1]) {
					foundLocation = true;
				} else {
					tempOut << line << endl;
				}
			}	

			in.close();
			tempOut.close();

			if(foundLocation) {
				remove("Locations.txt");
				rename("temp.txt", "locations.txt");
				message = "Location has been removed.\n";
			} else {
				remove("temp.txt");
				cout << "Location not found." << endl << endl;
				message = "Location was not found.\n";
			}
		}

		else if(tempArr[0] == "displaying") {
			cout << endl;
			cout << "Displaying all subscribed locations: " << endl << endl;

			ifstream in("locations.txt");

			string line;

			while(getline(in, line)) {
				cout << "\t* " << line << endl << endl;
				message = "Displaying all locations subscribed to complete!";
			}
			in.close();
		}

		else if(tempArr[0] == "changePassword") {
			cout << endl;
			cout << "Changing passsword." << endl;

			bool foundUser = false;
			string password;

			ifstream in ("usernames.txt");
			ofstream out("tempPass.txt");

			string line;
			int pos;
			string s1;
			string s2;

			while(getline(in, line)) {
				pos = line.find(',');
				s1 = line.substr(0, pos);

				if(s1 == tempArr[1]) {
					foundUser = true;
					password = line.substr(pos + 1);
					if(password == tempArr[2]) {
						out << tempArr[1] << "," << tempArr[3] << endl;
						message = "Password has been changed!\n";
					} else {
						message = "Incorrect current password.\n";
					}
				} else {
					out << line << endl;
				}
			}

			in.close();
			out.close();	

			if(!foundUser) {
				message = "Invalid username.\v";
			}

			remove("usernames.txt");
			rename("tempPass.txt", "usernames.txt");
		}

		int sendMessage = send(newSocket,message.c_str(),strlen(message.c_str()),0);
		


		if(sendMessage < 0) {

			cout << "Error on send" << endl;
		}

	}

	close(newSocket);
	close(serverSocket);


	return 0;
}

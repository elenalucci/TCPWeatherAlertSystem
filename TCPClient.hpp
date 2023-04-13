#ifndef TCPCLIENT_HPP
#define TCPCLIENT_HPP

#include <iostream>
#include <string>

using namespace std;

class TCPClient{


	private:
		std::string username;
		std::string password;
	
	public:
		TCPClient();
		bool login(std::string username,std::string password);
		bool registerUser(std::string username,std::string password);





};
#endif

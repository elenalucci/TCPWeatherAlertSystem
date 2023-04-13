#include "TCPClient.hpp"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


TCPClient::TCPClient(){
	std::cout << "aye yo" << std::endl;
}

bool TCPClient::login(std::string username,std::string password){	
	std::cout << "in login func" << std::endl;
	return true;
}

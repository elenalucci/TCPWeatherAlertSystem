#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct UserInfo {
	string username;
	string password;
	vector<string> subscribedLocations;
};

struct Message {
	string sender;
	string content;
	string sendTo;
};

class User {
	private:
		map<string, UserInfo> registeredUsers;
		vector<string> onlineUsers;
		vector<Message> log;
	public:
		void registerUser();
		void login();
		void logout(string username);
		void changePassword(string username);
		void subscribeLocation(string username);
		void unsubscribeLocation(string username);
		void showSubscribed(string username);
};

#endif


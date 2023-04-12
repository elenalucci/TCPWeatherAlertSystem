#include <string>
#include <vector>
#include <iostream>

#include "User.hpp"

using namespace std;

class User {

	User(const string& username, const string& password, int socketNo) 
		: userName(username), passWord(password), socketNO(socketNo) {

	}

	const string& getUsername() const {
		return userName;
	}

	bool login(const string& password) {
		if(passWord == password) {
			loggedIn = true;
			cout << "User: " << userName << " is logged in!\n\n";
			return true;
		}
		cout << "Login failed for user: " << userName << "\n\n";
		return false;
	}

	void logout() {
		loggedIn = false;
		cout << "User: " << userName << " has been logged out\n";
	}

	bool registerUser(const string& password) {
		if(registered) {
			cout << "User " << userName << " is already registered.\n";
			return false;
		}
		passWord = password;
		registered = true;
		cout << "User " << userName << " registered\n";
		return true;
	}

	bool changePassword(const string& oldPassword, const string& newPassword) {
		if(loggedIn && passWord == oldPassword) {
			passWord = newPassword;
			cout << "Password changed.\n";
			return true;
		}
		cout << "Password change failed.\n";
		return false;
	}

	void subscribeLocation(const string& location) {
		auto it = find(location.begin(), location.end(), loc);
		if(it == location.end()) {
			location.push_back(loc);
			cout << "User: " << userName << " is subscribed to " << loc << "\n";
		}
	}

	void unsubscribeLocation(const string& location) {
		auto it = find(location.begin(), location.end(), loc);
		if(it != location.end()) {
			location.erase(it);
			cout << "User: " << userName << " is unsubscribed from " << loc << "\n";
		}
	}

	const vector<string>& getLocations() const {
		return location;
	}

	int getSocetNo() const {
		return socketNO;
	}

	void sendMessage(const string& message) {
		messages.push_back(message);
	}

	const vector<string>& getMessages() const {
		return messages;
	}


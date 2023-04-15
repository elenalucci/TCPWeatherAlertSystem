#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

#include "User.hpp"

using namespace std;

void User::registerUser() {
	UserInfo newUser;
	string username;
	string password;

	cout << "Please enter a new username: ";
	cin >> username;
	newUser.username = username;

	cout << "Please enter a new password: ";
	cin >> password;
	newUser.password = password;

	registeredUsers.insert(pair<string, UserInfo>(username, newUser));

	ofstream out;
	out.open("usernames.txt", ios::app);
	out <<username << "," << password << endl;
	out.close();

	cout << "Registration successful!\n";
}

void User::login() {
	string username;
	string password;
	bool foundUser = false;
	ifstream in("usernames.txt");

	cout << "Username: ";
	cin >> username;

	cout << "Password: ";
	cin >> password;

	if(in.is_open()) {
		string line;
		while(getline(in, line)) {
			stringstream ss(line);
			string user;
			string pass;
			getline(ss, user, ',');
			getline(ss, pass);

			if(user == username && pass == password) {
				foundUser = true;
				cout << "Login successful!" << endl;
				onlineUsers.push_back(username);
				break;
			}
		}
		in.close();
	}
	if(!foundUser) {
		cout << "Invalid username or password." << endl;
	}
}

void User::logout(string username) {
	vector<string>::iterator it = find(onlineUsers.begin(), onlineUsers.end(), username);
	if(it != onlineUsers.end()) {
		onlineUsers.erase(it);
		cout << "Logout successful!" << endl;
	} else {
		cout << "User is not logged in." << endl;
	}
}

void User::changePassword(string username) {
	if(registeredUsers.find(username) == registeredUsers.end()) {
		cout << "User not found." << endl;
		return;
	}
	string currentPassword;
	string newPassword;

	cout << "Please enter your current password: ";
	cin >> currentPassword;

	ifstream in("usernames.txt");
	string line;

	bool foundUser = false;
	while(getline(in, line)) {
		stringstream ss(line);
		string user;
		string pass;
		getline(ss, user, ',');
		getline(ss, pass);

		if(user == username && pass == currentPassword) {
			foundUser = true;
			break;
		}
	}
	in.close();

	if(!foundUser) {
		cout << "Invalid password. Please try again." << endl;
		return;
	}
	cout << "Please enter your new password: ";
	cin >> newPassword;

	registeredUsers[username].password = newPassword;

	ofstream out("usernames.txt");

	if(out.is_open()) {
		for(auto it : registeredUsers) {
			cout << it.second.username << "," << it.second.password << endl;
		}
		out.close();
	} else {
		cout << "Unable to open file." << endl;
		return;
	}
	cout << "Password changed successfully!" << endl;
}

void User::subscribeLocation(string username) {

}

void User::unsubscribeLocation(string username) {

}

void User::showSubscribed(string username) {

}

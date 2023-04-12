#ifndef USER_HPP
#define USER_HPP

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class User {

private:
    string userName;
    string passWord;
    bool registered = false;
    bool loggedIn = false;
    vector<string> location;
    int socketNO;
    vector<string> messages;

public:
    User(const string& username, const string& password, int socketNo);

    const string& getUsername() const;

    bool login(const string& password);

    void logout();

    bool registerUser(const string& password);

    bool changePassword(const string& oldPassword, const string& newPassword);

    void subscribeLocation(const string& location);
    
    void unsubscribeLocation(const string& location);

    const vector<string>& getLocations() const;

    int getSocetNo() const;

    void sendMessage(const string& message);

    const vector<string>& getMessages() const;
};

#endif


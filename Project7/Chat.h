#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "User.h"

struct Message
{
	std::string sender;
	std::string recipient;
	std::string content;

	Message(const std::string& sender, const std::string& recipient, const std::string& content) : sender(sender), recipient(recipient), content(content)
	{}
};


class Chat
{
private:
	std::vector<User> users;
	std::vector<Message> messages;
public:
	bool registerUser(const std::string& login, const std::string& password, const std::string& name);
	bool login(const std::string& login, const std::string& password);
	void sendMessage(const std::string& sender, const std::string& recipient, const std::string& message);
	void displayMessage();
	const std::vector<User>& getUsers() const;
};
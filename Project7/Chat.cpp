#include "Chat.h"
#include <iostream>

bool Chat::registerUser(const std::string& login, const std::string& password, const std::string& name)
{
	for (const auto& user : users)
	{
		if (user.login == login)
		{
			std::cout << "User with this login already exists." << std::endl;
			return false;
		}
	}

	users.emplace_back(login, password, name);
	std::cout << "User " << name << " registered successfully." << std::endl;
	return true;
}

bool Chat::login(const std::string& login, const std::string& password)
{
	for (const auto& user : users)
	{
		if (user.login == login && user.password == password)
		{
			std::cout << "Logged in as " << user.name << "." << std::endl;
			return true;
		}
	}

	std::cout << "Invalid login or password." << std::endl;
	return false;
}

void Chat::sendMessage(const std::string& sender, const std::string& recipientName, const std::string& message)
{
	bool recipientFound = false;
	std::string recipientLogin;

	for (const auto& user : users)
	{
		if (user.name == recipientName)
		{
			recipientFound = true;
			recipientLogin = user.login;

			break;
		}
	}
	if (!recipientFound)
	{
		std::cout << "User " << recipientName << " not found." << std::endl;
		return;
	}

	messages.emplace_back(sender, recipientLogin, message);
	std::cout << "Message from " << sender << " to " << recipientName << ". " << message << std::endl;

}

void Chat::displayMessage()
{
	for (const auto& message : messages)
	{
		std::string senderName;
		for (const auto& user : users)
		{
			if (user.login == message.sender)
			{
				senderName = user.name;
				break;
			}
		}
		std::string recipienName;
		for (const auto& user : users)
		{
			if (user.login == message.recipient)
			{
				recipienName = user.name;
				break;
			}
		}
		std::cout << "Message from " << senderName << " to  " << recipienName << ": " << message.content << std::endl;
	}
}
const std::vector<User>& Chat::getUsers() const
{
	return users;
}
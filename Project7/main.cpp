#include <iostream>
#include "Chat.h"

struct LoggedInUser
{
	std::string login;
	std::string name;
	std::vector<std::string> receivedMessages;
};


int main()
{
	Chat chat;
	LoggedInUser currentUser;

	std::cout << "Welcome to the Chat Application!" << std::endl;
	std::cout << "Commands available: register, login, exit" << std::endl;

	std::string command;
	while (true)
	{
		std::cout << "-> ";
		std::getline(std::cin, command);

		if (command == "register")
		{
			std::string login, password, name;
			std::cout << "Enter login: ";
			std::getline(std::cin,login);
			std::cout << "Enter password: ";
			std::getline(std::cin, password);
			std::cout << "Enter name: ";
			std::getline(std::cin, name);

			chat.registerUser(login, password, name);
		}
		else if (command == "login")
		{
			std::string login, password;
			std::cout << "Enter login: ";
			std::getline(std::cin, login);
			std::cout << "Enter password: ";
			std::getline(std::cin, password);

			if (chat.login(login, password))
			{
				currentUser.login = login;
				for (const auto& user : chat.getUsers())
				{
					if (user.login == login)
					{
						currentUser.name = user.name;
						break;
					}
				}
				std::cout << "Welcome " << currentUser.name << std::endl;
				std::cout << "Commands available: send, display." << std::endl;
			}
		}
		else if (command == "exit")
		{
			std::cout << "Exiting Chat Application." << std::endl;
			break;
		}
		else if (!currentUser.login.empty())
		{
			if (command == "send")
			{
				std::string recipient, message;
				std::cout << "Enter recipient name: ";
				std::getline(std::cin, recipient);
				std::cout << "Enter message: ";
				std::getline(std::cin, message);

				chat.sendMessage(currentUser.login, recipient, message);
			}
			else if (command == "display")
			{
				chat.displayMessage();
			}
			else
			{
				std::cout << "Unknown command. Please try again." << std::endl;
			}
		}
		else
		{
			std::cout << " Uncnown command or not logged in. Please try again." << std::endl;
		}
	}

	return 0;
}
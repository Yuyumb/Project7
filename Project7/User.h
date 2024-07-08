#pragma once
#include <string>

class User
{
public:
	std::string login;
	std::string password;
	std::string name;

	User(const std::string& login, const std::string& password, const std::string& name);
};
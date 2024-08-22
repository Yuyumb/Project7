#include "Chat.h"

bool Chat::registerUser(const std::string& login, const std::string& password, const std::string& name) {
    std::string password_hash = std::to_string(std::hash<std::string>{}(password));

    if (!user_table.find(login).empty()) {
        std::cout << "User with this login already exists." << std::endl;
        return false;
    }

    user_table.add(login, password_hash);

    user_list.emplace_back(login, password, name);
    std::cout << "User " << name << " registered successfully." << std::endl;
    return true;
}

bool Chat::login(const std::string& login, const std::string& password) {
    std::string password_hash = std::to_string(std::hash<std::string>{}(password));
    std::string stored_hash = user_table.find(login);

    if (stored_hash == password_hash) {
        std::cout << "Logged in successfully." << std::endl;
        return true;
    }
    else {
        std::cout << "Invalid login or password." << std::endl;
        return false;
    }
}

void Chat::sendMessage(const std::string& sender, const std::string& recipientName, const std::string& message) {
    bool recipientFound = false;
    std::string recipientLogin;

    for (const auto& user : user_list) {
        if (user.name == recipientName) {
            recipientFound = true;
            recipientLogin = user.login;
            break;
        }
    }

    if (!recipientFound) {
        std::cout << "User " << recipientName << " not found." << std::endl;
        return;
    }

    messages.emplace_back(sender, recipientLogin, message);
    std::cout << "Message from " << sender << " to " << recipientName << ": " << message << std::endl;
}

void Chat::displayMessage() {
    for (const auto& message : messages) {
        std::string senderName;
        std::string recipientName;

        for (const auto& user : user_list) {
            if (user.login == message.sender) {
                senderName = user.name;
            }
            if (user.login == message.recipient) {
                recipientName = user.name;
            }
        }

        std::cout << "Message from " << senderName << " to " << recipientName << ": " << message.content << std::endl;
    }
}

const std::vector<User>& Chat::getUsers() const {
    return user_list;
}
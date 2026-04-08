#include <iostream>
#include <sstream>
#include "SystemManager.h"

int main() {
    SystemManager sm;
    std::string line;

    std::cout << "User Management System ready. Enter a command or type exit." << std::endl;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line))
            break;

        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string cmd;
        ss >> cmd;

        if (cmd == "createUser") {
            int id;
            std::string name, email;
            if (ss >> id >> name >> email) {
                sm.createUser(id, name, email);
                std::cout << "Created user " << id << " (" << name << ")." << std::endl;
            } else {
                std::cout << "Usage: createUser {userId} {username} {email}" << std::endl;
            }
        }
        else if (cmd == "deleteUser") {
            int id;
            if (ss >> id) {
                sm.deleteUser(id);
                std::cout << "Deleted user " << id << "." << std::endl;
            } else {
                std::cout << "Usage: deleteUser {userId}" << std::endl;
            }
        }
        else if (cmd == "allUsers") {
            std::cout << "All users:" << std::endl;
            sm.allUsers();
        }
        else if (cmd == "getUser") {
            int id;
            if (ss >> id) {
                sm.getUser(id);
            } else {
                std::cout << "Usage: getUser {userId}" << std::endl;
            }
        }
        else if (cmd == "createGroup") {
            int id;
            if (ss >> id) {
                sm.createGroup(id);
                std::cout << "Created group " << id << "." << std::endl;
            } else {
                std::cout << "Usage: createGroup {groupId}" << std::endl;
            }
        }
        else if (cmd == "deleteGroup") {
            int id;
            if (ss >> id) {
                sm.deleteGroup(id);
                std::cout << "Deleted group " << id << "." << std::endl;
            } else {
                std::cout << "Usage: deleteGroup {groupId}" << std::endl;
            }
        }
        else if (cmd == "allGroups") {
            std::cout << "All groups:" << std::endl;
            sm.allGroups();
        }
        else if (cmd == "getGroup") {
            int id;
            if (ss >> id) {
                sm.getGroup(id);
            } else {
                std::cout << "Usage: getGroup {groupId}" << std::endl;
            }
        }
        else if (cmd == "exit") {
            std::cout << "Exiting." << std::endl;
            break;
        }
        else {
            std::cout << "Unknown command: " << cmd << ". Available commands: createUser, deleteUser, allUsers, getUser, createGroup, deleteGroup, allGroups, getGroup, exit." << std::endl;
        }
    }

    return 0;
}
 
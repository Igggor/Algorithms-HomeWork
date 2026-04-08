#pragma once
#include <string>
#include <iostream>

class User {
private:
    int id;
    std::string name;
    std::string email;
    int groupId; // -1 если нет группы

public:
    User() : id(0), name(), email(), groupId(-1) {}
    User(int id, const std::string& name, const std::string& email)
        : id(id), name(name), email(email), groupId(-1) {}

    int getId() const { return id; }
    std::string getName() const { return name; }
    std::string getEmail() const { return email; }

    int getGroupId() const { return groupId; }
    void setGroupId(int gid) { groupId = gid; }

    void print() const {
        std::cout << "User ID: " << id
                  << ", Name: " << name
                  << ", Email: " << email
                  << ", Group ID: " << groupId << std::endl;
    }
};
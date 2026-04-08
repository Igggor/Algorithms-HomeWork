#pragma once
#include <vector>
#include <iostream>
#include <algorithm>

class Group {
private:
    int id;
    std::vector<int> users;

public:
    Group() : id(0) {}
    Group(int id) : id(id) {}

    int getId() const { return id; }

    void addUser(int userId) {
        users.push_back(userId);
    }

    void removeUser(int userId) {
        users.erase(std::remove(users.begin(), users.end(), userId), users.end());
    }

    const std::vector<int>& getUsers() const {
        return users;
    }

    void print() const {
        std::cout << "Group ID: " << id << "\nUsers: ";
        for (int u : users)
            std::cout << u << " ";
        std::cout << std::endl;
    }
};
#pragma once
#include <unordered_map>
#include <iostream>
#include "User.h"
#include "Group.h"

class SystemManager {
private:
    std::unordered_map<int, User> users;
    std::unordered_map<int, Group> groups;

public:
    void createUser(int id, const std::string& name, const std::string& email) {
        users.emplace(id, User(id, name, email));
    }

    void deleteUser(int id) {
        if (users.count(id)) {
            int gid = users[id].getGroupId();
            if (gid != -1 && groups.count(gid)) {
                groups[gid].removeUser(id);
            }
            users.erase(id);
        }
    }

    void getUser(int id) {
        if (users.count(id))
            users[id].print();
    }

    void allUsers() {
        for (auto& [id, user] : users)
            user.print();
    }

    void createGroup(int id) {
        groups.emplace(id, Group(id));
    }

    void deleteGroup(int id) {
        if (groups.count(id)) {
            for (int userId : groups[id].getUsers()) {
                users[userId].setGroupId(-1);
            }
            groups.erase(id);
        }
    }

    void getGroup(int id) {
        if (!groups.count(id)) return;

        Group& g = groups[id];
        std::cout << "Group ID: " << id << "\nUsers:\n";

        for (int userId : g.getUsers()) {
            if (users.count(userId))
                users[userId].print();
        }
    }

    void allGroups() {
        for (auto& [id, group] : groups) {
            getGroup(id);
            std::cout << "------\n";
        }
    }
};
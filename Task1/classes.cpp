#include "classes.h"
#include <algorithm>

Group::Group() : id(""), name("") {}

Group::Group(std::string id, std::string name) : id(id), name(name) {}

std::string Group::get_id() const { return id; }
std::string Group::get_name() const { return name; }

void Group::add_user(std::shared_ptr<User> user){
    users.push_back(user);
}

void Group::remove_user(const std::string &user_id){
    users.erase(std::remove_if(users.begin(), users.end(),
                               [&user_id](const std::weak_ptr<User> &wp)
                               {
                                   auto u = wp.lock();
                                   return !u || u->get_id() == user_id;
                               }),
                users.end());
}

std::string Group::get_group_info() const {
    std::string result = "Group ID: " + id + ", Name: " + name + ", Users: ";
    for (const auto &wp : users)
    {
        if (auto u = wp.lock())
            result += u->get_id() + " ";
    }
    return result;
}

std::vector<std::string> Group::get_user_ids() const {
    std::vector<std::string> ids;
    for (const auto &wp : users){
        if (auto u = wp.lock())
            ids.push_back(u->get_id());
    }
    return ids;
}



void Groups::add_group(std::shared_ptr<Group> group){
    groups[group->get_id()] = group;
}

void Groups::delete_group(const std::string &id){
    groups.erase(id);
}

std::shared_ptr<Group> Groups::get_group(const std::string &id){
    auto it = groups.find(id);
    return it != groups.end() ? it->second : nullptr;
}

std::string Groups::all_groups_info() const{
    std::string result;
    for (const auto &pair : groups)
        result += pair.second->get_group_info() + "\n";
    return result;
}


User::User() : user_name(""), id(""), meta_information("") {}

User::User(std::string user_name, std::string id, std::string meta_information)
    : user_name(user_name), id(id), meta_information(meta_information) {}

std::string User::get_id() const { return id; }
std::string User::get_user_name() const { return user_name; }
std::string User::get_meta() const { return meta_information; }

std::string User::get_user_info() const{
    std::string group_info = "none";
    if (auto g = group.lock())
        group_info = g->get_id();
    return "ID: " + id + ", Name: " + user_name + ", Meta: " + meta_information + ", Group: " + group_info;
}

void User::set_group(std::shared_ptr<Group> g) {
    group = g; 
}


std::shared_ptr<Group> User::get_group() const { 
    return group.lock(); 
}

void User::remove_group() { 
    group.reset(); 
}


void Users::add_user(std::shared_ptr<User> user){
    users[user->get_id()] = user;
}

void Users::delete_user(const std::string &user_id){
    users.erase(user_id);
}

std::shared_ptr<User> Users::get_user(const std::string &user_id){
    auto it = users.find(user_id);
    return it != users.end() ? it->second : nullptr;
}

std::string Users::all_users_info() const{
    std::string result;
    for (const auto &pair : users)
        result += pair.second->get_user_info() + "\n";
    return result;
}
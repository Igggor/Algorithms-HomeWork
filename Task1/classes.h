#pragma once

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include <string>


class User
{
private:
    std::string user_name;
    std::string id;
    std::string meta_information;
    std::weak_ptr<Group> group;

public:
    User();
    User(std::string user_name, std::string id, std::string meta_information);
    std::string get_id() const;
    std::string get_user_name() const;
    std::string get_meta() const;
    std::string get_user_info() const;
    void set_group(std::shared_ptr<Group> g);
    std::shared_ptr<Group> get_group() const;
    void remove_group();
};

class Group
{
private:
    std::string id;
    std::string name;
    std::vector<std::weak_ptr<User>> users;

public:
    Group();
    Group(std::string id, std::string name);
    std::string get_id() const;
    std::string get_name() const;
    void add_user(std::shared_ptr<User> user);
    void remove_user(const std::string &user_id);
    std::string get_group_info() const;
    std::vector<std::string> get_user_ids() const;
};

class Groups
{
private:
    std::unordered_map<std::string, std::shared_ptr<Group>> groups;

public:
    void add_group(std::shared_ptr<Group> group);
    void delete_group(const std::string &id);
    std::shared_ptr<Group> get_group(const std::string &id);
    std::string all_groups_info() const;
};

class Users
{
private:
    std::unordered_map<std::string, std::shared_ptr<User>> users;

public:
    void add_user(std::shared_ptr<User> user);
    void delete_user(const std::string &user_id);
    std::shared_ptr<User> get_user(const std::string &user_id);
    std::string all_users_info() const;
};
#pragma once
#include <string>
#include <vector>
#include <cmath>

#define TABLE_SIZE 8

class HashTable {
public:
    HashTable();
    ~HashTable();
    void add(const std::string& login, const std::string& password_hash);
    std::string find(const std::string& login) const;

private:
    int hash(const std::string& key, int i) const;

    struct Entry {
        std::string login;
        std::string password_hash;
        bool is_deleted;
        bool is_active;

        Entry() : is_deleted(false), is_active(false) {}
        Entry(const std::string& login, const std::string& password_hash)
            : login(login), password_hash(password_hash), is_deleted(false), is_active(true) {}
    };

    std::vector<Entry> table;
    int size;

    void resize();
    const float LOAD_FACTOR = 0.75f;
};
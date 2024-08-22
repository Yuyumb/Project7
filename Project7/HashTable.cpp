#include "HashTable.h"
#include <stdexcept>

HashTable::HashTable() : size(TABLE_SIZE) {
    table.resize(size);
}

HashTable::~HashTable() {
    
}

int HashTable::hash(const std::string& key, int i) const {
    float A = (std::sqrt(5) - 1) / 2;
    unsigned int hash1 = 0;
    for (char c : key) {
        hash1 = hash1 * 31 + c;
    }
    return (static_cast<int>(hash1 * A) % size + i * i) % size;
}

void HashTable::add(const std::string& login, const std::string& password_hash) {
    if ((float)size / table.size() > LOAD_FACTOR) {
        resize();
    }

    int i = 0;
    int index;
    do {
        index = hash(login, i++);
        if (!table[index].is_active || table[index].is_deleted) {
            table[index] = Entry(login, password_hash);
            return;
        }
    } while (i < size);
}

void HashTable::resize() {
    std::vector<Entry> old_table = table;
    size *= 2;
    table.clear();
    table.resize(size);

    for (const auto& entry : old_table) {
        if (entry.is_active && !entry.is_deleted) {
            add(entry.login, entry.password_hash);
        }
    }
}

std::string HashTable::find(const std::string& login) const {
    int i = 0;
    int index;
    do {
        index = hash(login, i++);
        if (table[index].is_active && table[index].login == login) {
            return table[index].password_hash;
        }
    } while (i < size && table[index].is_active);
    return "";
}
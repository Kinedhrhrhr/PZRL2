#include "HashTable.h"
#include <cmath>

HashTable::HashTable(size_t size) noexcept
    : _capacity(size > 0 ? (int32_t)size : 1)
    , _filled(0)
    , table(_capacity)
{
}

HashTable::~HashTable()
{
    table.clear();
    _capacity = 0;
    _filled = 0;
}

size_t HashTable::hash_function(const KeyType &key) const
{
    size_t hash = 0;
    for (char c : key) {
        hash = hash * 113 + (size_t)c;
    }
    return hash % _capacity;
}

void HashTable::insert(const KeyType &key, const ValueType &value)
{
    if (getLoadFactor() > 0.75) {
        size_t new_capacity = _capacity * 2;
        HashTable new_table(new_capacity);
        
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                new_table.insert(pair.first, pair.second);
            }
        }
        
        *this = std::move(new_table);
    }
    
    size_t index = hash_function(key);
    
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            pair.second = value;
            return;
        }
    }
    
    table[index].push_back({key, value});
    _filled++;
}

bool HashTable::find(const KeyType &key, ValueType &value) const
{
    size_t index = hash_function(key);
    
    for (const auto& pair : table[index]) {
        if (pair.first == key) {
            value = pair.second;
            return true;
        }
    }
    
    return false;
}

void HashTable::remove(const KeyType &key)
{
    size_t index = hash_function(key);
    auto& bucket = table[index];
    
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == key) {
            bucket.erase(it);
            _filled--;
            return;
        }
    }
}

ValueType& HashTable::operator[](const KeyType &key)
{
    size_t index = hash_function(key);
    
    for (auto& pair : table[index]) {
        if (pair.first == key) {
            return pair.second;
        }
    }
    
    table[index].push_back({key, ValueType()});
    _filled++;
    return table[index].back().second;
}

double HashTable::getLoadFactor()
{
    return (double)_filled / _capacity;
}

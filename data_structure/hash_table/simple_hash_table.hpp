#pragma once

#include <string>
#include <iostream>
using namespace std;

const int DEFAULT_BUCKET_SIZE = 32;

class HashTable
{
public:
    HashTable()
    {
        size = DEFAULT_BUCKET_SIZE;
        bucket = new string[size];
        for (int i = 0; i < size; ++i)
        {
            bucket[i] = "";
        }
    }

    ~HashTable() = default;

    /* if key already exists, update value */
    void add(string key)
    {
        unsigned hval = hash(key);
        bucket[hval%size] = key;
    }

    bool exists(string key)
    {
        unsigned hval = hash(key);
        if (bucket[hval].size() > 0)
            return true;

        return false;
    }

    void remove(string key)
    {
        unsigned hval = hash(key);
        bucket[hval] = "";
    }

private:
    string *bucket;
    int size;

    int hash(string key)
    {
        unsigned sum = 0;

        for (int i = 0; i < key.size(); ++i)
        {
            sum += key[i];
        }

        return sum % size;
    }
};
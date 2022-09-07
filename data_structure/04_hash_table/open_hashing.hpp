#pragma once

#include <string>
#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

const int DEFAULT_BUCKET_SIZE = 32;

typedef struct Item
{
    int data;
    string key;
} Item;

class HashTable
{
public:
    HashTable()
    {
        size = DEFAULT_BUCKET_SIZE;
        bucket.resize(DEFAULT_BUCKET_SIZE);
    }

    ~HashTable() = default;

    /* open hashing - closed addressing */
    void insert(string key, int value)
    {
        Item *item = new Item{value, key};
        unsigned hashIndex = hash(key);

        bucket[hashIndex].push_back(item);
    }

    Item *remove(Item *item)
    {
        string key = item->key;
        unsigned hashIndex = hash(key);
        auto it = bucket[hashIndex].begin();

        if((*it)->key.compare(key) == 0 && (*it)->data == item->data)
        {
            Item *temp = *it;
            bucket[hashIndex].erase(it);
            return temp;
        }

        return nullptr;
    }

    Item *search(string key)
    {
        unsigned hashIndex = hash(key);

        for (int i = 0; i < bucket[hashIndex].size(); ++i)
        {
            if (bucket[hashIndex][i]->key.compare(key) == 0)
            {
                return bucket[hashIndex][i];
            }
        }

        return nullptr;
    }

    void display()
    {
        for (int i = 0; i < size; ++i)
        {
            printf("[%d] -> ", i);
            for (int j = 0; j < bucket[i].size(); ++j)
            {
                Item *temp = bucket[i][j];
                printf("(%d, '%s') - ", bucket[i][j]->data, bucket[i][j]->key.c_str());
            }
            
            printf("\n");
        }
    }

private:
    vector<vector<Item *>> bucket;
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
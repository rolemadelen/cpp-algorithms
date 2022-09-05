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

        for (int i = 0; i < DEFAULT_BUCKET_SIZE; ++i)
            bucket[i] = nullptr;
    }

    ~HashTable() = default;

    /* Linear Probing */
    void insert(string key, int value)
    {
        Item *item = new Item{value, key};
        unsigned hashIndex = hash(key);

        while (bucket[hashIndex] != nullptr)
        {
            ++hashIndex;
            hashIndex %= size;
        }

        bucket[hashIndex] = item;
    }

    Item *remove(Item *item)
    {
        string key = item->key;
        unsigned hashIndex = hash(key);

        while (bucket[hashIndex] != nullptr)
        {
            if (bucket[hashIndex]->key.compare(key) == 0)
            {
                Item *removedItem = bucket[hashIndex];
                delete bucket[hashIndex];
                bucket[hashIndex] = nullptr;
                return removedItem;
            }

            ++hashIndex;
            hashIndex %= size;
        }

        return nullptr;
    }

    Item *search(string key)
    {
        unsigned hashIndex = hash(key);

        while (bucket[hashIndex] != nullptr)
        {
            if (bucket[hashIndex]->key.compare(key) == 0)
            {
                Item *item = bucket[hashIndex];
                return item;
            }

            ++hashIndex;
            hashIndex %= size;
        }

        return nullptr;
    }

    void display()
    {
        for (int i = 0; i < size; ++i)
        {
            if (bucket[i] != NULL)
                printf("(%d, %s) ", bucket[i]->data, bucket[i]->key.c_str());
            else
                printf(" - ");
        }
        printf("\n");
    }

private:
    vector<Item *> bucket;
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
#include "../include/bplustree.hpp"
#include <iostream>

int main() {
    BPLUSTREE::BplusTree tree("/home/yuxintao/duckdb_study/data/data.bin", true);
    BPLUSTREE::BplusTree::key_t key;
    BPLUSTREE::BplusTree::value_t value;
    strcpy(key.k, "hello");
    strcpy(value.email, "1921");
    strcpy(value.name, "yuxintao");
    value.age = 12;
    tree.insert(key, value);
    strcpy(key.k, "we");
    strcpy(value.email, "1");
    strcpy(value.name, "intao");
    value.age = 142;
    tree.insert(key, value);
    
    strcpy(key.k, "hello");
    tree.search(key, &value);
    std::cout << value.email << value.age << value.name;
    return 0;
}
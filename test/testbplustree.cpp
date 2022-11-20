#include "../include/bplustree.hpp"
#include <iostream>

int main() {
    FILE *fp = NULL;
    if ((fp = freopen("./log.txt", "w", stdout)) == NULL) {
        std::cout << "reopen error" << std::endl;
        return 1;
    }
    BPLUSTREE::BplusTree tree("./data.bin", true);
    BPLUSTREE::BplusTree::key_t key;
    BPLUSTREE::BplusTree::value_t value;
    int ret;
    // sprintf(key.k, "%d", 455);
    // ret = tree.search(key, &value);
        
    //     if (ret != 0) {
    //         std::cout << "search error " << 455 <<  std::endl;
    //         return 1;
    //     }
    //     std::cout << "key: " << key.k << " value.age: " << value.age << 
    //                                     " value.email: " << value.email << 
    //                                     " value.name: " << value.name << std::endl; 

    for (int i = 0; i < 1500; ++i) {
        memset(&key, 0, sizeof(key));
        memset(&value, 0, sizeof(value));
        sprintf(key.k, "%d", i);
        value.age = i;
        sprintf(value.email, "%d@com", i);
        sprintf(value.name, "0x%x", i);
        ret = tree.insert(key, value);
        if (ret != 0) {
            std::cout << "insert error " << i <<  std::endl;
            return 1;
        }
    }

    for (int i = 0; i < 1500; ++i) {
        memset(&key, 0, sizeof(key));
        memset(&value, 0, sizeof(value));
        sprintf(key.k, "%d", i);
        ret = tree.search(key, &value);
        
        if (ret != 0) {
            std::cout << "search error " << i <<  std::endl;
            return 1;
        }
        std::cout << "key: " << key.k << " value.age: " << value.age << 
                                        " value.email: " << value.email << 
                                        " value.name: " << value.name << std::endl; 
    }

    for (int i = 750; i < 1500; ++i) {
        memset(&key, 0, sizeof(key));
        memset(&value, 0, sizeof(value));
        sprintf(key.k, "%d", i);
        ret = tree.remove(key);
        if (ret != 0) {
            std::cout << "remove error " << i <<  std::endl;
        }
    }
    
    for (int i = 0; i < 1500; ++i) {
        memset(&key, 0, sizeof(key));
        memset(&value, 0, sizeof(value));
        sprintf(key.k, "%d", i);
        ret = tree.search(key, &value);
        if (ret != 0) {
            std::cout << "search error " << i <<  std::endl;
            return 1;
        }
        std::cout << "key: " << key.k << " value.age: " << value.age << 
                                        " value.email: " << value.email << 
                                        " value.name: " << value.name << std::endl; 
    }

    fclose(fp);
    return 0;
}
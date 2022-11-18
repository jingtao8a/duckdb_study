#ifndef BPLUS_TREE_HPP
#define BPLUS_TREE_HPP

#include <string>
#include <stddef.h>
#include <string.h>

#define BP_ORDER 50

namespace BPLUSTREE {

class BplusTree{
public:
    struct meta_t{
        size_t order; /* `order` of B+ tree */
        size_t value_size; /* size of value */
        size_t key_size;   /* size of key */
        size_t internal_node_num; /* how many internal nodes */
        size_t leaf_node_num;     /* how many leafs */
        size_t height;            /* height of tree (exclude leafs) */
        off_t slot;        /* where to store new block */
        off_t root_offset; /* where is the root of internal nodes */
        off_t leaf_offset; /* where is the first leaf */
    };
    
    struct value_t {
        char name[256];
        int age;
        char email[256];
    };

    struct key_t {
        char k[16];
        key_t(const char *str = "") {
            bzero(k, sizeof(k));
            strcpy(k, str);
        }
        
        bool operator<(const key_t& rhs) {
            return keyCmp(*this, rhs) < 0;
        }
        
        bool operator==(const key_t& rhs) {
            return keyCmp(*this, rhs) == 0;
        }
    private:
        //正:a > b     0:a == b    负:a < b
        static int keyCmp(const key_t& a, const key_t& b) {
            int x = strlen(a.k) - strlen(b.k);
            return x == 0 ? strcmp(a.k, b.k) : x;
        }
    };

    struct index_t{ 
        key_t key;
        off_t child;
    };

    struct internal_node_t{
        off_t parent;
        off_t next;
        off_t prev;
        size_t n;//how many children
        index_t children[BP_ORDER];
    };

    struct record_t {
        key_t key;
        value_t value;
    };

    struct leaf_node_t {
        off_t parent;
        off_t next;
        off_t prev;
        size_t n;
        record_t children[BP_ORDER];
    };

public:
    
public:
    BplusTree(std::string path, bool forceEmpty=false);
private:
    std::string m_path;
    meta_t m_meta;
};

}

#endif
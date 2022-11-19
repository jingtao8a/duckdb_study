#ifndef BPLUS_TREE_HPP
#define BPLUS_TREE_HPP

#include <string>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <algorithm>

#define BP_ORDER 50
#define OFFSET_META 0
#define OFFSET_BLOCK OFFSET_META + sizeof(meta_t)
#define SIZE_NO_CHILDREN sizeof(leaf_node_t) - BP_ORDER * sizeof(record_t)

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
            return BplusTree::keyCmp(*this, rhs) < 0;
        }
        
        bool operator==(const key_t& rhs) {
            return BplusTree::keyCmp(*this, rhs) == 0;
        }
        
    };

    struct index_t{ 
        key_t key;
        off_t child;
        bool operator<(const key_t& rhs) {
            return BplusTree::keyCmp(key, rhs) < 0;
        }
        
        bool operator==(const key_t& rhs) {
            return BplusTree::keyCmp(key, rhs) == 0;
        }
    };

    struct internal_node_t{
        typedef index_t* child_t;
        off_t parent;
        off_t next;
        off_t prev;
        size_t n;//how many children
        index_t children[BP_ORDER];
    };

    struct record_t {
        key_t key;
        value_t value;
        bool operator<(const key_t& rhs) {
            return BplusTree::keyCmp(key, rhs) < 0;
        }
        
        bool operator==(const key_t& rhs) {
            return BplusTree::keyCmp(key, rhs) == 0;
        }
    };

    struct leaf_node_t {
        typedef record_t* child_t;
        off_t parent;
        off_t next;
        off_t prev;
        size_t n;
        record_t children[BP_ORDER];
    };

public:
    BplusTree(std::string path, bool forceEmpty=false);
    meta_t getMeta() { return m_meta; }

    //查找
    /* find index */
    off_t search_index(const key_t &key);
    /* find leaf */
    off_t search_leaf(off_t index, const key_t& key);
    off_t search_leaf(const key_t& key);
    
    int search(const key_t& key, value_t *value);
    
    //插入
    /* insert into leaf without split */
    void insert_record_no_split(leaf_node_t *leaf, const key_t &key, const value_t &value);
    
    /* change children's parent */
    void reset_index_children_parent(index_t *begin, index_t *end, off_t parent);
        
    template<class T>
    void node_create(off_t offset, T *node, T *next);
    
    /* add key to the internal node */
    void insert_key_to_index(off_t offset, const key_t &key, off_t old, off_t after);
    void insert_key_to_index_no_split(internal_node_t &node, const key_t &key, off_t value);

    int insert(const key_t& key, value_t value);
    
    //删除
    void remove_from_index(off_t offset, internal_node_t &node, const key_t &key);
    
    /* borrow one key from other internal node */
    bool borrow_key(bool from_right, internal_node_t &borrower, off_t offset);
    
    /* borrow one record from other leaf */
    bool borrow_key(bool from_right, leaf_node_t &borrower);
    
    /* change one's parent key to another key */
    void change_parent_child(off_t parent, const key_t& o, const key_t& n);

    template<class T>
    void node_remove(T *prev, T *node);

    int remove(const key_t& key);
    
private:
    template <class T>
    static typename T::child_t begin(T &node) {
        return node.children;
    }

    template <class T>
    static typename T::child_t end(T &node) {
        return node.children + node.n;
    }

    static index_t *find(internal_node_t &node, const key_t& key) {
        return std::upper_bound(begin(node), end(node) - 1, key);
    }

    static record_t *find(leaf_node_t &node, const key_t& key) {
        return std::lower_bound(begin(node), end(node), key);
    }

    //正:a > b     0:a == b    负:a < b
    static int keyCmp(const key_t& a, const key_t& b) {
        int x = strlen(a.k) - strlen(b.k);
        return x == 0 ? strcmp(a.k, b.k) : x;
    }
private:
    void open_file(std::string mode = "rb+");
    void close_file();
    void init_from_empty();

    //alloc from disk
    off_t alloc(size_t size);
    off_t alloc(leaf_node_t *leaf);
    off_t alloc(internal_node_t *node);

    //unalloc
    void unalloc(leaf_node_t *leaf, off_t offset);
    void unalloc(internal_node_t *node, off_t offset);

    //write block to disk
    template<class T>
    int unmap(T *block, off_t offset) {
        return unmap(block, offset, sizeof(T));
    }

    int unmap(void *block, off_t offset, size_t size);

    /* read block from disk */
    template<class T>
    int map(T *block, off_t offset) {
        return map(block, offset, sizeof(T));
    }

    int map(void *block, off_t offset, size_t size);


private:
    std::string m_path;
    meta_t m_meta;
    FILE *m_fp;
    int m_fpLevel;
};

}

#endif
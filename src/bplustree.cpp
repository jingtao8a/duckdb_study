#include "../include/bplustree.hpp"
#include <assert.h>

namespace BPLUSTREE{

//正:a > b     0:a == b    负:a < b
static int keyCmp(const BplusTree::key_t& a, const BplusTree::key_t& b) {
    int x = strlen(a.k) - strlen(b.k);
    return x == 0 ? strcmp(a.k, b.k) : x;
}

#define OPERATOR_KEYCMP(type) \
    bool operator< (const BplusTree::key_t &l, type r) {\
        return keyCmp(l, r.key) < 0;\
    }\
    bool operator< (type l, const BplusTree::key_t &r) {\
        return keyCmp(l.key, r) < 0;\
    }\
    bool operator== (const BplusTree::key_t &l, type r) {\
        return keyCmp(l, r.key) == 0;\
    }\
    bool operator== (type l, const BplusTree::key_t &r) {\
        return keyCmp(l.key, r) == 0;\
    }


OPERATOR_KEYCMP(BplusTree::index_t);
OPERATOR_KEYCMP(BplusTree::record_t);

BplusTree::index_t *BplusTree::find(internal_node_t &node, const key_t& key) {
    return std::upper_bound(begin(node), end(node) - 1, key);
}

BplusTree::record_t *BplusTree::find(leaf_node_t &node, const key_t& key) {
    return std::lower_bound(begin(node), end(node), key);
}

BplusTree::BplusTree(std::string path, bool forceEmpty) 
    :m_path(path), m_fp(NULL), m_fpLevel(0) {
    if (!forceEmpty) {
        if (map(&m_meta, OFFSET_META) != 0) {//将文件中的meta数据读出来
            forceEmpty = true;//meta数据不存在，强制清空
        }
    }
    if (forceEmpty) {
        open_file("w+");
        init_from_empty();
        close_file();
    }
}

void BplusTree::init_from_empty() {
    bzero(&m_meta, sizeof(meta_t));
    m_meta.order = BP_ORDER;//B+树的度
    m_meta.value_size = sizeof(value_t);
    m_meta.key_size = sizeof(key_t);
    m_meta.height = 1;//B+树的高度为1
    m_meta.slot = OFFSET_BLOCK;

//init root node
    internal_node_t root;
    root.next = root.prev = root.parent = 0;
    root.n = 0;
    m_meta.root_offset = alloc(&root);

//init empty leaf
    leaf_node_t leaf;
    leaf.next = leaf.prev = 0;
    leaf.n = 0;
    leaf.parent = m_meta.root_offset;
    m_meta.leaf_offset = root.children[0].child = alloc(&leaf);

//save
    unmap(&m_meta, OFFSET_META);
    unmap(&root, m_meta.root_offset);
    unmap(&leaf, root.children[0].child);
}

//查找
off_t BplusTree::search_index(const key_t &key) {
    off_t org = m_meta.root_offset;
    int height = m_meta.height;
    while (height > 1) {
        internal_node_t internalNode;
        map(&internalNode, org);

        index_t *i = find(internalNode, key);
        org = i->child;
        --height;
    }
    return org;
}

off_t BplusTree::search_leaf(off_t index, const key_t& key) {
    internal_node_t internalNode;
    map(&internalNode, index);
    index_t *i = find(internalNode, key);
    return i->child;
}

off_t BplusTree::search_leaf(const key_t& key) {
    return search_leaf(search_index(key), key);
}

int BplusTree::search(const key_t& key, value_t *value) {
    leaf_node_t leaf;
    map(&leaf, search_leaf(key));
    record_t *record = find(leaf, key);
    if (record != end(leaf)) {
        *value = record->value;
        return keyCmp(record->key, key);//这个值为0时表示查找成功，其它均为失败
    }
    return -1;
}
//插入
void BplusTree::reset_index_children_parent(index_t *begin, index_t *end, off_t parent) {
    internal_node_t node;
    while (begin != end) {
        map(&node, begin->child);
        node.parent = parent;
        unmap(&node, begin->child, SIZE_NO_CHILDREN);
        ++begin;
    }
}

/* add key to the internal node */
void BplusTree::insert_key_to_index(off_t offset, const key_t &key, off_t old, off_t after) {
    if (offset == 0) {
        internal_node_t root;
        root.n = 2;
        root.next = root.prev = root.parent = 0;
        root.children[0].key = key;
        root.children[0].child = old;
        root.children[1].child = after;

        m_meta.root_offset = alloc(&root);
        m_meta.height++;//B+树高度加1

        unmap(&m_meta, OFFSET_META);
        unmap(&root, m_meta.root_offset);
        // update children's parent
        reset_index_children_parent(begin(root), end(root), m_meta.root_offset);
        return;
    }
    internal_node_t node;
    map(&node, offset);
    if (node.n == m_meta.order) {
        //split when full
        internal_node_t new_node;
        node_create(offset, &node, &new_node);

        //find even split point
        size_t point = (node.n - 1) / 2;
        bool place_right = keyCmp(key, node.children[point].key) > 0;
        if (place_right) {
            ++point;
            //prevent the 'key' begin the right 'middle key'
            if (keyCmp(key, node.children[point].key) < 0) {
                --point;
            }
        }

        key_t middle_key = node.children[point].key;//这个key将不存在于node和new_node中了

        //split
        std::copy(begin(node) + point + 1, end(node), end(new_node));
        new_node.n = node.n - point - 1;
        node.n = point + 1;

        //put the new key
        if (place_right) {
            insert_key_to_index_no_split(new_node, key, after);
        } else {
            insert_key_to_index_no_split(node, key, after);
        }


        unmap(&node, offset);
        unmap(&new_node, node.next);

        // update children's parent
        reset_index_children_parent(begin(new_node), end(new_node), node.next);
        //given the middle key to the parent
        insert_key_to_index(node.parent, middle_key, offset, node.next);
    } else {
        insert_key_to_index_no_split(node, key, after);
        unmap(&node, offset);
    }
}

void BplusTree::insert_key_to_index_no_split(internal_node_t &node, const key_t& key, off_t after) {
    index_t *where = find(node, key);
    std::copy_backward(where, end(node), end(node) + 1);

    where->key = key;
    where->child = (where + 1)->child;
    (where + 1)->child = after;
    node.n++;
}

template<class T>
void BplusTree::node_create(off_t offset, T *node, T *next) {
    //new sibling node
    next->parent = node->parent;   
    next->next = node->next;
    next->prev = offset;
    node->next = alloc(next);
    if (next->next != 0) {
        T old_next;
        map(&old_next, next->next, SIZE_NO_CHILDREN);
        old_next.prev = node->next;
        unmap(&old_next, next->next, SIZE_NO_CHILDREN);
    }
    unmap(&m_meta, OFFSET_META);
}

/* insert into leaf without split */
void BplusTree::insert_record_no_split(leaf_node_t *leaf, const key_t &key, const value_t &value) {
    record_t *where = find(*leaf, key);
    std::copy_backward(where, end(*leaf), end(*leaf) + 1);
    where->key = key;
    where->value = value;
    leaf->n++;
}

int BplusTree::insert(const key_t& key, value_t value) {
    off_t parent = search_index(key);
    off_t offset = search_leaf(parent, key);
    leaf_node_t leaf;
    map(&leaf, offset);

    //check if we have the same key
    if (std::binary_search(begin(leaf), end(leaf), key)) {
        return 1;
    }

    if (leaf.n == m_meta.order) {
        //split when full
        //new sibling leaf
        leaf_node_t new_leaf;
        node_create(offset, &leaf, &new_leaf);
        //find even split point
        size_t point = leaf.n / 2;
        bool place_right = keyCmp(key, leaf.children[point].key) > 0;
        if (place_right) {
            point++;
        }

        std::copy(begin(leaf) + point, end(leaf), begin(new_leaf));

        new_leaf.n = leaf.n - point;
        leaf.n = point;
        if (place_right) {
            insert_record_no_split(&new_leaf, key, value);
        } else {
            insert_record_no_split(&leaf, key, value);
        }

        //save leafs
        unmap(&leaf, offset);
        unmap(&new_leaf, leaf.next);

        //insert new index key
        insert_key_to_index(parent, begin(new_leaf)->key, offset, leaf.next);
    } else {
        insert_record_no_split(&leaf, key, value);
        unmap(&leaf, offset);
    }
    return 0;
}



//删除
bool BplusTree::borrow_key(bool from_right, internal_node_t &borrower, off_t offset) {
    off_t lender_off = from_right ? borrower.next : borrower.prev;
    internal_node_t lender;
    map(&lender, lender_off);

    assert(lender.n >= m_meta.order / 2);
    if (lender.n != m_meta.order / 2) {//可以borrow
        index_t *where_to_lend, *where_to_put;
        internal_node_t parent;

        if (from_right) {
            where_to_lend = begin(lender);
            where_to_put = end(borrower);

            map(&parent, borrower.parent);
            index_t *where = std::lower_bound(begin(parent), end(parent) - 1, (end(borrower) - 1)->key);
            where->key = where_to_lend->key;
            unmap(&parent, borrower.parent);
        } else {
            where_to_lend = end(lender) - 1;
            where_to_put = begin(borrower);
            
            map(&parent, lender.parent);
            index_t *where = find(parent, begin(lender)->key);
            where_to_put->key = where->key;
            where->key = (where_to_lend - 1)->key;
            unmap(&parent, lender.parent);
        }
        //store
        std::copy_backward(where_to_put, end(borrower), end(borrower) + 1);
        *where_to_put = *where_to_lend;
        borrower.n++;
        
        //erase
        reset_index_children_parent(where_to_lend, where_to_lend + 1, offset);
        std::copy(where_to_lend + 1, end(lender), where_to_lend);
        lender.n--;
        unmap(&lender, lender_off);
        return true;
    }
    return false;
}

void BplusTree::remove_from_index(off_t offset, internal_node_t &node, const key_t &key) {
    size_t min_n = m_meta.root_offset == offset ? 1 : m_meta.order / 2;//如果是根节点，一个node的最小key的数量为1，如果是其它node为 度 / 2
    assert(node.n >= min_n && node.n <= m_meta.order);

    //remove key
    key_t index_key = begin(node)->key;

    index_t *to_delete = find(node, key);
    (to_delete + 1)->child = to_delete->child;
    std::copy(to_delete + 1, end(node), to_delete);
    node.n--;

    if (node.n == 1 && m_meta.root_offset == offset && m_meta.internal_node_num != 1) {//这个node就是root,并且这个node已经空了
        unalloc(&node, m_meta.root_offset);
        m_meta.height--;
        m_meta.root_offset = begin(node)->child;
        unmap(&m_meta, OFFSET_META);
        return;
    }

    //merge or borrow
    if (node.n < min_n) {
        internal_node_t parent;
        map(&parent, node.parent);
        bool borrowed = false;
        if (offset != begin(parent)->child) {
            borrowed = borrow_key(false, node, offset);
        }
        if (!borrowed && offset != (end(parent) - 1)->child) {
            borrowed = borrow_key(true, node, offset);
        }

        if (!borrowed) {
            if (offset == (end(parent) - 1)->child) {
                // if leaf is last element then merge | prev | leaf |
                assert(node.prev != 0);
                internal_node_t prev;
                map(&prev, node.prev);

                // merge
                index_t *where = find(parent, begin(prev)->key);
                reset_index_children_parent(begin(node), end(node), node.prev);
                merge_keys(prev, node);
                unmap(&prev, node.prev);
            } else {
                // else merge | leaf | next |
                assert(node.next != 0);
                internal_node_t next;
                map(&next, node.next);

                // merge
                index_t *where = find(parent, index_key);
                reset_index_children_parent(begin(next), end(next), offset);
                merge_keys(node, next);
                unmap(&node, offset);
            }
        } else {
            unmap(&node, offset);
        }
    } else {
        unmap(&node, offset);
    }
}

bool BplusTree::borrow_key(bool from_right, leaf_node_t &borrower) {
    off_t lender_off = from_right ? borrower.next: borrower.prev;
    leaf_node_t lender;
    map(&lender, lender_off);

    assert(lender.n >= m_meta.order / 2);

    if (lender.n != m_meta.order / 2) {//可以borrow
        record_t *where_to_lend, *where_to_put;
        if (from_right) {
            where_to_lend = begin(lender);
            where_to_put = end(borrower);
            change_parent_child(borrower.parent, begin(borrower)->key, lender.children[1].key);
        } else {
            where_to_lend = end(lender) - 1;
            where_to_put = begin(borrower);
            change_parent_child(lender.parent, begin(lender)->key, where_to_lend->key);
        }
        //store
        std::copy_backward(where_to_put, end(borrower), end(borrower) + 1);
        *where_to_put = *where_to_lend;
        borrower.n++;

        //erase
        std::copy(where_to_lend + 1, end(lender), where_to_lend);
        lender.n--;
        unmap(&lender, lender_off);
        return true;
    }
    return false;
}

void BplusTree::change_parent_child(off_t parent, const key_t& o, const key_t& n) {
    internal_node_t node;
    map(&node, parent);
    index_t *w = find(node, o);
    assert(w != end(node));

    w->key = n;
    unmap(&node, parent);
    if (w == end(node) - 1) {
        change_parent_child(node.parent, o, n);
    }
}

template<class T>
void BplusTree::node_remove(T *prev, T *node) {
    unalloc(node, prev->next);
    prev->next = node->next;
    if (node->next != 0) {
        T next;
        map(&next, node->next, SIZE_NO_CHILDREN);
        next.prev = node->prev;
        unmap(&next, node->next, SIZE_NO_CHILDREN);
    }
    unmap(&m_meta, OFFSET_META);
}

int BplusTree::remove(const key_t& key) {
    internal_node_t parent;
    leaf_node_t leaf;
    //find parent node
    off_t parent_off = search_index(key);
    map(&parent, parent_off);

    //find leaf node
    index_t *where = find(parent, key);
    off_t offset = where->child;
    map(&leaf, offset);

    //verify
    if (!std::binary_search(begin(leaf), end(leaf), key)) {//不存在这个key值
        return -1;
    }
    size_t min_n = m_meta.leaf_node_num == 1 ? 0 : m_meta.order / 2;
    assert(leaf.n >= min_n && leaf.n <= m_meta.order);

    
    //delete the key
    record_t *to_delete = find(leaf, key);
    std::copy(to_delete + 1, end(leaf), to_delete);
    leaf.n--;

    //merge or borrow
    if (leaf.n < min_n) {
        bool borrowed = false;
        if (leaf.prev != 0) {
            borrowed = borrow_key(false, leaf);
        }

        if (!borrowed && leaf.next != 0) {
            borrowed = borrow_key(true, leaf);
        }

        if (!borrowed) {
            key_t index_key;
            if (where == end(parent) - 1) {
                // if leaf is last element then merge | prev | leaf |
                assert(leaf.prev != 0);
                leaf_node_t prev;
                map(&prev, leaf.prev);
                index_key = begin(prev)->key;

                merge_leafs(&prev, &leaf);
                node_remove(&prev, &leaf);
                unmap(&prev, leaf.prev);
            } else {
                // else merge | leaf | next |
                assert(leaf.next != 0);
                leaf_node_t next;
                map(&next, leaf.next);
                index_key = begin(leaf)->key;

                merge_leafs(&leaf, &next);
                node_remove(&leaf, &next);
                unmap(&leaf, offset);
            }

            // remove parent's key
            remove_from_index(parent_off, parent, index_key);
        } else {
            unmap(&leaf, offset);
        }
    } else {
        unmap(&leaf, offset);
    }
    return 0;
}


void BplusTree::merge_leafs(leaf_node_t *left, leaf_node_t *right) {
    std::copy(begin(*right), end(*right), end(*left));
    left->n += right->n;
}

void BplusTree::merge_keys(internal_node_t &node, internal_node_t &next) {
    std::copy(begin(next), end(next), end(node));
    node.n += next.n;
    node_remove(&node, &next);
}


void BplusTree::open_file(std::string mode) {
    if (m_fpLevel == 0) {
        m_fp = fopen(m_path.c_str(), mode.c_str());
    }
    ++m_fpLevel;
}

void BplusTree::close_file() {
    --m_fpLevel;
    if (m_fpLevel == 0) {
        fclose(m_fp);
        m_fp = NULL;
    }
}

//alloc from disk
off_t BplusTree::alloc(size_t size) {
    off_t slot = m_meta.slot;
    m_meta.slot += size;
    return slot;
}

off_t BplusTree::alloc(leaf_node_t *leaf) {
    leaf->n = 0;
    m_meta.leaf_node_num++;
    return alloc(sizeof(leaf_node_t)); 
}

off_t BplusTree::alloc(internal_node_t *node) {
    node->n = 1;
    m_meta.internal_node_num++;
    return alloc(sizeof(internal_node_t));
}

//unalloc
void BplusTree::unalloc(leaf_node_t *leaf, off_t offset) {
    --m_meta.leaf_node_num;
}

void BplusTree::unalloc(internal_node_t *node, off_t offset) {
    --m_meta.internal_node_num;
}

//write block to disk
int BplusTree::unmap(void *block, off_t offset, size_t size) {
    open_file();
    fseek(m_fp, offset, SEEK_SET);
    size_t wd = fwrite(block, size, 1, m_fp);
    close_file();
    return wd - 1;
}

/* read block from disk */
int BplusTree::map(void *block, off_t offset, size_t size) {
    open_file();
    fseek(m_fp, offset, SEEK_SET);
    size_t rd = fread(block, size, 1, m_fp);
    close_file();
    return rd - 1;
}


}
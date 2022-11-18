#include "../include/bplustree.hpp"

namespace BPLUSTREE{

BplusTree::BplusTree(std::string path, bool forceEmpty) 
    :m_path(path), m_fp(NULL), m_fpLevel(0) {
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
    m_meta.root_offset = alloc(&root);

//init empty leaf
    leaf_node_t leaf;
    leaf.next = leaf.prev = 0;
    leaf.parent = m_meta.root_offset;
    m_meta.leaf_offset = root.children[0].child = alloc(&leaf);

//save
    unmap(&m_meta, OFFSET_META);
    unmap(&root, m_meta.root_offset);
    unmap(&leaf, root.children[0].child);
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
#ifndef DUCKDBMS_HPP
#define DUCKDBMS_HPP

#include "bplustree.hpp"
#include <memory>

class DuckDBMS{
public:
    DuckDBMS();

private:
    static void printHelpMess();

    static void intToKeyT(BPLUSTREE::BplusTree::key_t *a,int *b);
    
    static bool is_file_exist(const char *fileName);

    static void printTable(int *index, BPLUSTREE::BplusTree::value_t *values);

private:
    void initialSystem();

    void selectCommand();

    int insertRecord(int *key, BPLUSTREE::BplusTree::value_t *values);
    
    int deleteRecord(int *index);
    
    int searchRecord(int *index, BPLUSTREE::BplusTree::value_t *return_val);
    
    void searchAll(int *i_start, int *i_end);
    
    int updateRecord(int *key, BPLUSTREE::BplusTree::value_t *values);
    
private:
    std::shared_ptr<BPLUSTREE::BplusTree> m_duck_db_ptr;
};

#endif
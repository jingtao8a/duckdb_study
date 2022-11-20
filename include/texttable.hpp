#ifndef TEXTTABLE_HPP
#define TEXTTABLE_HPP

#include <iostream>
#include <map>
#include <iomanip>
#include <vector>
#include <string>

class TextTable {
public:
    enum class Alignment { LEFT, RIGHT }; //对齐方式向左或向右对齐
    friend std::ostream & operator<<( std::ostream & stream, const TextTable& table );

private:  
    template <typename Iterator>
    void addRow(Iterator begin, Iterator end) {
        for(auto i = begin; i != end; ++i) {
           add( * i ); 
        }
        endOfRow();
    }

    template <typename Container>
    void addRow(const Container& container ) {
        addRow(container.begin(), container.end());
    }

public:
    void add(const std::string& content );

    void endOfRow();

//setter and getter
    void setAlignment( unsigned i, Alignment alignment ) {
        m_alignment[ i ] = alignment;
    }

    Alignment getAlignment(unsigned i) const{ //获取某一列的对齐机制
        return m_alignment[i];
    }

    int getWidth( unsigned i ) const{//获取某一列的宽度
        return m_width[ i ]; 
    }
    
    char getVertical() const{ 
        return m_vertical; 
    }

    char getHorizontal() const{ 
        return m_horizontal;
    }

    std::vector<std::vector<std::string> >& getRows() const{
        return m_rows;
    }

    unsigned getColumns() const{//获取列数
        return m_rows[ 0 ].size();
    }
private:
    void setup() const;
    void determineWidths() const;
    void setupAlignment() const;

    std::string ruler() const;

    static std::string repeat( unsigned times, char c );

private:
    char m_horizontal = '-';
    char m_vertical = '|';
    char m_corner = '+';
    std::vector<std::string> m_current;
    mutable std::vector<std::vector<std::string> > m_rows;
    mutable std::vector< unsigned > m_width;//每一列的宽度
    mutable std::map<unsigned, Alignment > m_alignment;
};

std::ostream & operator<<( std::ostream & stream, const TextTable& table );


#endif
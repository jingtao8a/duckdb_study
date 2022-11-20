#include "../include/texttable.hpp"
#include <algorithm>

void TextTable::add(const std::string& content ) {
    m_current.push_back(content);
}

void TextTable::endOfRow() {
    m_rows.push_back( m_current );
    m_current.clear();
}

std::string TextTable::ruler() const{
    std::string result;
    result += m_corner;
    for( auto width = m_width.begin(); width != m_width.end(); ++ width ) {
        result += repeat( *width, m_horizontal);
        result += m_corner;
    }

    return result;
}

//静态成员函数
std::string TextTable::repeat( unsigned times, char c ) {
    std::string result;
    while (times--) {
        result += c;
    }
    return result;
}

void TextTable::setup() const{
    determineWidths();
    setupAlignment();
}

void TextTable::determineWidths() const{
    m_width.assign(getColumns(), 0 );
    for ( auto rowIterator = m_rows.begin(); rowIterator != m_rows.end(); ++ rowIterator ) {
        std::vector<std::string>& row = *rowIterator;
        for ( unsigned i = 0; i < row.size(); ++i ) {
            m_width[ i ] = std::max(m_width[ i ], (unsigned)row[ i ].size());
        }
    }
}

void TextTable::setupAlignment() const{
    for ( unsigned i = 0; i < getColumns(); ++i ) {
        if ( m_alignment.find( i ) == m_alignment.end() ) {
            m_alignment[ i ] = Alignment::LEFT;//默认每一列向左对齐
        }
    }
}

//全局函数
std::ostream & operator<<(std::ostream & stream, const TextTable & table ) {
    table.setup();
    stream << table.ruler() << "\n";
    for ( auto rowIterator = table.getRows().begin(); rowIterator != table.getRows().end(); ++ rowIterator ) {
        std::vector<std::string> const & row = * rowIterator;
        stream << table.getVertical();
        for ( unsigned i = 0; i < row.size(); ++i ) {
            auto alignment = table.getAlignment( i ) == TextTable::Alignment::LEFT ? std::left : std::right;
            stream << std::setw( table.getWidth( i ) ) << alignment << row[ i ];
            stream << table.getVertical();
        }
        stream << "\n";
        stream << table.ruler() << "\n";
    }

    return stream;
}



#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include "Spliter.h"
#include <string>
#include <vector>

namespace buf
{

class Tokenizer
{
public:
    typedef std::string value_type;
    typedef std::vector<value_type> container;
    typedef container::size_type size_type;

public:
    Tokenizer(const char* tokens, char sp)
    {
        if (tokens)
            split(m_toks, tokens, sp);
    }

    Tokenizer(const char* tokens, const char* sp)
    {
        if (tokens && sp)
            split(m_toks, tokens, sp);
    }

    Tokenizer(const std::string& tokens, char sp)
    {
        if (tokens.length())
            split(m_toks, tokens, sp);
    }

    Tokenizer(const std::string& tokens, const std::string& sp)
    {
        if (tokens.length() && sp.length())
            split(m_toks, tokens, sp);
    }

    Tokenizer(const Tokenizer& tk) : m_toks(tk.m_toks) {}
    ~Tokenizer() { clear(); }

    inline size_type size() const { return m_toks.size(); }
    inline void clear() { m_toks.clear(); }
    inline void pop_front() { m_toks.erase(m_toks.begin()); }

    Tokenizer& operator=(const Tokenizer& tk)
    {
        m_toks = tk.m_toks;
        return *this;
    }

    const value_type& operator[](size_type i) const
    {
        if (i < m_toks.size())
            return m_toks[i];

        static std::string null = "";
        return null;
    }

    value_type& operator[](size_type i)
    {
        if (i < m_toks.size())
            return m_toks[i];

        static std::string null = "";
        return null;
    }

private:
    container m_toks;
};

} // namespace buf

using namespace buf;

#endif // TOKENIZER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */


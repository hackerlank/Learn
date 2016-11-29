
#ifndef BUFFER_H_
#define BUFFER_H_

#include "Platform.h"
#include "BufferBase.h"
#include <vector>
#include <string>

namespace buf
{

namespace cstr
{
    const unsigned char end = '\0';
} // namespace cstr

class MemReader;
class Buffer;

class BufferMem : public BufferBase
{
public:
    typedef UINT8 value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

public:
    BufferMem(size_type size, size_type curr = 0, size_type off = 0)
        : BufferBase(size, curr, off) {}

    inline bool checksize(size_type size) { return (wsize() >= size); }

protected:
    pointer _data;
};

template <size_t SIZE = TRUNK_SIZE>
class BufferStack : public BufferBase
{
public:
    typedef UINT8 value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;

public:
    BufferStack(size_type size, size_type curr = 0, size_type off = 0)
        : BufferBase(size, curr, off) {}

    inline bool checksize(size_type size) { return (wsize() >= size); }

protected:
    value_type _data[SIZE];
};

class BufferContainer : public BufferBase
{
public:
    typedef std::vector<UINT8> container;
    typedef container::pointer pointer;
    typedef container::const_pointer const_pointer;
    typedef container::value_type value_type;

public:
    BufferContainer(size_type size, size_type curr = 0, size_type off = 0)
        : BufferBase(size, curr, off), _data(size) {}

    inline bool checksize(size_type size)
    {
        resize(size);
        return true;
    }

    inline void resize(size_type size)
    {
        if (wsize() < size + 8)
        {
            unsigned int nsize = max() + TRUNK_SIZE * ((TRUNK_SIZE+size+8)/TRUNK_SIZE);
            _data.resize(nsize, 0); // XXX: &_data[N]
            _max = nsize;
        }
    }

protected:
    container _data;
};

template <typename T = BufferContainer>
class BufferReader : public T
{
public:
    typedef typename T::size_type size_type;
    typedef typename T::value_type value_type;
    typedef typename T::const_pointer const_pointer;
    typedef typename T::pointer pointer;

protected:
    using T::_data;
    using T::_off;
    using T::_curr;
    using T::_max;
    using T::_outofdata;

    using T::rsize;
    using T::wsize;
    using T::empty;
    using T::clear;

public:
    BufferReader(size_type size, size_type curr = 0, size_type off = 0) : T(size, curr, off) {}

    // XXX: you do not save the value returned by rbuf and wbuf
    // XXX: rbuf and wbuf will be used as function but not inline
    inline const_pointer rbuf() const { return &_data[_off]; }
    inline pointer rbuf() { return &_data[_off]; }

    inline const_pointer wbuf() const { return &_data[_curr]; }
    inline pointer wbuf() { return &_data[_curr]; }

    inline char* c_rbuf() { return reinterpret_cast<char*>(&_data[_off]); }
    inline char* c_wbuf() { return reinterpret_cast<char*>(&_data[_curr]); }

    inline const char* c_rbuf() const { return reinterpret_cast<const char*>(&_data[_off]); }
    inline const char* c_wbuf() const { return reinterpret_cast<const char*>(&_data[_curr]); }

    BufferReader& read(void* v, size_type c, size_type* got = NULL)
    {
        if (!rsize())
        {
            _outofdata = true;
            return *this;
        }

        if (rsize() >= c)
        {
            _outofdata = false;
            MEMCPY(v, &_data[_off], c);
            _off += c;
            if (got)
                *got = c;
        }
        else
        {
            _outofdata = true;
            MEMCPY(v, &_data[_off], rsize());
            _off = _curr;
            if (got)
                *got = _curr - _off;
        }
        return *this;
    }

#define READ(t, v)                                      \
        if (rsize() >= sizeof(v))                       \
        {                                               \
            _outofdata = false;                         \
            v = *reinterpret_cast<t*>(&_data[_off]);    \
            _off += sizeof(v);                          \
            if (got)                                    \
                *got = true;                            \
        }                                               \
        else                                            \
            _outofdata = true;                          \
        return *this; 

    BufferReader& read(bool& v, bool* got = NULL) { READ(bool, v); }
    BufferReader& read(char& v, bool* got = NULL) { READ(char, v); }
    BufferReader& read(unsigned char& v, bool* got = NULL) { READ(unsigned char, v); }
    BufferReader& read(short& v, bool* got = NULL) { READ(short, v); }
    BufferReader& read(unsigned short& v, bool* got = NULL) { READ(unsigned short, v); }
    BufferReader& read(int& v, bool* got = NULL) { READ(int, v); }
    BufferReader& read(unsigned int& v, bool* got = NULL) { READ(unsigned int, v); }
    BufferReader& read(long& v, bool* got = NULL) { READ(long, v); }
    BufferReader& read(unsigned long& v, bool* got = NULL) { READ(unsigned long, v); }
    BufferReader& read(long long& v, bool* got = NULL) { READ(long long, v); }
    BufferReader& read(unsigned long long& v, bool* got = NULL) { READ(unsigned long long, v); }
    BufferReader& read(float& v, bool* got = NULL) { READ(float, v); }
    BufferReader& read(double& v, bool* got = NULL) { READ(double, v); }
    BufferReader& read(long double& v, bool* got = NULL) { READ(long double, v); }

#undef READ

    inline const value_type& at(size_type i) const
    {
        if (i+_off >= _max)
        {
            static value_type t;
            return t;
        }
        return *&_data[i+_off];
    }

    // XXX: DANGEROUS!!! YOU MUST KNOW WHAT YOR ARE DOING
#if defined(CXX0X) && CXX0X
    template <typename U = value_type>
#else
    template <typename U>
#endif
    inline const U& at(size_type i = 0) const
    {
        if (i+_off >= _max || (wsize() < sizeof(U))) // XXX:
        {
            static U u;
            return u;
        }
        return *reinterpret_cast<U*>(&_data[i+_off]);
    }

    inline const value_type& operator[](size_type i) const
    {
        if (i+_off >= _max)
        {
            static value_type t;
            return t;
        }
        return *&_data[i+_off];
    }

    // XXX: wflip in BufferBase
    void rflip(size_type size = 0)
    {
        _off += size;
        if (_off < _curr)
        {
            if (_off)
            {
                size_type c = _curr - _off;
                MEMCPY(&_data[0], &_data[_off], c);
                _off = 0;
                _curr = c;
            }
        }
        else
        {
            _off = _curr = 0;
        }
    }
};

template <typename T = BufferContainer>
class BufferWriter : public BufferReader<T>
{
public:
    typedef BufferReader<T> Base;

    typedef typename T::size_type size_type;
    typedef typename T::value_type value_type;
    typedef typename T::const_pointer const_pointer;
    typedef typename T::pointer pointer;

public:
    using T::_data;
    using T::_off;
    using T::_curr;
    using T::_max;

    using T::rsize;
    using T::wsize;
    using T::empty;
    using T::clear;
    using T::checksize;

    using Base::rbuf;
    using Base::wbuf;

public:
    BufferWriter(size_type size, size_type curr = 0, size_type off = 0)
        : BufferReader<T>(size, curr, off) {}

#if 0
    inline BufferWriter& operator=(const BufferWriter& buf)
    {
        if (this == &buf)
            return *this;
        clear();
        return append(buf.rbuf(), buf.rsize());
    }
#endif

    inline BufferWriter& put(const void* buf, size_type size, unsigned char lennull = 0)
    {
        return append(buf, size, lennull);
    }

    // XXX: do not call remove() frequently
    void remove(size_t s, size_t n)
    {
        if (_off+s >= _max)
            return;
        if (_off+s+n > _max)
            n = _max-s-_off;

        if (_off+s+n >= _curr)
        {
            _curr = _off+s;
        }
        else
        {
            MEMMOVE(&_data[0]+_off+s, &_data[0]+_off+s+n, n);
            _curr -= n;
        }
    }

    inline value_type& at(size_type i)
    {
        if (i+_off >= _max)
        {
            static value_type t;
            return t;
        }
        return *&_data[i+_off];
    }

    // XXX: DANGEROUS!!! YOU MUST KNOW WHAT YOR ARE DOING
#if defined(CXX0X) && CXX0X
    template <typename U = value_type>
#else
    template <typename U>
#endif
    inline U& at(size_type i = 0)
    {
        if (i+_off >= _max || (wsize() < sizeof(U))) // XXX:
        {
            static U u;
            return u;
        }
        return *reinterpret_cast<U*>(&_data[i+_off]);
    }

    // XXX: DANGEROUS!!! YOU MUST KNOW WHAT YOR ARE DOING
    inline value_type& operator[](size_type i)
    {
        if (i+_off >= _max)
        {
            static value_type t;
            return t;
        }
        return *&_data[i+_off];
    }

    BufferWriter& append(const void* buf, size_type size, unsigned char lennull = 0)
    {
        if (lennull)
        {
            size_type nsize = size;
            if (lennull & BUF_LEN) // XXX: size must be less or equal to 0xffff
            {
                if (size > 0xffff)
                    return *this;
                nsize += sizeof(strlen_t);
            }
            if (lennull & BUF_NULL)
                nsize += 1;
            if (!checksize(nsize))
                return *this;

            if (lennull & BUF_LEN)
            {
                // XXX: strlen_t to store size
                if (lennull & BUF_NULL)
                    *reinterpret_cast<strlen_t*>(&_data[_curr]) = size + 1;
                else
                    *reinterpret_cast<strlen_t*>(&_data[_curr]) = size;
                _curr += sizeof(strlen_t);
                MEMCPY(&_data[_curr], buf, size);
                _curr += size;
                if (lennull & BUF_NULL)
                    _data[_curr++] = '\0';
            }
            else if (lennull & BUF_NULL)
            {
                MEMCPY(&_data[_curr], buf, size);
                _curr += size;
                _data[_curr++] = '\0';
            }
        }
        else
        {
            if (!checksize(size))
                return *this;
            MEMCPY(&_data[_curr], buf, size);
            _curr += size;
        }
        return *this;
    }
};

class MemReader : public BufferReader<BufferMem>
{
public:
    typedef BufferReader<BufferMem> Base;
    using Base::rsize;
    using Base::wsize;
    using Base::read;

public:
    MemReader() : Base(0, 0) { _data = NULL; }

    MemReader(const_pointer data, size_type size)
        : Base(size, size)
    {
        _data = const_cast<pointer>(data);
    }

    MemReader(const void* data, size_type size)
        : Base(size, size)
    {
        _data = reinterpret_cast<pointer>(const_cast<void*>(data));
    }

    MemReader(const MemReader& mr) : Base(mr._max, mr._curr, mr._off)
    {
        _data = mr._data;
    }

    ~MemReader()
    {}

    inline MemReader& operator>>(bool& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(char& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(unsigned char& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(short& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(unsigned short& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(int& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(unsigned& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(long& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(unsigned long& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(long long& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(unsigned long long& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(float& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(double& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(long double& v) { return *reinterpret_cast<MemReader*>(&read(v)); }
    inline MemReader& operator>>(std::string& str)
    {
        strlen_t len = 0;
        read(len);
        if (len)
        {
            str.resize(len);
            read(&str[0], len);
        }
        return *this;
    }

};

MemReader& operator>>(MemReader& mr, Buffer& buf);

class MemWriter : public BufferWriter<BufferMem>
{
public:
    typedef BufferWriter<BufferMem> Base;
    using Base::rsize;
    using Base::wsize;

public:
    MemWriter() : Base(0, 0) { _data = NULL; }

    MemWriter(const_pointer data, size_type size)
        : Base(size, 0, 0)
    {
        _data = const_cast<pointer>(data);
    }

    MemWriter(const void* data, size_type size)
        : Base(size, 0, 0)
    {
        _data = reinterpret_cast<pointer>(const_cast<void*>(data));
    }

    MemWriter(const MemWriter& mw) : Base(mw._max, mw._curr, mw._off)
    {
        _data = mw._data;
    }

    ~MemWriter()
    {}

    inline MemWriter& operator>>(bool& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(char& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(unsigned char& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(short& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(unsigned short& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(int& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(unsigned& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(long& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(unsigned long& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(long long& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(unsigned long long& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(float& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(double& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(long double& v) { return *reinterpret_cast<MemWriter*>(&read(v)); }
    inline MemWriter& operator>>(std::string& str)
    {
        strlen_t len = 0;
        read(len);
        if (len)
        {
            str.resize(len);
            read(&str[0], len);
        }
        return *this;
    }

#define WRITE(t, v)                                 \
        if (!checksize(sizeof(v)))                  \
            return *this;                           \
        *reinterpret_cast<t*>(&_data[_curr]) = v;   \
        _curr += sizeof(v);                         \
        return *this;

    inline MemWriter& operator<<(bool v) { WRITE(bool, v); }
    inline MemWriter& operator<<(char v) { WRITE(char, v); }
    inline MemWriter& operator<<(unsigned char v) { WRITE(unsigned char, v); }
    inline MemWriter& operator<<(short v) { WRITE(short, v); }
    inline MemWriter& operator<<(unsigned short v) { WRITE(unsigned short, v); }
    inline MemWriter& operator<<(int v) { WRITE(int, v); }
    inline MemWriter& operator<<(unsigned int v) { WRITE(unsigned int, v); }
    inline MemWriter& operator<<(long v) { WRITE(long, v); }
    inline MemWriter& operator<<(unsigned long v) { WRITE(unsigned long, v); }
    inline MemWriter& operator<<(long long v) { WRITE(long long, v); }
    inline MemWriter& operator<<(unsigned long long v) { WRITE(unsigned long long, v); }
    inline MemWriter& operator<<(float v) { WRITE(float, v); }
    inline MemWriter& operator<<(double v) { WRITE(double, v); }
    inline MemWriter& operator<<(long double v) { WRITE(long double, v); }

#undef WRITE

    // XXX: save as [length][str]
    inline MemWriter& operator<<(const char* str)
    {
        if (!str)
            return *this;
        strlen_t len = strlen(str);
        return *reinterpret_cast<MemWriter*>(&append(str, len, BUF_LEN));
    }

    inline MemWriter& operator<<(const std::string& str)
    {
        return (*this)<<(str.c_str());
    }

};

MemWriter& operator>>(MemWriter& mr, Buffer& buf);

class Buffer : public BufferWriter<BufferContainer>
{
public:
    typedef BufferWriter<BufferContainer> Base;
    using Base::read;
    using Base::append;

public:
    Buffer(size_type SIZE = DEFAULT_BUFFER_SIZE)
        : Base(SIZE)
    {}

    Buffer(const Buffer& b)
        : Base(b._max, b._curr, b._off)
    {
        MEMCPY(&_data[0], &b._data[0], _curr);
    }

    Buffer(const void* data, size_type size)
        : Base(DEFAULT_BUFFER_SIZE>size?DEFAULT_BUFFER_SIZE:size, size)
    {
        MEMCPY(&_data[0], data, _curr);
    }


    ~Buffer()
    {
        clear();
    }

    inline Buffer& operator>>(bool& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(char& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(unsigned char& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(short& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(unsigned short& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(int& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(unsigned& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(long& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(unsigned long& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(long long& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(unsigned long long& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(float& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(double& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(long double& v) { return *reinterpret_cast<Buffer*>(&read(v)); }
    inline Buffer& operator>>(std::string& str)
    {
        strlen_t len = 0;
        read(len);
        if (len)
        {
            str.resize(len);
            read(&str[0], len);
        }
        return *this;
    }

#define WRITE(t, v)                                 \
        if (!checksize(sizeof(v)))                  \
            return *this;                           \
        *reinterpret_cast<t*>(&_data[_curr]) = v;   \
        _curr += sizeof(v);                         \
        return *this;

    inline Buffer& operator<<(bool v) { WRITE(bool, v); }
    inline Buffer& operator<<(char v) { WRITE(char, v); }
    inline Buffer& operator<<(unsigned char v) { WRITE(unsigned char, v); }
    inline Buffer& operator<<(short v) { WRITE(short, v); }
    inline Buffer& operator<<(unsigned short v) { WRITE(unsigned short, v); }
    inline Buffer& operator<<(int v) { WRITE(int, v); }
    inline Buffer& operator<<(unsigned int v) { WRITE(unsigned int, v); }
    inline Buffer& operator<<(long v) { WRITE(long, v); }
    inline Buffer& operator<<(unsigned long v) { WRITE(unsigned long, v); }
    inline Buffer& operator<<(long long v) { WRITE(long long, v); }
    inline Buffer& operator<<(unsigned long long v) { WRITE(unsigned long long, v); }
    inline Buffer& operator<<(float v) { WRITE(float, v); }
    inline Buffer& operator<<(double v) { WRITE(double, v); }
    inline Buffer& operator<<(long double v) { WRITE(long double, v); }

#undef WRITE

    // XXX: save as [length][str]
    inline Buffer& operator<<(const char* str)
    {
        if (!str)
            return *this;
        strlen_t len = strlen(str);
        return *reinterpret_cast<Buffer*>(&append(str, len, BUF_LEN));
    }

    inline Buffer& operator<<(const std::string& str)
    {
        return (*this)<<(str.c_str());
    }


};

Buffer& operator>>(Buffer& sbuf, Buffer& buf);
Buffer& operator<<(Buffer& sbuf, const MemReader& mr);
Buffer& operator<<(Buffer& sbuf, const Buffer& buf);

template<size_t SIZE = TRUNK_SIZE>
class StackBuffer : public BufferWriter<BufferStack<SIZE> >
{
public:
    typedef BufferWriter<BufferStack<SIZE> > Base;
    typedef typename Base::size_type size_type;
    typedef typename Base::value_type value_type;
    typedef typename Base::const_pointer const_pointer;
    typedef typename Base::pointer pointer;

public:
    using Base::_data;
    using Base::_off;
    using Base::_curr;
    using Base::_max;

    using Base::rsize;
    using Base::wsize;
    using Base::append;
    using Base::read;
    using Base::checksize;

public:

    StackBuffer() : Base(SIZE)
    {}

    StackBuffer(const StackBuffer& sb) : Base(SIZE)
    {
        append(sb._data, sb.rsize()>wsize()?wsize():sb.rsize());
    }

    StackBuffer(const void* data, size_type size) : Base(SIZE)
    {
        append(data, size>wsize()?wsize():size);
    }

    ~StackBuffer()
    {}

#define WRITE(t, v)                                 \
        if (!checksize(sizeof(v)))                  \
            return *this;                           \
        *reinterpret_cast<t*>(&_data[_curr]) = v;   \
        _curr += sizeof(v);                         \
        return *this;

    inline StackBuffer<SIZE>& operator<<(bool v) { WRITE(bool, v); }
    inline StackBuffer<SIZE>& operator<<(char v) { WRITE(char, v); }
    inline StackBuffer<SIZE>& operator<<(unsigned char v) { WRITE(unsigned char, v); }
    inline StackBuffer<SIZE>& operator<<(short v) { WRITE(short, v); }
    inline StackBuffer<SIZE>& operator<<(unsigned short v) { WRITE(unsigned short, v); }
    inline StackBuffer<SIZE>& operator<<(int v) { WRITE(int, v); }
    inline StackBuffer<SIZE>& operator<<(unsigned int v) { WRITE(unsigned int, v); }
    inline StackBuffer<SIZE>& operator<<(long v) { WRITE(long, v); }
    inline StackBuffer<SIZE>& operator<<(unsigned long v) { WRITE(unsigned long, v); }
    inline StackBuffer<SIZE>& operator<<(long long v) { WRITE(long long, v); }
    inline StackBuffer<SIZE>& operator<<(unsigned long long v) { WRITE(unsigned long long, v); }
    inline StackBuffer<SIZE>& operator<<(float v) { WRITE(float, v); }
    inline StackBuffer<SIZE>& operator<<(double v) { WRITE(double, v); }
    inline StackBuffer<SIZE>& operator<<(long double v) { WRITE(long double, v); }

#undef WRITE

    inline StackBuffer<SIZE>& operator>>(char& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(unsigned char& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(short& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(unsigned short& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(int& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(unsigned& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(long& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(unsigned long& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(long long& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(unsigned long long& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(float& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(double& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(long double& v) { return *reinterpret_cast<StackBuffer<SIZE>*>(&read(v)); }
    inline StackBuffer<SIZE>& operator>>(std::string& str)
    {
        strlen_t len = 0;
        read(len);
        if (len)
        {
            str.resize(len);
            read(&str[0], len);
        }
        return *this;
    }
};

} // namespace buf

#endif // BUFFER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */


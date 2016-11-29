
#ifndef BUFFERBASE_H_
#define BUFFERBASE_H_

#include "Platform.h"
#include "Noncopyable.h"

namespace buf
{

#define BUF_LEN  0x1
#define BUF_NULL 0x2

class BufferBase// : public Noncopyable
{
public:
    typedef unsigned int size_type;

public:
    BufferBase(size_type size, size_type curr = 0, size_type off = 0)
        : _curr(curr), _off(off), _max(size), _outofdata(false) {}
    ~BufferBase() {}

    inline size_type rsize() const { return _curr - _off; }
    inline size_type wsize() const { return _max - _curr; }

    inline bool empty() const { return _curr == _off; }
    inline void clear() { _off = _curr = 0; }

    // XXX: DANGEROUS, YOU MUST KNOW WHAT YOU ARE DOING
    inline void wflip(size_type size)
    {
        _curr += size;
        if (_curr > _max)
            _curr = _max;
    }

    inline void rflip_silence(size_type size)
    {
        _off += size;
        if (_off >= _curr)
        {
            _off = _curr;
            _outofdata = true;
        }
    }

    inline size_type curr() const { return _curr; }
    inline size_type off() const { return _off; }
    inline size_type max() const { return _max; }

    inline bool isOutOfData() const { return _outofdata; }

protected:
    size_type _curr;
    size_type _off;
    size_type _max;
    bool _outofdata;
};

} // namespace buf

#endif // BUFFERBASE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */


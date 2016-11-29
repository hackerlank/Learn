
#ifndef NONCOPYABLE_H_
#define NONCOPYABLE_H_

namespace buf
{

class Noncopyable
{
protected:
    Noncopyable() {}
    ~Noncopyable() {}

private:
    Noncopyable(const Noncopyable&);
    Noncopyable& operator=(const Noncopyable&);
};

} // namespace buf

#endif // NONCOPYABLE_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */


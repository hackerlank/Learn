
#ifndef ENUMERATOR_H_
#define ENUMERATOR_H_

/**
 *  TODO: When I is map<K, V>::iterator, you should define
 *        a subclass of each with T = map<K, V>::value_type
 **/

template <typename T>
class Enumerator
{
public:
    typedef T value_type;

public:
    virtual ~Enumerator() {}
    virtual bool operator()(value_type*) { return false; } // XXX: 如果是在非const的函数里调用请实现这个函数
    virtual bool operator()(value_type&) { return false; }
    virtual bool operator()(const value_type*) const { return false; } // XXX: 如果是在const函数里调用请实现这个函数
    virtual bool operator()(const value_type&) const { return false; }
};

#endif // ENUMERATOR_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */


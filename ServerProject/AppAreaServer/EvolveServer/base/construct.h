#ifndef CONSTRUCT_H
#define CONSTRUCT_H

//缓存中构建对象
template<class T>
inline  void constructInBuffer(T *ptr)
{       
    new (static_cast<void*>(ptr)) T();
}       

#endif

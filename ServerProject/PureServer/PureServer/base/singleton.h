#ifndef SINGLETON_H
#define SINGLETON_H
#include <cstddef>
#include "head.h"
using namespace std;

class SharedPtr : public boost::enable_shared_from_this<SharedPtr>
{
    public:
        SharedPtr()
        {
        }
        virtual ~SharedPtr()
        {
        }
        boost::shared_ptr<SharedPtr> getSharedPtr()
        {
            boost::shared_ptr<SharedPtr> ptr = shared_from_this();
            return ptr;
        }
};

class DisCopy
{
    private:
        DisCopy& operator = (const DisCopy& arg);
        DisCopy(const DisCopy &arg);
    protected:
        DisCopy()
        {
        }
        ~DisCopy()
        {
        }
};

template<typename T>
class Singleton : private DisCopy
{
    private:
        static T *s_instance;
    protected:
        Singleton()
        {
        }
        ~Singleton()
        {
        }
    public:
        static T& getInstance()
        {
            if(!s_instance)
            {
                s_instance = new T();
            }
            return *s_instance;
        }
};

template<typename T> T* Singleton<T>::s_instance = NULL;

#endif



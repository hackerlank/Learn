
#ifndef UNORDEREDCONTAINER_H_
#define UNORDEREDCONTAINER_H_

#include "Config.h"
#include <string>

#if COMPILER(GCC) && (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 3)
#  include <tr1/unordered_map>
#  include <tr1/unordered_set>
#elif defined(__APPLE__) && COMPILER(GCC) && (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 2)
#  include <tr1/unordered_map>
#  include <tr1/unordered_set>
#elif COMPILER(GCC) && __GNUC__ >= 3
#  include <ext/hash_map>
#  include <ext/hash_set>
#elif COMPILER(MSVC) && (_MSC_VER > 1500 || _MSC_VER == 1500 && _HAS_TR1)   // VC9.0 SP1 and later
#  include <unordered_map>
#  include <unordered_set>
#else
#  include <hash_map>
#  include <hash_set>
#endif

#if COMPILER(MSVC) && _MSC_VER >= 1600    // VS100
#  define UNORDERED_MAP std::unordered_map
#  define UNORDERED_SET std::unordered_set
#  define UNORDERED_MULTIMAP std::unordered_multimap
#  define HASH_NAMESPACE_START namespace std {
#  define HASH_NAMESPACE_END }
#  define HASH_NAMESPACE std
#elif COMPILER(MSVC) && _MSC_VER >= 1500 && _HAS_TR1
#  define UNORDERED_MAP std::tr1::unordered_map
#  define UNORDERED_SET std::tr1::unordered_set
#  define UNORDERED_MULTIMAP std::tr1::unordered_multimap
#  define HASH_NAMESPACE_START namespace std { namespace tr1 {
#  define HASH_NAMESPACE_END } }
#  define HASH_NAMESPACE std::tr1
#elif COMPILER(MSVC) && _MSC_VER >= 1300
#  define UNORDERED_MAP stdext::hash_map
#  define UNORDERED_SET stdext::hash_set
#  define UNORDERED_MULTIMAP stdext::unordered_multimap
#  define HASH_NAMESPACE_START namespace stdext {
#  define HASH_NAMESPACE_END }
#  define HASH_NAMESPACE stdext
using stdext::hash_map;
using stdext::hash_set;
#elif COMPILER(GCC) && (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 3)
#  define UNORDERED_MAP std::tr1::unordered_map
#  define UNORDERED_SET std::tr1::unordered_set
#  define UNORDERED_MULTIMAP std::tr1::unordered_multimap
#  define HASH_NAMESPACE_START namespace std { namespace tr1 {
#  define HASH_NAMESPACE_END } }
#  define HASH_NAMESPACE std::tr1
#elif defined(__APPLE__) && COMPILER(GCC) && (__GNUC__ > 4 || __GNUC__ == 4 && __GNUC_MINOR__ >= 2)
#  define UNORDERED_MAP std::tr1::unordered_map
#  define UNORDERED_SET std::tr1::unordered_set
#  define UNORDERED_MULTIMAP std::tr1::unordered_multimap
#  define HASH_NAMESPACE_START namespace std { namespace tr1 {
#  define HASH_NAMESPACE_END } }
#  define HASH_NAMESPACE std::tr1
#elif COMPILER(GCC) && __GNUC__ >= 3
#  define UNORDERED_MAP __gnu_cxx::hash_map
#  define UNORDERED_SET __gnu_cxx::hash_set
#  define UNORDERED_MULTIMAP __gnu_cxx::unordered_multimap
#  define HASH_NAMESPACE_START namespace __gnu_cxx {
#  define HASH_NAMESPACE_END }
#  define HASH_NAMESPACE __gnu_cxx

HASH_NAMESPACE_START

template<>
class hash<unsigned long long>
{
    public:
        size_t operator()(const unsigned long long& __x) const { return (size_t)__x; }
};

template<typename T>
class hash<T*>
{
    public:
        size_t operator()(T* const& __x) const { return (size_t)__x; }
};

template<> struct hash<std::string>
{
    size_t operator()(const std::string& __x) const
    {
        return hash<const char*>()(__x.c_str());
    }
};

HASH_NAMESPACE_END

#else
#  define UNORDERED_MAP std::hash_map
#  define UNORDERED_SET std::hash_set
#  define HASH_NAMESPACE_START namespace std {
#  define HASH_NAMESPACE_END }
using std::hash_map;
using std::hash_set;
#endif

#endif // UNORDEREDCONTAINER_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */


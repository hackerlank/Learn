
#ifndef TYPETRAITS_H_
#define TYPETRAITS_H_

#include <string>

namespace buf
{

template <typename T> struct remove_pointer { typedef T type; };
template <typename T> struct remove_pointer<T*> { typedef T type; };

template <typename T> struct remove_const { typedef T type; };
template <typename T> struct remove_const<const T> { typedef T type; };

template <typename T> struct remove_pointer_const { typedef T type; };
template <typename T> struct remove_pointer_const<const T*> { typedef T type; };

template <typename T> struct remove_volatile { typedef T type; };
template <typename T> struct remove_volatile<volatile T> { typedef T type; };

template <typename T> struct remove_reference { typedef T type; };
template <typename T> struct remove_reference<T&> { typedef T type; };
template <typename T> struct remove_reference<const T&> { typedef T type; };

typedef unsigned long true_t;
typedef unsigned char false_t;

template <typename T> struct is_bool { enum { value = 0 }; };
template <> struct is_bool<bool> { enum { value = 1 }; };

template <typename T> struct is_char { enum { value = 0 }; };
template <> struct is_char<char> { enum { value = 1 }; };
template <typename T> struct is_uchar { enum { value = 0 }; };
template <> struct is_uchar<unsigned char> { enum { value = 1 }; };

template <typename T> struct is_short { enum { value = 0 }; };
template <> struct is_short<short> { enum { value = 1 }; };
template <typename T> struct is_ushort { enum { value = 0 }; };
template <> struct is_ushort<unsigned short> { enum { value = 1 }; };

template <typename T> struct is_int { enum { value = 0 }; };
template <> struct is_int<int> { enum { value = 1 }; };
template <typename T> struct is_uint { enum { value = 0 }; };
template <> struct is_uint<unsigned int> { enum { value = 1 }; };

template <typename T> struct is_long { enum { value = 0 }; };
template <> struct is_long<long> { enum { value = 1 }; };
template <typename T> struct is_ulong { enum { value = 0 }; };
template <> struct is_ulong<unsigned long> { enum { value = 1 }; };

template <typename T> struct is_longlong { enum { value = 0 }; };
template <> struct is_longlong<long long> { enum { value = 1 }; };
template <typename T> struct is_ulonglong { enum { value = 0 }; };
template <> struct is_ulonglong<unsigned long long> { enum { value = 1 }; };

template <typename T> struct is_integer { enum { value = 0 }; };
template <> struct is_integer<bool> { enum { value = 1 }; };
template <> struct is_integer<const bool> { enum { value = 1 }; };
template <> struct is_integer<char> { enum { value = 1 }; };
template <> struct is_integer<const char> { enum { value = 1 }; };
template <> struct is_integer<short> { enum { value = 1 }; };
template <> struct is_integer<const short> { enum { value = 1 }; };
template <> struct is_integer<unsigned short> { enum { value = 1 }; };
template <> struct is_integer<const unsigned short> { enum { value = 1 }; };
template <> struct is_integer<int> { enum { value = 1 }; };
template <> struct is_integer<const int> { enum { value = 1 }; };
template <> struct is_integer<unsigned int> { enum { value = 1 }; };
template <> struct is_integer<const unsigned int> { enum { value = 1 }; };
template <> struct is_integer<long> { enum { value = 1 }; };
template <> struct is_integer<const long> { enum { value = 1 }; };
template <> struct is_integer<unsigned long> { enum { value = 1 }; };
template <> struct is_integer<const unsigned long> { enum { value = 1 }; };
template <> struct is_integer<long long> { enum { value = 1 }; };
template <> struct is_integer<const long long> { enum { value = 1 }; };
template <> struct is_integer<unsigned long long> { enum { value = 1 }; };
template <> struct is_integer<const unsigned long long> { enum { value = 1 }; };

template <typename T> struct is_unsigned{ enum { value = 0 }; };
template <> struct is_unsigned<bool> { enum { value = 0 }; };
template <> struct is_unsigned<const bool> { enum { value = 0 }; };
template <> struct is_unsigned<char> { enum { value = 0 }; };
template <> struct is_unsigned<const char> { enum { value = 0 }; };
template <> struct is_unsigned<unsigned char> { enum { value = 1 }; };
template <> struct is_unsigned<const unsigned char> { enum { value = 1 }; };
template <> struct is_unsigned<short> { enum { value = 0 }; };
template <> struct is_unsigned<const short> { enum { value = 0 }; };
template <> struct is_unsigned<unsigned short> { enum { value = 1 }; };
template <> struct is_unsigned<const unsigned short> { enum { value = 1 }; };
template <> struct is_unsigned<int> { enum { value = 0 }; };
template <> struct is_unsigned<const int> { enum { value = 0 }; };
template <> struct is_unsigned<unsigned int> { enum { value = 1 }; };
template <> struct is_unsigned<const unsigned int> { enum { value = 1 }; };
template <> struct is_unsigned<long> { enum { value = 0 }; };
template <> struct is_unsigned<const long> { enum { value = 0 }; };
template <> struct is_unsigned<unsigned long> { enum { value = 1 }; };
template <> struct is_unsigned<const unsigned long> { enum { value = 1 }; };
template <> struct is_unsigned<long long> { enum { value = 0 }; };
template <> struct is_unsigned<const long long> { enum { value = 0 }; };
template <> struct is_unsigned<unsigned long long> { enum { value = 1 }; };
template <> struct is_unsigned<const unsigned long long> { enum { value = 1 }; };

template <typename T> struct is_float { enum { value = 0 }; };
template <> struct is_float<float> { enum { value = 1 }; };
template <> struct is_float<double> { enum { value = 1 }; };
template <> struct is_float<long double> { enum { value = 1 }; };

template <typename T> struct is_double { enum { value = 0 }; };
template <> struct is_double<double> { enum { value = 1 }; };

template <typename T> struct is_longdouble { enum { value = 0 }; };
template <> struct is_longdouble<long double> { enum { value = 1 }; };

template <typename T> struct is_number { static const bool value = is_integer<T>::value || is_float<T>::value; };

template <typename T> struct is_str { enum { value = 0 }; };
template <> struct is_str<char*> { enum { value = 1 }; };
template <> struct is_str<const char*> { enum { value = 1 }; };

template <typename T> struct is_string { enum { value = 0 }; };
template <> struct is_string<std::string> { enum { value = 1 }; };
template <> struct is_string<const std::string> { enum { value = 1 }; };

template <typename T>
struct is_const_pointer
{
    template <typename U>
    static true_t is_const_pointer_tester(void (*)(const U*));
    static false_t is_const_pointer_tester(...);

    enum { value = (sizeof(true_t) == sizeof(is_const_pointer_tester((void (*)(T))0))) };
};

template <typename T>
struct is_pointer
{
    template <typename U> static true_t is_pointer_tester(U*);
    static false_t is_pointer_tester(...);

    enum { value = (sizeof(true_t) == sizeof(is_pointer_tester((T)0))) };
};

template <typename T>
struct is_const
{
    enum {
        value = (is_pointer<T>::value && \
                is_const_pointer<typename remove_pointer<T>::type*>::value) \
            || is_const_pointer<T*>::value
    };
};

template <typename T>
struct is_class_or_union
{
    template <typename U> static true_t is_class_or_union_tester(void (U::*)());
    template <typename U> static false_t is_class_or_union_tester(...);

    enum { value = (sizeof(true_t) == sizeof(is_class_or_union_tester<T>(0))) };
};

template <typename T, typename U>
struct is_same_type
{
    template <typename X, typename Y>
    struct is_same_type_tester { enum { value = 0 }; };
    template <typename X>
    struct is_same_type_tester<X, X> { enum { value = 1 }; };

    enum { value = is_same_type_tester<T, U>::value };
};

template <typename T, typename U>
struct is_drived_from
{
    static true_t is_drived_from_tester(U* u);
    static false_t is_drived_from_tester(...);

    enum { value = (sizeof(true_t) == sizeof(is_drived_from_tester((T*)0))) };
};

template <typename T, typename U>
struct is_subclass
{
    enum { value = is_drived_from<T, U>::value };
};

// XXX: avoid cast warnings
template <typename TO, typename FROM>
inline TO nasty_cast(FROM f)
{
    union
    {
        FROM f;
        TO t;
    } u;
    u.f = f;
    return u.t;
}

} // namespace buf

#endif // TYPETRAITS_H_

/* vim: set ai si nu sm smd hls is ts=4 sm=4 bs=indent,eol,start */


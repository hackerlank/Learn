#ifndef BASE_CONSTRUCT_H
#define BASE_CONSTRUCT_H

template<class T>
inline void constructInPlace(T *ptr)
{
	new ((void*)ptr) T();
}

template<class Ty,class Tparam>
inline void constructInPlace(Ty *ptr,Tparam param)
{
	new ((void*)ptr) Ty(param);
}

template<class Ty,class Tparam,class Tparam2>
inline void constructInPlace(Ty *ptr,Tparam param,Tparam2 param2)
{
	new ((void*)ptr) Ty(param,param2);
}

template<class Ty,class Tparam,class Tparam2,class Tparam3>
inline void constructInPlace(Ty *ptr,Tparam param,Tparam param2,Tparam3 param3)
{
	new ((void*)ptr) Ty(param,param2,param3);
}

#endif

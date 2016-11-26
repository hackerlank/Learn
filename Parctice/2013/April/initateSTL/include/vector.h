/************************************************************
	文件名：vector.h
	文件作用：类vector类的属性和方法的声明
	作者：chenzhen
	创建日期：2013.04.01
************************************************************/
#ifndef VECTOR_H
#define VECTOR_H
#include"iterator.h"
#include"allocate.h"
template<typename Tp,typename Alloc = Allocate<Tp> >
class Vector
{
	protected:

	Alloc alloc;
	
	typedef typename Alloc::point_type point_type;
	
	point_type start,finish,store_end;
	
	public:
	
	Vector():start(0),finish(0),store_end(0)
	{
	}
	
	Vector(size_t size)
	{
		init(size);
	}
	
	Vector(size_t size,const Tp& values)
	{
		init(size,values);
	}
	
	Vector(const Vector& values):start(values.start),finish(values.finish),alloc(values.alloc),store_end(values.store_end)
	{
	}
	
	void init(size_t n)
	{
		start = alloc.allocate(n);
		finish = start;
		store_end = start + n;
	}
	
	void init(size_t n,const Tp& values)
	{
		start = alloc.allocate(n);
		store_end = start + n;
		for(finish = start; finish != store_end;++finish)
		{
			_construct(&*finish,values);
		}
	}
	
	bool empty()
	{
		return start == finish;
	}
	
	size_t size()
	{
		return finish - start;
	}
};

#endif
	
	
	

	
	
	
/****************************************************************
 * Filename: bit_ops.h
 * 
 * Description: 位图的一些基本操作
 *
 * Original Author : bison, 2012-6-18
 *
 ****************************************************************/
 
  
#ifndef BIT_OPS_H_
#define BIT_OPS_H_

#include<iostream>
#include <sstream>
using namespace std;

//int型位数偏移量
#define OFFSET 5
//整型过滤
#define INT_MASK 31

typedef enum {
	SET_BIT,
	CLEAR_BIT,
	CHANGE_BIT
} BIT_OPS_T;

/********************************************************************
 * bit_ops - 二进制的基本位操作
 * @index:  所要操作的位
 * @bitMap: 所要操作的位图
 * @op:     所要做的操作：SET_BIT:置1；CLEAR_BIT:清0；CHANGE_BIT:取反
 ********************************************************************/
inline void bit_ops(int index, void *bitMap, BIT_OPS_T op)
{
	int mask;
	unsigned *temp = (unsigned *)bitMap;
	temp += index >> OFFSET;			//unsigned 位
	mask = 1 << (index & INT_MASK);		//二进制位
	switch (op)
	{
	case SET_BIT:			//置1
		*temp |= mask;
		break;
	case CLEAR_BIT:			//清0
		*temp &= ~mask;
		break;
	case CHANGE_BIT:		//取反
		*temp ^= mask;
		break;
	default:
		break;
	}
}

/********************************************************************
 * test_bit - 测试某一位的值
 * @index: 	所要测试的位
 * @bitMap: 所要测试的位图
 * Return:  所测试的位的值
 ********************************************************************/
inline int test_bit(int index, const void *bitMap)
{
	return 1UL & (((const unsigned *) bitMap)[index >> OFFSET] >> (index & INT_MASK));
}

/********************************************************************
 * ffs - find first set,从低位找整型数第一个被置1的位
 * @x: 被查找的数
 * Return: 返回第一个被置1的位的位数
 ********************************************************************/
inline int ffs(int x)
{
	int r = 1;
	if (!x)
	{
		return 0;
	}
	if (!(x & 0xffff))
	{
		x >>= 16;
		r += 16;
	}
	if (!(x & 0xff))
	{
		x >>= 8;
		r += 8;
	}
	if (!(x & 0xf))
	{
		x >>= 4;
		r += 4;
	}
	if (!(x & 0x3))
	{
		x >>= 2;
		r += 2;
	}
	if (!(x & 0x1))
	{
		x >>= 1;
		r += 1;
	}
	return r;
}

/********************************************************************
 * fls - find last set:找到最后一个被置1位的位置
 * @x: 所要查找的整数
 * Return: 最后一个被置1的位的位置
 ********************************************************************/
inline int fls(int x)
{
	int r = 32;
	
	if(!x)
	{
		return 0;
	}
	if (!(x & 0xffff0000u))
	{
		x <<= 16;
		r -= 16;
	}
	if (!(x & 0xff000000u))
	{
		x <<= 8;
		r -= 8;
	}
	if (!(x & 0xf0000000u))
	{
		x <<= 4;
		r -= 4;
	}
	if (!(x & 0xc0000000u))
	{
		x <<= 2;
		r -= 2;
	}
	if (!(x & 0x80000000u))
	{
		x <<= 1;
		r -= 1;
	}
	return r;
}

/*************************************************************
 * ffz - find first zero:找到第一个为0的位置
 * @x: 所要查找的值
 * Return: 第一个为0的位置
 *************************************************************/
inline int ffz(int x)
{
	int r = 0;
	while (x & 1)
	{
		x >>= 1;
		r += 1;
	}
	return r;
}


inline int ffz(long x)
{
	int r = 0;
	while (x & 1)
	{
		x >>= 1;
		r += 1;
	}
	return r;
}
/***********************************************************
 * string2int - 字符串转换成整型，忽略前面的0
 * @str: 所要转换的字符串
 * Return: 返回转换的整数。如"0023"转换后则为23,"00"转成0
 ***********************************************************/
inline int string2int(string str)
{
	int i = 0, ret = str.size();
	string dst;
	
	for (; i < ret && str[i] == '0'; i++){}
	
	if (i == ret)
	{
		return 0;
	}
	
	dst = str.substr(i);
	istringstream is(dst);
	is>>ret;
	
	return ret;
}

#endif
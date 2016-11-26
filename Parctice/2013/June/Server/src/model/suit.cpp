#include"suit.h"
Suit::Suit(string _suit_id,int _type,string _suit_name,int _hp,int _mp,int _outHrt,int _inHrt,int _outAttVal,int _inAttVal,int _outDefVal,int _inDefVal,
			int _hit,int _crit,int _dodge,int _tenacity)
{
	suit_id = _suit_id;				//套装Id
	type = _type;					//套装类别
	suit_name = _suit_name;			//套装名称
	hp = _hp;						//套装提升生命值的数值
	mp = _mp;						//套装提升真气值的数值
	outHrt = _outHrt;				//套装提升外功伤害的数值
	inHrt = _inHrt;					//套装提升内功伤害的数值
	outAttVal = _outAttVal;			//套装提升外功攻击的数值
	inAttVal = _inAttVal;			//套装提升内功攻击的数值
	outDefVal = _outDefVal;			//套装提升外功防御的数值
	inDefVal = _inDefVal;			//套装提升内功防御的数值
	hit = _hit;						//套装提升的命中的数值
	crit = _crit;					//套装提升的暴击的数值
	dodge = _dodge;					//套装提升的闪避的数值
	tenacity = _tenacity;			//套装提升的韧性的数值

}
string Suit::getsuit_id(void)			//套装Id
{
	return suit_id;
}
int	   Suit::gettype(void)				//套装类别
{
	return type;
}
string Suit::getsuit_name(void)			//套装名称
{
	return suit_name;
}
int	   Suit::gethp(void)					//套装提升生命值的数值
{
	return hp;
}
int    Suit::getmp(void)					//套装提升真气值的数值
{
	return mp;
}
int    Suit::getoutHrt(void)				//套装提升外功伤害的数值
{
	return outHrt;
}
int    Suit::getinHrt(void)				//套装提升内功伤害的数值
{
	return inHrt;
}
int    Suit::getoutAttVal(void)			//套装提升外功攻击的数值
{
	return outAttVal;
}
int    Suit::getinAttVal(void)			//套装提升内功攻击的数值
{
	return inAttVal;
}
int    Suit::getoutDefVal(void)			//套装提升外功防御的数值
{
	return outDefVal;
}
int    Suit::getinDefVal(void)			//套装提升内功防御的数值
{
	return inDefVal;
}
int    Suit::gethit(void)				//套装提升的命中的数值
{
	return hit;
}
int    Suit::getcrit(void)				//套装提升的暴击的数值
{
	return crit;
}
int    Suit::getdodge(void)				//套装提升的闪避的数值
{
	return dodge;
}
int    Suit::gettenacity(void)			//套装提升的韧性的数值
{
	return tenacity;
}
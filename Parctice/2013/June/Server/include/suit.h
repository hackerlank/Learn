#ifndef SUIT
#define SUIT
#include<string>
using namespace std;
class Suit{
	private :
		string suit_id;				//套装Id
		int	   type;				//套装类别
		string suit_name;			//套装名称
		int	   hp;					//套装提升生命值的数值
		int    mp;					//套装提升真气值的数值
		int    outHrt;				//套装提升外功伤害的数值
		int    inHrt;				//套装提升内功伤害的数值
		int    outAttVal;			//套装提升外功攻击的数值
		int    inAttVal;			//套装提升内功攻击的数值
		int    outDefVal;			//套装提升外功防御的数值
		int    inDefVal;			//套装提升内功防御的数值
		int    hit;					//套装提升的命中的数值
		int    crit;				//套装提升的暴击的数值
		int    dodge;				//套装提升的闪避的数值
		int    tenacity;			//套装提升的韧性的数值
	public :
		Suit(string _suit_id,int _type,string _suit_name,int _hp,int _mp,int _outHrt,int _inHrt,int _outAttVal,int _inAttVal,int _outDefVal,int _inDefVal,
			int _hit,int _crit,int _dodge,int _tenacity);
			
			string getsuit_id(void);			//套装Id
			int	   gettype(void);				//套装类别
			string getsuit_name(void);			//套装名称
			int	   gethp(void);					//套装提升生命值的数值
			int    getmp(void);					//套装提升真气值的数值
			int    getoutHrt(void);				//套装提升外功伤害的数值
			int    getinHrt(void);				//套装提升内功伤害的数值
			int    getoutAttVal(void);			//套装提升外功攻击的数值
			int    getinAttVal(void);			//套装提升内功攻击的数值
			int    getoutDefVal(void);			//套装提升外功防御的数值
			int    getinDefVal(void);			//套装提升内功防御的数值
			int    gethit(void);				//套装提升的命中的数值
			int    getcrit(void);				//套装提升的暴击的数值
			int    getdodge(void);				//套装提升的闪避的数值
			int    gettenacity(void);			//套装提升的韧性的数值	
};
#endif
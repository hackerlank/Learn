#ifndef HAT_VAL_RILE_H
#define HAT_VAL_RILE_H
class HatValRue
{
private:
	double hatInRag;       //进入仇恨范围时的值
	double genHitPer;      //普通攻击仇恨值增长比例
	double sklHitPer;		//伤害技能仇恨值增长比例
	double proLosPer;		//损益技能仇恨值增长比例
	double friHitGan;       //第一次攻击仇恨值
	double chageAirPer;        //转换目标仇恨比例
	double hatUpVal;         //恨值上限值
	double redueValPer;      //达到仇恨上限时，仇恨缩减比例
	int hatRage;              //仇恨范围
public:
	HatValRue(double _hatInRag,double _genHitPer,double _sklHitPer,double _proLosPer,double _friHitGan,double _chageAir,double hatUpVal,double _redueValPer,int _hatRage);
	int getHatRage(void);
	double getHatInRag(void);
	double getGenHitPer(void);
	double getSklHitPer(void);
	double getProLosPer(void);
	double getFriHitGan(void);
	double getChageAirPer(void);
	double getHatUpVal(void);
	double getRedueValPer(void);
};
#endif

/*

*/
#ifndef HERO_HELP_H
#define HERO_HELP_H
#include<string>
#include<iostream>
#include<map>
#include"skill.h"
using namespace std;
class Skill;
class HeroHelp 
{
	private:
		bool   isflight;					//玩家上一次战斗是否已经处理完毕 evan add 2012.9.25
		
		bool   isyd;						//当攻击动画播放时；玩家不能移动
		int	   isyd_contime;				//动画播放时间
		int    isyd_now_time;				//动画播放开始时间
		int	   life_change;					//攻击者的血值变化
		int	   type;						//技能效果类型
		
		int 	fight_status;				//此次攻击是否产品暴击，或者被对方闪避等效果；（1，无暴击无闪避；2，暴击；3，闪避；）
		/*debuff效果*/
		/*1:定身*/
		bool   ds;      					//是否触发定身效果
		string ds_id;  					    //玩家所受攻击的定身技能ID
		int	   ds_contime;					//定身技能持续时间
		int    ds_now_time;					//定身技能释放时间
		/*2:点穴*/
		bool   dx;							//是否触发点穴效果
		string dx_id;  					    //玩家所受攻击的点穴技能ID
		int	   dx_contime;					//点穴技能持续时间
		int    dx_now_time;					//点穴技能释放时间	
		/*3:眩晕*/
		bool   xy;							//是否触发眩晕效果
		string xy_id;						//玩家所受攻击的眩晕技能Id
		int    xy_contime;					//眩晕技能持续时间
		int    xy_now_time;					//眩晕技能释放时间
		/*4:击退*/
		bool	jt;							//是否触发击退效果
		
		/*5:降低敌方韧性*/
		bool   jdrx;						//是否触发降低韧性效果
		string jdrx_id;						//玩家所受攻击的降低韧性技能ID
		int	   jdrx_contime;				//降低韧性技能持续时间
		int    jdrx_now_time;				//降低韧性技能释放时间
		int    jdrx_value;					//降低的韧性值
		/*6:降低敌方命中*/
		bool   jdmz;						//是否触发降低命中效果
		string jdmz_id;						//玩家所受攻击的降低命中技能Id
		int    jdmz_contime;				//降低命中技能持续时间
		int    jdmz_now_time;				//降低命中技能释放时间
		int    jdmz_value;					//降低的命中值
		
		/*7:降低敌方攻防总值*/
		bool   jdgf;						//是否触发降低攻防效果
		string jdgf_id;						//玩家所受攻击的降低攻防技能Id
		int    jdgf_contime;				//降低攻防技能持续时间
		int    jdgf_now_time;				//降低攻防技能释放时间
		int    jdgf_ngvalue;				//降低的内功攻击值
		int    jdgf_wgvalue;				//降低的外功攻击值
		int    jdgf_nfvalue;				//降低的内功防御值
		int    jdgf_wfvalue;				//降低的外功防御值
		/*8:持续掉血*/
		bool   cxdx;						//是否触发持续掉血功能
		string cxdx_id;						//玩家所受攻击的降低续掉血技能Id
		int    cxdx_contime;				//持续掉血技能持续时间
		int    cxdx_now_time;				//持续掉血技能释放时间
		int    cxdx_value;					//降低的掉血的血值
		string cxdx_hiterid;				//受擊者Id
		/*buff效果*/	
		/*10:可反弹部分物理伤害给释放者*/
		bool   ftsh;						//是否触发反弹伤害
		string ftsh_id;						//反弹伤害技能ID
		int    ftsh_contime;				//反弹伤害技能持续时间
		int    ftsh_now_time;				//反弹伤害技能触发时间
		int    ftsh_value;					//反弹伤害率（乘以1000）
		int    ftsh_hitvalue;				//反弹伤害值
		/*11:消耗自身血量提升攻击力*/
		bool   xhxl;						//是否触发此技能
		string xhxl_id;						//技能Id
		int    xhxl_contime;				//技能持续时间
		int    xhxl_now_time;				//技能触发时间
		int    xhxl_inhurt;					//技能增加内功伤害值
		int    xhxl_outhurt;				//技能增加外功伤害值
		/*12:附加偷血效果*/
		bool   tx;							//是否触发偷血技能
		string tx_id;						//偷血技能Id
		int    tx_contime;					//偷血技能持续时间
		int    tx_now_time;					//偷血技能触发时间
		int    tx_value;					//偷血率
		/*13:短期内附加一个血包*/
		bool   xb;							//是否触发此技能
		string xb_id;						//血包技能Id
		int    xb_contime;					//此技能持续时间
		int    xb_now_time;					//此技能触发时间
		int    xb_value;					//血包值
		/*14:短期内无敌状态*/
		bool   wd;							//是否触发此技能
		string wd_id;						//无敌技能Id
		int    wd_contime;					//此技能持续时间
		int    wd_now_time;					//此技能触发时间
	public:
	HeroHelp(bool _isyd,bool _ds,bool _dx,bool _xy,bool _jt,bool _jdrx,bool _jdmz,bool _jdgf,bool _ftsh,bool _xhxl,bool _tx,bool _xb,bool _wd);
	
	bool   getisflight(void);					//玩家上一次战斗是否已经处理完毕 evan add 2012.9.25
	void   setisflight(bool _isflight);
	
	bool   getisyd(void);				//当攻击动画播放时；玩家不能移动
	void   setisyd(bool _isyd);
	
	int	   getisyd_contime(void);		//动画播放时间
	void   setisyd_contime(int _isyd_contime);
	
	int    getisyd_now_time(void);		//动画播放开始时间
	void   setisyd_now_time(int _isyd_now_time);
	
	int	   getlife_change(void);					//攻击者的血值变化
	void   setlife_change(int _life_change);
	
	int 	getfight_status(void);				//此次攻击是否产品暴击，或者被对方闪避等效果；（1，无暴击无闪避；2，暴击；3，闪避；）
	void    setfight_status(int _fight_status);
	/*debuff效果*/
		/*1:定身*/
	bool   getds(void);      			//是否触发定身定身效果
	void   setds(bool _ds);	
	
	string getds_id(void);  			//玩家所受攻击的定身技能ID
	void   setds_id(string _ds_id);
	
	int	   getds_contime(void);			//定身技能持续时间
	void   setds_contime(int _ds_contime);
	
	int    getds_now_time(void);		//定身技能释放时间
	void   setds_now_time(int _ds_now_time);
	
		/*2:点穴*/
	bool   getdx(void);					//是否触发点穴效果
	void   setdx(bool _dx);
	
	string getdx_id(void);  			//玩家所受攻击的点穴技能ID
	void   setdx_id(string _dx_id);
	
	int	   getdx_contime(void);			//点穴技能持续时间
	void   setdx_contime(int _dx_contime);
	
	int    getdx_now_time(void);		//点穴技能释放时间
	void   setdx_now_time(int _dx_now_time);
		/*3:眩晕*/
	bool   getxy(void);					//是否触发眩晕效果
	void   setxy(bool _xy);
	
	string getxy_id(void);				//玩家所受攻击的眩晕技能Id
	void   setxy_id(string _xy_id);
	
	int    getxy_contime(void);			//眩晕技能持续时间
	void   setxy_contime(int _xy_contime);
	
	int    getxy_now_time(void);		//眩晕技能释放时间
	void   setxy_now_time(int _xy_now_time);
		/*4:击退*/
	bool   getjt(void);							//是否触发击退效果
	void   setjt(bool _jt);	
		/*5:降低敌方韧性*/
	bool   getjdrx(void);						//是否触发降低韧性效果
	void   setjdrx(bool _jdrx);
	
	string getjdrx_id(void);					//玩家所受攻击的降低韧性技能ID
	void   setjdrx_id(string _jdrx_id);
	
	int	   getjdrx_contime(void);				//降低韧性技能持续时间
	void   setjdrx_contime(int _jdrx_contime);
	
	int    getjdrx_now_time(void);				//降低韧性技能释放时间
	void   setjdrx_now_time(int _jdrx_now_time);
	
	int    getjdrx_value(void);					//降低韧性值
	void   setjdrx_value(int _jdrx_value);
	
	/*6:降低敌方命中*/
	bool   getjdmz(void);						//是否触发降低命中效果
	void   setjdmz(int _jdmz);
	
	string getjdmz_id(void);					//玩家所受攻击的降低命中技能Id
	void   setjdmz_id(string _jdmz_id);
	
	int    getjdmz_contime(void);				//降低命中技能持续时间
	void   setjdmz_contime(int _jdmz_contime);
	
	int    getjdmz_now_time(void);				//降低命中技能释放时间
	void   setjdmz_now_time(int _jdmz_now_time);
	
	int    getjdmz_value(void);					//降低的命中值
	void   setjdmz_value(int _jdmz_value);
	
	/*7:降低敌方攻防总值*/
	bool   getjdgf(void);						//是否触发降低攻防效果
	void   setjdgf(int _jdgf);
	
	string getjdgf_id(void);					//玩家所受攻击的降低攻防技能Id
	void   setjdgf_id(string _jdgf_id);
	
	int    getjdgf_contime(void);				//降低攻防技能持续时间
	void   setjdgf_contime(int _jdgf_contime);
	
	int    getjdgf_now_time(void);				//降低攻防技能释放时间
	void   setjdgf_now_time(int _jdgf_now_time);
	
	int    getjdgf_ngvalue(void);				//降低的内功攻击值
	void   setjdgf_ngvalue(int _jdgf_ngvalue);
	
	int    getjdgf_wgvalue(void);				//降低的外功攻击值
	void   setjdgf_wgvalue(int _jdgf_wgvalue);
	
	int    getjdgf_nfvalue(void);				//降低的内功防御值
	void   setjdgf_nfvalue(int _jdgf_nfvalue);
	
	int    getjdgf_wfvalue(void);				//降低的外功防御值
	void   setjdgf_wfvalue(int _jdgf_wfvalue);
	/*8:持续掉血*/
	bool   getcxdx(void);						//是否触发持续掉血功能
	void   setcxdx(bool _cxdx);
	
	string getcxdx_id(void);					//玩家所受攻击的降低续掉血技能Id
	void   setcxdx_id(string _cxdx_id);
	
	int    getcxdx_contime(void);				//持续掉血技能持续时间
	void   setcxdx_contime(int _cxdx_contime);
	
	int    getcxdx_now_time(void);				//持续掉血技能释放时间
	void   setcxdx_now_time(int _cxdx_now_time);
	
	int    getcxdx_value(void);					//降低的掉血的血值
	void   setcxdx_value(int _cxdx_value);
	
	string getcxdx_hiterid(void);				//受擊者Id
	void   setcxdx_hiterid(string _cxdx_hiterid);
		/*buff效果*/	
		/*10:可反弹部分物理伤害给释放者*/
	bool   getftsh(void);						//是否触发反弹伤害
	void   setftsh(bool _ftsh);
	string getftsh_id(void);					//反弹伤害技能ID
	void   setftsh_id(string _ftsh_id);
	
	int    getftsh_contime(void);				//反弹伤害技能持续时间
	void   setftsh_contime(int _ftsh_contime);
	
	int    getftsh_now_time(void);				//反弹伤害技能触发时间
	void   setftsh_now_time(int _ftsh_now_time);
	
	int    getftsh_value(void);					//反弹伤害率（乘以1000）
	void   setftsh_value(int _ftsh_value);
	
	int    getftsh_hitvalue(void);				//反弹伤害值
	void   setftsh_hitvalue(int _ftsh_hitvalue);
	/*11:消耗自身血量提升攻击力*/
	bool   getxhxl(void);						//是否触发此技能
	void   setxhxl(bool _xhxl);
	
	string getxhxl_id(void);					//技能Id
	void   setxhxl_id(string _xhxl_id);
	
	int    getxhxl_contime(void);				//技能持续时间
	void   setxhxl_contime(int _xhxl_contime);
	
	int    getxhxl_now_time(void);				//技能触发时间
	void   setxhxl_now_time(int _xhxl_now_time);
	
	int    getxhxl_inhurt(void);				//技能增加内功伤害值
	void   setxhxl_inhurt(int _xhxl_inhurt);
	
	int    getxhxl_outhurt(void);				//技能增加外功伤害值
	void   setxhxl_outhurt(int _xhxl_outhurt);
	/*12:附加偷血效果*/
	bool   gettx(void);							//是否触发偷血技能
	void   settx(bool _tx);
	
	string gettx_id(void);						//偷血技能Id
	void   settx_id(string _tx_id);
	
	int    gettx_contime(void);					//偷血技能持续时间
	void   settx_contime(int _tx_contime);
	
	int    gettx_now_time(void);				//偷血技能触发时间
	void   settx_now_time(int _tx_now_time);
	
	int    gettx_value(void);					//偷血率
	void   settx_value(int _tx_value);
	/*13:短期内附加一个血包*/
	bool   getxb(void);							//是否触发此技能
	void   setxb(bool _xb);
	
	string getxb_id(void);						//血包技能Id
	void   setxb_id(string _xb_id);
	
	int    getxb_contime(void);					//此技能持续时间
	void   setxb_contime(int _xb_contime);
	
	int    getxb_now_time(void);				//此技能触发时间
	void   setxb_now_time(int _xb_now_time);
	
	int    getxb_value(void);					//血包值
	void   setxb_value(int _xb_value);
	/*14:短期内无敌状态*/
	bool   getwd(void);							//是否触发此技能
	void   setwd(bool _wd);
	
	string getwd_id(void);						//无敌技能Id
	void   setwd_id(string _wd_id);
	
	int    getwd_contime(void);					//此技能持续时间
	void   setwd_contime(int _wd_contime);
	
	int    getwd_now_time(void);				//此技能触发时间
	void   setwd_now_time(int _wd_now_time);
};
#endif


#include"hero_help.h"
HeroHelp::HeroHelp(bool _isyd,bool _ds,bool _dx,bool _xy,bool _jt,bool _jdrx,bool _jdmz,bool _jdgf,bool _ftsh,bool _xhxl,bool _tx,bool _xb,bool _wd)
{
	isyd =  _isyd;
	ds = _ds;
	dx = _dx;
	xy = _xy;
	jt = _jt;
	jdrx = _jdrx;
	jdmz = _jdmz;
	jdgf = _jdgf;
	ftsh = _ftsh;
	xhxl = _xhxl;
	tx = _tx;
	xb = _xb;
	wd = _wd;
	life_change = 0;
	isflight = false;
}
bool   HeroHelp::getisflight(void)					//玩家上一次战斗是否已经处理完毕 evan add 2012.9.25
{
	return isflight;
}
void   HeroHelp::setisflight(bool _isflight)
{
	isflight = _isflight;
}
	
bool   HeroHelp::getisyd(void)				//当攻击动画播放时；玩家不能移动
{
	return isyd;
}
void   HeroHelp::setisyd(bool _isyd)
{
	isyd = _isyd;
}
int	   HeroHelp::getisyd_contime(void)		//动画播放时间
{
	return isyd_contime;
}
void   HeroHelp::setisyd_contime(int _isyd_contime)
{
	isyd_contime = _isyd_contime;
}

int    HeroHelp::getisyd_now_time(void)		//动画播放开始时间
{
	return isyd_now_time;
}
void   HeroHelp::setisyd_now_time(int _isyd_now_time)
{
	isyd_now_time = _isyd_now_time;
}

int	   HeroHelp::getlife_change(void)					//攻击者的血值变化
{
	return life_change;
}
void   HeroHelp::setlife_change(int _life_change)
{
	life_change = _life_change;
}

int    HeroHelp::getfight_status(void)				//此次攻击是否产品暴击，或者被对方闪避等效果；（1，无暴击无闪避；2，暴击；3，闪避；）
{
	return fight_status;
}
void   HeroHelp::setfight_status(int _fight_status)
{
	fight_status = _fight_status;
}
	/*debuff效果*/
		/*1:定身*/
bool   HeroHelp::getds(void)      				//是否触发定身定身效果
{
	return ds;
}
void   HeroHelp::setds(bool _ds)	
{
	ds = _ds;
}

string HeroHelp::getds_id(void)  				//玩家所受攻击的定身技能ID
{
	return ds_id;
}
void   HeroHelp::setds_id(string _ds_id)
{
	ds_id = _ds_id;
}
	
int	   HeroHelp::getds_contime(void)			//定身技能持续时间
{
	return ds_contime;
}
void   HeroHelp::setds_contime(int _ds_contime)
{
	ds_contime = _ds_contime;
}
	
int    HeroHelp::getds_now_time(void)			//定身技能释放时间
{
	return ds_now_time;
}
void   HeroHelp::setds_now_time(int _ds_now_time)
{
	ds_now_time = _ds_now_time;
}
	
		/*2:点穴*/
bool   HeroHelp::getdx(void)					//是否触发点穴效果
{
	return dx;
}
void   HeroHelp::setdx(bool _dx)
{
	dx = _dx;
}
	
string HeroHelp::getdx_id(void)  				//玩家所受攻击的点穴技能ID
{
	return dx_id;
}	
void   HeroHelp::setdx_id(string _dx_id)
{
	dx_id = _dx_id;
}
	
int	   HeroHelp::getdx_contime(void)			//点穴技能持续时间
{
	return dx_contime;
}
void   HeroHelp::setdx_contime(int _dx_contime)
{
	dx_contime = _dx_contime;
}
	
int    HeroHelp::getdx_now_time(void)			//点穴技能释放时间
{
	return dx_now_time;
}
void   HeroHelp::setdx_now_time(int _dx_now_time)
{
	dx_now_time = _dx_now_time;
}
		/*3:眩晕*/
bool   HeroHelp::getxy(void)					//是否触发眩晕效果
{
	return xy;
}
void   HeroHelp::setxy(bool _xy)
{
	xy = _xy;
}	
string HeroHelp::getxy_id(void)					//玩家所受攻击的眩晕技能Id
{
	return xy_id;
}
void   HeroHelp::setxy_id(string _xy_id)
{
	xy_id = _xy_id;
}
	
int    HeroHelp::getxy_contime(void)			//眩晕技能持续时间
{
	return xy_contime;
}
void   HeroHelp::setxy_contime(int _xy_contime)
{
	xy_contime = _xy_contime;
}
	
int    HeroHelp::getxy_now_time(void)			//眩晕技能释放时间
{
	return xy_now_time;
}
void   HeroHelp::setxy_now_time(int _xy_now_time)
{
	xy_now_time = _xy_now_time;
}
		/*4:击退*/
bool   HeroHelp::getjt(void)							//是否触发击退效果
{
	return jt;
}
void   HeroHelp::setjt(bool _jt)	
{
	jt = _jt;
}
		/*5:降低敌方韧性*/
bool   HeroHelp::getjdrx(void)						//是否触发降低韧性效果
{
	return jdrx;
}
void   HeroHelp::setjdrx(bool _jdrx)
{
	jdrx = _jdrx;
}
	
string HeroHelp::getjdrx_id(void)					//玩家所受攻击的降低韧性技能ID
{
	return jdrx_id;
}
void   HeroHelp::setjdrx_id(string _jdrx_id)
{
	jdrx_id = _jdrx_id;
}
	
int	   HeroHelp::getjdrx_contime(void)				//降低韧性技能持续时间
{
	return jdrx_contime;
}
void   HeroHelp::setjdrx_contime(int _jdrx_contime)
{
	jdrx_contime = _jdrx_contime;
}	
int    HeroHelp::getjdrx_now_time(void)				//降低韧性技能释放时间
{
	return jdrx_now_time;
}
void   HeroHelp::setjdrx_now_time(int _jdrx_now_time)
{
	jdrx_now_time = _jdrx_now_time;
}
	
int    HeroHelp::getjdrx_value(void)					//降低韧性值
{
	return jdrx_value;
}
void   HeroHelp::setjdrx_value(int _jdrx_value)
{
	jdrx_value = _jdrx_value;
}
	/*6:降低敌方命中*/
bool   HeroHelp::getjdmz(void)							//是否触发降低命中效果
{
	return jdmz;
}
void   HeroHelp::setjdmz(int _jdmz)
{
	jdmz = _jdmz;
}

string HeroHelp::getjdmz_id(void)						//玩家所受攻击的降低命中技能Id
{
	return jdmz_id;
}
void   HeroHelp::setjdmz_id(string _jdmz_id)
{
	jdmz_id = _jdmz_id;
}

int    HeroHelp::getjdmz_contime(void)					//降低命中技能持续时间
{
	return jdmz_contime;
}
void   HeroHelp::setjdmz_contime(int _jdmz_contime)
{
	jdmz_contime = _jdmz_contime;
}

int    HeroHelp::getjdmz_now_time(void)					//降低命中技能释放时间
{
	return jdmz_now_time;
}
void   HeroHelp::setjdmz_now_time(int _jdmz_now_time)
{
	jdmz_now_time = _jdmz_now_time;
}

int    HeroHelp::getjdmz_value(void)					//降低的命中值
{
	return jdmz_value;
}
void   HeroHelp::setjdmz_value(int _jdmz_value)
{
	jdmz_value = _jdmz_value;
}
/*7:降低敌方攻防总值*/
bool   HeroHelp::getjdgf(void)						//是否触发降低攻防效果
{
	return jdgf;
}
void   HeroHelp::setjdgf(int _jdgf)
{
	jdgf = _jdgf;
}
	
string HeroHelp::getjdgf_id(void)					//玩家所受攻击的降低攻防技能Id
{
	return jdgf_id;
}
void   HeroHelp::setjdgf_id(string _jdgf_id)
{
	jdgf_id = _jdgf_id;
}
	
int    HeroHelp::getjdgf_contime(void)				//降低攻防技能持续时间
{
	return jdgf_contime;
}
void   HeroHelp::setjdgf_contime(int _jdgf_contime)
{
	jdgf_contime = _jdgf_contime;
}

int    HeroHelp::getjdgf_now_time(void)				//降低攻防技能释放时间
{
	return jdgf_now_time;
}
void   HeroHelp::setjdgf_now_time(int _jdgf_now_time)
{
	jdgf_now_time = _jdgf_now_time;
}

int    HeroHelp::getjdgf_ngvalue(void)				//降低的内功攻击值
{
	return jdgf_ngvalue;
}
void   HeroHelp::setjdgf_ngvalue(int _jdgf_ngvalue)
{
	jdgf_ngvalue = _jdgf_ngvalue;
}
	
int    HeroHelp::getjdgf_wgvalue(void)				//降低的外功攻击值
{
	return jdgf_wgvalue;
}
void   HeroHelp::setjdgf_wgvalue(int _jdgf_wgvalue)
{
	jdgf_wgvalue = _jdgf_wgvalue;
}
	
int    HeroHelp::getjdgf_nfvalue(void)				//降低的内功防御值
{
	return jdgf_nfvalue;
}
void   HeroHelp::setjdgf_nfvalue(int _jdgf_nfvalue)
{
	jdgf_nfvalue = _jdgf_nfvalue;
}
	
int    HeroHelp::getjdgf_wfvalue(void)				//降低的外功防御值
{
	return jdgf_wfvalue;
}
void   HeroHelp::setjdgf_wfvalue(int _jdgf_wfvalue)
{
	jdgf_wfvalue = _jdgf_wfvalue;
}
/*8:持续掉血*/
bool   HeroHelp::getcxdx(void)						//是否触发持续掉血功能
{
	return cxdx;
}
void   HeroHelp::setcxdx(bool _cxdx)
{
	cxdx = _cxdx;
}

string HeroHelp::getcxdx_id(void)					//玩家所受攻击的降低续掉血技能Id
{
	return cxdx_id;
}
void   HeroHelp::setcxdx_id(string _cxdx_id)
{
	cxdx_id = _cxdx_id;
}
	
int    HeroHelp::getcxdx_contime(void)				//持续掉血技能持续时间
{
	return cxdx_contime;
}
void   HeroHelp::setcxdx_contime(int _cxdx_contime)
{
	cxdx_contime = _cxdx_contime;
}
	
int    HeroHelp::getcxdx_now_time(void)				//持续掉血技能释放时间
{
	return cxdx_now_time;
}
void   HeroHelp::setcxdx_now_time(int _cxdx_now_time)
{
	cxdx_now_time = _cxdx_now_time;
}
	
int    HeroHelp::getcxdx_value(void)					//降低的掉血的血值
{
	return cxdx_value;
}
void   HeroHelp::setcxdx_value(int _cxdx_value)
{
	cxdx_value = _cxdx_value;
}
	
string HeroHelp::getcxdx_hiterid(void)				//受擊者Id
{
	return cxdx_hiterid;
}
void   HeroHelp::setcxdx_hiterid(string _cxdx_hiterid)
{
	cxdx_hiterid = _cxdx_hiterid;
}
	/*buff效果*/	
	/*10:可反弹部分物理伤害给释放者*/
bool   HeroHelp::getftsh(void)						//是否触发反弹伤害
{
	return ftsh;
}
void   HeroHelp::setftsh(bool _ftsh)
{
	ftsh = _ftsh;
}
string HeroHelp::getftsh_id(void)					//反弹伤害技能ID
{
	return ftsh_id;
}
void   HeroHelp::setftsh_id(string _ftsh_id)
{
	ftsh_id = _ftsh_id;
}
	
int    HeroHelp::getftsh_contime(void)				//反弹伤害技能持续时间
{
	return ftsh_contime;
}
void   HeroHelp::setftsh_contime(int _ftsh_contime)
{
	ftsh_contime = _ftsh_contime;
}	
int    HeroHelp::getftsh_now_time(void)				//反弹伤害技能触发时间
{
	return ftsh_now_time;
}
void   HeroHelp::setftsh_now_time(int _ftsh_now_time)
{
	ftsh_now_time = _ftsh_now_time;
}
	
int    HeroHelp::getftsh_value(void)					//反弹伤害率（乘以1000）
{
	return ftsh_value;
}
void   HeroHelp::setftsh_value(int _ftsh_value)
{
	ftsh_value = _ftsh_value;
}

int    HeroHelp::getftsh_hitvalue(void)				//反弹伤害值
{
	return ftsh_hitvalue;
}
void   HeroHelp::setftsh_hitvalue(int _ftsh_hitvalue)
{
	ftsh_hitvalue = _ftsh_hitvalue;
}
	/*11:消耗自身血量提升攻击力*/
bool   HeroHelp::getxhxl(void)						//是否触发此技能
{
	return xhxl;
}
void   HeroHelp::setxhxl(bool _xhxl)
{
	xhxl = _xhxl;
}

string HeroHelp::getxhxl_id(void)					//技能Id
{
	return xhxl_id;
}
void   HeroHelp::setxhxl_id(string _xhxl_id)
{
	xhxl_id = _xhxl_id;
}
	
int    HeroHelp::getxhxl_contime(void)				//技能持续时间
{
	return xhxl_contime;
}
void   HeroHelp::setxhxl_contime(int _xhxl_contime)
{
	xhxl_contime = _xhxl_contime;
}
	
int    HeroHelp::getxhxl_now_time(void)				//技能触发时间
{
	return xhxl_now_time;	
}
void   HeroHelp::setxhxl_now_time(int _xhxl_now_time)
{
	xhxl_now_time = _xhxl_now_time;
}
	
int    HeroHelp::getxhxl_inhurt(void)				//技能增加内功伤害值
{
	return xhxl_inhurt;
}
void   HeroHelp::setxhxl_inhurt(int _xhxl_inhurt)
{
	xhxl_inhurt =_xhxl_inhurt;
}
	
int    HeroHelp::getxhxl_outhurt(void)				//技能增加外功伤害值
{
	return xhxl_outhurt;
}
void   HeroHelp::setxhxl_outhurt(int _xhxl_outhurt)
{
	xhxl_outhurt = _xhxl_outhurt;
}

/*12:附加偷血效果*/
bool   HeroHelp::gettx(void)							//是否触发偷血技能
{
	return tx;
}
void   HeroHelp::settx(bool _tx)
{
	tx = _tx;
}

string HeroHelp::gettx_id(void)						//偷血技能Id
{
	return tx_id;
}
void   HeroHelp::settx_id(string _tx_id)
{
	tx_id = _tx_id;
}

int    HeroHelp::gettx_contime(void)					//偷血技能持续时间
{
	return tx_contime;
}
void   HeroHelp::settx_contime(int _tx_contime)
{
	tx_contime = _tx_contime;
}

int    HeroHelp::gettx_now_time(void)				//偷血技能触发时间
{
	return tx_now_time;
}
void   HeroHelp::settx_now_time(int _tx_now_time)
{
	tx_now_time = _tx_now_time;
}
	
int    HeroHelp::gettx_value(void)					//偷血率
{
	return tx_value;
}
void   HeroHelp::settx_value(int _tx_value)
{
	tx_value = _tx_value;
}

/*13:短期内附加一个血包*/
bool   HeroHelp::getxb(void)							//是否触发此技能
{
	return xb;
}
void   HeroHelp::setxb(bool _xb)
{
	xb = _xb;
}

string HeroHelp::getxb_id(void)						    //血包技能Id
{
	return xb_id;
}
void   HeroHelp::setxb_id(string _xb_id)
{
	xb_id = _xb_id;
}

int    HeroHelp::getxb_contime(void)					//此技能持续时间
{
	return xb_contime;
}
void   HeroHelp::setxb_contime(int _xb_contime)
{
	xb_contime = _xb_contime;
}
	
int    HeroHelp::getxb_now_time(void)					//此技能触发时间
{
	return xb_now_time;
}
void   HeroHelp::setxb_now_time(int _xb_now_time)
{
	xb_now_time = _xb_now_time;
}
	
int    HeroHelp::getxb_value(void)						//血包值
{
	return xb_value;
}
void   HeroHelp::setxb_value(int _xb_value)
{
	xb_value = _xb_value;
}
/*14:短期内无敌状态*/
bool   HeroHelp::getwd(void)							//是否触发此技能
{
	return wd;
}
void   HeroHelp::setwd(bool _wd)
{
	wd = _wd;
}
string HeroHelp::getwd_id(void)						//无敌技能Id
{
	return wd_id;
}
void   HeroHelp::setwd_id(string _wd_id)
{
	wd_id = _wd_id;
}
int    HeroHelp::getwd_contime(void)					//此技能持续时间
{
	return wd_contime;
}
void   HeroHelp::setwd_contime(int _wd_contime)
{
	wd_contime = _wd_contime;
}
	
int    HeroHelp::getwd_now_time(void)				//此技能触发时间
{
	return wd_now_time;
}
void   HeroHelp::setwd_now_time(int _wd_now_time)
{
	wd_now_time = _wd_now_time;
}
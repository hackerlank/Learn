#ifndef SKILL_CONFIGURATION_H
#define SKILL_CONFIGURATION_H
#include<iostream>
#include<string>
#include<map>
using namespace std;
class Skill_Configuration
{
private: 
			/*基础属性*/
			string id;           		//技能Id
			string name;         		//技能名称
			int    type;				//技能类型  （1，主动；2，被动；3，debuff；4，buff；5，医疗；）
			int    effect;              //技能附加效果
										/*
											主动：1：无；2：定身；3：点穴；4：击退；5：眩晕；6：降低敌方韧性；
												  7：附加降低敌方命中；8：单体攻击技能，附加敌人持续掉血效果；
												  9：单体攻击技能，附加中毒敌人攻防数值下降效果
											
											被动：1：增加人物血量上限；2：增加人物韧性；3：增加人物闪避；4：增加人物暴击；
												  5：增加人物命中；6：增加人物外功伤害；7：增加人物外功攻击；8：增加人物内功攻击；
												  9：增加人物外功防；10：增加人物内功防御
										*/
			int    con_time;            //效果持续时间
			int    cd_time;             //技能cd（冷却时间）
			int	   factor;              //技能系数基础值
			int    genuine;             //真气消耗
			int	   time_sec;            //技能动画播放时间（秒）
			int    time_usec;           //技能动画播放时间（微秒）
			int    last_time_sec;        //上次使用技能时间（秒）
			int    last_time_usec;       //上次使用技能时间（微妙）			
			int    skill_grade;         //技能等级			
			int	   factor_growup;		//技能系数成长参数 
			int    control_grade;		//等级限制	
			int    useup_money;			//玩家升级消耗的金钱
			int    useup_exp;			//玩家升级消耗的经验值	
			
			//int	   skill_book;			//玩家是否获取到技能书，1，获取到了；0，未获取到 	
			int    value1;				//候补属性1
			int    value2;				//候补属性2
			int    value3;			    //候补属性3
			/*主动攻击类型属性 */			
			int  nggjjdz_debuff;	    //debuff降低内功攻击
			int  wggjjdz_debuff;		//debuff降低外功攻击		
			int  ngfyjdz_debuff;		//debuff降低内功防御		
			int  wgfyjdz_debuff;		//debuff降低外功防御
			int  mzjd_debuff;			//debuff降低命中
			int  jdrx_debuff;			//debuff降低韧性
			int	 jdsb_debuff;			//debuff降低闪避
			int  jdbj_debuff;			//debuff降低暴击
			int  cxdx_debuff;			//持续掉血值
			int  attack_type;			//攻击形式
										/*攻击形式1：单体攻击；2：向前冲锋单体攻击；3：向后撤退单体攻击；
												  4：前方直线群体攻击；5：以玩家为中心可移动圆面群体攻击；
												  6：以玩家为圆心圆面群体攻击；7：以鼠标所点坐标为圆心圆面群体攻击
										*/
			int  attack_range;			//攻击距离
			int  genuine_growup;		//技能消耗成长参数
			int	 effect_growup;			//附加效果成长参数
			/*被动攻击属性 */
			int    smsxjdz_bd;          //附加生命上限
			int    wgshbfb_bd;          //附加外功伤害
			int    wggjbfb_bd;          //附加外功攻击
			int    nggjbfb_bd;          //附加内功攻击
			int    wgfybfb_bd;          //附加外功防御
			int    ngfybfb_bd;          //附加内功防御
			int    mzjdz_bd;            //附加命中
			int    bjjdz_bd;            //附加暴击
			int    sbjdz_bd;            //附加闪避
			int    rxjdz_bd;            //附加韧性
			int    fjxgcs_growup_bd;	//附加效果绝对值成长参数
			/*医疗技能属性   */
			int    cure_type;           //医疗形式：1，单体医疗；2，群体医疗
			
			/*buff技能属性   */
			int   zjngshbfb_buff;        //buff增加内功伤害
			int   zjwgshbfb_buff;        //buff增加外功伤害
			int   zjsmsx_buff;        	 //buff增加生命上限
			int   ftsh_buff;             //反弹伤害
			int   smxh_buff;       		 //生命消耗
			int   xxl_buff;              //吸血率
			int   cxsjcz_buff;           //持续时间初值
			int	  consumer_growth;		 //技能消耗成长参数
			int   cxsjcz_growup_buff;	 //技能持续时间成长参数
			int   cd_growup_buff;		 //技能CD成长参数      
			int   xg_growup_buff;		 //技能效果成长
public:
		/*主动攻击类型属性*/	
		Skill_Configuration(string _id,string _name,int _type,int _effect,int _con_time,int _cd_time,int _factor,
							int	_genuine,int _time_sec,int _time_usec,int  _nggjjdz_debuff,int _wggjjdz_debuff,
							int _ngfyjdz_debuff,int _wgfyjdz_debuff,int _mzjd_debuff,int _jdrx_debuff,int _jdsb_debuff,
							int _jdbj_debuff,int _cxdx_debuff,int _attack_type,int _attack_range,int _effect_growup,
							int _genuine_growup,int _factor_growup,int _control_grade,int _value1,int _value2,int _value3);						
		/*被动攻击属性  */
		Skill_Configuration(string _id,string _name,int _type,int _effect,int _smsxjdz_bd,int _wgshbfb_bd,int _wggjbfb_bd,
							int _nggjbfb_bd,int _wgfybfb_bd,int _ngfybfb_bd,int _mzjdz_bd,int _bjjdz_bd,int _sbjdz_bd,
							int _rxjdz_bd,int _fjxgcs_growup_bd,int _control_grade);
			/*医疗技能属性 */
		Skill_Configuration(string _id,string _name,int _type,int _effect,int _con_time,int _cd_time,int _factor,int _genuine,
							int _time_sec,int _time_usec,int _cure_type,int _factor_growup,int _control_grade,int _values1);


			/*buff技能属性   */
		Skill_Configuration(string _id,string _name,int _type,int _effect,int _cd_time,int _genuine,int _zjngshbfb_buff,
							int _zjwgshbfb_buff,int _zjsmsx_buff,int _ftsh_buff,int _smxh_buff,int _xxl_buff,int _cxsjcz_buff,
							int _consumer_growth,int _cxsjcz_growup_buff,int _cd_growup_buff,int _xg_growup_buff,int _control_grade);
			
			/*基础属性*/
			string getid(void);           		//技能Id
			string getname(void);         		//技能名称
			int    gettype(void);				//技能类型  （1，主动；2，被动；3，debuff；4，buff；5，医疗；）
			int    geteffect(void);              //技能附加效果
										/*
											主动：1：无；2：定身；3：点穴；4：击退；5：眩晕；6：降低敌方韧性；
												  7：附加降低敌方命中；8：单体攻击技能，附加敌人持续掉血效果；
												  9：单体攻击技能，附加中毒敌人攻防数值下降效果
											
											被动：1：增加人物血量上限；2：增加人物韧性；3：增加人物闪避；4：增加人物暴击；
												  5：增加人物命中；6：增加人物外功伤害；7：增加人物外功攻击；8：增加人物内功攻击；
												  9：增加人物外功防；10：增加人物内功防御
										*/
			int    getcon_time(void);            //效果持续时间

			
			int    getcd_time(void);             //技能cd（冷却时间）

			
			int	   getfactor(void);              //技能系数基础值

			
			int    getgenuine(void);             //真气消耗

			
			int	   gettime_sec(void);            //技能动画播放时间（秒）

			
			int    gettime_usec(void);           //技能动画播放时间（微秒）

			
			int    getlast_time_sec(void);//技能上次使用时间：秒

		    
			int    getlast_time_usec(void); //技能上次使用时间：微秒

			int    getskill_grade(void);          //技能等级

			
			int	   getfactor_growup(void);		//技能系数成长参数   2012.6.19 evan
			
			int    getcontrol_grade(void);		//等级限制  2012.6.25 evan
	

			int    getuseup_money(void);			//玩家升级消耗的金钱 2012.6.25 evan

			
			int    getuseup_exp(void);			//玩家升级消耗的经验值	2012.6.25	evan
		
			
			//int	   getskill_book(void);			//玩家是否获取到技能书，1，获取到了；0，未获取到 	2012.6.25	evan
			//void   setskill_book(int _skill_book);
			
			int    getvalue1(void);				//候补属性1
			int    getvalue2(void);				//候补属性2
			int    getvalue3(void);			    //候补属性3
			/*主动攻击类型属性    */
			int    getnggjjdz_debuff(void);	    //debuff降低内功攻击
			int    getwggjjdz_debuff(void);		//debuff降低外功攻击		
			int    getngfyjdz_debuff(void);		//debuff降低内功防御		
			int    getwgfyjdz_debuff(void);		//debuff降低外功防御
			int    getmzjd_debuff(void);			//debuff降低命中
			int    getjdrx_debuff(void);			//debuff降低韧性
			int	   getjdsb_debuff(void);			//debuff降低闪避
			int    getjdbj_debuff(void);			//debuff降低暴击
			int    getcxdx_debuff(void);			//持续掉血值
			int    getattack_type(void);			//攻击形式
										/*攻击形式1：单体攻击；2：向前冲锋单体攻击；3：向后撤退单体攻击；
												  4：前方直线群体攻击；5：以玩家为中心可移动圆面群体攻击；
												  6：以玩家为圆心圆面群体攻击；7：以鼠标所点坐标为圆心圆面群体攻击
										*/
			int    getattack_range(void);			//攻击距离
			int    getgenuine_growup(void);		//技能消耗成长参数
			int	   geteffect_growup(void);			//附加效果成长参数
			/*被动攻击属性 */
			int    getsmsxjdz_bd(void);          //附加生命上限
			int    getwgshbfb_bd(void);          //附加外功伤害
			int    getwggjbfb_bd(void);          //附加外功攻击
			int    getnggjbfb_bd(void);          //附加内功攻击
			int    getwgfybfb_bd(void);          //附加外功防御
			int    getngfybfb_bd(void);          //附加内功防御
			int    getmzjdz_bd(void);            //附加命中
			int    getbjjdz_bd(void);            //附加暴击
			int    getsbjdz_bd(void);            //附加闪避
			int    getrxjdz_bd(void);            //附加韧性
			int    getfjxgcs_growup_bd(void);	//附加效果绝对值成长参数
			/*医疗技能属性   */
			int    getcure_type(void);           //医疗形式：1，单体医疗；2，群体医疗
			
			/*buff技能属性   */
			int    getzjngshbfb_buff(void);        //buff增加内功伤害
			int    getzjwgshbfb_buff(void);        //buff增加外功伤害
			int    getzjsmsx_buff(void);        	 //buff增加生命上限
			int    getftsh_buff(void);             //反弹伤害
			int    getsmxh_buff(void);       		 //生命消耗
			int    getxxl_buff(void);              //吸血率
			int    getcxsjcz_buff(void);           //持续时间初值
			int	   getconsumer_growth(void);		 //技能消耗成长参数
			int    getcxsjcz_growup_buff(void);	 //技能持续时间成长参数
			int    getcd_growup_buff(void);		 //技能CD成长参数      
			int    getxg_growup_buff(void);		 //技能效果成长
			~Skill_Configuration(void);
};
#endif

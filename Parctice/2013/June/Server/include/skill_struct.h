#ifndef SKILL_STRUCT
#define SKILL_STRUCT
typedef struct
{
/*基础属性*/
	char identity[50],id[50],name[50];	
	int    type;				//技能类型  （1，主动；2，被动；3，debuff；4，buff；5，医疗；）
	int    effect;              //技能附加效果
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
	int    value1;				//候补属性1
	int    value2;				//候补属性2
	int    value3;			    //候补属性3
	/*主动攻击类型属性   */ 
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
	int  attack_range;			//攻击距离
	int  genuine_growup;		//技能消耗成长参数
	int	 effect_growup;			//附加效果成长参数
	/*被动攻击属性  14*/
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
	/*医疗技能属性   1*/
	int    cure_type;           //医疗形式：1，单体医疗；2，群体医	
	/*buff技能属性   8*/
	int   zjngshbfb_buff;        //buff增加内功伤害
	int   zjwgshbfb_buff;        //buff增加外功伤害
	int   zjsmsx_buff;        	 //buff增加生命
	int   ftsh_buff;             //反弹伤害
	int   smxh_buff;       		 //生命消耗
	int   xxl_buff;              //吸血率
	int   cxsjcz_buff;           //持续时间初值
	int	  consumer_growth;		 //技能消耗成长参数
	int   cxsjcz_growup_buff;	 //技能持续时间成长参数
	int   cd_growup_buff;		 //技能CD成长参数      
	int   xg_growup_buff;		 //技能效果成长
}MemSkill;
#endif
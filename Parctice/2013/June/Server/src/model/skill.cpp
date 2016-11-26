/*********************************************************** 
文件类型：	头文件

文件名称：	skill.h

文件作用：	实体类Slill(技能)的属性和功能的定义
			文件未完：1》攻击范围
					2》耗魔值
					3》组合技能
			完成者：Evan
完成时间：2012-2-22 16:07

修改者：

修改时间：

修改内容：
*************************************************************/
#include<string.h>
#include"skill.h"
#include"command_other_function_all_over.h"


Skill::Skill(MemSkill _memskill)
{
	memskill = _memskill;
	strncpy(identity,memskill.identity,sizeof(identity));
	identity[strlen(memskill.identity)]='\0';
	id = memskill.id;     
	name = memskill.name;       
	type = memskill.type;			
	effect = memskill.effect;        
	con_time = memskill.con_time;           
	cd_time = memskill.cd_time;            
	factor = memskill.factor;           
	genuine = memskill.genuine;         
	time_sec = memskill.time_sec;         
	time_usec = memskill.time_usec;         
	last_time_sec = memskill.last_time_sec;    
	last_time_usec = memskill.last_time_usec;   	
	skill_grade = memskill.skill_grade;    
	factor_growup = memskill.factor_growup;	
	control_grade = memskill.control_grade;	
	useup_money = memskill.useup_money;		
	useup_exp = memskill.useup_exp;		
	value1 = memskill.value1;			
	value2 = memskill.value2;			
	value3 = memskill.value3;			   
	nggjjdz_debuff = memskill.nggjjdz_debuff;	 
	wggjjdz_debuff = memskill.wggjjdz_debuff;
	ngfyjdz_debuff = memskill.ngfyjdz_debuff;
	wgfyjdz_debuff = memskill.wgfyjdz_debuff;
	mzjd_debuff = memskill.mzjd_debuff;	
	jdrx_debuff = memskill.jdrx_debuff;	
	jdsb_debuff = memskill.jdsb_debuff;	
	jdbj_debuff = memskill.jdbj_debuff;	
	cxdx_debuff = memskill.cxdx_debuff;	
	attack_type = memskill.attack_type;		
	attack_range = memskill.attack_range;
	genuine_growup = memskill.genuine_growup;	
	effect_growup = memskill.effect_growup;
	smsxjdz_bd = memskill.smsxjdz_bd; 
	wgshbfb_bd = memskill.wgshbfb_bd;
	wggjbfb_bd = memskill.wggjbfb_bd;      
	nggjbfb_bd = memskill.nggjbfb_bd;   
	wgfybfb_bd = memskill.wgfybfb_bd;        
	ngfybfb_bd = memskill.ngfybfb_bd;     
	mzjdz_bd = memskill.mzjdz_bd;         
	bjjdz_bd = memskill.bjjdz_bd;      
	sbjdz_bd = memskill.sbjdz_bd;          
	rxjdz_bd = memskill.rxjdz_bd;          
	fjxgcs_growup_bd = memskill.fjxgcs_growup_bd;
	cure_type = memskill.cure_type;
	zjngshbfb_buff = memskill.zjngshbfb_buff;   
	zjwgshbfb_buff = memskill.zjwgshbfb_buff;   
	zjsmsx_buff = memskill.zjsmsx_buff;   
	ftsh_buff = memskill.ftsh_buff;    
	smxh_buff = memskill.smxh_buff;     
	xxl_buff = memskill.xxl_buff;         
	cxsjcz_buff = memskill.cxsjcz_buff;     
	consumer_growth = memskill.consumer_growth;		
	cxsjcz_growup_buff = memskill.cxsjcz_growup_buff;	
	cd_growup_buff = memskill.cd_growup_buff;	
	xg_growup_buff = memskill.xg_growup_buff;		
}
void Skill::newmem(void)
{
	strcpy(memskill.identity,identity);
	strcpy(memskill.id,id.c_str());
	strcpy(memskill.name,name.c_str());
	memskill.type = type;			
	memskill.effect = effect;        
	memskill.con_time = con_time;           
	memskill.cd_time = cd_time;            
	memskill.factor = factor;           
	memskill.genuine = genuine;         
	memskill.time_sec = time_sec;         
	memskill.time_usec = time_usec;         
	memskill.last_time_sec = last_time_sec;    
	memskill.last_time_usec = last_time_usec;   	
	memskill.skill_grade = skill_grade;    
	memskill.factor_growup = factor_growup;	
	memskill.control_grade = control_grade;	
	memskill.useup_money = useup_money;		
	memskill.useup_exp = useup_exp;		
	memskill.value1 = value1;			
	memskill.value2 = value2;			
	memskill.value3 = value3;			   
	memskill.nggjjdz_debuff = nggjjdz_debuff;	 
	memskill.wggjjdz_debuff = wggjjdz_debuff;
	memskill.ngfyjdz_debuff = ngfyjdz_debuff;
	memskill.wgfyjdz_debuff = wgfyjdz_debuff;
	memskill.mzjd_debuff = mzjd_debuff;	
	memskill.jdrx_debuff = jdrx_debuff;	
	memskill.jdsb_debuff = jdsb_debuff;	
	memskill.jdbj_debuff = jdbj_debuff;	
	memskill.cxdx_debuff = cxdx_debuff;	
	memskill.attack_type = attack_type;		
	memskill.attack_range = attack_range;
	memskill.genuine_growup = genuine_growup;	
	memskill.effect_growup = effect_growup;
	memskill.smsxjdz_bd = smsxjdz_bd; 
	memskill.wgshbfb_bd = wgshbfb_bd;
	memskill.wggjbfb_bd = wggjbfb_bd;      
	memskill.nggjbfb_bd = nggjbfb_bd;   
	memskill.wgfybfb_bd = wgfybfb_bd;        
	memskill.ngfybfb_bd = ngfybfb_bd;     
	memskill.mzjdz_bd = mzjdz_bd;         
	memskill.bjjdz_bd = bjjdz_bd;      
	memskill.sbjdz_bd = sbjdz_bd;          
	memskill.rxjdz_bd = rxjdz_bd;          
	memskill.fjxgcs_growup_bd = fjxgcs_growup_bd;
	memskill.cure_type = cure_type;
	memskill.zjngshbfb_buff = zjngshbfb_buff;   
	memskill.zjwgshbfb_buff = zjwgshbfb_buff;   
	memskill.zjsmsx_buff = zjsmsx_buff;   
	memskill.ftsh_buff = ftsh_buff;    
	memskill.smxh_buff = smxh_buff;     
	memskill.xxl_buff = xxl_buff;         
	memskill.cxsjcz_buff = cxsjcz_buff;     
	memskill.consumer_growth = consumer_growth;		
	memskill.cxsjcz_growup_buff = cxsjcz_growup_buff;	
	memskill.cd_growup_buff = cd_growup_buff;	
	memskill.xg_growup_buff = xg_growup_buff;
}

//----------------------------------------memcached end------------------------------------------------------------
Skill::Skill(Skill_Configuration *skill_configuration)   //evan add 2012.9.17
{
	char* uuid = cid();
	strcpy(identity,uuid);
	free(uuid); //by benliao to avoid mem leak 20121129
	id = skill_configuration->getid();     
	name = skill_configuration->getname();       
	type = skill_configuration->gettype(); 			
	effect = skill_configuration->geteffect();        
	con_time = skill_configuration->getcon_time();            
	cd_time = skill_configuration->getcd_time();             
	factor = skill_configuration->getfactor();            
	genuine = skill_configuration->getgenuine();          
	time_sec = skill_configuration->gettime_sec();          
	time_usec = skill_configuration->gettime_usec();          
	last_time_sec = 0;     
	last_time_usec = 0;    	
	skill_grade = 1;     
	factor_growup = skill_configuration->getfactor_growup(); 	
	control_grade = skill_configuration->getcontrol_grade(); 	
	useup_money = 0; 		
	useup_exp = 0 ;		
	value1 = skill_configuration->getvalue1(); 			
	value2 = skill_configuration->getvalue2(); 			
	value3 = skill_configuration->getvalue3(); 			   
	nggjjdz_debuff = skill_configuration->getnggjjdz_debuff(); 	 
	wggjjdz_debuff = skill_configuration->getwggjjdz_debuff(); 
	ngfyjdz_debuff = skill_configuration->getngfyjdz_debuff(); 
	wgfyjdz_debuff = skill_configuration->getwgfyjdz_debuff(); 
	mzjd_debuff = skill_configuration->getmzjd_debuff(); 	
	jdrx_debuff = skill_configuration->getjdrx_debuff(); 	
	jdsb_debuff = skill_configuration->getjdsb_debuff(); 	
	jdbj_debuff = skill_configuration->getjdbj_debuff(); 	
	cxdx_debuff = skill_configuration->getcxdx_debuff(); 	
	attack_type = skill_configuration->getattack_type(); 		
	attack_range = skill_configuration->getattack_range(); 
	genuine_growup = skill_configuration->getgenuine_growup(); 	
	effect_growup = skill_configuration->geteffect_growup(); 
	smsxjdz_bd = skill_configuration->getsmsxjdz_bd();  
	wgshbfb_bd = skill_configuration->getwgshbfb_bd(); 
	wggjbfb_bd = skill_configuration->getwggjbfb_bd();       
	nggjbfb_bd = skill_configuration->getnggjbfb_bd();    
	wgfybfb_bd = skill_configuration->getwgfybfb_bd();         
	ngfybfb_bd = skill_configuration->getngfybfb_bd();      
	mzjdz_bd = skill_configuration->getmzjdz_bd();          
	bjjdz_bd = skill_configuration->getbjjdz_bd();       
	sbjdz_bd = skill_configuration->getsbjdz_bd();           
	rxjdz_bd = skill_configuration->getrxjdz_bd();           
	fjxgcs_growup_bd = skill_configuration->getfjxgcs_growup_bd(); 
	cure_type = skill_configuration->getcure_type(); 
	zjngshbfb_buff = skill_configuration->getzjngshbfb_buff();    
	zjwgshbfb_buff = skill_configuration->getzjwgshbfb_buff();    
	zjsmsx_buff = skill_configuration->getzjsmsx_buff();    
	ftsh_buff = skill_configuration->getftsh_buff();     
	smxh_buff = skill_configuration->getsmxh_buff();      
	xxl_buff = skill_configuration->getxxl_buff();          
	cxsjcz_buff = skill_configuration->getcxsjcz_buff();      
	consumer_growth = skill_configuration->getconsumer_growth(); 		
	cxsjcz_growup_buff = skill_configuration->getcxsjcz_growup_buff(); 	
	cd_growup_buff = skill_configuration->getcd_growup_buff(); 	
	xg_growup_buff = skill_configuration->getxg_growup_buff(); 
}
//extern Mem mem;
/*主动攻击类型属性  22*/
		Skill::Skill(string _id,string _name,int _type,int _effect,int _con_time,int _cd_time,int _factor,
							int	_genuine,int _time_sec,int _time_usec,int  _nggjjdz_debuff,int _wggjjdz_debuff,
							int _ngfyjdz_debuff,int _wgfyjdz_debuff,int _mzjd_debuff,int _jdrx_debuff,int _jdsb_debuff,
							int _jdbj_debuff,int _cxdx_debuff,int _attack_type,int _attack_range,int _effect_growup,
							int _genuine_growup,int _factor_growup,int _control_grade,int _useup_money,int _useup_exp,int _value1)
		{
			char* uuid = cid();
			strcpy(identity,uuid);
			free(uuid);
			id = _id;     
			name = _name;       
			type = _type;			
			effect = _effect;        
			con_time = _con_time;           
			cd_time = _cd_time;            
			factor = _factor;           
			genuine = _genuine;         
			time_sec = _time_sec;         
			time_usec = _time_usec;         
			last_time_sec = 0;    
			last_time_usec = 0;   	
			skill_grade = 1;    
			factor_growup = _factor_growup;	
			control_grade = _control_grade;	
			useup_money = _useup_money;		
			useup_exp = _useup_exp;		
			value1 = _value1;			
			value2 = 0;			
			value3 = 0;			   
			nggjjdz_debuff = _nggjjdz_debuff;	 
			wggjjdz_debuff = _wggjjdz_debuff;
			ngfyjdz_debuff = _ngfyjdz_debuff;
			wgfyjdz_debuff = _wgfyjdz_debuff;
			mzjd_debuff = _mzjd_debuff;	
			jdrx_debuff = _jdrx_debuff;	
			jdsb_debuff = _jdsb_debuff;	
			jdbj_debuff = _jdbj_debuff;	
			cxdx_debuff = _cxdx_debuff;	
			attack_type = _attack_type;		
			attack_range = _attack_range;
			genuine_growup = _genuine_growup;	
			effect_growup = _effect_growup;
			smsxjdz_bd = 0; 
			wgshbfb_bd = 0;
			wggjbfb_bd = 0;      
			nggjbfb_bd = 0;   
			wgfybfb_bd = 0;        
			ngfybfb_bd = 0;     
			mzjdz_bd = 0;         
			bjjdz_bd = 0;      
			sbjdz_bd = 0;          
			rxjdz_bd = 0;          
			fjxgcs_growup_bd = 0;
			cure_type = 0;
			zjngshbfb_buff = 0;   
			zjwgshbfb_buff = 0;   
			zjsmsx_buff = 0;   
			ftsh_buff = 0;    
			smxh_buff = 0;     
			xxl_buff = 0;         
			cxsjcz_buff = 0;     
			consumer_growth = 0;		
			cxsjcz_growup_buff = 0;	
			cd_growup_buff = 0;	
			xg_growup_buff = 0;	
		}		
	
		/*被动攻击属性  18*/
		Skill::Skill(string _id,string _name,int _type,int _effect,int _smsxjdz_bd,int _wgshbfb_bd,int _wggjbfb_bd,
							int _nggjbfb_bd,int _wgfybfb_bd,int _ngfybfb_bd,int _mzjdz_bd,int _bjjdz_bd,int _sbjdz_bd,
							int _rxjdz_bd,int _fjxgcs_growup_bd,int _control_grade,int _useup_money,int _useup_exp)
		{
			char* uuid = cid();
			strcpy(identity,uuid);
			free(uuid);
			id = _id;     
			name = _name;       
			type = _type;			
			effect = _effect;        
			con_time = 0;           
			cd_time = 0;            
			factor = 0;           
			genuine = 0;         
			time_sec = 1;         
			time_usec = 0;         
			last_time_sec = 0;    
			last_time_usec = 0;   	
			skill_grade = 1;    
			factor_growup = 0;	
			control_grade = _control_grade;	
			useup_money = _useup_money;		
			useup_exp = _useup_exp;		
			value1 = 0;			
			value2 = 0;			
			value3 = 0;			   
			nggjjdz_debuff = 0;	 
			wggjjdz_debuff = 0;
			ngfyjdz_debuff = 0;
			wgfyjdz_debuff = 0;
			mzjd_debuff = 0;	
			jdrx_debuff = 0;	
			jdsb_debuff = 0;	
			jdbj_debuff = 0;	
			cxdx_debuff = 0;	
			attack_type = 0;		
			attack_range = 0;
			genuine_growup = 0;	
			effect_growup = 0;
			smsxjdz_bd = _smsxjdz_bd; 
			wgshbfb_bd = _wgshbfb_bd;
			wggjbfb_bd = _wggjbfb_bd;      
			nggjbfb_bd = _nggjbfb_bd;   
			wgfybfb_bd = _wgfybfb_bd;        
			ngfybfb_bd = _ngfybfb_bd;     
			mzjdz_bd = _mzjdz_bd;         
			bjjdz_bd = _bjjdz_bd;      
			sbjdz_bd = _sbjdz_bd;          
			rxjdz_bd = _rxjdz_bd;          
			fjxgcs_growup_bd = _fjxgcs_growup_bd;
			cure_type = 0;
			zjngshbfb_buff = 0;   
			zjwgshbfb_buff = 0;   
			zjsmsx_buff = 0;   
			ftsh_buff = 0;    
			smxh_buff = 0;     
			xxl_buff = 0;         
			cxsjcz_buff = 0;     
			consumer_growth = 0;		
			cxsjcz_growup_buff = 0;	
			cd_growup_buff = 0;	
			xg_growup_buff = 0;		
		}
			
			/*医疗技能属性   11*/
		Skill::Skill(string _id,string _name,int _type,int _effect,int _con_time,int _cd_time,int _factor,int _genuine,
							int _time_sec,int _time_usec,int _cure_type,int _factor_growup,int _control_grade,
							int _useup_money,int _useup_exp)
		{
			char* uuid = cid();
			strcpy(identity,uuid);
			free(uuid);
			id = _id;     
			name = _name;       
			type = _type;			
			effect = _effect;        
			con_time = _con_time;           
			cd_time = _cd_time;            
			factor = _factor;           
			genuine = _genuine;         
			time_sec = _time_sec;         
			time_usec = _time_usec;         
			last_time_sec = 0;    
			last_time_usec = 0;   	
			skill_grade = 1;    
			factor_growup = _factor_growup;	
			control_grade = _control_grade;	
			useup_money = _useup_money;		
			useup_exp = _useup_exp;		
			value1 = 0;			
			value2 = 0;			
			value3 = 0;			   
			nggjjdz_debuff = 0;	 
			wggjjdz_debuff = 0;
			ngfyjdz_debuff = 0;
			wgfyjdz_debuff = 0;
			mzjd_debuff = 0;	
			jdrx_debuff = 0;	
			jdsb_debuff = 0;	
			jdbj_debuff = 0;	
			cxdx_debuff = 0;	
			attack_type = 0;		
			attack_range = 0;
			genuine_growup = 0;	
			effect_growup = 0;
			smsxjdz_bd = 0; 
			wgshbfb_bd = 0;
			wggjbfb_bd = 0;      
			nggjbfb_bd = 0;   
			wgfybfb_bd = 0;        
			ngfybfb_bd = 0;     
			mzjdz_bd = 0;         
			bjjdz_bd = 0;      
			sbjdz_bd = 0;          
			rxjdz_bd = 0;          
			fjxgcs_growup_bd = 0;
			cure_type = _cure_type;
			zjngshbfb_buff = 0;   
			zjwgshbfb_buff = 0;   
			zjsmsx_buff = 0;   
			ftsh_buff = 0;    
			smxh_buff = 0;     
			xxl_buff = 0;         
			cxsjcz_buff = 0;     
			consumer_growth = 0;		
			cxsjcz_growup_buff = 0;	
			cd_growup_buff = 0;	
			xg_growup_buff = 0;	
		}

			/*buff技能属性   8*/
		Skill::Skill(string _id,string _name,int _type,int _effect,int _cd_time,int _genuine,int _zjngshbfb_buff,
							int _zjwgshbfb_buff,int _zjsmsx_buff,int _ftsh_buff,int _smxh_buff,int _xxl_buff,int _cxsjcz_buff,
							int _consumer_growth,int _cxsjcz_growup_buff,int _cd_growup_buff,int _xg_growup_buff,int _control_grade,
							int _useup_money,int _useup_exp)
		{
			char* uuid = cid();
			strcpy(identity,uuid);
			free(uuid);

			id = _id;     
			name = _name;       
			type = _type;			
			effect = _effect;        
			con_time = 0;           
			cd_time = _cd_time;            
			factor = 0;           
			genuine = _genuine;         
			time_sec = 1;         
			time_usec = 0;         
			last_time_sec = 0;    
			last_time_usec = 0;   	
			skill_grade = 1;    
			factor_growup = 0;	
			control_grade = _control_grade;	
			useup_money = _useup_money;		
			useup_exp = _useup_exp;		
			value1 = 0;			
			value2 = 0;			
			value3 = 0;			   
			nggjjdz_debuff = 0;	 
			wggjjdz_debuff = 0;
			ngfyjdz_debuff = 0;
			wgfyjdz_debuff = 0;
			mzjd_debuff = 0;	
			jdrx_debuff = 0;	
			jdsb_debuff = 0;	
			jdbj_debuff = 0;	
			cxdx_debuff = 0;	
			attack_type = 0;		
			attack_range = 0;
			genuine_growup = 0;	
			effect_growup = 0;
			smsxjdz_bd = 0; 
			wgshbfb_bd = 0;
			wggjbfb_bd = 0;      
			nggjbfb_bd = 0;   
			wgfybfb_bd = 0;        
			ngfybfb_bd = 0;     
			mzjdz_bd = 0;         
			bjjdz_bd = 0;      
			sbjdz_bd = 0;          
			rxjdz_bd = 0;          
			fjxgcs_growup_bd = 0;
			cure_type = 0;
			zjngshbfb_buff = _zjngshbfb_buff;   
			zjwgshbfb_buff = _zjwgshbfb_buff;   
			zjsmsx_buff = _zjsmsx_buff;   
			ftsh_buff = _ftsh_buff;    
			smxh_buff = _smxh_buff;     
			xxl_buff = _xxl_buff;         
			cxsjcz_buff = _cxsjcz_buff;     
			consumer_growth = _consumer_growth;		
			cxsjcz_growup_buff = _cxsjcz_growup_buff;	
			cd_growup_buff = _cd_growup_buff;	
			xg_growup_buff = _xg_growup_buff;	
		}
		MemSkill* Skill::getmemskill(void)  //evan add 2012.9.17
		{
			return &memskill;
		}
		char* Skill::getidentity(void)			//技能实例Id	evan add 2012.8.3
		{
			return identity;
		}
			/*基础属性*/
		string Skill::getid(void)           		//技能Id
		{
			return id;
		}
		string Skill::getname(void)         		//技能名称
		{
			return name;
		}
		int    Skill::gettype(void)				//技能类型  （1，主动；2，被动；3，debuff；4，buff；5，医疗；）
		{
			return type;
		}
		int    Skill::geteffect(void)              //技能附加效果
		{
			return effect;
		}
			
		int    Skill::getcon_time(void)            //效果持续时间
		{
			return con_time;
		}
		void   Skill::setcon_time(int _con_time)
		{
			con_time = _con_time;
			string key = id + "con_time";
			string value = itos(con_time);
			//mem.rep(key,value);
		}
		
		int    Skill::getcd_time(void)             //技能cd（冷却时间）
		{
			return cd_time;
		}
		void   Skill::setcd_time(int _cd_time)
		{
			cd_time = _cd_time;
			string key = id + "cd_time";
			string value = itos(cd_time);
			//mem.rep(key,value);
		}
		
		int	   Skill::getfactor(void)              //技能系数基础值
		{
			return factor;
		}
		void   Skill::setfactor(int _factor)
		{
			factor = _factor;
			string key = id + "factor";
			string value = itos(factor);
			//mem.rep(key,value);
		}
			
		int    Skill::getgenuine(void)             //真气消耗
		{
			return genuine;
		}
		void   Skill::setgenuine(int _genuine)
		{
			genuine = _genuine;
		}
			
		int	   Skill::gettime_sec(void)            //技能动画播放时间（秒）
		{
			return time_sec;
		}
		void   Skill::settime_sec(int _time_sec)
		{
			time_sec = _time_sec;
			string key = id + "time_sec";
			string value = itos(time_sec);
			//mem.rep(key,value);
		}
			
		int    Skill::gettime_usec(void)           //技能动画播放时间（微秒）
		{
			return time_usec;
		}
		void   Skill::settime_usec(int _time_usec)
		{
			time_usec = _time_usec;
			string key = id + "time_usec";
			string value = itos(time_usec);
			//mem.rep(key,value);
		}
		
		int    Skill::getlast_time_sec(void)//技能上次使用时间：秒
		{
			return last_time_sec;
		}
		void   Skill::setlast_time_sec(int _last_time_sec)
		{
			last_time_sec = _last_time_sec;
			string key = id + "last_time_sec";
			string value = itos(last_time_sec);
			//mem.rep(key,value);
		}
		    
		int    Skill::getlast_time_usec(void) //技能上次使用时间：微秒
		{	
			return last_time_usec;
		}
		void   Skill::setlast_time_usec(int _last_time_usec)
		{
			last_time_usec = _last_time_usec;
			string key = id + "last_time_usec";
			string value = itos(last_time_usec);
			//mem.rep(key,value);
		}
			
		
		int   Skill::getskill_grade(void)          //技能等级
		{
			return skill_grade;
		}
		void  Skill::setskill_grade(int _skill_grade)
		{
			skill_grade = _skill_grade;
			string key = id + "skill_grade";
			string value = itos(skill_grade);
			//mem.rep(key,value);
		}
		
		int	  Skill::getfactor_growup(void)		//技能系数成长参数   2012.6.19 evan
		{
			return factor_growup;
		}
		
		int    Skill::getcontrol_grade(void)		//等级限制  2012.6.25 evan
		{
			return control_grade;
		}
		void   Skill::setcontrol_grade(int _control_grade)
		{
			control_grade = _control_grade;
			string key = id + "control_grade";
			string value = itos(control_grade);
			//mem.rep(key,value);
		}
		int    Skill::getuseup_money(void)			//玩家升级消耗的金钱 2012.6.25 evan
		{
			return useup_money;
		}
		void   Skill::setuseup_money(int _useup_money)
		{
			useup_money = _useup_money;
			string key = id + "useup_money";
			string value = itos(useup_money);
			//mem.rep(key,value);
		}
			
		int    Skill::getuseup_exp(void)			//玩家升级消耗的经验值	2012.6.25	evan
		{
			return useup_exp;
		}
		void   Skill::setuseup_exp(int _useup_exp)
		{
			useup_exp = _useup_exp;
			string key = id + "useup_exp";
			string value = itos(useup_exp);
			//mem.rep(key,value);
		}
		
		int    Skill::getvalue1(void)			//候补属性1
		{
			return value1;
		}
		int    Skill::getvalue2(void)				//候补属性2
		{
			return value2;
		}
		int    Skill::getvalue3(void)			    //候补属性3
		{
			return value3;
		}
			
			/*主动攻击类型属性    12*/
		int   Skill::getnggjjdz_debuff(void)	    //debuff降低内功攻击绝对值
		{
			return nggjjdz_debuff;
		}
		void  Skill::setnggjjdz_debuff(int _nggjjdz_debuff)
		{
			nggjjdz_debuff = _nggjjdz_debuff;
			string key = id + "nggjjdz_debuff";
			string value = itos(nggjjdz_debuff);
			//mem.rep(key,value);	
		}
		int   Skill::getwggjjdz_debuff(void)		//debuff降低外功攻击绝对值
		{
			return wggjjdz_debuff;
		}
		void  Skill::setwggjjdz_debuff(int _wggjjdz_debuff)
		{
			wggjjdz_debuff = _wggjjdz_debuff;
			string key = id + "wggjjdz_debuff";
			string value = itos(wggjjdz_debuff);
			//mem.rep(key,value);				
		}
			
		int   Skill::getngfyjdz_debuff(void)		//debuff降低内功防御绝对值
		{
			return ngfyjdz_debuff;
		}
		void  Skill::setngfyjdz_debuff(int _ngfyjdz_debuff)
		{
			ngfyjdz_debuff = _ngfyjdz_debuff;
			string key = id + "ngfyjdz_debuff";
			string value = itos(ngfyjdz_debuff);
			//mem.rep(key,value);				
		}
			
		int   Skill::getwgfyjdz_debuff(void)		//debuff降低外功防御绝对值
		{
			return wgfyjdz_debuff;
		}
		void  Skill::setwgfyjdz_debuff(int _wgfyjdz_debuff)
		{
			wgfyjdz_debuff = _wgfyjdz_debuff;
			string key = id + "wgfyjdz_debuff";
			string value = itos(wgfyjdz_debuff);
			//mem.rep(key,value);				
		}
			
		int   Skill::getmzjd_debuff(void)		//debuff降低命中绝对值
		{
			return mzjd_debuff;
		}
		void  Skill::setmzjd_debuff(int _mzjd_debuff)
		{
			mzjd_debuff = _mzjd_debuff;
			string key = id + "mzjd_debuff";
			string value = itos(mzjd_debuff);
			//mem.rep(key,value);	
		}
			
		int   Skill::getjdrx_debuff(void)		//debuff降低韧性绝对值
		{
			return jdrx_debuff;
		}
		void  Skill::setjdrx_debuff(int _jdrx_debuff)
		{
			jdrx_debuff = _jdrx_debuff;
			string key = id + "jdrx_debuff";
			string value = itos(jdrx_debuff);
			//mem.rep(key,value);
		}	
		int	  Skill::getjdsb_debuff(void)		//debuff降低闪避绝对值
		{
			return jdsb_debuff;
		}
		void  Skill::setjdsb_debuff(int _jdsb_debuff)
		{
			jdsb_debuff = _jdsb_debuff;
			string key = id + "jdsb_debuff";
			string value = itos(jdsb_debuff);
			//mem.rep(key,value);
		}	

		int   Skill::getjdbj_debuff(void)		//debuff降低暴击绝对值
		{
			return jdbj_debuff;
		}
		void  Skill::setjdbj_debuff(int _jdbj_debuff)
		{	
			jdbj_debuff = _jdbj_debuff;
			string key = id + "jdbj_debuff";
			string value = itos(jdbj_debuff);
			//mem.rep(key,value);
		}	

		int   Skill::getcxdx_debuff(void)		//持续掉血百分比
		{
			return cxdx_debuff;
		}
		void  Skill::setcxdx_debuff(int _cxdx_debuff)
		{
			cxdx_debuff = _cxdx_debuff;
			string key = id + "cxdx_debuff";
			string value = itos(cxdx_debuff);
			//mem.rep(key,value);
		}	

		int    Skill::getattack_type(void)         //攻击形式
		{
			return attack_type;
		}
		void   Skill::setattack_type(int _attack_type)
		{
			attack_type = _attack_type;
			string key = id + "attack_type";
			string value = itos(attack_type);
			//mem.rep(key,value);
		}	

		int    Skill::getattack_range(void)        //攻击距离
		{
			return attack_range;
		}
		void   Skill::setattack_range(int _attack_range)
		{
			attack_range = _attack_range;
			string key = id + "attack_range";
			string value = itos(attack_range);
			//mem.rep(key,value);
		}	
		int   Skill::getgenuine_growup(void)		//技能消耗成长参数
		{
			return genuine_growup;
		}
		void  Skill::setgenuine_growup(int _genuine_growup)
		{
			genuine_growup = _genuine_growup;
			string key = id + "genuine_growup";
			string value = itos(genuine_growup);
			//mem.rep(key,value);
		}
			
		int	  Skill::geteffect_growup(void)			//附加效果成长参数
		{
			return effect_growup;
		}
		void  Skill::seteffect_growup(int _effect_growup)
		{
			effect_growup = _effect_growup;
			string key = id + "effect_growup";
			string value = itos(effect_growup);
			//mem.rep(key,value);
		}
			/*被动攻击属性  14*/
		int   Skill::getsmsxjdz_bd(void)          //附加生命上限
		{
			return smsxjdz_bd;
		}
		void  Skill::setsmsxjdz_bd(int _smsxjdz_bd)
		{
			smsxjdz_bd = _smsxjdz_bd;
			string key = id + "smsxjdz_bd";
			string value = itos(smsxjdz_bd);
			//mem.rep(key,value);
		}

		int    Skill::getwgshbfb_bd(void)          //附加外功伤害百分比
		{
			return wgshbfb_bd;
		}
		void   Skill::setwgshbfb_bd(int _wgshbfb_bd)
		{
			wgshbfb_bd = _wgshbfb_bd;
			string key = id + "wgshbfb_bd";
			string value = itos(wgshbfb_bd);
			//mem.rep(key,value);
		}	

		int    Skill::getwggjbfb_bd(void)          //附加外功攻击百分比
		{
			return wggjbfb_bd;
		}
		void   Skill::setwggjbfb_bd(int _wggjbfb_bd)
		{
			wggjbfb_bd = _wggjbfb_bd;
			string key = id + "wggjbfb_bd";
			string value = itos(wggjbfb_bd);
			//mem.rep(key,value);
		}	

		int    Skill::getnggjbfb_bd(void)          //附加内功攻击百分比
		{
			return nggjbfb_bd;
		}
		void   Skill::setnggjbfb_bd(int _nggjbfb_bd)
		{
			nggjbfb_bd = _nggjbfb_bd;
			string key = id + "nggjbfb_bd";
			string value = itos(nggjbfb_bd);
			//mem.rep(key,value);
		}	

		int    Skill::getwgfybfb_bd(void)          //附加外功防御百分比
		{
			return wgfybfb_bd;
		}
		void   Skill::setwgfybfb_bd(int _wgfybfb_bd)
		{
			wgfybfb_bd = _wgfybfb_bd;
			string key = id + "wgfybfb_bd";
			string value = itos(wgfybfb_bd);
			//mem.rep(key,value);
		}	

		int    Skill::getngfybfb_bd(void)          //附加内功防御百分比
		{
			return ngfybfb_bd;
		}
		void   Skill::setngfybfb_bd(int _ngfybfb_bd)
		{
			ngfybfb_bd = _ngfybfb_bd;
			string key = id + "ngfybfb_bd";
			string value = itos(ngfybfb_bd);
			//mem.rep(key,value);
		}	

		int    Skill::getmzjdz_bd(void)            //附加命中绝对值
		{
			return mzjdz_bd;
		}
		void   Skill::setmzjdz_bd(int _mzjdz_bd)
		{
			mzjdz_bd = _mzjdz_bd;
			string key = id + "mzjdz_bd";
			string value = itos(mzjdz_bd);
			//mem.rep(key,value);
		}	
		int    Skill::getbjjdz_bd(void)            //附加暴击绝对值
		{
			return bjjdz_bd;
		}
		void   Skill::setbjjdz_bd(int _bjjdz_bd)
		{
			bjjdz_bd = _bjjdz_bd;
			string key = id + "bjjdz_bd";
			string value = itos(bjjdz_bd);
			//mem.rep(key,value);
		}	

		int    Skill::getsbjdz_bd(void)            //附加闪避绝对值
		{
			return sbjdz_bd;
		}
		void   Skill::setsbjdz_bd(int _sbjdz_bd)
		{
			sbjdz_bd = _sbjdz_bd;
			string key = id + "sbjdz_bd";
			string value = itos(sbjdz_bd);
			//mem.rep(key,value);
		}	

		int    Skill::getrxjdz_bd(void)            //附加韧性绝对值
		{
			return rxjdz_bd;
		}
		void   Skill::setrxjdz_bd(int _rxjdz_bd)
		{
			rxjdz_bd = _rxjdz_bd;
			string key = id + "rxjdz_bd";
			string value = itos(rxjdz_bd);
			//mem.rep(key,value);
		}	
		int    Skill::getfjxgcs_growup_bd(void)	//附加效果绝对值成长参数 2012.6.19 evan 
		{
			return fjxgcs_growup_bd;
		}	
		
			/*医疗技能属性   1*/
		int    Skill::getcure_type(void)           //医疗形式：1，单体医疗；2，群体医疗
		{
			return cure_type;
		}
		void   Skill::setcure_type(int _cure_type)
		{
			cure_type = _cure_type;
			string key = id + "cure_type";
			string value = itos(cure_type);
			//mem.rep(key,value);
		}
			
			/*buff技能属性   8*/
		int   Skill::getzjngshbfb_buff(void)        //buff增加内功伤害百分比
		{
			return zjngshbfb_buff;
		}
		void  Skill::setzjngshbfb_buff(int _zjngshbfb_buff)
		{
			zjngshbfb_buff = _zjngshbfb_buff;
			string key = id + "zjngshbfb_buff";
			string value = itos(zjngshbfb_buff);
			//mem.rep(key,value);
		}	

		int   Skill::getzjwgshbfb_buff(void)        //buff增加外功伤害百分比
		{
			return zjwgshbfb_buff;
		}
		void  Skill::setzjwgshbfb_buff(int _zjwgshbfb_buff)
		{
			zjwgshbfb_buff = _zjwgshbfb_buff;
			string key = id + "zjwgshbfb_buff";
			string value = itos(zjwgshbfb_buff);
			//mem.rep(key,value);
		}	
		int   Skill::getzjsmsx_buff(void)        	 //buff增加生命上限
		{
			return zjsmsx_buff;
		}
		void  Skill::setzjsmsx_buff(int _zjsmsx_buff)
		{
			zjsmsx_buff = _zjsmsx_buff;
			string key = id + "zjsmsx_buff";
			string value = itos(zjsmsx_buff);
			//mem.rep(key,value);
		}
		int   Skill::getftsh_buff(void)             //反弹伤害百分比
		{
			return ftsh_buff;
		}
		void  Skill::setftsh_buff(int _ftsh_buff)
		{
			ftsh_buff = _ftsh_buff;
			string key = id + "ftsh_buff";
			string value = itos(ftsh_buff);
			//mem.rep(key,value);
		}	
		int   Skill::getsmxh_buff(void)      		 //生命消耗
		{
			return smxh_buff;
		}
		void  Skill::setsmxh_buff(int _smxh_buff)
		{
			smxh_buff = _smxh_buff;
			string key = id + "smxh_buff";
			string value = itos(smxh_buff);
			//mem.rep(key,value);
		}

		int   Skill::getxxl_buff(void)              //吸血率
		{
			return xxl_buff;
		}
		void  Skill::setxxl_buff(int _xxl_buff)
		{
			xxl_buff = _xxl_buff;
			string key = id + "xxl_buff";
			string value = itos(xxl_buff);
			//mem.rep(key,value);
		}	

		int   Skill::getcxsjcz_buff(void)           //持续时间初值
		{
			return cxsjcz_buff;
		}
		void  Skill::setcxsjcz_buff(int _cxsjcz_buff)
		{
			cxsjcz_buff = _cxsjcz_buff;
			string key = id + "cxsjcz_buff";
			string value = itos(cxsjcz_buff);
			//mem.rep(key,value);
		}	
		int	  Skill::getconsumer_growth(void)	 //技能消耗成长参数
		{
			return consumer_growth;
		}
			
		int   Skill::getcxsjcz_growup_buff(void)	 //技能持续时间成长参数
		{
			return cxsjcz_growup_buff;
		}		
		int   Skill::getcd_growup_buff(void)		 //技能CD成长参数    
		{
			return cd_growup_buff;
		}
		int   Skill::getxg_growup_buff(void)		 //技能效果成长			
		{
			return xg_growup_buff;
		}		
	
	
		string Skill::formSklMsg(void)            //生成技能消息
		{
			string skiMsg;                                       		
		    // skiMsg = "2";
			// skiMsg += intTostring(10);
			/*技能id*/
			skiMsg += charTostring(const_cast<char*>(id.c_str()));
			/*技能名称*/
			// skiMsg += charTostring(const_cast<char*>(name.c_str()));
			
			// /*技能类型*/
			// skiMsg += intTostring(type);
			// /*技能附加效果*/
			// skiMsg += intTostring(effect);
			// /*技能等级*/
			// skiMsg += intTostring(skill_grade);
			// /*技能系数成长参数*/
			// skiMsg += intTostring(factor_growup);
			
			/*技能等级*/
			skiMsg += intTostring(skill_grade);
			
			/*等级限制*/
			skiMsg += intTostring(control_grade);
			/*消耗真气值*/
			skiMsg += intTostring(genuine);	
			/*玩家等级消耗金钱*/
			skiMsg += intTostring(useup_money);			
			/*玩家等级消耗经验值*/
			skiMsg += intTostring(useup_exp);
			
			cout<<"skiMsg:"<<skiMsg<<endl;
			return skiMsg;
		}

/************************************************************
	文件名：statuaryBase.cpp
	文件作用：StatuaryBase类的实现文件
	作者：chenzhen
	创建日期：2013.03.01
************************************************************/

#include"statuaryBase.h"
#include"hero.h"


StatuaryBase::StatuaryBase(char* _vocation,map<string,string> &_limitToPhotoId,Point _piexPt,char* _mapId)
{
	memset(vocation,'\0',sizeof(vocation));
	strncpy(vocation,_vocation,strlen(_vocation));
	
	memset(mapId,'\0',sizeof(mapId));
	strncpy(mapId,_mapId,strlen(_mapId));
	
	limitToPhotoId = _limitToPhotoId;
	
	piexPt = _piexPt;
}

/*获得职业id*/
char* StatuaryBase::getVocation(void)
{
	return vocation;
}

/*获得地图id*/
char* StatuaryBase::getMapId(void)
{
	return mapId;
}

/*获得像素点*/
Point StatuaryBase::getPiexPt(void)
{
	return piexPt;
}

/*角色赢得雕像*/
MemStatuaryHero* StatuaryBase::winStatuary(void *memHeros,char* titleId)
{
	char* photoId;
	
	MemHero *memHero = (MemHero*)(memHeros);
	
	if(memHeros == NULL || titleId == NULL)
	{
		cout<<"StatuaryBase::winStatuary the parm is NULL:"<<endl;
		return NULL;
	}
	

	photoId = getPhotoId(titleId);

	if(photoId == NULL)
	{
		cout<<"StatuaryBase::winStatuary the photoId is NULL:"<<endl;
		return NULL;
	}
	
	MemStatuaryHero* winerMemStatuaryHero = new MemStatuaryHero(memHero->identity,memHero->nickName,memHero->basicHeroData.party,\
	memHero->level,memHero->basicHeroData.lifeVal,memHero->basicHeroData.lifeUpperVal+memHero->allBuffDrug[0].effect_value,\
	memHero->basicHeroData.magicVal,memHero->basicHeroData.magicUpperVal,mapId,photoId,titleId,titleId,lastSeconds,piexPt);
	
#if 0	
	MemStatuaryHero* winerMemStatuaryHero = new MemStatuaryHero(winer->getIdentity(),winer->getNickName(),winer->getParty(),\
	winer->getLevel(),winer->getLifeUpperVal(),winer->getLifeVal(),winer->getMagicUpperVal(),winer->getMagicVal(),\
	mapId,photoId,titleId,titleId,lastSeconds,piexPt);
#endif
	return winerMemStatuaryHero;
}

/*根据参数require获得相对应的图片id*/
char* StatuaryBase::getPhotoId(char* require)
{
	map<string,string>::iterator require_it;
	if(limitToPhotoId.empty() || require == NULL)
	{
		cout<<"StatuaryBase::getPhotoId error:"<<endl;
		return NULL;
	}	
	
	require_it = limitToPhotoId.find(require);
	
	if(require_it == limitToPhotoId.end())
	{
		cout<<"StatuaryBase::getPhotoId can not find require error:"<<require<<endl;
		return NULL;
	}
	
	return const_cast<char*>((require_it->second).c_str());
}

/*根据参数require获得相对应的图片id,测试用的*/
char* StatuaryBase::testGetPhotoId(char* require)
{
	map<string,string>::iterator require_it;
	if(limitToPhotoId.empty() || require == NULL)
	{
		cout<<"StatuaryBase::testGetPhotoId error:"<<endl;
		return NULL;
	}	
	
	require_it = limitToPhotoId.begin();
	
	return const_cast<char*>((require_it->second).c_str());
}




	
	
	


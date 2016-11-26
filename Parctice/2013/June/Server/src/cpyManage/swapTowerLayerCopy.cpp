#include"towerLayerRecord.h"
#include"hero.h"
#include"cpy_series_command_function.h"

extern Hero* pg_hero;

/*¿ªÊ¼É¨µ´ÇàÒÂÂ¥*/
void swapTowerLayerCopy(char *buffer)
{	
	if(!pg_hero)
	{
		return;
	}
	TowerLayerRecord *towerLayerRecord = pg_hero->getTowerLayerRecord();
	if(towerLayerRecord == NULL)
	{
		cout<<"swapTowerLayerCopy the towerLayerRecord is NULL error:"<<pg_hero->getIdentity()<<endl;
		return;
	}
	towerLayerRecord->beginSwapOutReward();	
	
}

	
		
    

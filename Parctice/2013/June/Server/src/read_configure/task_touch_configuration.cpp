#include"task_touch_configuration.h"

Task_Touch_Configuration::Task_Touch_Configuration(string _touch_id, string _taskId,
							string _touch_type, unsigned int _hero_level)
{
	touch_id = _touch_id;
	taskId = _taskId;
	touch_type = _touch_type;
	hero_level = _hero_level;
}

string Task_Touch_Configuration::getTouch_Id(void)
{
	return touch_id;
}

string Task_Touch_Configuration::getTaskId(void)
{
	return taskId;
}

string Task_Touch_Configuration::getTouch_Type(void)
{
	return touch_type;
}

unsigned int Task_Touch_Configuration::getHero_Level(void)
{
	return hero_level;
}
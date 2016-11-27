#include "plateTaskManager.h"
#include "PlateServer.h"
#include "plateTask.h"
#include "base/baseSqlHandle.h"
#include "base/baseFunc.h"
#include "base/baseSqlRecord.h"

const bool PlateTaskManager::checkDependence(const WORD serverType)
{
	MysqlHandle *handle = PlateServer::s_mySqlPool->getHandle();
	LogErrorCheckCondition(handle,false,"数据库句柄为空");
	
	std::ostringstream oss;
	Record where;
	oss << "type<" << serverType << " and type != " << SUPERSERVER << " and type != " << PLATESERVER;
	where.put("type",oss.str());

	RecordSet *recordSet = handle->exeSelect("SERVERLIST",NULL,&where);
	bool ret = true;
	if(recordSet)
	{
		for(size_t index = 0;index < recordSet->size();++index)
		{
			PlateTask *task = PlateTaskManager::getInstance().getTaskByID((WORD)recordSet->get(index)->getValue("id"));
			if(!task || task->getState() != TcpTask::TTS_OKAY || !task->notifyMeReturnOK())
			{
				ret = false;
				break;
			}
		}
	}
	DELETE(recordSet);
	PlateServer::s_mySqlPool->putHandle(handle);
	return ret;
}

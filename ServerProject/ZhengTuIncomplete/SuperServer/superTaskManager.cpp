#include "superTaskManager.h"
#include "SuperServer.h"
#include "superTask.h"
#include "base/baseSqlHandle.h"
#include "base/baseFunc.h"
#include "base/baseSqlRecord.h"

const bool SuperTaskManager::checkDependence(const WORD serverType)
{
	MysqlHandle *handle = SuperServer::s_mySqlPool->getHandle();
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
			SuperTask *task = SuperTaskManager::getInstance().getTaskByID((WORD)recordSet->get(index)->getValue("id"));
			if(!task || task->getState() != TcpTask::TTS_OKAY || !task->notifyMeReturnOK())
			{
				ret = false;
				break;
			}
		}
	}
	DELETE(recordSet);
	SuperServer::s_mySqlPool->putHandle(handle);
	return ret;
}

#include "excel.h"

namespace ExcelTbx 
{
	ExcelTbx::ExcelTable<ExcelConf::Business,ExcelConf::Conf_t_Business,ExcelConf::Business::t_Business> _Business;

	void ExcelManager::init(const std::string &fileName,const ExcelTbx::ReadExcelFunc &func)
	{
		loadConf(fileName);
		loadTable("ExcelConf.Business",_Business,func);
	}

	const ExcelTbx::ExcelTable<ExcelConf::Business,ExcelConf::Conf_t_Business,ExcelConf::Business::t_Business >& Business()
	{
		 return _Business;
	}

	const ExcelConf::Conf_t_Business& Business(const unsigned int id)
	{
		 return _Business.get(id);
	}
}

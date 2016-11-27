#ifndef __EXCEL_H__
#define __EXCEL_H__
#include "Business.pb.h"
#include "excelBase.h"

namespace ExcelTbx 
{
	const ExcelTbx::ExcelTable<ExcelConf::Business,ExcelConf::Conf_t_Business,ExcelConf::Business::t_Business>& Business();

	const ExcelConf::Conf_t_Business& Business(const unsigned int id);
}

#endif
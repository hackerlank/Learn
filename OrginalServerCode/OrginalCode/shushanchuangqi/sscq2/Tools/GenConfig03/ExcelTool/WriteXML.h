#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

CString GetTableData(const CString& strData);
string GetTableStrData(const CString& strData);

bool Write_to_XML(std::vector< std::vector<CString> >& tableData,CString allPath,CString fileName);
bool Write_Server_C(std::vector< std::vector<CString> >& tableData,CString cstrAllPath,CString csrtfileName);
bool Write_AS_Binary(std::vector< std::vector<CString> >& tableData,CString cstrAllPath,CString csrtfileName);

//创建as容器类
bool Write_Client_AS(std::vector< std::vector<CString> >& tableData,CString cstrAllPath,CString csrtfileName);
//创建as数据类
bool Write_Client_AS_VO(std::vector< std::vector<CString> >& tableData,CString cstrAllPath,CString csrtfileName);

bool Write_Client_AS_Mgr(CString &path, std::vector<CString> &fileNames);
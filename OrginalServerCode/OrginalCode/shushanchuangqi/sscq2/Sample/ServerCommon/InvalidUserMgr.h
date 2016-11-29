#pragma once

class CInvalidUserMgr
{
public:
	static bool Init();
	static bool CheckUserName(const std::string& strName);

private:
	static std::set<string> _setInvalidName;
};
if(!con.create_db(pConfig->_strDBName))
{
    LOG_CRI << "Error creating DB: " << con.error();
    return false;
}

#ifdef __linux__
char initSql[4096] = {0};
snprintf(initSql, sizeof(initSql),
        "cd %s && if [ -f %s ]; then chmod +x %s && ./%s %s %s %s %u %s; fi && cd -",
        pConfig->_strSqlDir.c_str(), pConfig->_strSqlInit.c_str(), pConfig->_strSqlInit.c_str(), pConfig->_strSqlInit.c_str(),
        pConfig->_strDBAddr.c_str(), pConfig->_strDBUser.c_str(), pConfig->_strDBPassword.c_str(), pConfig->_wDBPort, pConfig->_strDBName.c_str());
int ret = system(initSql);
if (ret)
{
    LOG_CRI << "Error execute sql script: " << initSql << " result: " << ret;
    return false;
}
else
    LOG_INF << "Success execute sql script: " << initSql << " result: " << ret;
#else
# error "!!!!!!do nothing for windows!!!!!!"
#endif

if(!con.select_db(pConfig->_strDBName))
{
    LOG_CRI << "Error selecting DB: " << con.error();
    return false;
}

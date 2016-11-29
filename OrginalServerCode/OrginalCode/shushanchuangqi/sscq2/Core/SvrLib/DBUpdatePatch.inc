#ifdef __linux__
char onceSql[4096] = {0};
snprintf(onceSql, sizeof(onceSql),
        "cd %s && if [ -f %s ]; then chmod +x %s && ./%s %s %s %s %u %s && rm -f %s; fi && cd -",
        pConfig->_strSqlDir.c_str(), pConfig->_strSqlOnce.c_str(), pConfig->_strSqlOnce.c_str(), pConfig->_strSqlOnce.c_str(),
        pConfig->_strDBAddr.c_str(), pConfig->_strDBUser.c_str(), pConfig->_strDBPassword.c_str(), pConfig->_wDBPort, pConfig->_strDBName.c_str(),
        pConfig->_strSqlOnce.c_str());
int ret = system(onceSql);
if (ret)
{
    LOG_CRI << "Error execute sql script: " << onceSql << " result: " << ret;
    return false;
}
else
    LOG_INF << "Success execute sql script: " << onceSql << " result: " << ret;
#else
# error "!!!!!!do nothing for windows!!!!!!"
#endif

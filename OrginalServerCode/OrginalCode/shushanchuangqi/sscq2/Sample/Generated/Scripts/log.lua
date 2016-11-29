
function GetInfo(source, name, line)
    if source == nil then
        source = '?'
    end
    if name == nil then
        name = D.getinfo(3).name
    end
    if name == nil then
        name = '?'
    end
    if line == nil then
        line = D.getinfo(3).currentline
    end
    if line == nil then
        line = 0
    end
    return source,name,line
end

function LOG_CRI(msg)
    local source = D.getinfo(1).source
    local name = D.getinfo(2).name
    local line = D.getinfo(2).currentline
    source,name,line=GetInfo(source, name, line)
    local extmsg = ''
    if name == '?' then
        extmsg='\n'..debug.traceback()
    end
    LOG_OBJ:PushLogL(msg..extmsg, Log.ELLCRI, source..':'..name, line, true, true, true)
end

function LOG_WRN(msg)
    local source = D.getinfo(1).source
    local name = D.getinfo(2).name
    local line = D.getinfo(2).currentline
    source,name,line=GetInfo(source, name, line)
    local extmsg = ''
    if name == '?' then
        extmsg='\n'..debug.traceback()
    end
    LOG_OBJ:PushLogL(msg..extmsg, Log.ELLWRN, source..':'..name, line, true, true, true)
end

function LOG_INF(msg)
    local source = D.getinfo(1).source
    local name = D.getinfo(2).name
    local line = D.getinfo(2).currentline
    source,name,line=GetInfo(source, name, line)
    local extmsg = ''
    if name == '?' then
        extmsg='\n'..debug.traceback()
    end
    LOG_OBJ:PushLogL(msg..extmsg, Log.ELLINF, source..':'..name, line, true, true, true)
end

function LOG_DBG(msg)
    local source = D.getinfo(1).source
    local name = D.getinfo(2).name
    local line = D.getinfo(2).currentline
    source,name,line=GetInfo(source, name, line)
    local extmsg = ''
    if name == '?' then
        extmsg='\n'..debug.traceback()
    end
    LOG_OBJ:PushLogL(msg..extmsg, Log.ELLDBG, source..':'..name, line, true, true, true)
end

function LOG_DMY(msg)
    local source = D.getinfo(1).source
    local name = D.getinfo(2).name
    local line = D.getinfo(2).currentline
    source,name,line=GetInfo(source, name, line)
    local extmsg = ''
    if name == '?' then
        extmsg='\n'..debug.traceback()
    end
    LOG_OBJ:PushLogL(msg..extmsg, Log.ELLDMY, source..':'..name, line, true, true, true)
end

function LOG_CRI_APD(msg)
    local source = D.getinfo(1).source
    local name = D.getinfo(2).name
    local line = D.getinfo(2).currentline
    source,name,line=GetInfo(source, name, line)
    local extmsg = ''
    if name == '?' then
        extmsg='\n'..debug.traceback()
    end
    LOG_OBJ:PushLogL(msg..extmsg, Log.ELLCRI, source, name, line, false, true, true)
end

function LOG_WRN_APD(msg)
    local source = D.getinfo(1).source
    local name = D.getinfo(2).name
    local line = D.getinfo(2).currentline
    source,name,line=GetInfo(source, name, line)
    local extmsg = ''
    if name == '?' then
        extmsg='\n'..debug.traceback()
    end
    LOG_OBJ:PushLogL(msg..extmsg, Log.ELLWRN, source, name, line, false, true, true)
end

function LOG_INF_APD(msg)
    local source = D.getinfo(1).source
    local name = D.getinfo(2).name
    local line = D.getinfo(2).currentline
    source,name,line=GetInfo(source, name, line)
    local extmsg = ''
    if name == '?' then
        extmsg='\n'..debug.traceback()
    end
    LOG_OBJ:PushLogL(msg..extmsg, Log.ELLINF, source, name, line, false, true, true)
end

function LOG_DBG_APD(msg)
    local source = D.getinfo(1).source
    local name = D.getinfo(2).name
    local line = D.getinfo(2).currentline
    source,name,line=GetInfo(source, name, line)
    local extmsg = ''
    if name == '?' then
        extmsg='\n'..debug.traceback()
    end
    LOG_OBJ:PushLogL(msg..extmsg, Log.ELLDBG, source, name, line, false, true, true)
end

function LOG_DMY_APD(msg)
    local source = D.getinfo(1).source
    local name = D.getinfo(2).name
    local line = D.getinfo(2).currentline
    source,name,line=GetInfo(source, name, line)
    local extmsg = ''
    if name == '?' then
        extmsg='\n'..debug.traceback()
    end
    LOG_OBJ:PushLogL(msg..extmsg, Log.ELLDMY, source, name, line, false, true, true)
end


require_relative 'SessionMgr.rb'

class ProtocolBase
    def getProtID
        return @protID
    end

    def setSvrHandler(svrHandler)
        @svrHandler = svrHandler
    end

    def getSvrHandler
        return @svrHandler
    end

    def setSessionMgr(mgr)
        @sessionMgr = mgr
    end

    def onTimeOut(funcID, sessionID)
    end

    def finishProtocol
        @svrHandler.disconnect()
    end

    def getRobot
        return @svrHandler.getCurRobot()
    end
end


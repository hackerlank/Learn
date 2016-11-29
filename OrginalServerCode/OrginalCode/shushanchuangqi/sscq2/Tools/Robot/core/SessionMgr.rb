class Session
    attr_accessor:prot,:funcID,:data,:startTime
end

class SessionMgr
    @nextSessionID 
    @dicID2Session

    def initialize()
        @nextSessionID = 1
        @dicID2Session = Hash.new 
    end

    def getNewSession(prot, funcID)
        sessionID = @nextSessionID 
        @nextSessionID += 1
        if sessionID.equal?(0)
            @nextSessionID = 1
        end
        session = Session.new
        session.prot = prot
        session.funcID = funcID
        session.startTime = Time.now
        @dicID2Session[sessionID] = session
        return sessionID
    end
    
    def delSession(sessionID)
        @dicID2Session.delete(sessionID)
    end

    def storeData(sessionID, data)
        if not @dicID2Session.has_key?(sessionID)
            return false
        end
        session = @dicID2Session[sessionID]
        session.data = data
        return true
    end

    def getData(sessionID)
        session = @dicID2Session[sessionID]
        if session.nil?
            return nil
        else
            return session.data
        end
    end

    def timerCheck(now)
        @dicID2Session.each do |k, v|
            if now > v.startTime and now - v.startTime > 5
                v.prot.onTimeOut(v.funcID, k)
            end
        end
    end
end

#s = SessionMgr.new
#v = s.getNewSession(1, 1)
#s.storeData(v, "sdfsdfsdf")
#s.timerCheck(22)

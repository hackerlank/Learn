require_relative './ProtocolInclude.rb'
$arrRobot  = Array.new
class Robot
    @prot
    @gateConn
    @loginConn
    @dictID2Prot
    @connState
    @exsitState
#Robot状态处理，勿动#########
NO_CONNECTION            = 0
RECV_LOGIN_ACK           = 1
CONNECT_LOGIN_SUCCESSFUL = 2
CONNECT_GATE_SUCCESSFUL  = 3
WAIT_ROLE_ACK            = 4
GET_ROLE_DATA            = 5
WAIT_CREATE_ROLE         = 6
WAIT_CREATE_ROLE_ACK     = 7
WAIT_ENTER_GAME_ACK      = 8

DO_THING                 = 9
ERROR                    = 10
######################################################Robt Initialize BEGIN#############
   def initialize(usrID)                                                                                       
       #puts "Robot init data begin...."                                                
       @gateConn = SocketConn.new                                                      
       @loginConn = SocketConn.new                                                     
       @dictID2Prot = Hash.new
       @connState =  NO_CONNECTION
       registerProt()
       #robot data   
       @usrID = usrID
       @roleName = 'Robot_' + usrID.to_s
       @roleID
       @level
	   @exsitState = 0
	   @createState 
	   @strName = ''
	   @enterState
       initData()
   end
   #role data
   @roleData
   @roleID
   @time
   @tKeep
   attr_accessor:roleID
   attr_accessor:pos # role pos
   attr_accessor:bInit #role init
   attr_accessor:worldBossID #worldboss id
   attr_accessor:arrActivity #cur activity
   attr_accessor:mapID #player map id
   attr_accessor:playerState #player state
   attr_accessor:arrMonster #arround monster id
   attr_accessor:arrPassedDgnID #dungeon id
   attr_accessor:arrPlayerID #dungeon id
   attr_accessor:roomID #room 
   attr_accessor:multiDgnID # multi player dungeon cfg ID
   def initData
       @pos = SPosition.new
       @time = 0
       @tKeep = 0
       @tEventTime = 0
       @mapID = 0
       @playerState = 0
       @bInit = false
       @arrEvent = Array.new
       @arrActivity = Array.new
       @worldBossID = 0
       @arrMonster = Array.new
       @arrPassedDgnID = Array.new
       @arrPlayerID = Array.new
       @roomID = 0
       @multiDgnID = 0
       @flag = true
       initEvent()
   end
###################################################Robt Initialize END##################

########################################################################################
#一般情况下你只需要修改以下几个地方：
#   1、将协议注册到GateServer的连接上@gateConn
#   2、告诉Robot要做什么事情，在@arrEvent中注册
#   3、实现您注册的事件
########################################################################################
# 注册协议到指定的连接，一般都是发送到GateServer
   def registerProt
       @loginProt = LoginProt.new
       registerProtImpl(@loginProt, @loginConn)
       @roleInfoProt = RoleInfo.new
       registerProtImpl(@roleInfoProt, @gateConn)
       @gameSvrBasicProt = GameSvrBasic.new
       registerProtImpl(@gameSvrBasicProt, @gateConn)
       @mapProt = MapProt.new
       registerProtImpl(@mapProt, @gateConn)
       @globalChatProt = GlobalChatProt.new
       registerProtImpl(@globalChatProt, @gateConn)
	   @yelloDiamondProt = YelloDiamondProt.new
       registerProtImpl(@yelloDiamondProt, @gateConn)
	   @itemProt = ItemProt.new
       registerProtImpl(@itemProt, @gateConn)
	   @roleEventProt = RoleEventProt.new
       registerProtImpl(@roleEventProt, @gateConn)
   end
#注册Robot要执行的事件
   def initEvent
       #@arrEvent.push('sayHello')
   end
# 实现Robot要执行的事件
   def sayHello
      # puts 'Player enter sayHello() fucntion'
   end
###################################需要修改的地方结束###################################
	def getConnState
		return @connState
	end
   def setEnterState(state)
		@enterState = state
   end
   def getEnterState()
	   return @enterState
   end
   def getCode()
       return @code
   end
   def getExsitState()
       return @exsitState
   end
   def SetExsitState(state)
	   @exsitState = state
   end
   def getCreateState()
	   return @createState
   end
   def setCreateState(state)
	   @createState = state
   end
   def setRoleName(roleName)
       @strName = roleName
   end
   def getRoleName()
	   return @strName
   end
   def registerProtImpl(prot, conn)
       prot.setSvrHandler(conn)
       conn.registerProtocol(prot)
       conn.setCurRobot(self)
       protID = prot.getProtID()
       @dictID2Prot[protID] = prot
   end
   def abort
       @loginConn.disconnect()
       @gateConn.disconnect()
   end
   def setRoleInfo(roleData)
	   @roleData = roleData
   end
   def onGameReady()
	   ss = SShowInfo.new
	   arr = Array.new
       arr.push(ss)
	   @globalChatProt.send_Chat(1,"//boost",arr)
       @globalChatProt.send_Chat(1,"//entermap 2",arr)
       @connState = DO_THING
   end
   def OnLoginOK(roleID,gateIP, gatePort, code)
       @roleID = roleID
       @gateIP = gateIP
       @gatePort = gatePort
       @gateConn.setCode(0)
       @code = code
       @connState = CONNECT_LOGIN_SUCCESSFUL
	   puts "userID = [" + @usrID.to_s + " ] LoginServer Success"
   end
   def OnRecvPlayerDataAck()
	   if @gateConn.getCurRobot().getExsitState() == 0
	     @connState = WAIT_CREATE_ROLE
		 puts "userID = [" + @usrID.to_s + " ] need Create"
	   else
	     @connState = GET_ROLE_DATA
		 puts  "userID = [" + @usrID.to_s + " ] DataReady Success"
	   end
   end
   def OnRecvPlayerCreateAck()
       puts  "userID = [" + @usrID.to_s + " ] Create Ack  Recv"
	   if [0,1].include?(@gateConn.getCurRobot().getCreateState())
		     @connState = CONNECT_GATE_SUCCESSFUL
	   else
			 puts "Create Role Error,Robot ID = [" + @usrID.to_s + " ] deleted.  ERRorNO = "  + @gateConn.getCurRobot().getCreateState().to_s
			 @connState = ERROR
	   end
   end
   def run
      while 1
            case @connState
            when NO_CONNECTION
                if  @loginConn.connect($ip, $port, 1) == 0
                    @loginConn.setCode($port)
                    @loginProt.send_LoginReq(@usrID,1,14080801)
                    @connState = RECV_LOGIN_ACK 
                end
            when RECV_LOGIN_ACK
                @loginConn.recvPacket()
                return
            when CONNECT_LOGIN_SUCCESSFUL 
                @loginConn.disconnect()
                if @gateConn.connect(@gateIP, @gatePort, 1) == 0
                    data = ''
                    ByteUtil::writeUINT8(data, 1)
                    ByteUtil::writeUINT64(data, @roleID)
                    ByteUtil::writeUINT32(data, @code)
                    @gateConn.sendPacket(data)
                    @gateConn.setCode(@code)
                    @connState = CONNECT_GATE_SUCCESSFUL
					puts  "userID = [" + @usrID.to_s + " ] GateServer Success"
                end
               return
            when CONNECT_GATE_SUCCESSFUL
			    @connState = WAIT_ROLE_ACK
				@roleInfoProt.send_GetUserInfo()
			when WAIT_ROLE_ACK
			    puts "userID = [" + @usrID.to_s + " ] wait_role_ack"
			    @gateConn.recvPacket()
				return
			when GET_ROLE_DATA
			     @roleInfoProt.send_EnterGameReq()
				 @connState = WAIT_ENTER_GAME_ACK  
			when WAIT_CREATE_ROLE
				   _roleData = SCreateRoleInfo.new
				   _roleData.strName = @roleName
				   _roleData.eCareer = rand(1..4)
				   _roleData.eSex = rand(1..2)
				   @roleInfoProt.send_CreateRoleReq(_roleData)
				   @connState = WAIT_CREATE_ROLE_ACK   
            when WAIT_CREATE_ROLE_ACK
				 @gateConn.recvPacket()
				 return
		    when WAIT_ENTER_GAME_ACK
			     @gateConn.recvPacket()
				 return
            when DO_THING
			    @gateConn.recvPacket()
			    randomEvent()
                return
			when ERROR
			    $arrRobot.delete(@gateConn.getCurRobot())
				return
	        end
		end
   end 
   def randomEvent
       a = Time.now().to_i
       if a - @tKeep >= 10
           @gameSvrBasicProt.send_KeepAlive()    
           @tKeep = a
       end
      
       if (a - @time) >1 and @mapID != 0
           arr = Array.new
           pos = SPosition.new
           pos.fX = rand((@pos.fX - 5).abs .. @pos.fX + 10)
           pos.fY = rand((@pos.fY - 5).abs .. @pos.fY + 10)
           arr.push(pos)
           pos2 = SPosition.new
           pos2.fX = rand((@pos.fX - 5).abs .. @pos.fX + 10)
           pos2.fY = rand((@pos.fY - 5).abs .. @pos.fY + 10)
           arr.push(pos2)
           puts "userID = [" + @usrID.to_s + " ] is  moved  on map [" + @mapID.to_s + "]"
           @mapProt.send_PlayerMoveReq(@mapID, arr)
		   if(@mapID.to_i != 23)
		      ss = SShowInfo.new
			  puts "I want to enter mapID = 2"
	          arr = Array.new
              arr.push(ss)
              @globalChatProt.send_Chat(1,"//entermap 2",arr)
	          arr.clear
			end
           @time = a
       end
       if a - @tEventTime > 2
           if @arrEvent.length != 0
               evt = @arrEvent[Random::rand(@arrEvent.length)]
               send(evt)
           end
           @tEventTime = a
       end
   end
end
=begin
r = Robot.new(4321)
 while true
   begin
      r.run   
   rescue Interrupt
       r.abort
        puts 'Recv run function excetpion'
   end
        return
    rescue=>err
        puts err.message
        err.backtrace
    end
  end	
=end
$star= $*[0].to_i 
$en = $*[1].to_i

for i in ($star..$en) do 
    r = Robot.new(i)
    $arrRobot.push(r)
end
while true
      begin
		# for k in(0..6) 
       #     for j in (0..100) do 
		#	   $arrRobot.at(k*100 + j).run
		 #   end
		    #sleep(2)
		 # end
		 $arrRobot.each do |r|
            r.run   
	      end
   rescue Interrupt
        $arrRobot.each do |r|
            r.abort
		end
		$arrRobot.clear
        puts 'Recv run function excetpion'
        return
    rescue=>err
        puts err.message
        err.backtrace
    end
end

#################################################
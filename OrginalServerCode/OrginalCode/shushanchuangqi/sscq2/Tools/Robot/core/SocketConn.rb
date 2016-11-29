require_relative 'SocketBuffer.rb'
require_relative 'SessionMgr.rb'
require 'socket'
include Socket::Constants

class SocketConn
    def initialize(code = 5000)
        @socketBuffer = SocketBuffer.new
        @sessionMgr = SessionMgr.new
        @error = false
        @isRunning = false
        @protMap = Hash.new
        @socket = Socket.new(AF_INET, SOCK_STREAM, 0)
        @code = code
    end
    
    def connect(addr, port, clientID)
        begin
            sockaddr = Socket.sockaddr_in(port, addr)
            @socket.connect(sockaddr)
            return 0
        rescue
            return -1
        end
    end

    def disconnect
        if @socket
           @socket.close
			#puts "close socket"
        end
    end

    def setCurRobot(robot)
        @robot = robot
    end

    def getCurRobot
        return @robot
    end

    def setCode(code)
       @code = code 
    end

    def sendPacket(data)
        begin
        packet = String.new
        ByteUtil::writeUINT32(packet, data.bytesize)
        packet.concat(data)
        @socket.send packet, 0
        rescue Errno::EPIPE
            return
        end
    end
    def recvPacket()
        while 1
            begin
				data = @socket.recvfrom_nonblock(2048)#pair[0].chomp#pair[0].chomp
				#puts "data size = " + data[0].bytesize.to_s
                if data[0].bytesize== 0
                    return
                end
				#puts data.to_s
                @socketBuffer.writeData(data[0])
                packList = @socketBuffer.getPackets(@code)
                packList.each do |pack|
                    protID = ByteUtil::readUINT8(pack) 
                    prot = @protMap[protID]
                    if prot 
                        prot.handleMessage(pack)
                    end
                end
            rescue Errno::EWOULDBLOCK 
			    #sleep(1)
                return
            rescue Errno::EAGAIN
                puts "again"
                return
            rescue Exception=>e
                puts e.message
                puts e.backtrace
                #...
            end
        end
    end

# ×¢²áÐ­Òé
    def registerProtocol(protocol)
        protocol.setSvrHandler(self)
        protocol.setSessionMgr(@sessionMgr)
        @protMap[protocol.getProtID()] = protocol
    end

    def stopRecv
        @isRunning = false
    end

    def getErr
        return @error
    end

end

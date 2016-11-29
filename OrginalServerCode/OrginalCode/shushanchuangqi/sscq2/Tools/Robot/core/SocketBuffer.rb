require_relative 'ByteUtil.rb'
require 'zlib'
class SocketBuffer
    def initialize
        @buffData = ''
    end
    def writeData(data)
        if @buffData.bytesize == 0
           @buffData = data
        else
           @buffData = @buffData + data
        end
    end
	
    #def Jieya(string)
	#	zstream = Zlib::Inflate.new(Zlib::MAX_WBITS)
	#	buf = zstream.inflate(string)
	#	zstream.finish
	#	zstream.close
	#	buf
    #end
	def getPackets(dwCode)
        packetList = Array.new
		#BufferTemp = ''
        while (len = @buffData.bytesize) > 0 
            if len < 4
                return packetList
            end
            length = ByteUtil::readUINT32(@buffData)
            if len < length
                return packetList
            end
            data = ByteUtil::readData(@buffData, length)
            compr = ByteUtil::readUINT8(data)
            if compr == 1
			   data = Zlib::Inflate.inflate(data)
			end 
            if length > 0
                packetList.push(data)
            end
        end
        @buffData.clear()
        return packetList
    end
end

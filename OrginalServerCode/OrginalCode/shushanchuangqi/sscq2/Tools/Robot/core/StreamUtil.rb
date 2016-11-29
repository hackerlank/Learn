class StreamUtil
    #read data
    def StreamUtil.ReadData(data, len)
        strLen = data.length
        readLen = 0
        if len > strLen  
            readLen = strLen
        else
            realLen = len
            while realLen > 0 and data[realLen - 1] == '\0'
                --realLen
            end
            readLen = realLen
        end
        lenfmt = "a" + readLen.to_s
        val = data.unpack(lenfmt)
        data.slice!(0...readLen)
        return val[0]
    end

    def StreamUtil.ReadINT8(data)
        val = data.unpack("c")
        data.slice!(0...1)
        return val[0]
    end

    def StreamUtil.ReadUINT8(data)
        val = data.unpack("C")
        data.slice!(0...1)
        return val[0]
    end

    def StreamUtil.ReadINT16(data)
        val = data.unpack("s")
        data.slice!(0...2)
        return val[0]
    end

    def StreamUtil.ReadUINT16(data)
        val = data.unpack("S")
        data.slice!(0...2)
        return val[0]
    end
    
    def StreamUtil.ReadINT32(data)
        val = data.unpack("l")
        data.slice!(0...4)
        return val[0]
    end

    def StreamUtil.ReadUINT32(data)
        val = data.unpack("L")
        data.slice!(0...4)
        return val[0]
    end

    def StreamUtil.ReadINT64(data)
        val = data.unpack("q")
        data.slice!(0...8)
        return val[0]
    end

    def StreamUtil.ReadUINT64(data)
        val = data.unpack("Q")
        data.slice!(0...8)
        return val[0]
    end

    def StreamUtil.ReadFLOAT(data)
        val = data.unpack("f")
        data.slice!(0...4)
        return val[0]
    end
      
    def StreamUtil.ReadDOUBLE(data)
        val = data.unpack("d")
        data.slice!(0...8)
        return val[0]
    end

    def StreamUtil.ReadBOOL(data)
        val = data.unpack("c")
        data.slice!(0...1)
        return val[0] != 0
    end
    
    def StreamUtil.ReadSTRING(data)
        len = ReadUINT16(data)
        if len & 0x8000 != 0
            ext = ReadUINT16(data) 
            len = ((len & 0x7fff) << 16) + ext
        end
        if len > 0xfffffff
            puts "error"
        end
        lenfmt = "a" + len.to_s
        val = data.unpack(lenfmt)
        data.slice!(0...len)
        return val[0]
    end

    #write data 
    def StreamUtil.WriteINT8(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("c"))
    end

    def StreamUtil.WriteUINT8(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("C"))
    end

    def StreamUtil.WriteINT16(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("s"))
    end

    def StreamUtil.WriteUINT16(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("S"))
    end

    def StreamUtil.WriteINT32(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("l"))
    end

    def StreamUtil.WriteUINT32(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("L"))
    end

    def StreamUtil.WriteINT64(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("q"))
    end

    def StreamUtil.WriteUINT64(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("Q"))
    end

    def StreamUtil.WriteFLOAT(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("f"))
    end

    def StreamUtil.WriteDOUBLE(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("d"))
    end

    def StreamUtil.WriteBOOL(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("c"))
    end

end

file = File.open("t.data", "r")
ff = file.read(100)
#ff = file.read(28)
#c = StreamUtil::ReadINT64(ff)
#b = StreamUtil::ReadFLOAT(ff)
#a = StreamUtil::ReadDOUBLE(ff)
#puts c 
#puts b
#puts a
#a = StreamUtil::ReadINT8(ff)
#b = StreamUtil::ReadINT32(ff)
#c = StreamUtil::ReadINT16(ff)
#d = StreamUtil::ReadINT64(ff)
#e = StreamUtil::ReadFLOAT(ff)
#f = StreamUtil::ReadDOUBLE(ff)
#g = StreamUtil::ReadBOOL(ff)

#puts a
#puts b
#puts c
#puts d
#puts e
#puts f
#puts g

#a = StreamUtil::ReadSTRING(ff)
#b = StreamUtil::ReadDOUBLE(ff)
#puts a
#puts b

#def f
#    while 1
#        id = Thread.current
#        puts "current thread id is #{id}"
#        sleep 1
#    end
#end
#x = Thread.new{f()}
#arr = Array.new
#1000.times{ x = Thread.new{f()}; arr.push(x)}
#arr.each{|t| t.join }

a = StreamUtil::ReadData(ff, 100)
puts a

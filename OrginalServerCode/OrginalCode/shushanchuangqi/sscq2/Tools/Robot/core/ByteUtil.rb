class ByteUtil 
    #read data
    def self.readData(data, len)
        strLen = data.bytesize
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

    def self.readVectorLength(data)
        len = readUINT8(data)
        if (len & 0x80) != 0
            ext = readUINT8(data)
            len = ((len & 0x7F) << 8) + ext
        end
        if len > 0x7FFF
            puts 'readVectorLength error'
        end
        return len
    end

    def self.readINT8(data)
        val = data.unpack("c")
        data.slice!(0...1)
        return val[0]
    end

    def self.readUINT8(data)
        val = data.unpack("C")
        data.slice!(0...1)
        return val[0]
    end

    def self.readINT16(data)
        val = data.unpack("s")
        data.slice!(0...2)
        return val[0]
    end

    def self.readUINT16(data)
        val = data.unpack("S")
        data.slice!(0...2)
        return val[0]
    end
    
    def self.readINT32(data)
        val = data.unpack("l")
        data.slice!(0...4)
        return val[0]
    end

    def self.readUINT32(data)
        val = data.unpack("L")
        data.slice!(0...4)
        return val[0]
    end

    def self.readINT64(data)
        val = data.unpack("q")
        data.slice!(0...8)
        return val[0]
    end

    def self.readUINT64(data)
        val = data.unpack("Q")
        data.slice!(0...8)
        return val[0]
    end

    def self.readFLOAT(data)
        val = data.unpack("f")
        data.slice!(0...4)
        return val[0]
    end
      
    def self.readDOUBLE(data)
        val = data.unpack("d")
        data.slice!(0...8)
        return val[0]
    end

    def self.readBOOL(data)
        val = data.unpack("c")
        data.slice!(0...1)
        return val[0] != 0
    end
    
    def self.readSTRING(data)
        len = readUINT16(data)
        if len & 0x8000 != 0
            ext = readUINT16(data) 
            len = ((len & 0x7fff)<<16) + ext
        end
        if len > 0xfffffff
            puts "error"
        end
        lenfmt = "a" + len.to_s
        val = data.unpack(lenfmt)
        data.slice!(0...len)
        return val[0]
    end
    
    def self.readVecINT8(data)
        len = readVectorLength(data)
        arr = Array.new
        len.times do |i|
            arr[i] = readINT8(data)
        end
        return arr
    end
    
    def self.readVecUINT8(data)
        len = readVectorLength(data)
        arr = Array.new
        len.times do |i|
            arr[i] = readUINT8(data)
        end
        return arr
    end

    def self.readVecINT16(data)
        len = readVectorLength(data)
        arr = Array.new
        len.times do |i|
            arr[i] = readINT16(data)
        end
    end

    def self.readVecUINT16(data)
        len = readVectorLength(data)
        arr = Array.new
        len.times do |i|
            arr[i] = readUINT16(data)
        end
        return arr
    end

    def self.readVecINT32(data)
        len = readVectorLength(data)
        arr = Array.new
        len.times do |i|
            arr[i] = readINT32(data)
        end
        return arr
    end

    def self.readVecUINT32(data)
        len = readVectorLength(data)
        arr = Array.new
        len.times do |i|
            arr[i] = readUINT32(data)
        end
        return arr
    end

    def self.readVecSTRING(data)
        len = readVectorLength(data)
        arr = Array.new
        len.times do |i|
            arr[i] = readSTRING(data)
        end
        return arr
    end

    #write data 
    def self.writeVectorLength(data, len)
        if len > 0x7FFF
            puts 'writeVectorLength error'
        end
        if len > 0x7F
            writeUINT16(data, len >> 8 | 0x80 | len << 8)
        else
            writeUINT8(data, len)
        end
    end

    def self.writeData(data, val)
        arrVal = Array.new
        arrVal.push(val)
        strfmt = 'a' + val.bytesize.to_s
        data.concat(arrVal.pack(strfmt))
    end
    
    def self.writeStringLength(data, len)
        #puts len.class
        if len > 0x7FFFFFFF
            puts 'writeStringLength error'
        end
        if len > 0x7FFF
            writeUINT32(data, len >> 16 | 0x8000 | len << 16)
        else
            writeUINT16(data, len)
        end
    end

    def self.writeINT8(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("c"))
    end

    def self.writeUINT8(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("C"))
    end

    def self.writeINT16(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("s"))
    end

    def self.writeUINT16(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("S"))
    end

    def self.writeINT32(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("l"))
    end

    def self.writeUINT32(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("L"))
    end

    def self.writeINT64(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("q"))
    end

    def self.writeUINT64(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("Q"))
    end

    def self.writeFLOAT(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("f"))
    end

    def self.writeDOUBLE(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("d"))
    end

    def self.writeBOOL(data, val)
        arrVal = Array.new
        arrVal.push(val)
        data.concat(arrVal.pack("c"))
    end

    def self.writeSTRING(data, val)
        writeStringLength(data, val.bytesize)
        writeData(data, val)
    end

    def self.writeVecINT8(data, arr)
        len = arr.length
        writeVectorLength(data, len)
        arr.each do |v|
            writeINT8(data, v)
        end
    end

    def self.writeVecUINT8(data, arr)
        len = arr.length
        writeVectorLength(data, len)
        arr.each do |v|
            writeUINT8(data, v)
        end
    end

    def self.writeVecINT16(data, arr)
        len = arr.length
        writeVectorLength(data, len)
        arr.each do |v|
            writeINT16(data, v)
        end
    end

    def self.writeVecUINT16(data, arr)
        len = arr.length
        writeVectorLength(data, len)
        arr.each do |v|
            writeUINT16(data, v)
        end
    end

    def self.writeVecINT32(data, arr)
        len = arr.length
        writeVectorLength(data, len)
        arr.each do |v|
            writeINT32(data, v)
        end
    end

    def self.writeVecUINT32(data, arr)
        len = arr.length
        writeVectorLength(data, len)
        arr.each do |v|
            writeUINT32(data, v)
        end
    end

    def self.writeVecSTRING(data, arr)
        len = arr.length
        writeVectorLength(data, len)
        arr.each do |v|
            writeSTRING(data, v)
        end
    end


    def self.xor(data, key)
        data.bytesize.times do |i|
            rem = i % 4
            case rem
            when 0
                c = data.getbyte(i) ^ (key & 0xFF)
            when 1
                c = data.getbyte(i) ^ (key >> 8 & 0xFF)
            when 2
                c = data.getbyte(i) ^ (key >> 16 & 0xFF)
            when 3
                c = data.getbyte(i) ^ (key >> 24 & 0xFF)
            end
            data.setbyte(i, c)
            #data[i] = c.to_s
        end
    end
end

#file = File.open("t.data", "r")
#ff = file.read(100)
#ff = file.read(28)
#c = self::ReadINT64(ff)
#b = self::ReadFLOAT(ff)
#a = self::ReadDOUBLE(ff)
#puts c 
#puts b
#puts a
#a = self::ReadINT8(ff)
#b = self::ReadINT32(ff)
#c = self::ReadINT16(ff)
#d = self::ReadINT64(ff)
#e = self::ReadFLOAT(ff)
#f = self::ReadDOUBLE(ff)
#g = self::ReadBOOL(ff)

#puts a
#puts b
#puts c
#puts d
#puts e
#puts f
#puts g

#a = self::ReadSTRING(ff)
#b = self::ReadDOUBLE(ff)
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

#a = ByteUtil::ReadData(ff, 100)
#puts a

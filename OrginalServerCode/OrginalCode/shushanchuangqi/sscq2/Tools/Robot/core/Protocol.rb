require_relative './SocketConn.rb'
#require_relative '../Protocol/FuncProt.rb'
require_relative '../Protocol/LoginProt.rb'

class Protocol

    def initialize(socketConn)
        @funcProt = LoginProt.new
        socketConn.registerProtocol(@funcProt)
    end
end

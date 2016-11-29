
VERSION:=$(shell date +%y%m%d%H%M)
DIRS:=$(shell find -type d|grep -v \.svn)

define copy_config
	@rsync -rvc Generated/Config ../run --delete --exclude "ServerConfig.xml" --exclude "UDPLog.xml"
endef

define copy_script
	@rsync -rvc Generated/Scripts ../run --delete
endef

define strip_exec
	@objcopy --only-keep-debug ../run/GateServer ../run/GateServer.symbol
	@objcopy --strip-debug ../run/GateServer
	@objcopy --only-keep-debug ../run/GameServer ../run/GameServer.symbol
	@objcopy --strip-debug ../run/GameServer
	@objcopy --only-keep-debug ../run/DBServer ../run/DBServer.symbol
	@objcopy --strip-debug ../run/DBServer
	@objcopy --only-keep-debug ../run/CenterServer ../run/CenterServer.symbol
	@objcopy --strip-debug ../run/CenterServer
	@objcopy --only-keep-debug ../run/LoginServer ../run/LoginServer.symbol
	@objcopy --strip-debug ../run/LoginServer
	@objcopy --only-keep-debug ../run/LogServer ../run/LogServer.symbol
	@objcopy --strip-debug ../run/LogServer
	@objcopy --only-keep-debug ../run/ServerManager ../run/ServerManager.symbol
	@objcopy --strip-debug ../run/ServerManager
endef

all: debug

config:
	$(copy_config)

script:
	$(copy_script)

res:
	$(copy_config)
	$(copy_script)

debug: rmserversd libdebug
	premake4  --os=linux --platform=x64 --file=premake4.lua gmake
	@if [ -d .build ]; then config=debug $(MAKE) -C .build; fi
	$(copy_config)
	$(copy_script)
	
release: rmserversr librelease
	premake4  --os=linux --platform=x64 --file=premake4.lua gmake Release
	@if [ -d .build ]; then config=release $(MAKE) -C .build; fi
	$(copy_config)
	$(copy_script)

prepare:
	@if [ -f prepare.sh ]; then chmod +x prepare.sh;./prepare.sh; fi

rmserversd:
	@rm -f ../run/CenterServerD
	@rm -f ../run/LoginServerD
	@rm -f ../run/GateServerD
	@rm -f ../run/GameServerD
	@rm -f ../run/DBServerD
	@rm -f ../run/LogServerD

rmserversr:
	@rm -f ../run/CenterServer
	@rm -f ../run/LoginServer
	@rm -f ../run/GateServer
	@rm -f ../run/GameServer
	@rm -f ../run/DBServer
	@rm -f ../run/LogServer

libdebug:
	 $(MAKE) -C ../ThirdParty
	
librelease:
	 $(MAKE) release -C ../ThirdParty

tarball_only:
	$(strip_exec)
	cd ../run; tar cvzf release/server-$(VERSION).tgz --exclude='.svn' --exclude='*.symbol' --exclude='*.dll' --exclude='*D' --exclude='Config/ServerConfig.xml' --exclude='CrossConfig.xml' GateServer GameServer DBServer CenterServer LoginServer LogServer ServerManager Config Scripts run.sh
	cd ../run; tar cvzf release/server-$(VERSION).symbol.tgz --exclude='.svn' *.symbol

tardebug: debug
	cd ../run; tar cvzf release/server-$(VERSION).tgz --exclude='.svn' --exclude='*.symbol' --exclude='*.dll' --exclude='Config/ServerConfig.xml' --exclude='CrossConfig.xml' GateServerD GameServerD DBServerD CenterServerD LoginServerD LogServerD ServerManagerD Config Scripts run.sh

tarball: release
	$(strip_exec)
	cd ../run; tar cvzf release/server-$(VERSION).tgz --exclude='.svn' --exclude='*.symbol' --exclude='*.dll' --exclude='*D' --exclude='Config/ServerConfig.xml' --exclude='CrossConfig.xml' --exclude='UDPLog.xml' GateServer GameServer DBServer CenterServer LoginServer LogServer ServerManager Config Scripts run.sh
	cd ../run; tar cvzf release/server-$(VERSION).symbol.tgz --exclude='.svn' *.symbol

gateserver:
	$(MAKE) GateServer -C .build
gameserver:
	$(MAKE) GameServer -C .build
loginserver:
	$(MAKE) LoginServer -C .build
centerserver:
	$(MAKE) CenterServer -C .build
dbserver:
	$(MAKE) DBServer -C .build
log:
	$(MAKE) LoggerServer -C .build
loggerserver:
	$(MAKE) LoggerServer -C .build
servermanager:
	$(MAKE) ServerManager -C .build

clean:
	$(MAKE) clean -C ../ThirdParty
	@if [ -d .build ]; then $(MAKE) clean -C .build; rm -rf .build; fi
	@rm -rf .objs
	@find . -name "\.o" | xargs rm -rf {} \;

touch:
	touch .now
	find ../bin -newer .now -exec touch {} \;
	find ../obj -newer .now -exec touch {} \;
	find .      -newer .now -exec touch {} \;
	rm -f .now

docxy:
	@sed -i -e s\,INPUT\ *=.*$$,INPUT\ =\ "$(DIRS)"\,g Doxyfile
	doxygen



.PHONY: GenProtocol

all: GenProtocolD

release: GenProtocol

GenProtocolD:
	premake4  --os=linux --platform=x64 --file=premake4.lua gmake
	if [ -d .build ]; then cd .build && config=debug $(MAKE); fi

GenProtocol:
	premake4  --os=linux --platform=x64 --file=premake4.lua gmake
	if [ -d .build ]; then cd .build && config=release $(MAKE); fi

clean:
	$(MAKE) clean -C .build


BOOST:=boost_1_54_0
LUAJIT:=LuaJIT-2.0.2

all: debug

debug: boost libluajit
	premake4  --os=linux --platform=x64 --file=premake4.lua gmake Debug
	config=debug $(MAKE) -C .build

release: boost libluajit
	premake4  --os=linux --platform=x64 --file=premake4.lua gmake Release
	config=release $(MAKE) -C .build

boost:
	@if [ ! -d $(BOOST) -a -f $(BOOST).tar.gz ]; then tar vfxz $(BOOST).tar.gz; fi

libluajit:
	$(MAKE) -C $(LUAJIT)/src
	@cp -u $(LUAJIT)/src/libluajit.a lib

clean:
	@find . -name "*.o" | xargs rm -rf {} \;
	@if [ -d .build ]; then $(MAKE) clean -C .build; fi
	@rm -rf .objs; rm -rf .build;


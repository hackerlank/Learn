
J=16
DST=Sample
DIRS:=$(shell find -type d|grep -v \.svn)

all:debug

config:
	@if [ -d $(DST) ]; then $(MAKE) -j$(J) $@ -C $(DST); fi

script:
	@if [ -d $(DST) ]; then $(MAKE) -j$(J) $@ -C $(DST); fi

res:
	@if [ -d $(DST) ]; then $(MAKE) -j$(J) $@ -C $(DST); fi

debug:
	@if [ -d $(DST) ]; then $(MAKE) -j$(J) $@ -C $(DST); fi

release:
	@if [ -d $(DST) ]; then $(MAKE) -j$(J) $@ -C $(DST); fi

libdebug:
	@if [ -d $(DST) ]; then $(MAKE) -j$(J) $@ -C $(DST); fi
	
librelease:
	@if [ -d $(DST) ]; then $(MAKE) -j$(J) $@ -C $(DST); fi

libluajit:
	@if [ -d $(DST) ]; then $(MAKE) -j$(J) $@ -C $(DST); fi
	
tarball_only:
	@if [ -d $(DST) ]; then $(MAKE) $@ -C $(DST); fi

tarball: release
	@if [ -d $(DST) ]; then $(MAKE) $@ -C $(DST); fi

tardebug:
	@if [ -d $(DST) ]; then $(MAKE) -j$(J) $@ -C $(DST); fi
	
clean:
	@if [ -d $(DST) ]; then $(MAKE) $@ -C $(DST); fi
	$(MAKE) clean -C Tools

docxy:
	@sed -i -e s\,INPUT\ *=.*$$,INPUT\ =\ "$(DIRS)"\,g Doxyfile
	doxygen

touch:
	touch .now
	find . -cnewer .now
	find . -cnewer .now -exec touch {} \;
	rm -f .now

dos2unix:
	find . -name "*.h" | grep -v boost | xargs dos2unix
	find . -name "*.c" | grep -v boost | xargs dos2unix
	find . -name "*.cpp" | grep -v boost | xargs dos2unix
	find . -name "*.hpp" | grep -v boost | xargs dos2unix
	find . -name "*.php" | grep -v boost | xargs dos2unix

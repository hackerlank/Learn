
SHELL = /bin/sh
EXEC = ir_tree
BUILD_DIR = build

all:
	@( cd ${BUILD_DIR}; make )

clean:
	@echo 'start clean...'
	@($(RM) $(EXEC))
	@(cd ${BUILD_DIR}; make clean)
	@echo 'Finished!'
	@echo ''


SHELL = /bin/sh
EXEC = object
RM   = rm -rf 
BUILD_COM_DIR = common
BUILD_PRO_DIR = projectOne

all:
	@( cd ${BUILD_COM_DIR}; make )
	@( cd ${BUILD_PRO_DIR};make )

clean:
	@echo 'start clean...'
	@($(RM) $(EXEC))
	@(cd ${BUILD_COM_DIR}; make clean)
	@(cd ${BUILD_PRO_DIR};make clean)
	@echo 'Finished!'
	@echo ''

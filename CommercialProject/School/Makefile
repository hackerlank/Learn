SHELL = /bin/sh
EXEC = object
RM   = rm -rf

BUILD_PROTOL_DIR = protol
BUILD_BASE_DIR = base
BUILD_COM_DIR = common
BUILD_PLATE_SERVER_DIR = PlateServer
BUILD_SUPER_SERVER_DIR = SuperServer
BUILD_RECORD_SERVER_DIR = RecordServer
BUILD_SESSION_SERVER_DIR = SessionServer
BUILD_SCENE_SERVER_DIR = SceneServer
BUILD_GATEWAY_SERVER_DIR = GatewayServer
all:
	@(cd ${BUILD_PROTOL_DIR}; make cleanlib)
	@(cd ${BUILD_BASE_DIR}; make cleanlib)
	@(cd ${BUILD_COM_DIR}; make cleanlib)
	@(cd ${BUILD_PLATE_SERVER_DIR}; make cleanlib)
	@(cd ${BUILD_SUPER_SERVER_DIR}; make cleanlib)
	@(cd ${BUILD_RECORD_SERVER_DIR}; make cleanlib)
	@(cd ${BUILD_SESSION_SERVER_DIR}; make cleanlib)
	@(cd ${BUILD_SCENE_SERVER_DIR}; make cleanlib)
	@(cd ${BUILD_GATEWAY_SERVER_DIR}; make cleanlib)

	@(cd ${BUILD_PROTOL_DIR}; make)
	@(cd ${BUILD_BASE_DIR}; make)
	@(cd ${BUILD_COM_DIR}; make)
	@(cd ${BUILD_PLATE_SERVER_DIR}; make)
	@(cd ${BUILD_SUPER_SERVER_DIR}; make)
	@(cd ${BUILD_RECORD_SERVER_DIR}; make)
	@(cd ${BUILD_SESSION_SERVER_DIR}; make)
	@(cd ${BUILD_SCENE_SERVER_DIR}; make)
	@(cd ${BUILD_GATEWAY_SERVER_DIR}; make)
clean:
	@echo 'start clean...'
	@($(RM) $(EXEC))
	@(cd ${BUILD_PROTOL_DIR}; make clean)
	@(cd ${BUILD_BASE_DIR}; make clean)
	@(cd ${BUILD_COM_DIR}; make clean)
	@(cd ${BUILD_PLATE_SERVER_DIR}; make clean)
	@(cd ${BUILD_SUPER_SERVER_DIR}; make clean)
	@(cd ${BUILD_RECORD_SERVER_DIR}; make clean)
	@(cd ${BUILD_SESSION_SERVER_DIR}; make clean)
	@(cd ${BUILD_SCENE_SERVER_DIR}; make clean)
	@(cd ${BUILD_GATEWAY_SERVER_DIR}; make clean)
	@echo 'Finished!'
	@echo ''

SHELL = /bin/sh
EXEC = object
RM   = rm -rf

#编译选项:不区分警告和错误，遇到任何警告都停止编译,没有使用的局部变量,过时的用法,以及编译优化
WARNING_OPT = -g -Wall -Werror -Wno-unused-local-typedefs -Wno-narrowing -Wno-deprecated -fno-strict-aliasing
#debug模式
MACRO_OPT = -D_DEBUG_WCX -D_ZYZ_DEBUG -D_DEBUG_LBS -D_USE_CMD_NAMESPACE  -D_USE_EPOLL_ -D_GNU_SOURCE -D_REENTRANT -D_USE_GCC_4
#需要include进来的路径
DIR_OPT = -I/usr/local/include/hiredis/ -I/usr/gcc/lib/gcc/x86_64-unknown-linux-gnu/5.3.0/include/ -I/usr/local/protobuf/include/ -I/usr/include/libxml2/ -I/usr/local/include/ -I/usr/local/mysql/include/ -I../protocpp -I../base -I../excelcode
#debug编译选项
DEBUG_OPT = $(WARNING_OPT) $(MACRO_OPT) $(DIR_OPT)
#编译库文件路径
SUB_DIR = protocpp base excelcode
#目标文件路径
TARGET_DIR = loginserver superserver recordserver sceneserver gatewayserver robotserver
#cpu核数
NJOBS = `if [ "" == "$(NCPUS)" ]; then echo ""; else echo "-j$(NCPUS)"; fi`

SOURCE_TOOL_DIR = tooldir
TBX_DIR = configdir/excelTbx
PRO_DIR = configdir/protomsg

all:debug
res:
	#生成excel资源
	chmod +x $(SOURCE_TOOL_DIR)/parseExcelTool/tool_parse_excel.py
	@rm -rf $(TBX_DIR)/*.*
	@rm -rf excelcode/*.*
	
	@(cd $(SOURCE_TOOL_DIR)/parseExcelTool;./tool_parse_excel.py)
	@if ls $(SOURCE_TOOL_DIR)/parseExcelTool/readtbxxml/*.xml > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseExcelTool/readtbxxml/* $(TBX_DIR)/; fi
	@if ls $(SOURCE_TOOL_DIR)/parseExcelTool/tbx/*.tbx > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseExcelTool/tbx/* $(TBX_DIR)/; fi
	@if ls $(SOURCE_TOOL_DIR)/parseExcelTool/cppproto/*.h > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseExcelTool/cppproto/* excelcode/; fi
	@if ls $(SOURCE_TOOL_DIR)/parseExcelTool/managercpp/*.h > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseExcelTool/managercpp/* excelcode/; fi
		
	@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/readtbxxml
	@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/tbx
	@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/cppproto
	@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/managercpp
	@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/clientXml
	@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/pythonproto
	@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/serverproto
	
	#生成proto消息资源
	chmod +x $(SOURCE_TOOL_DIR)/parseProtoTool/tool_parse_xml_proto.py
	@rm -rf $(PRO_DIR)/*.*
	
	@(cd $(SOURCE_TOOL_DIR)/parseProtoTool;./tool_parse_xml_proto.py)
	@if ls $(SOURCE_TOOL_DIR)/parseProtoTool/protodir/*.proto > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseProtoTool/protodir/* $(PRO_DIR)/; fi
	@rm -rf $(SOURCE_TOOL_DIR)/parseProtoTool/protodir
proto:
	@rm -rf ./protocpp/*.{h,cpp,cc}
	@./protoc -I=./$(PRO_DIR) --cpp_out=./protocpp ./$(PRO_DIR)/*.proto
debug:
	@for dir in $(SUB_DIR); \
		do \
		FLYER_COMPILE_OPT='$(DEBUG_OPT) -DBUILD_STRING=$(BUILD_STRING)' PIC_FLAG='-fPIC' $(MAKE)  $(NJOBS) -C $$dir || exit 1; \
		done
	@for dir in $(TARGET_DIR); \
		do \
		FLYER_COMPILE_OPT='$(DEBUG_OPT) -DBUILD_STRING=$(BUILD_STRING)' PIC_FLAG='-fPIC' $(MAKE) ISDebug=TRUE $(NJOBS) -C $$dir || exit 1; \
		done
clean:
	@echo 'start clean...'
	@for dir in $(SUB_DIR); \
		do \
		$(MAKE)  -C $$dir clean; \
		done
	@for dir in $(TARGET_DIR); \
		do \
		$(MAKE) ISDebug=TRUE -C $$dir clean; \
		done
	@echo 'Finished!'
ctags:
	@ctags -R -h ".c.cpp.h" -o tags
clear:
	@for dir in $(TARGET_DIR); \
		do \
		cd ${dir};\
		rm -rf *.d;\
		rm -rf *.h~;\
		rm -rf *.cpp~;\
		rm -rf *.o;\
		done

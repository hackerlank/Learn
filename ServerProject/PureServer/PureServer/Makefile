SHELL = /bin/sh
EXEC = object
RM   = rm -rf

#编译选项:不区分警告和错误，遇到任何警告都停止编译,没有使用的局部变量,过时的用法,以及编译优化
WARNING_OPT = -g -Wall -Werror -Wno-unused-local-typedefs -Wno-narrowing -Wno-deprecated -fno-strict-aliasing
#debug模式
MACRO_OPT = -D_DEBUG_WCX -D_ZYZ_DEBUG -D_DEBUG_LBS -D_USE_CMD_NAMESPACE  -D_USE_EPOLL_ -D_GNU_SOURCE -D_REENTRANT -D_USE_GCC_4
#需要include进来的路径
DIR_OPT = -I/usr/gcc/lib/gcc/x86_64-unknown-linux-gnu/5.3.0/include/ -I/usr/local/protobuf/include/ -I/usr/include/libxml2/ -I/usr/local/include/ -I/usr/local/mysql/include/ -I../protocpp -I../base
#debug编译选项
DEBUG_OPT = $(WARNING_OPT) $(MACRO_OPT) $(DIR_OPT)
#编译库文件路径
SUB_DIR = protocpp base
#目标文件路径
TARGET_DIR = client server
#cpu核数
NJOBS = `if [ "" == "$(NCPUS)" ]; then echo ""; else echo "-j$(NCPUS)"; fi`

SOURCE_TOOL_DIR = tooldir

all:debug
res:
	#生成excel资源
	#chmod +x $(SOURCE_TOOL_DIR)/parseExcelTool/tool_parse_excel.py
	#@rm -rf tbx/*.*
	#@rm -rf tbxcpp/*.*
	
	#@(cd $(SOURCE_TOOL_DIR)/parseExcelTool;./tool_parse_excel.py)
	#@if ls $(SOURCE_TOOL_DIR)/parseExcelTool/readtbxxml/*.xml > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseExcelTool/readtbxxml/* tbx/; fi
	#@if ls $(SOURCE_TOOL_DIR)/parseExcelTool/tbx/*.tbx > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseExcelTool/tbx/* tbx/; fi
	#@if ls $(SOURCE_TOOL_DIR)/parseExcelTool/cppproto/*.h > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseExcelTool/cppproto/* tbxcpp/; fi
	#@if ls $(SOURCE_TOOL_DIR)/parseExcelTool/managercpp/*.h > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseExcelTool/managercpp/* tbxcpp/; fi
		
	#@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/readtbxxml
	#@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/tbx
	#@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/cppproto
	#@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/managercpp
	#@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/clientXml
	#@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/pythonproto
	#@rm -rf $(SOURCE_TOOL_DIR)/parseExcelTool/serverproto
	
	#生成xml资源
	#chmod +x $(SOURCE_TOOL_DIR)/parseXmlTool/tool_parse_xml.py
	#@rm -rf xml/*.*
	
	#@(cd $(SOURCE_TOOL_DIR)/parseXmlTool;./tool_parse_xml.py)
	#@if ls $(SOURCE_TOOL_DIR)/parseXmlTool/xmlcpp/*.h > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseXmlTool/xmlcpp/* xml/; fi
	#@if ls $(SOURCE_TOOL_DIR)/parseXmlTool/xmlcommon/*.h > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseXmlTool/xmlcommon/* xml/; fi
	#@if ls $(SOURCE_TOOL_DIR)/parseXmlTool/managerxmlcpp/*.h > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseXmlTool/managerxmlcpp/* xml/; fi
	
	#@rm -rf $(SOURCE_TOOL_DIR)/parseXmlTool/xmlcpp
	#@rm -rf $(SOURCE_TOOL_DIR)/parseXmlTool/xmlcommon
	#@rm -rf $(SOURCE_TOOL_DIR)/parseXmlTool/managerxmlcpp
	
	#生成proto消息资源
	chmod +x $(SOURCE_TOOL_DIR)/parseProtoTool/tool_parse_xml_proto.py
	@rm -rf protomsg/*.*
	
	@(cd $(SOURCE_TOOL_DIR)/parseProtoTool;./tool_parse_xml_proto.py)
	@if ls $(SOURCE_TOOL_DIR)/parseProtoTool/protodir/*.proto > /dev/null 2>&1; then cp $(SOURCE_TOOL_DIR)/parseProtoTool/protodir/* protomsg/; fi
	@rm -rf $(SOURCE_TOOL_DIR)/parseProtoTool/protodir
proto:
	@rm -rf ./protocpp/*.{h,cpp,cc}
	@./protoc -I=./protomsg --cpp_out=./protocpp ./protomsg/*.proto
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

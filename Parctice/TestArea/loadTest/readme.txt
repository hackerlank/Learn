此层级的makefile是顶层makefile

注意结构：
	src：所有的源文件.c和.h
	build：
		objs:将编译好的.o和.d文件放进去
		dep：暂时没有使用

注意：build/obj/中的subdir.mk文件，很重要！
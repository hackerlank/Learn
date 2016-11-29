
solution "Library"
    location ".build"
	language "C++"
    objdir ".objs"

    configurations { "Debug", "Release" }

    configuration "linux"
        defines {
            "_VERSION="..os.date("%y%m%d%H%M", os.time()),
        }

    configuration "not vs*"
        --buildoptions { "-Wall", "-fexceptions", "-fno-strict-aliasing", "-Wno-multichar" }
        buildoptions { "-Wno-multichar" }
		buildoptions { "-std=c++11" }
		linkoptions { "-rdynamic" }

    configuration "Debug"
        flags "Symbols"
        defines "_DEBUG"
		
	-- buildoptions "-march=native" -- for suse

    configuration "Release"
        flags { "OptimizeSpeed", "FloatFast", }
		defines "NDEBUG"
		
prj = "tinyxml"
project(prj)
    kind "StaticLib"
    files { prj.."/*.cpp", prj.."/*.h" }
    if os.isfile(prj.."/premake4.lua") then
        local func = loadfile(prj.."/premake4.lua");
        func();
    end
	includedirs {
		prj,
    }
	targetdir "lib"
	targetname "TinyXML"
    configuration { "Debug", "not vs*" }
    	buildoptions { "-pg" }
		targetsuffix "D"

--prj = "lua_tinker"
--project(prj)
--    kind "StaticLib"
--    files { prj.."/*.cpp", prj.."/*.h" }
--	includedirs {
--		"LuaJIT-2.0.2/src",
--		prj,
--    }
--	targetdir "lib"
--	targetname "lua_tinker"
--    configuration { "Debug", "not vs*" }
--    	buildoptions { "-pg" }
--		targetsuffix "D"
--

prj = "luabind-0.9.1"
project(prj)
    kind "StaticLib"
    files { prj.."/src/*.cpp", prj.."/src/luabind/*.cpp", prj.."/**.h" }
    if os.isfile(prj.."/premake4.lua") then
        local func = loadfile(prj.."/premake4.lua");
        func();
    end
    includedirs {
        "LuaJIT-2.0.2/src",
        "boost_1_54_0",
        prj,
        prj.."/luabind/**",
        prj.."/src",
    }
    targetdir "lib"
    targetname "LuaBind"
    configuration { "Debug", "not vs*" }
    buildoptions { "-pg" }
    targetsuffix "D"
    
prj = "AStar"
project(prj)
    kind "StaticLib"
    files { prj.."/*.cpp", prj.."/*.h" }
    if os.isfile(prj.."/premake4.lua") then
        local func = loadfile(prj.."/premake4.lua");
        func();
    end
	includedirs {
		prj,
    }
	targetdir "lib"
	targetname "AStar"
    configuration { "Debug", "not vs*" }
    	buildoptions { "-pg" }
		targetsuffix "D"
		
prj = "TaskLoad"
project(prj)
    kind "StaticLib"
    files { prj.."/*.cpp", prj.."/*.h" }
    if os.isfile(prj.."/premake4.lua") then
        local func = loadfile(prj.."/premake4.lua");
        func();
    end
	includedirs {
		"tinyxml",
		prj,
    }
	targetdir "lib"
	targetname "TaskLoad"
    configuration { "Debug", "not vs*" }
    	buildoptions { "-pg" }
		targetsuffix "D"

prj = "UDPLog"
project(prj)
    kind "StaticLib"
    files { prj.."/*.cpp", prj.."/*.h" }
    if os.isfile(prj.."/premake4.lua") then
        local func = loadfile(prj.."/premake4.lua");
        func();
    end
	includedirs {
		prj,
		"tinyxml",
    }
	targetdir "lib"
	targetname "UDPLog"
    configuration { "Debug", "not vs*" }
    	buildoptions { "-pg" }
		targetsuffix "D"


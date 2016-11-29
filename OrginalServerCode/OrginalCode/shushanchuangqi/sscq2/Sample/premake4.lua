local core="../Core/"
local thrd="../ThirdParty/"
local run="../run/"
local lib="../.lib"
local gen="Generated/"
local gcore="../GameCore/"
local battleutils="BattleUtils/"

solution "Server"
    location ".build"
    language "C++"
    objdir ".objs"

    configurations { "Debug", "Release" }

    configuration "windows"
        defines { "WIN32", "_WIN32" }

    configuration "bsd"
        includedirs { "/usr/local/include", "/usr/local/include/mysql" }
        libdirs { "/usr/local/lib" }

    configuration "macosx"
        includedirs { "/opt/local/include", "/opt/local/include/mysql" }
        libdirs { "/opt/local/lib" }

    configuration "linux"
    	includedirs {
            ".",
			core.."Network",
			core.."SvrLib",
			core.."Utility",
			gen.."ProtoGen",
			thrd.."tinyxml",
			thrd.."openssl/include",
			thrd.."mysql++-3.2.0/lib",
			thrd.."boost_1_54_0",
            thrd.."LuaJIT-2.0.2/src",
			thrd.."luabind-0.9.1",
			"/opt/app/mysql/include/mysql",
            "/opt/app/libmemcached-1.0.14/include",
        }
        libdirs {
            thrd.."lib",
			thrd.."mysql++-3.2.0",
			"/opt/app/mysql/include/mysql",
            "/opt/app/mysql/lib/mysql",
            "/usr/local/mysql/lib/mysql/",
            "/opt/app/libmemcached-1.0.14/lib",
        }
        defines {
            "_APPID=11003369783", "_VERSION="..os.date("%y%m%d%H%M", os.time()), "DEFAULT_BUFFER_SIZE=64*1024", "QQ_VERSION=1"
        }

    configuration { "not vs*" }
        buildoptions { "-std=c++11", "-pipe" }
		linkoptions { "-rdynamic" }

    configuration "not vs*"
        --buildoptions { "-Wall", "-fexceptions", "-fno-strict-aliasing", "-Wno-multichar" }
        buildoptions { "-Wall", "-fexceptions", "-fno-strict-aliasing" }
        --buildoptions { "-Wno-multichar" }

    configuration "Debug"
        flags "Symbols"
        defines "_DEBUG"
        defines "PROT_USE_XML"

    configuration "Release"
		flags "Symbols"
        flags { "OptimizeSpeed", "FloatFast",  }
		defines "NDEBUG"

allcorelibs = {
    "Network",
    "SvrLib",
    "Utility",
}

alllibs = {
	"ProtoGen",
	"ConfigLoad",
}

allsvrs = {
    "LoginServer",
    "CenterServer",
    "GateServer",
	"LogServer",
    "DBServer",
    "GameServer",
}

allprjs = {
    "ServerManager",
}

for _,prj in ipairs(allcorelibs) do
project(prj)
    kind "StaticLib"
    files { core..prj.."/**.cpp", core..prj.."/**.c", core..prj.."/**.h" }
    if os.isfile(core..prj.."/premake4.lua") then
        local func = loadfile(core..prj.."/premake4.lua");
        if func ~= nil then
            func();
        end
    end
	includedirs {
        core..prj,
        core..prj.."/**",
    }
	targetdir(lib)
    configuration { "Debug", "not vs*"}
    	buildoptions { "-pg" }
		targetsuffix "D"
		linkoptions { "-pg" }
end

project("GameCore")
    kind "StaticLib"
    files { gcore.."**.cpp", gcore.."**.c", gcore.."**.h", }
    includedirs {
		gcore.."./",
        core,
        core.."Utility",
        thrd.."tinyxml",
    }
	libdirs {
        lib,
        thrd.."lib",
    }

    targetdir(lib)

	configuration { "Debug" }
		links { "NetworkD", "UtilityD", "TinyXMLD", "ssl" }

	configuration { "Release" }
		links { "Network", "Utility", "TinyXML", "ssl" }

	configuration { "not vs*" }
		links {
			"pthread",
		}

    configuration { "Debug", "not vs*"}
    	buildoptions { "-pg" }
		targetsuffix "D"
		linkoptions { "-pg" }

for _,prj in ipairs(alllibs) do
project(prj)
    kind "StaticLib"
    files { 
        gen..prj.."/**.cpp", 
        gen..prj.."/**.c", 
        gen..prj.."/**.h" 
    }
    if os.isfile(gen..prj.."/premake4.lua") then
        local func = loadfile(gen..prj.."/premake4.lua");
        func();
    end
	includedirs {
        gen..prj,
        gen..prj.."/**",
    }
	targetdir(lib)
    configuration { "Debug", "not vs*"}
    	buildoptions { "-pg" }
		targetsuffix "D"
		linkoptions { "-pg" }
end

project("BattleUtils")
    kind "StaticLib"
    files { 
        battleutils.."**.cpp", 
        battleutils.."**.h",
        battleutils.."**/**.cpp", 
        battleutils.."**/**.h",
        "ServerCommon/CommonDef.h",
        "ServerCommon/CommonDef.cpp"
    }
    includedirs {
        battleutils,
        battleutils.."**",
        battleutils.."**/**",
		gen.."ProtoGen",
        gen.."ConfigLoad",
        "ServerCommon"
    }
	libdirs {
        lib,
        thrd.."lib",
    }

    targetdir(lib)

	configuration { "Debug" }
		links { "NetworkD", "UtilityD", "TinyXMLD", "ProtoGenD", "ConfigLoadD" }

	configuration { "Release" }
		links { "Network", "Utility", "TinyXML", "ProtoGen", "ConfigLoad" }

	configuration { "not vs*" }
		links {
			"pthread",
		}

    configuration { "Debug", "not vs*"}
    	buildoptions { "-pg" }
		targetsuffix "D"
		linkoptions { "-pg" }

for _,prj in ipairs(allsvrs) do
project(prj)
    kind "ConsoleApp"
    files {
         prj.."/**.cpp", prj.."/**.h"
    }
	if prj == "GameServer" or prj == "CenterServer" then
		files {
		"ServerCommon/GameVar.h",
		"ServerCommon/GameVar.cpp",
		"ServerCommon/UserForbidMgr.h",
		"ServerCommon/UserForbidMgr.cpp",
        "ServerCommon/Memcached.h",
        "ServerCommon/Memcached.cpp",
		"ServerCommon/GameBuffManager.h",
		"ServerCommon/GameBuffManager.cpp"}
	end
	if prj == "GameServer" or prj == "DBServer" then
		files {
		"ServerCommon/ItemType.h",
		"ServerCommon/ItemType.cpp"}
	end
	if prj == "GameServer" or prj == "CenterServer" or prj == "DBServer" then
		files {
        "ServerCommon/Parameter.h",
        "ServerCommon/Parameter.cpp",
		"ServerCommon/NameCheckMgr.h",
		"ServerCommon/NameCheckMgr.cpp"}
    end
	if prj == "CenterServer" or prj == "DBServer" then
		files {
		"ServerCommon/InvalidUserMgr.h",
		"ServerCommon/InvalidUserMgr.cpp"}
	end
	if prj == "GameServer" then
		files {
		"ServerCommon/ServiceDateMgr.h",
		"ServerCommon/ServiceDateMgr.cpp",
		"ServerCommon/CommonDef.h",
		"ServerCommon/CommonDef.cpp"}
	end
    if os.isfile(prj.."/premake4.lua") then
        local func = loadfile(prj.."/premake4.lua");
        func();
    end
    includedirs {
		thrd.."AStar",
		thrd.."TaskLoad",
		thrd.."UDPLog",
		thrd.."LuaJIT-2.0.2/src",
		thrd.."luabind-0.9.1",
		thrd.."zlib-1.2.8",
        thrd.."DC_CPP_SDK_V2.0/inc",
		prj,
        prj.."/**",
        prj.."/**/**",
        "ServerCommon",
        core.."Network",
        core.."SvrLib",
        core.."Utility",
        gcore,
		gen.."ProtoGen",
        gen.."ConfigLoad",
    }

	libdirs {
        lib,
        thrd.."lib",
        thrd.."DC_CPP_SDK_V2.0/lib",
        "/opt/app/mysql/lib/mysql",
        "/usr/local/mysql/lib/mysql/",
    }

	targetdir(run)

	if prj == "CenterServer" then
        links {
            "curl",
        }
    end
	if prj == "GameServer" then
        configuration { "Debug" }
            links {
                "BattleUtilsD" }
        configuration { "Release" }
            links {
                "BattleUtils" }
	end

	configuration { "Debug" }
		links {
            "SvrLibD", "NetworkD",
            "GameCoreD", "UtilityD", "SvrLibD", "GameCoreD",
            "AStarD", "TaskLoadD", "LuaBindD", "TinyXMLD", "UDPLogD", "ProtoGenD", "ConfigLoadD",
            "memcached"
        }

	configuration { "Release" }
		links {
            "SvrLib", "Network",
            "GameCore", "Utility", "SvrLib", "GameCore",
            "AStar", "TaskLoad", "LuaBind", "TinyXML", "UDPLog", "ProtoGen", "ConfigLoad",
            "memcached"
        }

	configuration { "not vs*" }
		links {
			"mysqlpp",
			"luajit",
			"z",
			"pthread",
			"rt",
            "dcapi_cpp-64"
		}
    configuration { "Debug", "not vs*"}
    	--buildoptions { "-pg", "-ftime-report"}
    	buildoptions { "-pg"}
		targetsuffix "D"
		linkoptions { "-pg" }
end

for _,prj in ipairs(allprjs) do
project(prj)
    kind "ConsoleApp"
    files {
        prj.."/**.cpp", prj.."/**.c", prj.."/**.h",
    }
    if os.isfile(prj.."/premake4.lua") then
        local func = loadfile(prj.."/premake4.lua");
        func();
    end
    includedirs {
		prj,
		prj.."/**",
		core.."SvrLib",
		core.."Utility",
    }
	libdirs {
        lib,
        thrd.."lib",
    }

	configuration { "Debug" }
		links { "SvrLibD", "NetworkD", "UtilityD", "SvrLibD", "TinyXMLD" }

	configuration { "Release" }
		links { "SvrLib", "Network", "Utility", "SvrLib", "TinyXML" }

	configuration { "not vs*" }
		links {
			"pthread",
		}

	targetdir(run)

    configuration { "Debug", "not vs*"}
    	buildoptions { "-pg" }
		targetsuffix "D"
		linkoptions { "-pg" }
end


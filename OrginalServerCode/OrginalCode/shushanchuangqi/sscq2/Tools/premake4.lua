local core="../Core/"
local thrd="../ThirdParty/"
local gen="Generated/"
local lib="../.lib"

solution "Tools"
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
			--thrd.."openssl/include",
			thrd.."mysql++-3.2.0/lib",
			"/opt/app/mysql/include/mysql",
			thrd.."boost_1_54_0",
        }
        libdirs {
            thrd.."lib",
            "/opt/app/mysql/lib/mysql",
            "/usr/local/mysql/lib/mysql/",
        }
        defines {
            "_VERSION="..os.date("%y%m%d%H%M", os.time()),
        }

    configuration { "not vs*" }
        buildoptions { "-std=c++11" }
		linkoptions { "-rdynamic" }

    configuration "not vs*"
        --buildoptions { "-Wall", "-fexceptions", "-fno-strict-aliasing", "-Wno-multichar" }
        buildoptions { "-Wno-multichar" }

    configuration "Debug"
        flags "Symbols"
        defines "_DEBUG"

    configuration "Release"
		flags "Symbols"
        flags { "OptimizeSpeed", "FloatFast",  }
		defines "NDEBUG"


allprjs = {
    "GenProtocol",
}

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
        core,
        thrd.."tinyxml",
    }
	libdirs {
        lib,
        thrd.."lib",
    }

    targetdir("bin")

	configuration { "Debug" }
		--links { "NetworkD", "UtilityD", "TinyXMLD", "ssl" }
		links { "NetworkD", "UtilityD", "TinyXMLD" }

	configuration { "Release" }
		--links { "Network", "Utility", "TinyXML", "ssl" }
		links { "Network", "Utility", "TinyXML" }

	configuration { "not vs*" }
		links {
			"pthread",
		}

    configuration { "Debug", "not vs*"}
    	buildoptions { "-pg" }
		targetsuffix "D"
end


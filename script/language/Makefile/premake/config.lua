
-- A solution contains projects, and defines the available configurations
solution "Hello1"
configurations { "Debug", "Release" }

-- A project defines one build target
project "Hello1"
kind "ConsoleApp"
language "C++"
files { "**.h", "**.cpp" }

configuration "Debug"
defines { "DEBUG" }
flags { "Symbols" }

configuration "Release"
defines { "NDEBUG" }
flags { "Optimize" }


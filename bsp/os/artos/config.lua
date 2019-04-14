
-- A solution contains projects, and defines the available configurations
solution "artos"
configurations { "Debug", "Release" }

-- A project defines one build target
project "artos"
kind "ConsoleApp"
language "C"
files { "**.h", "**.c" }

configuration "Debug"
defines { "DEBUG" }
flags { "Symbols" }

configuration "Release"
defines { "NDEBUG" }
flags { "Optimize" }


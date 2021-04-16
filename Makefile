dir_scripts = 'scripts'
dir_build   = 'build'

ifeq ($(OS), Windows_NT)
	current_os := Windows
else
	current_os := $(shell uname)
endif

default:
ifeq ($(current_os), Linux)
	@sh -x $(dir_scripts)/test/server.sh
endif

vcpkg:
ifeq ($(current_os), Linux)
	@sh -x $(dir_scripts)/install/vcpkg_on_linux.sh
endif

fmt:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/fmt/format_on_linux.sh
endif          

build: sample server test benchmark
ifeq ($(current_os), Linux)        
endif          

rebuild: clean build 
ifeq ($(current_os), Linux)        
endif          

sample:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/build/build_on_linux.sh -DBUILD_SAMPLE=ON
endif          

server:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/build/build_on_linux.sh -DBUILD_SERVER=ON
endif          

test:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/build/build_on_linux.sh -DBUILD_TEST=ON
endif          

benchmark:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/build/build_on_linux.sh -DBUILD_BENCHMARK=ON
endif          

execute: clean fmt build
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/execute/execute_on_linux.sh
endif          

clean: 
ifeq ($(current_os), Linux)        
	rm -rf $(dir_build)
endif          

.PHONY: default vcpkg fmt build sample server test benchmark execute clean

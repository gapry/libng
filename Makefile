dir_scripts = 'scripts'
dir_build   = 'build'

ifeq ($(OS), Windows_NT)
	current_os := Windows
else
	current_os := $(shell uname)
endif

default: clean build

vcpkg:
ifeq ($(current_os), Linux)
	@sh -x $(dir_scripts)/install/vcpkg_on_linux.sh
endif

fmt:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/fmt/format_on_linux.sh
endif          

build:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/build/build_on_linux.sh
endif          

execute:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/execute/execute_on_linux.sh
endif          

clean: 
ifeq ($(current_os), Linux)        
	rm -rf $(dir_build)
endif          

.PHONY: default vcpkg fmt build execute clean

dir_scripts = 'scripts'
dir_build   = 'build'

ifeq ($(OS), Windows_NT)
	current_os := Windows
else
	current_os := $(shell uname)
endif

vcpkg:
ifeq ($(current_os), Linux)
	@sh -x $(dir_scripts)/install/linux.sh
endif

fmt:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/fmt.sh
endif          

build:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/build.sh
endif          

execute:
ifeq ($(current_os), Linux)        
	@sh -x $(dir_scripts)/run.sh
endif          

clean: 
ifeq ($(current_os), Linux)        
	rm -rf $(dir_build)
endif          

.PHONY: vcpkg fmt build execute clean

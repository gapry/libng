function(libng_add_source_group src_path src_files)
  foreach(files ${src_files})
    get_filename_component(dir_parent "${files}" PATH)
    file(RELATIVE_PATH dir_parent ${src_path} ${dir_parent})
    string(REPLACE "/" "\\" src_files_group "${dir_parent}")
    set(src_files_group "${src_files_group}")
    source_group("${src_files_group}" FILES "${files}")
  endforeach()
endfunction()

function(libng_set_target_warning_level target_name)
	if(MSVC)
	  target_compile_options(${target_name} PRIVATE /WX)     #warning treated as error
	  target_compile_options(${target_name} PRIVATE /W4)     #warning level 4
	  target_compile_options(${target_name} PRIVATE /wd4100) #warning C4100: unreferenced formal parameter in function
	  target_compile_options(${target_name} PRIVATE /wd4201) #warning C4201: nonstandard extension used: nameless struct/union
	  target_compile_options(${target_name} PRIVATE /wd4127) #warning C4127: conditional expression is constant
	else()
	  target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic -Werror)
	endif()
endfunction()

function(libng_set_target_unity_build_mode target_name)
  set_target_properties(${target_name} PROPERTIES UNITY_BUILD ON
                                                  UNITY_BUILD_MODE BATCH
                                                  UNITY_BUILD_BATCH_SIZE 32)	
endfunction()

function(libng_add_library target_name src_path)
  file(GLOB_RECURSE src_files "${src_path}/*.*")
  libng_add_source_group(${src_path} "${src_files}")
  add_library(${target_name} "${src_files}")
  # target_precompile_headers(${target_name} PUBLIC "${target_name}_pch.hpp")
  target_include_directories(${target_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  libng_set_target_warning_level(${target_name})
  libng_set_target_unity_build_mode(${target_name})
endfunction()

function(libng_add_executable target_name src_path)
  file(GLOB_RECURSE src_files "${src_path}/*.*")
  libng_add_source_group(${src_path} "${src_files}")
  add_executable(${target_name} ${src_files})
  # target_precompile_headers(${target_name} PUBLIC "${target_name}_pch.hpp")
  libng_set_target_warning_level(${target_name})
  libng_set_target_unity_build_mode(${target_name})
endfunction()

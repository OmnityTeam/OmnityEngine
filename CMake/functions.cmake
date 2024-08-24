function(omnity_define_module)
	omnity_check_project_setup()
	omnity_get_current_module_target_name(CURRENT_MODULE_TARGET_NAME)
	aux_source_directory("src" CURRENT_MODULE_SOURCES)
	list(LENGTH CURRENT_MODULE_SOURCES MODULE_SOURCE_COUNT)
	if (${MODULE_SOURCE_COUNT} EQUAL 0)
		message(SEND_ERROR "${CURRENT_MODULE_TARGET_NAME} has no source")
	endif()
	add_library(${CURRENT_MODULE_TARGET_NAME} ${CURRENT_MODULE_SOURCES})
	if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/include")
		target_include_directories(${CURRENT_MODULE_TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")
	endif()
	message("Found module ${CURRENT_MODULE_TARGET_NAME}")
endfunction()

function(omnity_add_compile_definitions)
	omnity_get_current_module_target_name(CURRENT_MODULE_TARGET_NAME)
	foreach (ITEM IN LISTS ARGN)
		add_compile_definitions(${CURRENT_MODULE_TARGET_NAME} ${ITEM})
	endforeach()
endfunction()

function(omnity_module_dependencies)
	omnity_get_current_module_target_name(CURRENT_MODULE_TARGET_NAME)
	foreach (ITEM IN LISTS ARGN)
		omnity_target_link_module(${CURRENT_MODULE_TARGET_NAME} PRIVATE ${ITEM})
	endforeach()
endfunction()

function(omnity_module_link_libraries)
	omnity_get_current_module_target_name(CURRENT_MODULE_TARGET_NAME)
	foreach (ITEM IN LISTS ARGN)
		target_link_libraries(${CURRENT_MODULE_TARGET_NAME} PRIVATE ${ITEM})
	endforeach()
endfunction()

function(omnity_module_include_directories)
	omnity_get_current_module_target_name(CURRENT_MODULE_TARGET_NAME)
	include_directories(${CURRENT_MODULE_TARGET_NAME} PRIVATE ${ARGN})
endfunction()

function(omnity_project_setup)
	set(OMNITY_SOURCE_ROOT ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
	message("Setup omnity source at ${CMAKE_CURRENT_SOURCE_DIR}")
endfunction()

function(omnity_check_project_setup)
	if (NOT CMAKE_CURRENT_SOURCE_DIR)
		message(FATAL_ERROR "Project not setup")
	endif()
endfunction()

function(omnity_get_current_module_target_name var_name)
	cmake_path(RELATIVE_PATH CMAKE_CURRENT_SOURCE_DIR 
		BASE_DIRECTORY "${OMNITY_SOURCE_ROOT}" 
		OUTPUT_VARIABLE CURRENT_MODEL_RELV_PATH)
	string(REPLACE "/" ";" CURRENT_MODEL_NAME_DEFINE "${CURRENT_MODEL_RELV_PATH}")
	list(LENGTH CURRENT_MODEL_NAME_DEFINE CURRENT_NAME_ARG_LEN)
	if (NOT ${CURRENT_NAME_ARG_LEN} EQUAL 2)
		message(FATAL_ERROR "We are not in a module directory")
	endif()
	list(GET CURRENT_MODEL_NAME_DEFINE 0 MODULE_SPACE)
	list(GET CURRENT_MODEL_NAME_DEFINE 1 MODULE_NAME)
	set(${var_name} "${MODULE_SPACE}.${MODULE_NAME}" PARENT_SCOPE)
endfunction()

function(omnity_get_current_space_name var_name)
	cmake_path(RELATIVE_PATH CMAKE_CURRENT_SOURCE_DIR 
		BASE_DIRECTORY "${OMNITY_SOURCE_ROOT}" 
		OUTPUT_VARIABLE CURRENT_MODEL_RELV_PATH)
	string(REPLACE "/" ";" CURRENT_MODEL_NAME_DEFINE "${CURRENT_MODEL_RELV_PATH}")
	list(LENGTH CURRENT_MODEL_NAME_DEFINE CURRENT_NAME_ARG_LEN)
	if (${MODULE_NAME_ARG_LEN} EQUAL 0)
		message(FATAL_ERROR "We are in the global space")
	endif()
	list(GET CURRENT_MODEL_NAME_DEFINE 0 MODULE_SPACE)
	set(${var_name} ${MODULE_SPACE} PARENT_SCOPE)
endfunction()

function(omnity_add_executable target_name)
	add_executable(${ARGV} "${target_name}.cpp")
endfunction()

function(omnity_add_library target_name)
	add_library(${ARGV} "${target_name}.cpp")
endfunction()

function(omnity_target_link_module target_name)
	omnity_check_project_setup()
	set (CURRENT_SCOPE "PUBLIC")
	foreach (ITEM IN LISTS ARGN)
		string(TOUPPER ${ITEM} LOWER_ITEM)	
		if (${LOWER_ITEM} STREQUAL "PUBLIC")
			set (CURRENT_SCOPE "PUBLIC")
			continue()
		elseif (${LOWER_ITEM} STREQUAL "PRIVATE")
			set (CURRENT_SCOPE "PRIVATE")
			continue()
		elseif (${LOWER_ITEM} STREQUAL "INTERFACE")
			set (CURRENT_SCOPE "INTERFACE")
			continue()
		endif()
		string(REPLACE "::" ";" MODULE_NAME_DEFINE "${ITEM}")
		list(LENGTH MODULE_NAME_DEFINE MODULE_NAME_ARG_LEN)
		if (${MODULE_NAME_ARG_LEN} EQUAL 1)
			omnity_get_current_space_name(CURRENT_MODULE_SPACE)
			set(MODULE_SPACE ${CURRENT_MODULE_SPACE})
			list(GET MODULE_NAME_DEFINE 0 MODULE_NAME)
		elseif (${MODULE_NAME_ARG_LEN} EQUAL 2)
			list(GET MODULE_NAME_DEFINE 0 MODULE_SPACE)
			list(GET MODULE_NAME_DEFINE 1 MODULE_NAME)
		else()
			message(FATAL_ERROR "Not a vaild module name: ${MODULE_NAME}")
		endif()
		set(CURRENT_OMNITY_MODULE_PATH "${OMNITY_SOURCE_ROOT}/${MODULE_SPACE}/${MODULE_NAME}")
		set(CURRENT_OMNITY_MODULE_INCLUDE "${OMNITY_SOURCE_ROOT}/${MODULE_SPACE}/${MODULE_NAME}/include")
		set(CURRENT_OMNITY_MODULE_TARGET "${MODULE_SPACE}.${MODULE_NAME}")
		if (NOT TARGET ${CURRENT_OMNITY_MODULE_TARGET})
			add_subdirectory("${CURRENT_OMNITY_MODULE_PATH}" "${CMAKE_BINARY_DIR}/Binary/Module/${MODULE_SPACE}/${MODULE_NAME}/")
		endif()
		target_link_libraries("${target_name}" ${CURRENT_SCOPE} "${CURRENT_OMNITY_MODULE_TARGET}")
		if (EXISTS "${CURRENT_OMNITY_MODULE_INCLUDE}")
			target_include_directories("${target_name}" PRIVATE "${CURRENT_OMNITY_MODULE_INCLUDE}")
		endif()
	endforeach()
endfunction()
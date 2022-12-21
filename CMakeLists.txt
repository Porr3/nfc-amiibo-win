cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME nfc-amiibo)
project(${PROJECT_NAME} VERSION 0.2.0 LANGUAGES CXX)

if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE "Release")
endif()

message(STATUS "Build Mode: ${CMAKE_BUILD_TYPE}")

if(MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

add_subdirectory(amiitool)

if(WIN32)
	option(BUILD_EXAMPLES "" OFF)
	option(BUILD_DOXYGEN "" OFF)
	option(BUILD_UTILS "" ON)
	option(LIBNFC_STATIC "" ON)
	option(LIBNFC_DRIVER_PCSC "" ON)
	option(LIBNFC_DRIVER_ACR122_PCSC "" ON)
	option(LIBNFC_DRIVER_ACR122_USB "" OFF)
	option(LIBNFC_DRIVER_PN53X_USB "" OFF)
	add_subdirectory(libnfc)

	include_directories(libnfc/include)
else()
	# TODO: Check if libnfc-dev is installed, if not print message and exit
endif()

file(GLOB src "*.cpp")

add_executable(${PROJECT_NAME} ${src})

target_link_libraries(${PROJECT_NAME} PUBLIC nfc amiitool ${PCSC_LIBRARIES})
set_target_properties(${PROJECT_NAME}
  PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin"
)

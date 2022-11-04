cmake_minimum_required (VERSION 3.20)

project(JBT)

set(JBT_HEADERS
	"include/JBT.hpp"
)

set(JBT_SOURCES
	"src/serializer.cpp"
)

add_library(JBT
	${JBT_HEADERS}
	${JBT_SOURCES}
)

target_include_directories(JBT PUBLIC "include")

find_package(ZLIB REQUIRED)
target_link_libraries(JBT PRIVATE ZLIB::ZLIB)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET JBT PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory(examples)


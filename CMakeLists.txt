cmake_minimum_required (VERSION 3.20)

project(jbt)

set(JBT_HEADERS
	"include/jbt/jbt.hpp"
	"include/jbt/internal.hpp"
	"include/jbt/tag.hpp"
	"include/jbt/serialization.hpp"
)

set(JBT_SOURCES
	"src/jbt.cpp"
	"src/tag.cpp"
	"src/serialization.cpp"
)

add_library(jbt
	${JBT_HEADERS}
	${JBT_SOURCES}
)

target_include_directories(jbt PUBLIC "include")

find_package(ZLIB REQUIRED)
target_link_libraries(jbt PRIVATE ZLIB::ZLIB)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET jbt PROPERTY CXX_STANDARD 20)
endif()

add_subdirectory(examples)


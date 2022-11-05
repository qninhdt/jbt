project(JBT_examples)

set(JBT_EXAMPLES
	"example_1.cpp"
)


foreach(example IN LISTS JBT_EXAMPLES)
	add_executable("JBT_${example}" ${example})
	target_link_libraries("JBT_${example}" PRIVATE jbt)
	find_package(nlohmann_json CONFIG REQUIRED)
	target_link_libraries("JBT_${example}" PRIVATE nlohmann_json::nlohmann_json)
endforeach()
project(JBT_examples)

set(JBT_EXAMPLES
	"example_1.cpp"
)

foreach(example IN LISTS JBT_EXAMPLES)
	add_executable("JBT_${example}" ${example})
	target_link_libraries("JBT_${example}" PRIVATE JBT)
endforeach()
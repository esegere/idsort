add_library(
	parseopt
	src/field.cpp
)

add_library(
	opterr
	src/opterr.cpp
)

target_link_libraries(
	parseopt
	opterr
)

target_include_directories(
	opterr
	PRIVATE
	include
)

target_include_directories(
	parseopt
	PUBLIC
	include
)

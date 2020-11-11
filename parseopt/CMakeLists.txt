add_library(
	parseopt
	src/field.cpp
)

add_library(
	opterr
	src/opterr.cpp
)

add_library(
	parseutil
	src/parseutil.cpp
)

target_link_libraries(
	parseopt
	opterr
	parseutil
)

target_include_directories(
	parseutil
	PRIVATE
	include
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

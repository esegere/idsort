add_library(
	parseopt
	src/field.cpp
)

target_include_directories(
	parseopt
	PUBLIC
	include
)

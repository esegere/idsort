add_library(
	analyzer
	src/sortinfo.cpp
)

target_link_libraries(
	analyzer
	parseopt
)

target_include_directories(
	analyzer
	PUBLIC
	include
)

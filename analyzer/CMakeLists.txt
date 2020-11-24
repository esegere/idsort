add_library(
	analyzer
	src/sortinfo.cpp
	src/writesort.cpp
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

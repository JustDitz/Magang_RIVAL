cmake_minimum_required(VERSION 3.0)

project( oprec )

find_package( OpenCV REQUIRED )

add_executable( oprec src/Tugas_1/main.cpp  src/Tugas_1/function.cpp )

target_link_libraries( oprec ${OpenCV_LIBS} )	

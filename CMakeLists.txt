cmake_minimum_required(VERSION 2.8)

project(wordnettest)


SET (WordNet_INC_DIRS "/usr/inlude")
SET (WordNet_LIB_DIRS "wordnet")

include_directories( ${WordNet_INC_DIRS} )

add_executable(wordnettest main.cpp)

target_link_libraries( wordnettest ${WordNet_LIB_DIRS} )




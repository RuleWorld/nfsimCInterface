cmake_minimum_required(VERSION 2.8.4)

set(SUB_DIRS
    include/
    include/nauty24 
    include/NFutil 
    include/NFutil/MTrand 
    include/NFtest/transcription 
    include/NFtest/tlbr 
    include/NFtest/simple_system 
    include/NFtest/agentcell/cell 
    include/NFtest/agentcell 
    include/NFscheduler 
    include/NFreactions/transformations 
    include/NFreactions/reactions 
    include/NFreactions/reactantLists 
    include/NFreactions/mappings 
    include/NFreactions 
    include/NFoutput 
    include/NFinput 
    include/NFinput/TinyXML 
    include/NFinput/json 
    include/NFfunction/muParser 
    include/NFfunction 
    include/NFcore 
    include/NFcore/reactionSelector 
    include/NFcore/moleculeLists 
)


project(nfsim_c)

set(SOURCE_FILES
    nfsim_connector.cpp
    nfsim_connector.h)

add_definitions("-Wno-deprecated-declarations")
add_definitions(-std=c++11)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${SUB_DIRS})
link_directories(lib)

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} NFsim)


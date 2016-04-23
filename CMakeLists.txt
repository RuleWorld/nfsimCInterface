cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_VERBOSE_MAKEFILE on)

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

add_definitions("-fPIC")

set(SOURCE_FILES
    src/nfsim_c.cpp
    src/nfsim_c.h
    src/nfsim_c_structs.h
    src/nfsim_c_structs.cpp
)



add_definitions("-Wno-deprecated-declarations")
add_definitions(-std=c++11)


add_library(objlib OBJECT ${SOURCE_FILES})
# shared libraries need PIC
set_property(TARGET ${objlib} PROPERTY POSITION_INDEPENDENT_CODE 1)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${SUB_DIRS})
link_directories(${CMAKE_SOURCE_DIR}/lib)


add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:objlib>)
target_link_libraries(${PROJECT_NAME} NFsim)

#add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:objlib>)


#add_executable(example example.c)
#target_link_libraries(example ${PROJECT_NAME} NFsim stdc++)
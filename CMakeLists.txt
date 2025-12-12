cmake_minimum_required(VERSION 3.10)
project(Lab4 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)  # Auto-export symbols for DLLs
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
    
    # Remove "lib" prefix from DLLs
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

# Define library names as variables
set(LIB1_NAME lib_1)
set(LIB2_NAME lib_2)

add_library(${LIB1_NAME} SHARED 
    lib_1/prime_1.cpp
    lib_1/square_1.cpp
)

add_library(${LIB2_NAME} SHARED 
    lib_2/prime_2.cpp
    lib_2/square_2.cpp
)

set_target_properties(${LIB1_NAME} PROPERTIES OUTPUT_NAME "mathlib1")
set_target_properties(${LIB2_NAME} PROPERTIES OUTPUT_NAME "mathlib2")

# Program 1 - Static linking
add_executable(program1 program1/main.cpp)
target_link_libraries(program1 ${LIB1_NAME})

# Program 2 - Dynamic loading
add_executable(program2 program2/main.cpp)
if(WIN32)
    target_link_libraries(program2 kernel32)
endif()

if(MINGW)
    add_definitions(-DMINGW)
    set(CMAKE_SHARED_LIBRARY_PREFIX "")
    set(CMAKE_SHARED_LIBRARY_SUFFIX ".dll")
    set(CMAKE_IMPORT_LIBRARY_SUFFIX ".dll.a")
endif()

if(WIN32)
    # Copy mathlib1.dll for program1
    add_custom_command(TARGET program1 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:${LIB1_NAME}>"
        "$<TARGET_FILE_DIR:program1>"
        COMMENT "Copying mathlib1.dll to program1 directory"
    )
    
    # Copy both DLLs for program2
    add_custom_command(TARGET program2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:${LIB1_NAME}>"
        "$<TARGET_FILE_DIR:program2>"
        COMMENT "Copying mathlib1.dll to program2 directory"
    )
    
    add_custom_command(TARGET program2 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "$<TARGET_FILE:${LIB2_NAME}>"
        "$<TARGET_FILE_DIR:program2>"
        COMMENT "Copying mathlib2.dll to program2 directory"
    )
endif()


install(TARGETS ${LIB1_NAME} ${LIB2_NAME} program1 program2
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
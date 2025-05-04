cmake_minimum_required(VERSION 3.35)

set(CMAKE_CXX_COMPILER /usr/bin/clang++-19)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(
    dice-game
    LANGUAGES CXX
)

include(cmake/clang-cxx-dev-tools.cmake)

# =======================================
#      ENABLING COMPILE COMMANDS EXPORT FOR CLANG-TIDY
# =======================================
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# =======================================

# =======================================
#      SETTING UP COMPILE OPTIONS
# =======================================
# add_compile_options(-Wall)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(
    "${CMAKE_CXX_FLAGS}"
    "-Wunused"
)
# =======================================

# =======================================
#      SUBMODULES CHECKOUT
# =======================================
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules.")
        endif()
    endif()
endif()

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/googletest/CMakeLists.txt")
   message(FATAL_ERROR "The necessary submodule gtest was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
endif()
# =======================================

set(EXTERNAL_DEPS ${PROJECT_SOURCE_DIR}/external)
set(SOURCE_CODE_DIR ${PROJECT_SOURCE_DIR}/src)
set(SOURCE_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_LIBRARY ${PROJECT_NAME}_lib)

message(STATUS "Collecting sources")

file(GLOB_RECURSE PROJECT_SOURCES
    ${SOURCE_CODE_DIR}/*.cpp
)

# =======================================
#   Remove main.cpp from sources so we can have static library
# =======================================
list(REMOVE_ITEM PROJECT_SOURCES ${SOURCE_CODE_DIR}/main.cpp)
# =======================================

message(STATUS "Collected source files: \n${PROJECT_SOURCES}")

add_library(${PROJECT_LIBRARY} STATIC ${PROJECT_SOURCES})

target_include_directories(${PROJECT_LIBRARY}
    PUBLIC
        ${SOURCE_INCLUDE_DIR}
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_CODE_DIR}/main.cpp
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${SOURCE_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBRARY})


# =======================================
#       UNIT TESTS
# =======================================
set(TESTS_DIR ${PROJECT_SOURCE_DIR}/test)

add_subdirectory(${EXTERNAL_DEPS}/googletest)

message(STATUS "Setting up unit tests")
file(GLOB_RECURSE TEST_SRCS
${TESTS_DIR}/*.cpp)

message(STATUS "Collected source files for tests: \n${TEST_SRCS}")

add_executable(unit_tests ${TEST_SRCS})

target_include_directories(unit_tests
    PUBLIC
        ${EXTERNAL_DEPS}/googletest
        ${SOURCE_INCLUDE_DIR}
)

target_link_libraries(unit_tests
    PRIVATE
        gtest
        gtest_main
        ${PROJECT_LIBRARY}
)

enable_testing()
add_test(NAME UnitTest COMMAND unit_tests)


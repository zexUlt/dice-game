file(GLOB
    ALL_CXX_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/include/*.hpp
    ${PROJECT_SOURCE_DIR}/src/*.cpp
)

option(APPLY_FIX OFF)

find_program(CLANG_TIDY "clang-tidy")
if(CLANG_TIDY)
    if(APPLY_FIX)
        add_custom_target(clang-tidy
            COMMAND /usr/bin/clang-tidy
            --fix
            -p=${PROJECT_SOURCE_DIR}/build
            --extra-arg=-std=c++20
            ${ALL_CXX_SOURCE_FILES} ${PROJECT_SOURCE_DIR}/main.cpp
        )
    else()
        add_custom_target(clang-tidy
            COMMAND /usr/bin/clang-tidy
            -p=${PROJECT_SOURCE_DIR}/build
            --extra-arg=-std=c++20
            ${ALL_CXX_SOURCE_FILES} ${PROJECT_SOURCE_DIR}/main.cpp
            )
    endif()
endif()
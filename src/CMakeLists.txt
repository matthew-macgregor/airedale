if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(VCPKG_TARGET_TRIPLET "x64-windows-static" CACHE STRING "")
endif()

find_package(Boost 1.82.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
find_package(unofficial-sodium 1.0.18 CONFIG REQUIRED)

add_executable(airedale
    main.cpp
    policy.cpp
    util.cpp
    providers/chacha20.cpp
    providers/checksum.cpp
    providers/mt19937.cpp
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message("Using MSVC")
    # using Visual Studio C++
    set(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
    target_compile_options(airedale PUBLIC /MT)
    target_link_options(airedale PUBLIC /INCREMENTAL:NO /NODEFAULTLIB:MSVCRT)
else()
    target_link_libraries(airedale -static)
endif()

target_include_directories(airedale PUBLIC ../include)
target_link_libraries(airedale PRIVATE unofficial-sodium::sodium)

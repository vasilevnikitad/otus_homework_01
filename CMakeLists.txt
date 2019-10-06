cmake_minimum_required(VERSION 3.12)

project(helloworld VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Boost COMPONENTS log_setup REQUIRED)
find_package(Boost COMPONENTS log REQUIRED)

set( PROJECT_BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER} )

configure_file(project_info.hpp.in ${PROJECT_SOURCE_DIR}/project_info.hpp)

add_library(project_info project_info.cpp)
add_executable(helloworld_cli main.cpp)
add_executable(test_project_info test_project_info.cpp)

set_target_properties(
    helloworld_cli project_info test_project_info
        PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            COMPILE_DEFINITIONS BOOST_ALL_DYN_LINK
            COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra;-Werror"
)

set_target_properties(
    test_project_info
        PROPERTIES
            INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(
    helloworld_cli
        project_info
        boost_system
        boost_thread
        boost_log_setup
        boost_log
        Threads::Threads
)

target_link_libraries(
    test_project_info
        project_info
        boost_unit_test_framework
        Threads::Threads
)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT vasilevnikitad@gmail.com)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

install(
    TARGETS helloworld_cli test_project_info project_info 
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static
)


include(CPack)

add_test(helloworld_tests test_project_info)
enable_testing()

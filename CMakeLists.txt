cmake_minimum_required(VERSION 3.12)

set( PROJECT_BUILD_NUMBER $ENV{TRAVIS_BUILD_NUMBER} )

if ("${PROJECT_BUILD_NUMBER}" STREQUAL "")
    set(PROJECT_BUILD_NUMBER "1")
endif ("${PROJECT_BUILD_NUMBER}" STREQUAL "")

project(helloworld VERSION 0.0.${PROJECT_BUILD_NUMBER})

find_package(Threads REQUIRED)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)
find_package(Boost COMPONENTS log_setup REQUIRED)
find_package(Boost COMPONENTS log REQUIRED)


configure_file(project_info.hpp.in ${PROJECT_SOURCE_DIR}/project_info.hpp)

add_executable(helloworld_cli main.cpp)
add_executable(test_project_info test_project_info.cpp)

set_target_properties(
    helloworld_cli test_project_info
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
        boost_system
        boost_thread
        boost_log_setup
        boost_log
        Threads::Threads
)

target_link_libraries(
    test_project_info
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
    TARGETS helloworld_cli test_project_info
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib/static
)


include(CPack)

add_test(helloworld_tests test_project_info)
enable_testing()

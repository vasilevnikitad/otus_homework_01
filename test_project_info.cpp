#define BOOST_TEST_MODULE project_info_test_module

#include "project_info.hpp"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(project_info_test_suite)

BOOST_AUTO_TEST_CASE(project_info_test_build_num)
{
    BOOST_CHECK(project_info::version::get_build_num() > 0 );
}

BOOST_AUTO_TEST_SUITE_END()

#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/console.hpp>

#include "project_info.hpp"

#include <iostream>

int main()
{
  boost::log::add_console_log(std::cout, boost::log::keywords::format = "%Message%");

  BOOST_LOG_TRIVIAL(info) << "build " << project_info::version::get_patch();
  BOOST_LOG_TRIVIAL(info) << "Hello, World!";
  return 0;
}

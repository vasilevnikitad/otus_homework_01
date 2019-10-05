#include "project_info.hpp"

#include <ostream>
#include <iostream>


namespace project_info {
  std::ostream& operator << (std::ostream &out, project_info::version const &ver)
  {
    out << ver.get_major() << '.' << ver.get_minor() << '.' << ver.get_patch();
    return out;
  }
}


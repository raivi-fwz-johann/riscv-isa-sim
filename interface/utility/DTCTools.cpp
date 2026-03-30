#include "DTCTools.hpp"

#include <cstdlib>
#include <iostream>

namespace tools {

int fileDts2Dtb(const std::string &DtsFile, const std::string &OutPath) {
  char cmd[256];
  sprintf(cmd, "dtc -I dts -O dtb -o %s %s", OutPath.c_str(), DtsFile.c_str());
  return system(cmd);
}

} // namespace tools
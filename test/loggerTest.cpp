//
// Created by kangd on 24.02.18.
//

#include <raiCommon/rai_utils.hpp>

int main() {

  std::string path = "/tmp/test/test2/test3";
//  rai::Utils::logger->setLogPath(path);
  rai::Utils::timer->setLogPath(path);


//  rai::Utils::timer->getTimedItems();
  return 0;
}
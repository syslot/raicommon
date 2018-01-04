//
// Created by jhwangbo on 18. 1. 1.
//

#ifndef RAICOMMON_RAI_MESSAGE_LOGGER_HPP
#define RAICOMMON_RAI_MESSAGE_LOGGER_HPP

#include <sys/time.h>
#include <ostream>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace rai {

constexpr int RSEVERITY_INFO = 0;
constexpr int RSEVERITY_WARN = 1;
constexpr int RSEVERITY_FATAL = 2;

class RaiMsg {

 public:

  void stream(const char *file, const int line, std::stringstream& msg, int severity);

 private:
  std::stringstream log;
};

}

#endif //RAICOMMON_RAI_MESSAGE_LOGGER_HPP

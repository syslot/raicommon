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

const int RSEVERITY_INFO = 0;
const int RSEVERITY_WARN = 1;
const int RSEVERITY_FATAL = 2;

class RaiMsg {
  std::stringstream data_;
  time_t timestamp_;

 public:

  void stream(const char *file, int line, std::stringstream msg, int severity);

};

}

#endif //RAICOMMON_RAI_MESSAGE_LOGGER_HPP

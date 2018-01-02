//
// Created by jhwangbo on 18. 1. 1.
//
#include "raiCommon/utils/rai_message_logger/rai_message_logger.hpp"
#include <ctime>

namespace rai {

  void RaiMsg::stream(const char *file, const int line, std::stringstream& msg, int severity) {

    time_t currentTime;
    struct tm tm_time;

    time( &currentTime );                   // Get the current time
    localtime_r(&currentTime, &tm_time);  // Convert the current time to the local time

    const char* filename_start = file;
    const char* filename = filename_start;
    while(*filename != '\0')
      filename++;
    while((filename != filename_start) && (*(filename - 1) != '/'))
      filename--;

    std::stringstream printout;

    std::string color;

    switch(severity) {
      case 0:
        color = "";
        break;
      case 1:
        color = "\033[33m";
        break;
      case 2:
        color = "\033[1;31m";
        break;
    }

    printout << "[" << std::setfill('0')
             << std::setw(2) << 1 + tm_time.tm_mon << ':'
             << std::setw(2) << tm_time.tm_mday << ':'
             << std::setw(2) << tm_time.tm_hour << ':'
             << std::setw(2) << tm_time.tm_min << ':'
             << std::setw(2) << tm_time.tm_sec << ' '
             << std::setfill(' ')
             << filename
             <<':'<<line<<"] "<<color<<msg.str()<<"\033[0m\n";

    if(LOGTOFILE)
      log<<printout.str();
    else
      std::cout<<printout.str();

    if(severity == RSEVERITY_FATAL)
      exit(0);
  }

}

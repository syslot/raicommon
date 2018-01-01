//
// Created by jhwangbo on 18. 1. 1.
//
#include "raiCommon/utils/rai_message_logger/rai_message_logger.hpp"


namespace rai {

  void RaiMsg::stream(const char *file, int line, std::stringstream msg, int severity) {

    struct ::tm tm_time;
    localtime_r(&timestamp_, &tm_time);

    const char* filename_start = file;
    const char* filename = filename_start;
    while(*filename != '\0')
      filename++;
    while((filename != filename_start) && (*(filename - 1) != '/'))
      filename--;

    std::string stripped_filename(filename);

    std::stringstream printout;
    printout << "["
             << std::setw(2) << 1 + tm_time.tm_mon
             << std::setw(2) << tm_time.tm_mday
             << '-'
             << std::setw(2) << tm_time.tm_hour
             << std::setw(2) << tm_time.tm_min
             << std::setw(2) << tm_time.tm_sec
             << stripped_filename
             <<":"<<line<<"] "<<msg.str()<<"\n";

    std::cout<<printout.str();

    if(severity == RSEVERITY_FATAL)
      exit(0);
  }

}

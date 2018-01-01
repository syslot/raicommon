//
// Created by jhwangbo on 18. 1. 1.
//

#ifndef RAICOMMON_RAI_MESSAGE_HPP
#define RAICOMMON_RAI_MESSAGE_HPP
#include "rai_message_logger.hpp"

#define RAIINFO(msg) rai::RaiMsg().stream(__FILE__, __LINE__, msg, RSEVERITY_INFO);
#define RAIIWARN(msg) rai::RaiMsg().stream(__FILE__, __LINE__, msg, RSEVERITY_WARN);
#define RAIFATAL(msg) rai::RaiMsg().stream(__FILE__, __LINE__, msg, RSEVERITY_FATAL);

#define RAIINFO_IF(con, msg) if(con) rai::RaiMsg().stream(__FILE__, __LINE__, msg, RSEVERITY_INFO);
#define RAIIWARN_IF(con, msg) if(con) rai::RaiMsg().stream(__FILE__, __LINE__, msg, RSEVERITY_WARN);
#define RAIFATAL_IF(con, msg) if(con) rai::RaiMsg().stream(__FILE__, __LINE__, msg, RSEVERITY_FATAL);

#define RAIFASSERT(con, msg) if(con) rai::RaiMsg().stream(__FILE__, __LINE__, msg, RSEVERITY_FATAL);

#endif //RAICOMMON_RAI_MESSAGE_HPP

#ifndef CONNECTHANDLER_H_
#define CONNECTHANDLER_H_

#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cerrno>

#include <fcntl.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/poll.h>

#include "HostInfo.h"

/* Thread connection handler */
void* ConnectHandler(void* thread_arg);

#endif /* CONNECTHANDLER_H_ */

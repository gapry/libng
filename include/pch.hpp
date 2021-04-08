#pragma once

#include "platform/os.hpp"

#ifdef GNET_OS_WINDOWS
// clang-format off
#include <Winsock2.h> 
#include <Windows.h>
// clang-format on
#include <conio.h>                 //
#include <ws2tcpip.h>              // getaddrinfo
#pragma comment(lib, "Ws2_32.lib") //
#else
#include <arpa/inet.h>  // htons
#include <netdb.h>      // struct addrinfo
#include <sys/ioctl.h>  //
#include <sys/socket.h> //
#include <unistd.h>     // sleep()
#include <poll.h>       //
#include <fcntl.h>      //
#include <fmt/core.h>   //
#include <iostream>     //
#include <signal.h>     //
#include <cstdio>       //
#include <cstring>      //
#include <sys/stat.h>   //
#include <sys/wait.h>   // wait
#include <syslog.h>     //
#endif

namespace gnet {

class ui;
class game;
class client;
class player;

} // namespace gnet

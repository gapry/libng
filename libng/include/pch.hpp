#pragma once

#include "platform/os.hpp"

#ifdef LIBNG_OS_WINDOWS
// clang-format off
#include <Winsock2.h> 
#include <Windows.h>
// clang-format on
#include <conio.h>                 //
#include <ws2tcpip.h>              // getaddrinfo
#pragma comment(lib, "Ws2_32.lib") //
#else
#include <arpa/inet.h>  // htons
#include <fcntl.h>      //
#include <netdb.h>      // struct addrinfo
#include <poll.h>       //
#include <signal.h>     //
#include <sys/ioctl.h>  //
#include <sys/socket.h> //
#include <sys/stat.h>   //
#include <sys/wait.h>   // wait
#include <syslog.h>     //
#include <unistd.h>     // sleep()
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fmt/core.h>
#include <iostream>
#include <utility>

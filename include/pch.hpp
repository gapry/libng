#pragma once

#ifdef _WIN32
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
#endif

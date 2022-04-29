#pragma once

#include <utility> // std::forward

#define LIBNG_FORWARD(T) (std::forward<decltype(T)>(T))
#include "Timer.hpp"

#include <stdlib.h>

#ifdef __unix__
#include <sys/time.h>
#elif defined _WIN32
#include <windows.h>
#error "Timer is not implemented for windows!"
#endif

unsigned int vox::platform::CurrentTime() {
    timeval t;
    gettimeofday(&t, NULL);
    return t.tv_sec * 1000000 + t.tv_usec;
}

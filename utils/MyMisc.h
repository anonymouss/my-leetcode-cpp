#ifndef __UITLS_MY_MISC__
#define __UITLS_MY_MISC__

#include <iostream>

auto disable_io_sync = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();

#endif // __UITLS_MY_MISC__
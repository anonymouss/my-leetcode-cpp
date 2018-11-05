#ifndef __UITLS_MY_MISC__
#define __UITLS_MY_MISC__

#include <iostream>

auto auto_disable_io_sync = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();

// test case util
int testId = 1;
auto TestCount = [](bool enableBoolean = false) {
    std::cout << "Case " << testId++ << ":\n";
    if (enableBoolean) std::cout << std::boolalpha;
};

#endif // __UITLS_MY_MISC__
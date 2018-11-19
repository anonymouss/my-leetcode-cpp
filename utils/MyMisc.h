#ifndef __UITLS_MY_MISC__
#define __UITLS_MY_MISC__

#include <iostream>

auto auto_disable_io_sync = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return 0;
}();


// test case util
enum class IOFormat : uint8_t {
    NONE = 0x0,
    BOOL = 0x1,
    OCTA = 0x2,
    HEXA = 0x4
};

int testId = 1;

auto TestCount = [](IOFormat format = IOFormat::NONE) {
    std::cout << "Case " << testId++ << ":\n";
    switch (format) {
        case IOFormat::BOOL:
            std::cout << std::boolalpha;
            break;
        case IOFormat::OCTA:
            std::cout << std::oct;
            break;
        case IOFormat::HEXA:
            std::cout << std::hex;
            break;
        default:
            break;
    }

};

#endif // __UITLS_MY_MISC__
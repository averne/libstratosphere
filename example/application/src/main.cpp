#include <cstdio>
#include <cstdint>
#include <array>
#include <switch.h>

#include "test.h"

int main(int argc, char* argv[]) {
    std::uint32_t test = 0;
    std::array<char, 0x10> buffer = {};
    consoleInit(NULL);

    if (auto rc = testInitialize(); R_FAILED(rc)) {
        std::printf("Failed to init test service: %#x\n", rc);
        goto loop;
    }

    if (auto rc = testTest1(&test); R_FAILED(rc)) {
        std::printf("Failed test1 command: %#x\n", rc);
        goto loop;
    }

    std::printf("Got value back: %#x\n", test);

    if (auto rc = testTest2(buffer.data(), buffer.size()); R_FAILED(rc)) {
        std::printf("Failed test2 command: %#x\n", rc);
        goto loop;
    }

    std::printf("Got string back: %s\n", buffer.data());

loop:
    testExit();

    std::printf("Press + to exit\n");

    while (appletMainLoop()) {
        hidScanInput();
        if (hidKeysDown(CONTROLLER_P1_AUTO) & KEY_PLUS)
            break;
        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}

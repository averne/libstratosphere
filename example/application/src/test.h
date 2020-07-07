#pragma once

#include <stdlib.h>
#include <switch.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    TestCmdId_TestCommand1 = 0,
    TestCmdId_TestCommand2 = 1,
} TestCmdId;

Result testInitialize(void);
void testExit(void);
Service *testServiceSession(void);

Result testTest1(u32 *out);
Result testTest2(void *buffer, size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

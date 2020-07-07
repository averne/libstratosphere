#define NX_SERVICE_ASSUME_NON_DOMAIN
#include "service_guard.h"
#include "test.h"

static Service g_testSrv;

NX_GENERATE_SERVICE_GUARD(test);

Result _testInitialize(void) {
    return smGetService(&g_testSrv, "test");
}

void _testCleanup(void) {
    serviceClose(&g_testSrv);
}

Service *testServiceSession(void) {
    return &g_testSrv;
}

Result testTest1(u32 *out) {
    u32 tmp = 0;
    Result rc = serviceDispatchOut(&g_testSrv, TestCmdId_TestCommand1, tmp);
    if (out)
        *out = tmp;
    return rc;
}

Result testTest2(void *buffer, size_t size) {
    return serviceDispatch(&g_testSrv, TestCmdId_TestCommand2,
        .buffer_attrs = { SfBufferAttr_Out | SfBufferAttr_HipcMapAlias },
        .buffers = { { buffer, size } },
    );
}

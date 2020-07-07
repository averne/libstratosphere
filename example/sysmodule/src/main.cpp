#include <stratosphere.hpp>

#include "server.hpp"

using namespace ams;

extern "C" {
    u32 __nx_applet_type = AppletType_None;

    #define INNER_HEAP_SIZE 1 * os::MemoryPageSize
    size_t nx_inner_heap_size = INNER_HEAP_SIZE;
    char   nx_inner_heap[INNER_HEAP_SIZE];

    void __libnx_initheap(void);
    void __appInit(void);
    void __appExit(void);

    /* Exception handling */
    alignas(0x10) u8 __nx_exception_stack[os::MemoryPageSize];
    u64 __nx_exception_stack_size = sizeof(__nx_exception_stack);
    void __libnx_exception_handler(ThreadExceptionDump *ctx);
}

namespace ams {
    ncm::ProgramId CurrentProgramId = { 0x0100000000000123ul };
    namespace result {
        bool CallFatalOnResultAssertion = false;
    }
}

void __libnx_initheap(void) {
	void*  addr = nx_inner_heap;
	size_t size = nx_inner_heap_size;

	/* Newlib */
	extern char *fake_heap_start;
	extern char *fake_heap_end;

	fake_heap_start = (char *)addr;
	fake_heap_end   = (char *)addr + size;
}

void __libnx_exception_handler(ThreadExceptionDump *ctx) {
    ams::CrashHandler(ctx);
}

void __appInit(void) {
    hos::InitializeForStratosphere();
    ams::CheckApiVersion();
}

void __appExit(void) {
    /* ... */
}

namespace {

struct TestServerOptions {
    static constexpr size_t PointerBufferSize = 0x100;
    static constexpr size_t MaxDomains        = 0;
    static constexpr size_t MaxDomainObjects  = 0;
};

constexpr auto serv_name = sm::ServiceName::Encode("test");

constexpr std::size_t num_servers  = 1;
constexpr std::size_t max_sessions = 1;

} // namespace

int main(int argc, char **argv) {
    static sf::hipc::ServerManager<num_servers, TestServerOptions, max_sessions> server_manager;
    R_ABORT_UNLESS(server_manager.RegisterServer<test::TestService>(serv_name, max_sessions));

    /* Loop forever, servicing our services. */
    server_manager.LoopProcess();

    return 0;
}

#pragma once

#include <stratosphere.hpp>

namespace test {

class TestService final: public ams::sf::IServiceObject {
    protected:
        enum class CommandId {
            TestCommand1 = 0,
            TestCommand2 = 1,
        };

    private:
        ams::Result TestCommand1(const ams::sf::Out<std::uint32_t> out);
        ams::Result TestCommand2(const ams::sf::OutBuffer &buffer);

    public:
        DEFINE_SERVICE_DISPATCH_TABLE {
            MAKE_SERVICE_COMMAND_META(TestCommand1),
            MAKE_SERVICE_COMMAND_META(TestCommand2),
        };
};

} // namespace test

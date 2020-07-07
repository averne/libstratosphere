#pragma once

#include <stratosphere.hpp>

namespace test {

class TestMitmService final: public ams::sf::IMitmServiceObject {
    protected:
        enum class CommandId {
            TestCommand1 = 0,
            TestCommand2 = 1,
        };

    public:
        static constexpr bool ShouldMitm(const ams::sm::MitmProcessInfo &client_info) {
            return true;
        }

        TestMitmService(std::shared_ptr<Service> &&s, const ams::sm::MitmProcessInfo &c):
            ams::sf::IMitmServiceObject(std::forward<std::shared_ptr<Service>>(s), c) { }

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

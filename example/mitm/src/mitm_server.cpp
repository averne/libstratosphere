#include <algorithm>
#include <string_view>

#include "mitm_server.hpp"

using namespace ams;

namespace test {

ams::Result TestMitmService::TestCommand1(const ams::sf::Out<std::uint32_t> out) {
    out.SetValue(0x37173);

    return ResultSuccess();
}

ams::Result TestMitmService::TestCommand2(const ams::sf::OutBuffer &buffer) {
    constexpr std::string_view str = "no yeet allowed";

    R_UNLESS(buffer.GetSize() > str.size(), 0x1337);

    std::copy(str.begin(), str.end(), buffer.GetPointer());

    return ResultSuccess();
}

} // namespace test

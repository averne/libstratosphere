#include <algorithm>
#include <string_view>

#include "server.hpp"

using namespace ams;

namespace test {

ams::Result TestService::TestCommand1(const sf::Out<std::uint32_t> out) {
    out.SetValue(0xdab);

    return ResultSuccess();
}


ams::Result TestService::TestCommand2(const ams::sf::OutBuffer &buffer) {
    constexpr std::string_view str = "yeeeeeeeeeeeeet";

    R_UNLESS(buffer.GetSize() > str.size(), 0x1337);

    std::copy(str.begin(), str.end(), buffer.GetPointer());

    return ResultSuccess();
}

} // namespace test

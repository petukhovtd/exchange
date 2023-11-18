#pragma once

#include <optional>

namespace exchange {

using ActorId = unsigned long long;

using ActorIdOpt = std::optional<ActorId>;

const constexpr ActorId startId = 0;

}// namespace exchange

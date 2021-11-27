#ifndef EXCHANGE_ID_H
#define EXCHANGE_ID_H

#include <optional>

namespace exchange
{

using ActorId = unsigned long long;

using ActorIdOpt = std::optional< ActorId >;

static const constexpr ActorId startId = 0;

}

#endif

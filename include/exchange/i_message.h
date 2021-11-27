#ifndef EXCHANGE_I_MESSAGE_H
#define EXCHANGE_I_MESSAGE_H

#include <memory>

namespace exchange
{

class IMessage
{
public:
     virtual ~IMessage() = default;
};

using MessagePtr = std::shared_ptr< IMessage >;

}

#endif

#ifndef EXCHANGE_I_ACTOR_H
#define EXCHANGE_I_ACTOR_H

#include <exchange/i_message.h>
#include <exchange/id.h>

#include <memory>
#include <optional>

namespace exchange
{

class Exchange;

class IActor
{
     friend Exchange;
public:
     virtual ~IActor() = default;

     virtual void Receive( const MessagePtr & message ) = 0;

     ActorIdOpt GetId() const
     {
          return id_;
     }

private:
     ActorIdOpt id_;
};

using ActorPtr = std::shared_ptr< IActor >;

}

#endif

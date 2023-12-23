#pragma once

#include <exchange/iactor.h>
#include <exchange/id.h>

namespace exchange {

class IExchange {
public:
  virtual ~IExchange() = default;

  virtual ActorId Add(const ActorPtr &actor) = 0;

  virtual void Delete(ActorId id) = 0;

  virtual bool Send(ActorId id, const MessagePtr &msg) const = 0;
};

}// namespace exchange
#pragma once

#include <exchange/iactor.h>
#include <exchange/id.h>

#include <memory>

namespace exchange {

class IExchange {
public:
  virtual ~IExchange() = default;

  virtual ActorId Add(const ActorPtr &actor) = 0;

  virtual ActorPtr Delete(ActorId id) = 0;

  virtual bool Send(ActorId id, const MessagePtr &msg) const = 0;
};

using ExchangePtr = std::shared_ptr<IExchange>;

}// namespace exchange

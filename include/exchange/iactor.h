#pragma once

#include <exchange/id.h>
#include <exchange/imessage.h>

#include <memory>

namespace exchange {

class IExchange;

class IActor {
public:
  virtual ~IActor() = default;

  virtual void Receive(const MessagePtr &message) = 0;

  virtual void SetId(ActorId id) = 0;

  virtual void ResetId() = 0;
};

using ActorPtr = std::shared_ptr<IActor>;

}// namespace exchange

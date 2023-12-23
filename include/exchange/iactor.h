#pragma once

#include <exchange/id.h>
#include <exchange/imessage.h>

#include <memory>
#include <optional>

namespace exchange {

class IExchange;

class IActor {
  friend IExchange;

public:
  virtual ~IActor() = default;

  virtual void Receive(const MessagePtr &message) = 0;

  ActorIdOpt GetId() const;

private:
  ActorIdOpt id_;
};

using ActorPtr = std::shared_ptr<IActor>;

}// namespace exchange

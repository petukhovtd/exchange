#pragma once

#include <memory>

namespace exchange {

class IMessage {
public:
  virtual ~IMessage() = default;
};

using MessagePtr = std::shared_ptr<IMessage>;

}// namespace exchange

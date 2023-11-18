#pragma once

#include <exchange/imessage.h>
#include <memory>

namespace exchange {

template<typename T>
class MessageHelper : public IMessage {
public:
  using Ptr = std::shared_ptr<T>;

  MessageHelper(const MessageHelper &) = delete;

  MessageHelper(MessageHelper &&) = delete;

  MessageHelper &operator=(const MessageHelper &) = delete;

  MessageHelper &operator=(MessageHelper &&) = delete;

  template<typename... Args>
  static Ptr Create(Args... t) {
    return std::make_shared<T>(t...);
  }

protected:
  MessageHelper() = default;

};

}// namespace exchange

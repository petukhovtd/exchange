#pragma once

#include <exchange/iactor.h>
#include <memory>

namespace exchange {

template<typename T>
class ActorHelper : public std::enable_shared_from_this<T>, public IActor {
public:
  using Ptr = std::shared_ptr<T>;
  using Weak = std::weak_ptr<T>;

  ActorHelper(const ActorHelper &) = delete;

  ActorHelper(ActorHelper &&) = delete;

  ActorHelper &operator=(const ActorHelper &) = delete;

  ActorHelper &operator=(ActorHelper &&) = delete;

  template<typename... Args>
  static Ptr Create(Args &&...args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
  }

  Weak GetWeak() {
    return std::enable_shared_from_this<T>::weak_from_this();
  }

protected:
  ActorHelper() = default;
};

}// namespace exchange

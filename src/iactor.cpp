#include <exchange/iactor.h>

namespace exchange {

ActorIdOpt IActor::GetId() const {
  return id_;
}

}// namespace exchange

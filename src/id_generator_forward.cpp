#include <exchange/id_generator_forward.h>

namespace exchange {

ActorId IdGeneratorForward::Next() {
  return ++id_;
}
void IdGeneratorForward::Unused(ActorId) {
}

}// namespace exchange

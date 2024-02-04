#include <exchange/id_generator_v.h>

namespace exchange {

IdGeneratorV::IdGeneratorV(size_t preSize) : IdGeneratorV() {
  unused_.reserve(preSize);
}

ActorId IdGeneratorV::Next() {
  if (!unused_.empty()) {
    const auto id = unused_.back();
    unused_.pop_back();
    return id;
  }
  return ++id_;
}

void IdGeneratorV::Unused(ActorId id) {
  unused_.push_back(id);
}

}// namespace exchange

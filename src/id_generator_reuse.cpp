#include <exchange/id_generator_reuse.h>

namespace exchange {

IdGeneratorReuse::IdGeneratorReuse(size_t preSize) : IdGeneratorReuse() {
  unused_.reserve(preSize);
}

ActorId IdGeneratorReuse::Next() {
  if (!unused_.empty()) {
    const auto id = unused_.back();
    unused_.pop_back();
    return id;
  }
  return ++id_;
}

void IdGeneratorReuse::Unused(ActorId id) {
  unused_.push_back(id);
}

}// namespace exchange

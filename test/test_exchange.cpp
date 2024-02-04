#include <gtest/gtest.h>

#include "common/test_actor.h"
#include "common/test_message.h"

#include <exchange/actor_storage_a.h>
#include <exchange/actor_storage_ht.h>
#include <exchange/actor_storage_v.h>
#include <exchange/id_generator_forward.h>
#include <exchange/exchange.h>
#include <random>

using DataType = int;

template<typename T>
struct ExchangeTest : public testing::Test {
protected:
  void SetUp() override {
    storage = std::make_unique<T>();
  }
  void TearDown() override {
    storage.reset();
  }

public:
  exchange::ActorStoragePtr storage = nullptr;
};

using ActorStorageTypes = ::testing::Types<exchange::ActorStorageA, exchange::ActorStorageV, exchange::ActorStorageHT>;
TYPED_TEST_SUITE(ExchangeTest, ActorStorageTypes);

TYPED_TEST(ExchangeTest, AddDelete) {
  auto generator = std::make_shared<exchange::IdGeneratorForward>();
  auto exchange = std::make_shared<exchange::Exchange>(std::move(this->storage), generator);

  auto actor = test::TestActor<DataType>::Create(exchange);
  EXPECT_EQ(actor->GetId(), exchange::defaultId);

  const auto id = exchange->Add(actor);
  EXPECT_NE(id, exchange::defaultId);

  EXPECT_EQ(actor->GetId(), id);

  const auto deletedActor = exchange->Delete(id);
  EXPECT_EQ(&*actor, &*deletedActor);
  EXPECT_NE(actor->GetId(), id);
  EXPECT_EQ(actor->GetId(), exchange::defaultId);
}

TYPED_TEST(ExchangeTest, Send) {
  auto generator = std::make_shared<exchange::IdGeneratorForward>();
  auto exchange = std::make_shared<exchange::Exchange>(std::move(this->storage), generator);

  auto actor = test::TestActor<DataType>::Create(exchange);
  const auto actorId = exchange->Add(actor);

  DataType data = 123;
  const auto msg = test::TestMessage<DataType>::Create(data);
  EXPECT_TRUE(exchange->Send(actorId, msg));
  EXPECT_EQ(actor->data, data);
}

TYPED_TEST(ExchangeTest, SendMany) {
  auto generator = std::make_shared<exchange::IdGeneratorForward>();
  auto exchange = std::make_shared<exchange::Exchange>(std::move(this->storage), generator);

  const size_t size = 100;
  const size_t minActors = 100;
  const size_t maxActors = minActors + size;
  const size_t minRemove = minActors / 2;
  const size_t maxRemove = minRemove + size;
  std::map<exchange::ActorId, test::TestActor<DataType>::Ptr> actors;

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<size_t> createDistr(minActors, maxActors);
  std::uniform_int_distribution<size_t> removeDistr(minRemove, maxRemove);
  const auto createActors = createDistr(gen);
  const auto removeActors = removeDistr(gen);
  for (size_t i = 0; i < createActors; ++i) {
    auto actor = test::TestActor<DataType>::Create(exchange);
    const auto actorId = exchange->Add(actor);
    EXPECT_NE(exchange::defaultId, actorId);
    actors[actorId] = actor;
  }

  std::uniform_int_distribution<size_t> deleteIdDistr(actors.begin()->first, std::prev(actors.end())->first);
  for (size_t i = 0; i < removeActors; ++i) {
    const auto removeId = deleteIdDistr(gen);
    if (actors.count(removeId)) {
      EXPECT_NE(exchange->Delete(removeId),nullptr) << removeId;
      actors.erase(removeId);
    }
  }

  DataType data = 0;
  for (const auto &pair : actors) {
    const auto& id = pair.first;
    const auto& actor = pair.second;
    ++data;
    const auto msg = test::TestMessage<DataType>::Create(data);
    EXPECT_TRUE(exchange->Send(id, msg));
    EXPECT_EQ(actor->data, data);
  }
}

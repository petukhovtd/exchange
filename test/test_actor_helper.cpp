#include <gtest/gtest.h>

#include <exchange/actor_helper.h>
#include <exchange/message_helper.h>

class TestActor : public exchange::ActorHelper<TestActor> {
public:
  using Handler = std::function<void(void)>;

  TestActor(const std::shared_ptr<int> &sharedPtr, std::unique_ptr<int> uniquePtr, int value)
      : sharedPtr_(sharedPtr), uniquePtr_(std::move(uniquePtr)), value_(value) {}

  TestActor(std::unique_ptr<int> uniquePtr, int value, const std::shared_ptr<int> &sharedPtr)
      : TestActor(sharedPtr, std::move(uniquePtr), value) {}

  TestActor(int value, const std::shared_ptr<int> &sharedPtr, std::unique_ptr<int> uniquePtr)
      : TestActor(sharedPtr, std::move(uniquePtr), value) {}

  TestActor(Handler &&handler, std::unique_ptr<int> uniquePtr)
      : uniquePtr_(std::move(uniquePtr)), handler_(handler) {}

  ~TestActor() override = default;

  void Receive(const exchange::MessagePtr &) override {
  }

  void SetId(exchange::ActorId id) override {
  }

  void ResetId() override {
  }

  exchange::ActorId GetId() override {
    return 0;
  }

private:
  std::shared_ptr<int> sharedPtr_ = nullptr;
  std::unique_ptr<int> uniquePtr_ = nullptr;
  int value_ = 0;
  Handler handler_ = [] {};
};

TEST(ActorHelperTest, CtorArgs) {
  auto sharedPtr = std::make_shared<int>(1);
  auto uniquePtr = std::make_unique<int>(2);
  int value = 3;
  {
    auto actor = TestActor::Create(sharedPtr, std::move(uniquePtr), value);
  }
  {
    auto actor = TestActor::Create(std::move(uniquePtr), value, sharedPtr);
  }
  {
    auto actor = TestActor::Create(value, sharedPtr, std::move(uniquePtr));
  }
  {
    auto actor = TestActor::Create([]{},std::move(uniquePtr));
  }
}

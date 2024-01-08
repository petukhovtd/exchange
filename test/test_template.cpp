#include <exchange/actor_helper.h>
#include <exchange/message_helper.h>

class TestActor : public exchange::ActorHelper<TestActor> {
public:
  TestActor(const std::shared_ptr<int> &sharedPtr, std::unique_ptr<int> uniquePtr, int value)
      : sharedPtr_(sharedPtr), uniquePtr_(std::move(uniquePtr)), value_(value) {}

  TestActor(std::unique_ptr<int> uniquePtr, int value, const std::shared_ptr<int> &sharedPtr)
      : TestActor(sharedPtr, std::move(uniquePtr), value) {}

  TestActor(int value, const std::shared_ptr<int> &sharedPtr, std::unique_ptr<int> uniquePtr)
      : TestActor(sharedPtr, std::move(uniquePtr), value) {}

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
  std::shared_ptr<int> sharedPtr_;
  std::unique_ptr<int> uniquePtr_;
  int value_;
};

class TestMessage : public exchange::MessageHelper<TestMessage> {
public:
  TestMessage(const std::shared_ptr<int> &sharedPtr, std::unique_ptr<int> uniquePtr, int value)
      : sharedPtr_(sharedPtr), uniquePtr_(std::move(uniquePtr)), value_(value) {}

  TestMessage(std::unique_ptr<int> uniquePtr, int value, const std::shared_ptr<int> &sharedPtr)
      : TestMessage(sharedPtr, std::move(uniquePtr), value) {}

  TestMessage(int value, const std::shared_ptr<int> &sharedPtr, std::unique_ptr<int> uniquePtr)
      : TestMessage(sharedPtr, std::move(uniquePtr), value) {}

  ~TestMessage() override = default;

private:
  std::shared_ptr<int> sharedPtr_;
  std::unique_ptr<int> uniquePtr_;
  int value_;
};

int main() {
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
    auto actor = TestMessage::Create(sharedPtr, std::move(uniquePtr), value);
  }
  {
    auto actor = TestMessage::Create(std::move(uniquePtr), value, sharedPtr);
  }
  {
    auto actor = TestMessage::Create(value, sharedPtr, std::move(uniquePtr));
  }
  return 0;
}

# exchange
Exchange is an open source implementation of the simple actor model. 
It isn't thread safe. You have to use external tools for thread safe and thread management
## Get and build
```sh
git clone https://github.com/petukhovtd/exchange.git
cd exchange
mkdir build
cd build 
cmake ..
```
## Example
Create message
```c++
struct Message : exchange::MessageHelper<Message> {
    ~Message() override = default;
    std::string data{};
};
```

Create actor
```c++
struct Actor : exchange::ActorHelper<Actor> {
  explicit Actor(const exchange::ExchangePtr &_exchange)
      : exchange(_exchange) {}

  ~Actor() override = default;

  void Receive(const exchange::MessagePtr &message) override {
    const auto m = std::dynamic_pointer_cast<Message>(message);
    if (m) {
      std::cout << "Actor with id: " << id << ", receive: " << m->data << std::endl;
    }
  }
  // SetId call in Exchange::Add
  void SetId(exchange::ActorId _id) override {
    id = _id;
  }
  // SetId call in Exchange::Delete
  void ResetId() override {
    id = exchange::defaultId;
  }

  exchange::ActorId GetId() override {
    return id;
  }

  void Send(exchange::ActorId _id, const std::string& data) const {
    auto ex = exchange.lock();
    if (ex) {
      auto message = Message::Create();
      message->data = data;
      std::cout << "Actor with id: " << id << ", send: " << data<< std::endl;
      ex->Send(_id, message);
    }
  }

  exchange::ActorId id = exchange::defaultId;
  // Use weak ptr, because exchange store shared_ptr<Actor>
  exchange::ExchangeWeak exchange;
};
```
Create exchange
```c++
auto idGenerator = std::make_shared<exchange::IdGeneratorForward>();
auto storage = std::make_unique<exchange::ActorStorageLine>();
auto exchange = std::make_shared<exchange::Exchange>(std::move(storage), idGenerator);
```
Create and register actors
```c++
auto sender = Actor::Create(exchange);
auto receiver = Actor::Create(exchange);

const auto senderId = exchange->Add(sender);
const auto receiverId = exchange->Add(receiver);
```
Send message
```c++
sender->Send( receiverId, "Hello World!" );
```

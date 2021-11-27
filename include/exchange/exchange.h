#ifndef EXCHANGE_EXCHANGE_H
#define EXCHANGE_EXCHANGE_H

#include <exchange/id.h>
#include <exchange/i_actor.h>
#include <exchange/i_message.h>

#include <unordered_map>
#include <mutex>

namespace exchange
{

class Exchange
{
public:
     /// @brief Добавить актора для обмена
     /// @param actor
     /// @return id актора
     static ActorId Insert( const ActorPtr& actor );

     /// @brief Отправить сообщение актору
     /// @param id актора
     /// @param message сообщение
     /// @return true сообщение отправлено актору
     /// @return false актор с таким id не найден, ссылка на актор невалидна
     static bool Send( ActorId id, const MessagePtr& message );

     /// @brief Удалить атора из обмена
     /// @param id актора
     static void Remove( ActorId id );

private:
     Exchange();

     static Exchange& GetInstance();

     static ActorId GetNextId();

     ActorId InsertImpl( const ActorPtr & actor );

     bool SendImpl( ActorId id, const MessagePtr& message );

     void RemoveImpl( ActorId id );

private:
     std::mutex mutex_;
     std::unordered_map< ActorId, std::weak_ptr< IActor > > actors_;
};

}

#endif

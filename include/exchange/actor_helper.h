#ifndef EXCHANGE_ACTOR_HELPER_H
#define EXCHANGE_ACTOR_HELPER_H

#include <exchange/i_actor.h>
#include <memory>

namespace exchange
{

template< typename T >
class ActorHelper: public std::enable_shared_from_this< T >, public IActor
{
public:
     using Ptr = std::shared_ptr< T >;
     using Weak = std::weak_ptr< T >;

     ActorHelper() = default;

     ActorHelper( const ActorHelper& ) = delete;

     ActorHelper( ActorHelper&& ) = delete;

     ActorHelper& operator=( const ActorHelper& ) = delete;

     ActorHelper& operator=( ActorHelper&& ) = delete;

     /// @brief Создание экземпляра класса
     /// @param t параметры конструктора
     /// @return экземпляр класса
     template< typename... Args >
     static Ptr Create( Args... t )
     {
          return std::make_shared< T >( t... );
     }

     /// @brief Получение слабой ссылки на экземпляр класса
     /// @return слабая ссылка на экземпляр класса
     Weak GetWeak()
     {
          return std::enable_shared_from_this< T >::weak_from_this();
     }

};

}

#endif

#ifndef EXCHANGE_MESSAGE_HELPER_H
#define EXCHANGE_MESSAGE_HELPER_H

#include <exchange/i_message.h>
#include <memory>

namespace exchange
{

template< typename T >
class MessageHelper: public IMessage
{
public:
     using Ptr = std::shared_ptr< T >;

     MessageHelper() = default;

     MessageHelper( const MessageHelper& ) = delete;

     MessageHelper( MessageHelper&& ) = delete;

     MessageHelper& operator=( const MessageHelper& ) = delete;

     MessageHelper& operator=( MessageHelper&& ) = delete;

     /// @brief Создание экземпляра класса
     /// @param t параметры конструктора
     /// @return экземпляр класса
     template< typename... Args >
     static Ptr Create( Args... t )
     {
          return std::make_shared< T >( t... );
     }
};

}

#endif

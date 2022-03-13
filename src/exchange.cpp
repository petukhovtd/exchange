#include <exchange/exchange.h>

namespace exchange
{

Exchange::Exchange()
: mutex_()
, actors_()
{}

ActorId Exchange::Insert( const ActorPtr& actor )
{
     return GetInstance().InsertImpl( actor );
}

bool Exchange::Send( ActorId id, const MessagePtr& message )
{
     return GetInstance().SendImpl( id, message );
}

void Exchange::Remove( ActorId id )
{
     return GetInstance().RemoveImpl( id );
}

ActorId Exchange::GetNextId()
{
     static ActorId id = startId;
     return ++id;
}

Exchange& Exchange::GetInstance()
{
     static Exchange instance;
     return instance;
}

ActorId Exchange::InsertImpl( const ActorPtr& actor )
{
     std::lock_guard< std::mutex > local( mutex_ );
     const ActorId id = GetNextId();
     actor->id_ = id;
     actors_[ id ] = actor;
     return id;
}

bool Exchange::SendImpl( ActorId id, const MessagePtr& message )
{
     ActorPtr actor = nullptr;
     {
          std::lock_guard< std::mutex > lock( mutex_ );
          const auto it = actors_.find( id );
          if( it == actors_.end() )
          {
               return false;
          }
          actor = it->second.lock();
     }

     if( !actor )
     {
          return false;
     }
     actor->Receive( message );
     return true;
}

void Exchange::RemoveImpl( ActorId id )
{
     std::lock_guard< std::mutex > lock( mutex_ );
     const auto it = actors_.find( id );
     if( it == actors_.end() )
     {
          return;
     }
     ActorPtr actor = it->second.lock();
     if( actor )
     {
          actor->id_ = std::nullopt;
     }
     actors_.erase( it );
}

}
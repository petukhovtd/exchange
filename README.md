# exchange


Реализация обмена сообщениями между акторами  
Для создания актора, наледуйте класс IActor или ActorHelper

        class MyActorSimple: public IActor
        {
        ...
        
        std::shared_ptr< MyActorSimple > actor = std::make_shared< MyActorSimple >;
        
        или
        
        class MyActorThreads: public ActorHelper< MyActor >
        {
        ...
        
        MyActorSimple::Ptr actor = MyActorSimple::Create();  
        
И реализуйте метод приема сообщений.  
Все классы сообщений наследуйте соответственно от IMessage или MessageHelper  
  
Регистрируйте актора в обменнике, получая его уникальный id  

        ActorId id = Exchange::Insert( actor );
        
Отправляйте сообщение актору

        Exchange::Send( id, MyMessage::Create() );


#include <iostream>
#include <string>
#include <zmq.hpp>
#include <QStringList>
#include <Cstring>


using namespace std;

int main()
{
    zmq::context_t context(1);

    //Outgoing message go out through here
    zmq::socket_t Pusher( context, ZMQ_PUSH ); /*Pusher.connect( "tcp://192.168.1.8:24041" ); Pusher.connect( "tcp://localhost:24041" ); enkel voor vorige versie's*/
    Pusher.connect( "tcp://benternet.pxl-ea-ict.be:24041" );

    //Incomming messages go here
    zmq::socket_t subscriber( context, ZMQ_SUB );
    subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
    subscriber.setsockopt( ZMQ_SUBSCRIBE, "TaMa1", 5);// subscriber.setsockopt( ZMQ_SUBSCRIBE, "naam vd subsciber", strln);

    //Message
    zmq::message_t * msg_IN = new zmq::message_t();
    zmq::message_t * msg_Out = new zmq::message_t();




    while( Pusher.connected() ||  subscriber.connected())
        {

            subscriber.recv( msg_IN);
            msg_Out->str() = "!" + msg_IN->str();


            Pusher.send(msg_Out,msg_Out->size());
             cout << "pushed"<< endl ;


        }


    return 0;
}

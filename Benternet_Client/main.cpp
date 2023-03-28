#include <iostream>
#include <string>
#include <zmq.hpp>
#include <QStringList>
#include <Cstring>


using namespace std;

int main()
{


    string sub = "!";


    zmq::context_t context(1);

    //Outgoing message go out through here
    zmq::socket_t Pusher( context, ZMQ_PUSH ); /*Pusher.connect( "tcp://192.168.1.8:24041" ); Pusher.connect( "tcp://localhost:24041" ); enkel voor vorige versie's*/
    Pusher.connect( "tcp://benternet.pxl-ea-ict.be:24041" );

    //Incomming messages go here
    zmq::socket_t subscriber( context, ZMQ_SUB );
    subscriber.connect( "tcp://benternet.pxl-ea-ict.be:24042" );
    subscriber.setsockopt( ZMQ_SUBSCRIBE, sub.c_str() ,sub.length());// subscriber.setsockopt( ZMQ_SUBSCRIBE, "naam vd subsciber", strln);



    while( Pusher.connected() ||  subscriber.connected())
        {

        _sleep(1000);

        string input;
            std::cin >> input;
            zmq::message_t msg_Out( "TaMa1" + input );
            Pusher.send(msg_Out);



        string output;
            zmq::message_t msg_In;
            subscriber.recv(msg_In);
            cout << msg_In.str() << std::endl;



    return 0;
}
}


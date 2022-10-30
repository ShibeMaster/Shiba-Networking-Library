# Shiba's Networking Library
This is a pretty small networking library that I've made to make to basic networking with normal C++ a lot easier.
I'll go into a bit of detail of how to effectively use this library, by making use of the network channel and network message systems that I've put in place.

### Introductions
The idea of this library is to use "Channels" and "Messages" to communicate between the host and client, instead of sending an char* array when using normal winsocks.
Unfortunately, the host will still need to port forward to allow clients to join.
To initialize the network capabilities of this library, you'll need to call ```ShibaNetLib::NetworkManager::Initialize()```.

### Network Connections
A network connection is how you'll be able to send messages through the network, you'll never need to manually create one of these yourself rather you'll normally be access it through being derived from a ```NetworkBehaviour``` or accessing the main connection through ```ShibaNetLib::Network::conn```. The network connection contains the socket that is being used to connect to the server, the network id of your client, a boolean of whether the connection is the server, the buffer of all the incoming information (you'll never need to access it this way though) and finally a boolean of whether to display debug information such as the size of the incoming packets. Just gonna put out there that most of the network things are handled on a seperate thread just incase it affects someone. To send a message you need to call ```Send(NetworkMessage* message, int size)``` with a point of the network message you want to send and the size of that same network message.

### Starting Connections
You either need to call ```ShibaNetLib::NetworkManager::StartHost()``` to host or ```ShibaNetLib::NetworkManager::StartClient()``` to connect, this must be done after initializing the network or it'll throw a network exception. 

### Network Channels
A network channel is how the host or client recieves the information, each channel needs to be registered with a channel id. Each network message with this channel id will be sent to the ```Incoming(char* buffer)``` method of the channel for you to do whatever you please with the data. If the message is considered a "reply", then it'll be sent to the ```IncomingReply(char* buffer)``` method instead. Currently, channel id 1 is reserved to the library itself for some connection things. To create your own network channel, you need to override the network channel class and add your own definition for the incoming methods. An example of creating a channel: 
```
class TestChannel : public ShibaNetLib::NetworkChannel {
public:
    using NetworkChannel::NetworkChannel;
    void Incoming(char* buffer) {
        TestMessage* message = (TestMessage*)buffer;
        // do whatever you need with the sent message here
        std::cout << message.text << std::endl;
    }
}
```
An exmaple of registering a channel:
```
TestChannel channel = TestChannel(2);
ShibaNetLib::NetworkChannelManager::AddNetworkChannel(&channel);
```

### Network Messages
Each network message contains a "Channel ID", a "Sender ID" and a boolean of whether it is a reply to a previously sent message. Just like the network channel, to create your own network message you need to override the base ```NetworkMessage``` struct and add the information you want to send. The channel id of the message is the registered id of the channel that will be responsible for handling this message. An example of creating a message:
```
struct TestMessage : ShibaNetLib::NetworkMessage {
    int number;
    std::string text;
    // generally whatever information you need to send
}
```
An example of sending a message:
```
TestMessage message;
message.channelid = 2;
message.senderid = ShibaNetLib::Network::conn.netId;
message.response = false;
message.text = "Hello Server!"
message.number = 2;

ShibaNetLib::Network::conn.Send(&message, sizeof(TestMessage));
```


### Network Events
I've made an event system for this library which is a bit more annoying to do compared to C# delegate events, the network events that currently exist are ```void OnClientStart(int id)```, ```void OnServerStart(int id)```, ```void OnClientJoin(int id)``` and ```void OnConnectionEnded(int id)```. To add a *static* method with the same parameters and return type that will be called on this event, you need to call something like ```ShibaNetLib::NetworkEvents::OnServerStart += TestServerStart```. ```OnClientStart(int id)``` is called on the client side when they join the server, ```OnServerStart(int id)``` is called when the server is started, ```OnClientJoin(int id)``` is called on the server side when a new client joins the server and finally ```OnConnectionEnded(int id)``` is called on both the server and client when the connection is ended. 


### Conclusion
This is a pretty basic but generally useful networking library that I've made, it's mostly just for use in my own personal projects so I use something other than the normal winsocks, but feel free to use it if you want to. Thanks for reading this! - Shiba

#ifndef CONFIG_H
#define CONFIG_H

// Change ADDRESS, USER, PSW to your mqtt broker

#define ADDRESS "localhost:1883" //default is 1883
#define USER    "User"
#define PSW     "Password"
#define TOPIC 	"drone"

#define CLIENTID    "ExampleClientPub"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

#endif// CONFIG_H

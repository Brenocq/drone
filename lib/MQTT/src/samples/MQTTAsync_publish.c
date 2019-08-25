/*******************************************************************************
 * Copyright (c) 2012, 2018 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution. 
 *
 * The Eclipse Public License is available at 
 *   http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at 
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Ian Craggs - initial contribution
 *******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MQTTAsync.h"

#if !defined(WIN32)
#include <unistd.h>
#else
#include <windows.h>
#endif

#if defined(_WRS_KERNEL)
#include <OsWrapper.h>
#endif

//#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
//#include <unistd.h>
#include <fcntl.h>
//#include <string.h>

#define ADDRESS     "localhost:1883"
#define CLIENTID    "ExampleClientPub"
#define TOPIC       "drone"
//#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

#define IN_FIFO "/tmp/drone_pub_fifo"

volatile MQTTAsync_token deliveredtoken;

int finished = 0;

char buf1 [512], buf2 [1024];

void connlost(void *context, char *cause)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	printf("\nConnection lost\n");
	printf("     cause: %s\n", cause);

	printf("Reconnecting\n");
	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
 		finished = 1;
	}
}


void onDisconnect(void* context, MQTTAsync_successData* response)
{
	printf("Successful disconnection\n");
	finished = 1;
}


void onSend(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_disconnectOptions opts = MQTTAsync_disconnectOptions_initializer;
	int rc;

	printf("Message with token value %d delivery confirmed\n", response->token);

	opts.onSuccess = onDisconnect;
	opts.context = client;

	if ((rc = MQTTAsync_disconnect(client, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start sendMessage, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
}


void onConnectFailure(void* context, MQTTAsync_failureData* response)
{
	printf("Connect failed, rc %d\n", response ? response->code : 0);
	finished = 1;
}


void onConnect(void* context, MQTTAsync_successData* response)
{
	MQTTAsync client = (MQTTAsync)context;
	MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;
	MQTTAsync_message pubmsg = MQTTAsync_message_initializer;
	int rc;

	printf("Successful connection\n");
	
	opts.onSuccess = onSend;
	opts.context = client;

	pubmsg.payload = buf2;
	pubmsg.payloadlen = (int)strlen(buf2);
	pubmsg.qos = QOS;
	pubmsg.retained = 0;
	deliveredtoken = 0;

	if ((rc = MQTTAsync_sendMessage(client, TOPIC, &pubmsg, &opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start sendMessage, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}
}

int MQ()
{
	finished = 0; //essa desgraça aqui falava que ja tinha feito uma vez, agora o mqtt deve estar pronto kct
	MQTTAsync client;
	MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;
	int rc;

	MQTTAsync_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);

	MQTTAsync_setCallbacks(client, NULL, connlost, NULL, NULL);

	conn_opts.keepAliveInterval = 20;
	conn_opts.cleansession = 1;
	conn_opts.onSuccess = onConnect;
	conn_opts.onFailure = onConnectFailure;
	conn_opts.context = client;

	if ((rc = MQTTAsync_connect(client, &conn_opts)) != MQTTASYNC_SUCCESS)
	{
		printf("Failed to start connect, return code %d\n", rc);
		exit(EXIT_FAILURE);
	}else{
		printf("delbem\n");	
	}

	printf("Waiting for publication of %s\n"
         "on topic %s for client with ClientID: %s\n",
         buf2, TOPIC, CLIENTID);
	
	while (!finished)
	{
		//printf("ta vendo \n");
		#if defined(WIN32)
			Sleep(100);
		#else
			usleep(10000L);
		#endif
	}

	MQTTAsync_destroy(&client);
 	return rc;
}

int main(int argc, char* argv[])
{

	int fd, fd_server, bytes_read;

	if ((fd = open (IN_FIFO, O_RDONLY)) == -1)
	   perror ("open");

	while(1){
		
		memset (buf2, '\0', sizeof (buf2));

		if ((bytes_read = read (fd, buf2, sizeof(buf2))) == -1)
			perror ("read");
		
		if (bytes_read == 0)
			continue;


		if (bytes_read > 0) {
			printf ("Message FIFO: %s\n", buf2);	
			MQ();		
		}
	
	}
	
	if (close (fd) == -1) {
	    perror ("close");
	}

 	return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <memory.h>

#define SERVER_FIFO "/tmp/addition_fifo_server"

char my_fifo_name [128];
char buf1 [512], buf2 [1024];

int main (int argc, char **argv)
{
    int fd, fd_server, bytes_read;

    // make client fifo
    sprintf (my_fifo_name, "/tmp/add_client_fifo%ld", (long) getpid ());

    if (mkfifo (my_fifo_name, 0664) == -1)
        perror ("mkfifo");

    while (1) {
        // get user input
        printf ("Type numbers to be added: ");
        if (fgets(buf1, sizeof (buf1), stdin) == NULL)
            break;

        strcpy (buf2, my_fifo_name);
        strcat (buf2, " ");
        strcat (buf2, buf1);

        // send message to server

        if ((fd_server = open (SERVER_FIFO, O_WRONLY)) == -1) {
            perror ("open: server fifo");
            break;
        }

        if (write (fd_server, buf2, strlen (buf2)) != strlen (buf2)) {
            perror ("write");
             break;
        }

        if (close (fd_server) == -1) {
            perror ("close");
            break;
        }

        // read the answer
        if ((fd = open (my_fifo_name, O_RDONLY)) == -1)
           perror ("open");
        memset (buf2, '\0', sizeof (buf2));
        if ((bytes_read = read (fd, buf2, sizeof (buf2))) == -1)
            perror ("read");

        if (bytes_read > 0) {
            printf ("Answer: %s\n", buf2);
        }

        if (close (fd) == -1) {
            perror ("close");
            break;
        }
    }
}
*/

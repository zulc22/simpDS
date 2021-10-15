#include <nds.h>
#include <dswifi9.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdio.h>
#include <string.h>
	
#include "http.h"

#ifndef VERSION
    #define VERSION "[v undef]"
#endif

const char* USER_AGENT = "SimpTube DS v" VERSION;
int retries = 0;
bool cdInited = false;

int main(void) {

    while (true) {

        if (!cdInited) {
            consoleDemoInit();  //setup the sub screen for printing
            cdInited = true;
        }

        iprintf("\n\nTry#%i\n", ++retries);

        iprintf("Init\n");
        if (!Wifi_CheckInit()) Wifi_InitDefault(true);

        int chinit=0;
        while (!chinit) {
            chinit=Wifi_CheckInit();
            iprintf("%i\r",chinit);
        }

        iprintf("\n");
        Wifi_AutoConnect();

        int assocStatus;
        bool connected=false;
        while (true) { // not an infinite loop -- while ("trying to connect")
            assocStatus = Wifi_AssocStatus();
            switch (assocStatus) {
                case ASSOCSTATUS_SEARCHING:
                    iprintf("Searching for hotspot...       \r");
                    break;
                case ASSOCSTATUS_AUTHENTICATING:
                    iprintf("Authenticating...              \r");
                    break;
                case ASSOCSTATUS_ASSOCIATING:
                    iprintf("Associating...                 \r");
                    break;
                case ASSOCSTATUS_ACQUIRINGDHCP:
                    iprintf("Obtaining IP address...        \r");
                    break;
                case ASSOCSTATUS_ASSOCIATED:
                    iprintf("Connected!                     \r");
                    connected=true;
                    break;
                case ASSOCSTATUS_CANNOTCONNECT:
                    iprintf("Could not connect...           \r");
                    break;
                case ASSOCSTATUS_DISCONNECTED:
                    iprintf("... not trying to connect ...  \r");
                    break;
            }
            if (assocStatus == ASSOCSTATUS_ASSOCIATED ||
                assocStatus == ASSOCSTATUS_CANNOTCONNECT) {
                    // These conditions mean we're "done" trying to connect and we can continue
                    break;
            }
        }
        iprintf("\n");

        if (!connected) {
            iprintf("Failed to connect. Retry\n");
            Wifi_DisableWifi();
        } else break;
    }

    iprintf("Connected\n\n");

    struct hostent* mahHost = gethostbyname("zulc22.com");
    getHttp(mahHost, "/");
    
    timeout(480);

	return 0;
}

void timeout(int frames) {
    iprintf("\n");
    for (int f=frames; f>=0; f--) {
        swiWaitForVBlank();
        iprintf("Timeout %i \r", f);
    }
    iprintf("\n");
}

void sendstr(int socket, char* data) {
    iprintf(data);
    send(socket, data, strlen(data), 0);
}

void getHttp(struct hostent* host, char* url) {
    // Let's send a simple HTTP request to a server and print the results!

    // Find the IP address of the server, with gethostbyname
    // struct hostent * host = gethostbyname( url );
    iprintf("Found IP Address!\n");
 
    // Create a TCP socket
    int my_socket;
    my_socket = socket( AF_INET, SOCK_STREAM, 0 );
    iprintf("Created Socket!\n");

    // Tell the socket to connect to the IP address we found, on port 80 (HTTP)
    struct sockaddr_in sain;
    sain.sin_family = AF_INET;
    sain.sin_port = htons(80);
    sain.sin_addr.s_addr= *( (unsigned long *)(host->h_addr_list[0]) );
    connect( my_socket,(struct sockaddr *)&sain, sizeof(sain) );
    iprintf("Connected to server!\n");

    // send our request
    sendstr(my_socket, "GET ");
    sendstr(my_socket, url);
    sendstr(my_socket, "HTTP/1.1\r\nHost: ");
    sendstr(my_socket, host->h_name);
    sendstr(my_socket, "\r\nUser-Agent: ");
    sendstr(my_socket, USER_AGENT);
    sendstr(my_socket, "\r\n\r\n");

    iprintf("Sent our request!\n");

    // Print incoming data
    iprintf("Printing incoming data:\n");

    int recvd_len;
    char incoming_buffer[256];

    while( ( recvd_len = recv( my_socket, incoming_buffer, 255, 0 ) ) != 0 ) { // if recv returns 0, the socket has been closed.
        if(recvd_len>0) { // data was received!
            incoming_buffer[recvd_len] = 0; // null-terminate
            iprintf(incoming_buffer);
		}
	}

	iprintf("Other side closed connection!");

	shutdown(my_socket,0); // good practice to shutdown the socket.

	closesocket(my_socket); // remove the socket.
}


#include "http.h"

const char* USER_AGENT = "SimpTube DS v" VERSION;

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


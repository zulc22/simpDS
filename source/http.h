#include "glob.h"

#ifndef VERSION
    #define VERSION "[v undef]"
#endif

void sendstr(int socket, char* data);
void getHttp(struct hostent* host, char* url);
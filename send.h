#ifndef send_h
#define send_h 

#include "utilities.h"

int sendPackets
(
    int id, 
    int sequence, 
    const char* 
    ipAddress, 
    int sockfd, 
    int ttl
);

struct sockaddr_in makeRecipientAddress(char* ipAddress);
struct icmphdr makeICMPHeader (int id, int seq);

#endif
#ifndef utilities_h
#define utilities_h

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <string>

#include <time.h>
#include <arpa/inet.h> 
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <cassert>
#include <cstdlib>
#include <unistd.h> 
#include <cerrno>


#include <tuple>
#include <chrono> 

bool isValidIpAddress(char* ipAddress);
void argumentValidation ( int argc, const char* argv[] );
u_int16_t compute_icmp_checksum (const void *buff, int length);


void printIPs(char array[3][20]);
void printOutput(int ttl, char ipAddresses[3][20], int packetsAmount, unsigned int avg_time);


#endif
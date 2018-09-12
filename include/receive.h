#pragma once

#include "utilities.h"

std::pair<int,std::chrono::high_resolution_clock::time_point> receivePackets
(
    int sockfd, 
    int pid, 
    int * ttl, 
    char ipAddresses[3][20]
);

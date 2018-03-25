#include "send.h"

struct icmphdr makeICMPHeader (int id, int seq)  {
  struct icmphdr icmp_header;
  icmp_header.type = ICMP_ECHO;
  icmp_header.code = 0;
  icmp_header.un.echo.id = id;
  icmp_header.un.echo.sequence = seq;
  icmp_header.checksum = 0;
  icmp_header.checksum = compute_icmp_checksum(
      (u_int16_t*)&icmp_header, 
      sizeof(icmp_header));
  return icmp_header;
}

struct sockaddr_in makeRecipientAddress (const char* ipAddress) {
    struct sockaddr_in recipient;
    bzero(&recipient, sizeof(recipient));
    recipient.sin_family = AF_INET;
    inet_pton(AF_INET, ipAddress, &recipient.sin_addr);
    return recipient;
}

int sendPackets(int id, int sequence, const char* ipAddress, int sockfd, int ttl) {

    struct icmphdr      icmp_header = makeICMPHeader(id, sequence);
    struct sockaddr_in  recipient = makeRecipientAddress(ipAddress);
    
    setsockopt(sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(int));

    ssize_t bytes_sent = sendto(
        sockfd,                         
        &icmp_header,                   
        sizeof(icmp_header),            
        0,
        (struct sockaddr*)&recipient,
        sizeof(recipient)                
    );           

    if (bytes_sent < 0){
        fprintf(stderr, "sendto error: %s\n", strerror(errno)); 
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
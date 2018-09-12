#include "receive.h"

std::pair<int, std::chrono::high_resolution_clock::time_point> receivePackets(
	int sockfd, int pid, int *ttl, char ipAddresses[3][20])
{

	int index;
	char ip_str[20];
	std::chrono::high_resolution_clock::time_point receiveTime;

	struct sockaddr_in sender;
	socklen_t sender_len = sizeof(sender);
	u_int8_t buffer[IP_MAXPACKET];
	u_int8_t *offset = buffer;

	ssize_t packet_len = recvfrom(
		sockfd,
		buffer,
		IP_MAXPACKET,
		MSG_DONTWAIT,
		(struct sockaddr *)&sender,
		&sender_len);

	if (packet_len < 0)
		fprintf(stderr, "recvfrom error: %s\n", strerror(errno));

	inet_ntop(AF_INET, &(sender.sin_addr), ip_str, sizeof(ip_str));

	struct iphdr *ip_header = (struct iphdr *)buffer;
	u_int8_t *icmp_packet = buffer + 4 * ip_header->ihl;
	struct icmphdr *icmp_header = (struct icmphdr *)icmp_packet;

	if (icmp_header->type == ICMP_ECHOREPLY)
	{
		if (icmp_header->un.echo.id == pid && (icmp_header->un.echo.sequence) / 3 == *ttl)
		{
			index = (icmp_header->un.echo.sequence) % 3;
			receiveTime = std::chrono::high_resolution_clock::now();
			strcpy(ipAddresses[index], ip_str);
			return std::make_pair(0, receiveTime);
		}
	}

	if (icmp_header->type == ICMP_TIME_EXCEEDED)
	{

		offset += 4 * ip_header->ihl + 8;
		struct iphdr *receivedIpHeader = (struct iphdr *)offset;
		offset += (receivedIpHeader->ihl * 4);
		struct icmphdr *receivedICMP = (struct icmphdr *)offset;

		if (receivedICMP->un.echo.id == pid && (receivedICMP->un.echo.sequence) / 3 == *ttl)
		{
			index = (receivedICMP->un.echo.sequence) % 3;
			receiveTime = std::chrono::high_resolution_clock::now();
			strcpy(ipAddresses[index], ip_str);
			return std::make_pair(1, receiveTime);
		}
	}

	return std::make_pair(-1, receiveTime);
}
#include "utilities.h"

// standardowy sposób sprawdzania czy dana funkcja jest poprawnym adresem IP
bool isValidIpAddress(const char *ipAddress)
{
    struct sockaddr_in sa;
    int result = inet_pton(AF_INET, ipAddress, &(sa.sin_addr));
    return result != 0;
}

void argumentValidation(int argc, const char *argv[])
{
    if (argc != 2)
    {
        throw std::invalid_argument("Wrong amount of arguments [1 argument allowed]\n");
    }

    if (!isValidIpAddress(argv[1]))
    {
        throw std::invalid_argument("Wrong IP address format, try again.\n");
    }
}

// funkcja udostępniona na stronie wykładu
u_int16_t compute_icmp_checksum(const void *buff, int length)
{
    u_int32_t sum;
    const u_int16_t *ptr = (u_int16_t *)buff;
    assert(length % 2 == 0);

    for (sum = 0; length > 0; length -= 2)
        sum += *ptr++;

    sum = (sum >> 16) + (sum & 0xffff);
    return (u_int16_t)(~(sum + (sum >> 16)));
}

void printIPs(char ipAddresses[3][20])
{
    bool inequality;
    if (ipAddresses[0] != 0)
        printf("%s ", ipAddresses[0]);
    for (int i = 1; i < 3; i++)
    {
        for (int j = 0; j < i; j++)
        {
            strcmp(ipAddresses[i], ipAddresses[j]) == 0 ? inequality = false : inequality = true;
        }
        if (inequality)
            printf("%s ", ipAddresses[i]);
    }
}

void printOutput(int ttl, char ipAddresses[3][20], int packetsAmount, unsigned int avg_time)
{
    printf("%i. ", ttl);
    if (packetsAmount == 0)
        printf("*\n");
    else if (packetsAmount == 3)
    {
        printIPs(ipAddresses);
        printf("%ums\n", avg_time);
    }
    else if (packetsAmount < 3)
    {
        printIPs(ipAddresses);
        printf("???\n");
    }
}

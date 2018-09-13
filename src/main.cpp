#include "utilities.h"
#include "send.h"
#include "receive.h"

pid_t pid = getpid();
long answerTime[3];
char ipAddresses[3][20];
bool stop = false;

int main(int argc, const char *argv[])
{
    argumentValidation(argc, argv);

    int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    if (sockfd < 0)
    {
        fprintf(stderr, "socket error: %s\n", strerror(errno));
        return EXIT_FAILURE;
    }

    struct sockaddr_in targetAddress;
    bzero(&targetAddress, sizeof(targetAddress));
    targetAddress.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &(targetAddress.sin_addr));

    for (int ttl = 1; ttl <= 30; ttl++)
    {

        for (int i = 0; i < 3; i++)
        {
            sendPackets(pid, 3 * ttl + i, argv[1], sockfd, ttl);
            memset(ipAddresses[i], 0, sizeof(ipAddresses[i]));
        }

        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

        int packetsAmount = 0;
        unsigned int avg_time = 0;
        std::chrono::high_resolution_clock::time_point recvTime[3];

        struct timeval tv;
        tv.tv_sec = 1;
        tv.tv_usec = 0;

        fd_set descriptors;
        FD_ZERO(&descriptors);
        FD_SET(sockfd, &descriptors);

        while (packetsAmount != 3)
        {

            int ready = select(sockfd + 1, &descriptors, NULL, NULL, &tv);

            if (ready < 0)
            {
                fprintf(stderr, "select error: %s\n", strerror(errno));
                break;
            }
            if (ready == 0)
                break;

            else
            {
                std::pair<int, std::chrono::high_resolution_clock::time_point> recvInfo =
                    receivePackets(sockfd, pid, &ttl, ipAddresses);

                if (recvInfo.first != -1)
                {
                    packetsAmount++;

                    recvTime[packetsAmount] = recvInfo.second;
                    answerTime[packetsAmount] =
                        std::chrono::duration_cast<std::chrono::milliseconds>(recvTime[packetsAmount] - start).count();

                    avg_time +=
                        std::chrono::duration_cast<std::chrono::milliseconds>(recvTime[packetsAmount] - start).count();

                    if (packetsAmount == 3)
                    {
                        avg_time /= 3;
                    }
                    if (recvInfo.first == 0)
                        stop = true;
                }
            }
        }

        printOutput(ttl, ipAddresses, packetsAmount, avg_time);
        if (stop)
            break;
    }
    return 0;
}
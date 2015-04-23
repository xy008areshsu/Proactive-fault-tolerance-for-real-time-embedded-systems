#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include "rtwtypes.h"
#include "send_udp.h"
#include <time.h>

#define CLOCK CLOCK_REALTIME

int32_T sd;
int32_T broadcastEnable = 1;
int32_T sendBufferSize = 321*240;
struct sockaddr_in broadcastAddr;
struct pollfd fds;  							// Array of file descriptors to poll
int32_T pollStatus;                             // Status of poll

struct timespec ts_tic[10];
struct timespec ts_toc[10];
double time_last;

void initUDP(void)
{
	int32_T ret;

	/* Open a socket */
	sd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sd <= 0)
	{
		printf("Error: could not open socket\n");
	}
	/* Set socket options */
	ret = setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &broadcastEnable, sizeof(broadcastEnable));
	if (ret)
	{
		printf("Error: could not set open socket to broadcast mode\n");
	}
    ret = setsockopt(sd, SOL_SOCKET, SO_SNDBUF, &sendBufferSize, sizeof(sendBufferSize));
	if (ret)
	{
		printf("Error: could not set socket buffer size\n");
	}
    /* Configure port and ip */
	memset(&broadcastAddr, 0, sizeof(broadcastAddr));
	broadcastAddr.sin_family = AF_INET;
	/* MW: Mark's laptop for testing (deprecated)*/
    /* OM: Set to final competition address */
	inet_pton(AF_INET, "169.254.230.213", &broadcastAddr.sin_addr);
	broadcastAddr.sin_port = htons(17725);
    
    /* Initialise polling */
    memset(&fds, 0 , sizeof(fds));
    /* Poll UDP for output */
    fds.fd = sd;
    fds.events = (POLLOUT | POLLHUP | POLLNVAL | POLLERR);

	printf("Socket opened for video transmit to host\n");
}

int32_T sendUDP(uint8_T *data, int32_T size)
{
	int32_T ret;

    /* Poll socket to check it is operational before trying a potentially */
    /* blocking call to sendto */
    
    /* Poll descriptors with 10 ms timeout */
    pollStatus = poll(&fds, 1, 10);
    
    if (fds.revents & POLLOUT)
    {
        ret = sendto(sd, data, size, 0, (struct sockaddr*)&broadcastAddr, sizeof broadcastAddr);
        if (ret < 0)
        {
            /* Socket has failed completely, no attempt to recover it */
            printf("Error: UDP video send failed\n");
            close(sd);
            return(-1);
        }
    }
    else
    {
        printf("POLL timeout, skipping transmit this time\n");
    }

}

void tic(int32_T idx)
{
    clock_gettime(CLOCK,&ts_tic[idx]);
}

void toc(double *tv, int32_T idx)
{
    clock_gettime(CLOCK,&ts_toc[idx]);
    *tv = (double)(ts_toc[idx].tv_sec - ts_tic[idx].tv_sec) + 
                    (double)(ts_toc[idx].tv_nsec - ts_tic[idx].tv_nsec)/1000000000.0d;
    
}

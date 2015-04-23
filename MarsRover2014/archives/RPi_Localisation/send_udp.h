#ifndef SEND_UDP
#define SEND_UDP

extern int32_T sendUDP(uint8_T *data, int32_T size);
extern void initUDP(void);
extern void tic(int32_T idx);
extern void toc(double *tv, int32_T idx);

#endif /* SEND_UDP */


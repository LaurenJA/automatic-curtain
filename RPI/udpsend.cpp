
#include<stdio.h>
#include<string>
#include<iostream>
#include <winsock.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
struct test {
    string str;
};
struct UdpHeartPack{
    char UDPData[16] ;
};
int main(int argc, char* argv[])
{
    struct UdpHeartPack udpPack;
    static int UDP_PORT = 7001;
    udpPack.UDPData[0] = 'h';
    udpPack.UDPData[1] = 'e';
    udpPack.UDPData[2] = 'l';
    udpPack.UDPData[3] = 'l';
    udpPack.UDPData[4] = 'o';
    udpPack.UDPData[5] = ' ';
    udpPack.UDPData[6] = 'c';
    udpPack.UDPData[7] = 'u';
    udpPack.UDPData[8] = 's';
    udpPack.UDPData[9] = 't';
    udpPack.UDPData[10] = 'o';
    udpPack.UDPData[11] = 'm';
    udpPack.UDPData[12] = 'e';
    udpPack.UDPData[13] = 'r';
    udpPack.UDPData[14] = '\0';
    char *pPack = (char *) &udpPack;
    WSADATA wsaData;
    SOCKET sockListener;
    SOCKADDR_IN saUdpServe;
    BOOL fBroadcast = TRUE;
    char sendBuff[800];
    int ncount=0;
    if(WSAStartup(MAKEWORD( 1, 1 ), &wsaData )!=0)
    {
        printf("Can't initiates windows socket!Program stop.\n");
        return -1;
    }
    sockListener=socket(PF_INET,SOCK_DGRAM,0);
    setsockopt ( sockListener,SOL_SOCKET,SO_BROADCAST, (CHAR *)&fBroadcast, sizeof (BOOL) );
    saUdpServ.sin_family = AF_INET;
    saUdpServ.sin_addr.s_addr = htonl ( INADDR_BROADCAST );
    saUdpServ.sin_port = htons (UDP_PORT);
    while(1)
    {
        Sleep(999);
        sprintf(sendBuff,"Message %d is: ok",ncount++);
        sendto ( sockListener,/*sendBuff*/pPack, lstrlen (sendBuff)/*sizeof(udpPack)*/, 0, (SOCKADDR *) &saUdpServe, sizeof (SOCKADDR_IN));
        printf("%s\n",sendBuff);
    }
    closesocket(sockListener);
    WSACleanup();
    return 0;
}
const static int    BUFFER_LENGTH = 15;

#include <stdio.h>
#include<winsock.h>
#include <conio.h>
#pragma comment(lib,"ws2_32.lib")
int main(int argc, char* argv[])
{
    WSADATA wsaData;
    SOCKET sockListener;
    SOCKADDR_IN sin,saClient;
    char cRecvBuff[800];
    int nSize,nbSize;
    int iAddrLen=sizeof(saClient);
    if(WSAStartup(MAKEWORD( 1, 1 ), &wsaData )!=0)
    {
        printf("Can't initiates windows socket!Program stop.\n");
        return -1;
    }
    sockListener=socket(AF_INET, SOCK_DGRAM,0);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(7001);
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind( sockListener, (SOCKADDR FAR *)&sin, sizeof(sin))!=0)
    {
        printf("Can't bind socket to local port!Program stop.\n");
        return -1;
    }
    while(1)
    {
        nSize = sizeof ( SOCKADDR_IN );
        if((nbSize=recvfrom (sockListener,cRecvBuff,800,0,
                             (SOCKADDR FAR *) &saClient,&nSize))==SOCKET_ERROR)
        {
            printf("Recive Error");
            break;
        }
        cRecvBuff[nbSize] = '\0';
         printf("%s\n",cRecvBuff);
    }
    return 0;
}
        

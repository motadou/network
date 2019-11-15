#ifndef __TESTNETWORK_DATETIME_H__
#define __TESTNETWORK_DATETIME_H__

#include <string>
#include <iostream>
#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <arpa/inet.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
class Util
{
public:
    static std::string CurrentDateTime(const std::string & sFormat = "%Y-%m-%d %H:%M:%S") { return Timestamp2Str(time(NULL), sFormat); }

    static std::string Timestamp2Str(time_t iTimestamp, const std::string & sFormat = "%Y-%m-%d %H:%M:%S")
	{
		struct tm xTime = {0};
		localtime_r(&iTimestamp, &xTime);

		char sTimeString[255] = "\0";

		strftime(sTimeString, sizeof(sTimeString), sFormat.c_str(), &xTime);

		return std::string(sTimeString);
	}

	static int CreateTcpSocket()
	{
		return ::socket(AF_INET, SOCK_STREAM, 0);
	}

	static int Connect(int iFd, const std::string & sHost, const uint16_t iPort)
	{
		struct sockaddr xPeer;
		memset(&xPeer, 0, sizeof(struct sockaddr));

		struct sockaddr_in * xAddr = (struct sockaddr_in *)&xPeer;
		xAddr->sin_family = AF_INET;
		xAddr->sin_port   = htons(iPort);
		if (::inet_pton(AF_INET, sHost.c_str(), &(xAddr->sin_addr)) != 1)
		{
			return -1;
		}

		return ::connect(iFd, &xPeer, sizeof(xPeer));
	}
		
	static int Bind(int iListenFd, const std::string & sHost, int iPort)
	{
		struct sockaddr xBindAddr;
		memset(&xBindAddr, 0, sizeof(struct sockaddr));

		struct sockaddr_in *pAddr = (struct sockaddr_in *)&xBindAddr;

		pAddr->sin_family = AF_INET;
		pAddr->sin_port   = htons(iPort);

		if (::inet_pton(AF_INET, sHost.c_str(), &(pAddr->sin_addr)) != 1)
		{
			return -1;
		}

		int iReuseAddr = 1;

		::setsockopt(iListenFd, SOL_SOCKET, SO_REUSEADDR, (const void *)&iReuseAddr, sizeof(int));

		return ::bind(iListenFd, &xBindAddr, sizeof(xBindAddr));
	}
	
	static int Listen(int iListenFd, int iConnBackLog)
	{
		if (::listen(iListenFd, iConnBackLog) < 0)
		{
			return -1;
		}

		return 0;
	}

	static int Send(int iFd, const std::string & sBuff)
	{
		return ::send(iFd, sBuff.data(), sBuff.size(), 0);
	}

	static int Accept(int iListenFd)
	{
		struct sockaddr_in xSockAddr;

		socklen_t iSockAddrSize = sizeof(sockaddr_in);

		return ::accept(iListenFd, (struct sockaddr *)&xSockAddr, &iSockAddrSize);
	}

	static int SetBlock(int iFd, bool bBlock)	
	{
		int iFLValue = 0;

		if ((iFLValue = ::fcntl(iFd, F_GETFL, 0)) == -1)
		{
			return -1;
		}

		if (::fcntl(iFd, F_SETFL, (bBlock)?(iFLValue & ~O_NONBLOCK):(iFLValue | O_NONBLOCK)) == -1)
		{
			return -1;
		}

		return 0;
	}
};

#endif

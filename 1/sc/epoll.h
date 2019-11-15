#ifndef __TESTNETWORK_EPOLL_H__
#define __TESTNETWORK_EPOLL_H__

#include <unistd.h>
#include <sys/epoll.h>

class Epoll
{
public:
    enum ENUM_EPOLL_TYPE
    {
        E_EPOLL_LISTEN = 1,    // 监听端口事件
        E_EPOLL_SOCKET = 2,    // 套接口网络事件
        E_EPOLL_HANDLE = 3,    // 内部事件
    };

public:
	Epoll() : m_vEvent(NULL), m_iEpollFd(0), m_iMaxEvents(0)
	{

	}

	~Epoll()
	{
		if (m_vEvent)       { delete [] m_vEvent; m_vEvent = NULL; }

		if (m_iEpollFd > 0) { ::close(m_iEpollFd);                 }
	}

public:
    void Initialize(int32_t iMaxEvents)
	{
		m_iMaxEvents = iMaxEvents;
		m_iEpollFd   = ::epoll_create(1);
		m_vEvent     = new epoll_event[iMaxEvents];
	}

    void AddEvent(int32_t iFd, uint32_t iH, uint32_t iL, uint32_t iEvent) { SysEpollCtrl(iFd, (((uint64_t)iH) << 32) | iL, iEvent, EPOLL_CTL_ADD); }
    void DelEvent(int32_t iFd, uint32_t iH, uint32_t iL, uint32_t iEvent) { SysEpollCtrl(iFd, (((uint64_t)iH) << 32) | iL, iEvent, EPOLL_CTL_DEL); }
    void ModEvent(int32_t iFd, uint32_t iH, uint32_t iL, uint32_t iEvent) { SysEpollCtrl(iFd, (((uint64_t)iH) << 32) | iL, iEvent, EPOLL_CTL_MOD); }
    int  WaitForEvent(int32_t iTimeoutMs)
	{
		int iRet = ::epoll_wait(m_iEpollFd, m_vEvent, m_iMaxEvents, iTimeoutMs);

		if (iRet < 0)
		{
			return 0;
		}

		return iRet;
	}

    epoll_event & GetEventByIndex(int32_t iIndex) { return m_vEvent[iIndex]; }

protected:
    void SysEpollCtrl(int32_t iFd, uint64_t iData, uint32_t iEvent, uint32_t iOpType)
	{
		struct epoll_event xEvent;
		xEvent.data.u64 = iData;
		xEvent.events   = iEvent | EPOLLET;

		::epoll_ctl(m_iEpollFd, iOpType, iFd, &xEvent);
	}

protected:
    epoll_event * m_vEvent;

    int32_t       m_iEpollFd;

    int32_t       m_iMaxEvents;
};


#endif

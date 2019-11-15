#include "util/include/tu_socket.h"
#include "util/include/tu_epoll.h"
#include "util/include/tu_datetime.h"

using namespace Thoth;

int RecvData(int iFd)
{
    char szBuff[8192] = "\0";
    int  iTotalLength = 0;

    for (; true; )
    {
        errno = 0;

        int iBytesReceived = ::recv(iFd, (void*)szBuff, sizeof(szBuff), 0);

        if (iBytesReceived == 0)
        {
            std::cout << TU_DateTime::CurrentDateTime() << " recv: close::" << errno << std::endl;

            return -1;
        }

        if (iBytesReceived == -1)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR)
            {
                std::cout << TU_DateTime::CurrentDateTime() <<  " recv again::" << errno << std::endl;
                break;
            }
            else
            {
                std::cout << TU_DateTime::CurrentDateTime() << " recv error::" << errno << std::endl;

                return -1;
            }
        }

        if (iBytesReceived < sizeof(szBuff))
        {
            std::cout << TU_DateTime::CurrentDateTime() <<  " recv size:" << iBytesReceived << std::endl;

            return 0;
        }
    }

    return 0;
}

int SendData(int iFd)
{

    std::string sSend = "98765432101";

    int iRet = ::send(iFd, sSend.data(), sSend.size(), 0);

    if ((iRet == -1) && (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR))
    {
        std::cout << "write irorrr" << std::endl;

        return 0;
    }

    if ((iRet != -1))
    {
        std::cout << "write:" << iRet << std::endl;

        return iRet;
    }

    /////////////////////////////////////////////////////////////////////////////////////
    /// 走到此处，说明出现问题，需要关闭连接

    std::cout << "write error" << std::endl;

    return -1;
}

int ProcessListen()
{


}

int main(int argc, char ** argv)
{
    TU_Socket sock;
    sock.CreateTcpSocket();
    sock.SetBlock(false);
    sock.Bind("192.168.9.100", 7788);
    sock.Listen(1);

    TU_Epoll xEpoll;
    xEpoll.Initialize(5);
    xEpoll.AddEvent(sock.GetSocketFd(), TU_Epoll::E_EPOLL_LISTEN, sock.GetSocketFd(), EPOLLIN | EPOLLOUT);

    std::cout << "Listen fd :" << sock.GetSocketFd() << std::endl;

    for (; true; )
    {
        int iEvent = xEpoll.WaitForEvent(200000);

        std::cout << TU_DateTime::CurrentDateTime() << "==========================================::" << iEvent << std::endl;

        for (int i = 0; i < iEvent; i++)
        {
            epoll_event xEvent = xEpoll.GetEventByIndex(i);

            std::cout << "|||E:" << (xEvent.data.u64 >> 32) << "|" << (xEvent.data.u32) << std::endl;

            switch (xEvent.data.u64 >> 32)
            {
                case TU_Epoll::E_EPOLL_LISTEN:
                {
                    for (uint32_t iListenFd = xEvent.data.u32; (xEvent.events & EPOLLIN); )
                    {
                        TU_Socket xSocket;

                        if (sock.Accept(xSocket) <= 0)
                        {
                            if (errno == EAGAIN)
                            {
                                break;
                            }
                            else
                            {
                                continue;
                            }
                        }

                        xSocket.SetBlock(false);

                        xSocket.SetAutoRelease(false);

                        int flag = 1;
                        if (::setsockopt(xSocket.GetSocketFd(), SOL_SOCKET, SO_KEEPALIVE, (char*)&flag, int(sizeof(int))) == -1)
                        {
                            std::cout << "set false" << std::endl;

                            return 0;
                        }

                        int keepIdle     = 60;
                        int keepInterval = 10;
                        int keepCount    = 13;

                        std::cout << setsockopt(xSocket.GetSocketFd(), SOL_TCP, TCP_KEEPIDLE,  (void *)&keepIdle, sizeof(keepIdle)) << std::endl;

                        std::cout << setsockopt(xSocket.GetSocketFd(), SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval)) << std::endl;

                        std::cout << setsockopt(xSocket.GetSocketFd(), SOL_TCP, TCP_KEEPCNT,   (void *)&keepCount, sizeof(keepCount)) << std::endl;

                        std::cout << "set success" << std::endl;

                        xEpoll.AddEvent(xSocket.GetSocketFd(), TU_Epoll::E_EPOLL_SOCKET, xSocket.GetSocketFd(), EPOLLIN | EPOLLOUT);

                        std::cout << "new sock:" << xSocket.GetSocketFd() << std::endl;
                    }
                    break; 
                }

            case TU_Epoll::E_EPOLL_SOCKET: 
                if (xEvent.events & (EPOLLERR | EPOLLHUP))
                {
                    std::cout << "close ::" << (xEvent.events & EPOLLERR?"EPOLLERR":" not ") << "|" << (xEvent.events & EPOLLHUP ? "EPOLLHUP" : " not ") << "|" << errno << std::endl;

                    break;
                }

                if (xEvent.events & (EPOLLOUT))
                {
                    //SendData(xEvent.data.u32);
                }

                if (xEvent.events & (EPOLLIN))
                {
                    RecvData(xEvent.data.u32);

                    static int i = 0;

                    ::sleep(30);

                    if (++i == 1)
                    {
                        std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
                        SendData(xEvent.data.u32);
                    }
                }

                break;
            }
        }

    }


    return 0;
}

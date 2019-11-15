#include "util.h"

int main(int argc, char ** argv)
{
    int iSocketFd = Util::CreateTcpSocket();
    Util::SetBlock(iSocketFd, true);
    Util::Connect(iSocketFd, "192.168.9.100", 7788);

    Util::Send(iSocketFd, "123456789");

    ::sleep(10 * 60);

    ::close(iSocketFd);

    ::sleep(10 * 60);

    return 0;
}

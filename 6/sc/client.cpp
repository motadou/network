#include "util/include/tu_socket.h"

using namespace Thoth;

int main(int argc, char ** argv)
{
    TU_Socket sock;
    sock.CreateTcpSocket();
    sock.SetBlock(true);
    sock.Connect("192.168.9.100", 7788);

    sock.Send("123456789");

    ::sleep(10 * 60);
    
    sock.Close();

    ::sleep(10 * 60);

    return 0;
}

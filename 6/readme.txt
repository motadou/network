mqq@dev-0-0:/home/kevintian$ sudo tcpdump -i eth0 -n port 7788
[sudo] password for mqq: 
tcpdump: verbose output suppressed, use -v or -vv for full protocol decode
listening on eth0, link-type EN10MB (Ethernet), capture size 262144 bytes


17:23:25.422433 IP 192.168.10.103.38686 > 192.168.9.100.7788: Flags [S], seq 1523833714, win 29200, options [mss 1460,sackOK,TS val 4294922047 ecr 0,nop,wscale 7], length 0
17:23:25.422455 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [S.], seq 4008163313, ack 1523833715, win 28960, options [mss 1460,sackOK,TS val 784434320 ecr 4294922047,nop,wscale 7], length 0
17:23:25.423711 IP 192.168.10.103.38686 > 192.168.9.100.7788: Flags [.], ack 1, win 229, options [nop,nop,TS val 4294922047 ecr 784434320], length 0
17:23:25.424012 IP 192.168.10.103.38686 > 192.168.9.100.7788: Flags [P.], seq 1:10, ack 1, win 229, options [nop,nop,TS val 4294922047 ecr 784434320], length 9
17:23:25.424024 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [.], ack 10, win 227, options [nop,nop,TS val 784434320 ecr 4294922047], length 0


17:23:55.424244 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784441820 ecr 4294922047], length 11
17:23:55.621456 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784441870 ecr 4294922047], length 11
17:23:55.821458 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784441920 ecr 4294922047], length 11
17:23:56.221454 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784442020 ecr 4294922047], length 11
17:23:57.021469 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784442220 ecr 4294922047], length 11
17:23:58.625430 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784442621 ecr 4294922047], length 11
17:24:01.837441 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784443424 ecr 4294922047], length 11
17:24:08.253465 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784445028 ecr 4294922047], length 11
17:24:21.101476 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784448240 ecr 4294922047], length 11
17:24:46.765426 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784454656 ecr 4294922047], length 11
17:25:38.093452 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784467488 ecr 4294922047], length 11
17:27:20.877472 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784493184 ecr 4294922047], length 11
17:29:21.197449 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784523264 ecr 4294922047], length 11
17:31:21.517476 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784553344 ecr 4294922047], length 11
17:33:21.837482 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784583424 ecr 4294922047], length 11
17:35:22.157455 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784613504 ecr 4294922047], length 11
17:37:22.477490 IP 192.168.9.100.7788 > 192.168.10.103.38686: Flags [P.], seq 1:12, ack 10, win 227, options [nop,nop,TS val 784643584 ecr 4294922047], length 11


mqq@dev-0-0:/home/kevintian/quote/test/sc$ ./server 
Listen fd :3

20191115172325==========================================::1
|||E:1|3
0
0
0
set success
new sock:5
20191115172325==========================================::1
|||E:2|5
20191115172325==========================================::1
|||E:2|5
20191115172325 recv size:9

XXXXXXXXXXXXXXXXXXXXXXXXXXX
write:11
20191115172715==========================================::0
20191115173035==========================================::0
20191115173355==========================================::0
20191115173715==========================================::0
20191115173922==========================================::1
|||E:2|5
close ::EPOLLERR|EPOLLHUP|0

第一次发送后所设置的超时时间实际上为1.5秒，此后该时间在每次重传时增加一倍，一直到64秒，采用的是指数退避算法。一共重传12次，大约9分钟才放弃重传，该时间在目前的TCP实现中是不可变的，Solaris2.2允许管理者改变这个时间，tcp_ip_abort_interval变量。且其默认值为两分钟，而不是最常用的9分钟。
————————————————
版权声明：本文为CSDN博主「chienchia」的原创文章，遵循 CC 4.0 BY-SA 版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/chienchia/article/details/39994591

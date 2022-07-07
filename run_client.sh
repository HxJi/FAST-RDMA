#!bin/bash

make && sudo make install && sudo modprobe rdma_krping debug=1 &&
#echo "client,addr=192.168.101.14,port=20886,count=200" >/proc/krping
echo "client,serv_poll,addr=192.168.101.14,port=20886,count=10,verbose" >/proc/krping
#echo "client,addr=192.168.101.14,port=20886,count=200,validate,verbose" >/proc/krping

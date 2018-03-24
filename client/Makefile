client:clean.o nAddAllAgentToEpoll.o create_connect.o setNonBlocking.o allocDealPackage.o dealData.o EpollCtl.o echoFunc.o nReadOperator.o writePackage.o EpollDo.o client.o
	gcc -o client clean.o nAddAllAgentToEpoll.o create_connect.o setNonBlocking.o allocDealPackage.o dealData.o EpollCtl.o echoFunc.o nReadOperator.o writePackage.o EpollDo.o client.o
	rm *.o

clean.o:clean.c global.h
	gcc -c -g clean.c

nAddAllAgentToEpoll.o:nAddAllAgentToEpoll.c global.h
	gcc -c -g nAddAllAgentToEpoll.c
	
create_connect.o:create_connect.c global.h
	gcc -c -g create_connect.c 
	
setNonBlocking.o:setNonBlocking.c global.h
	gcc -c -g setNonBlocking.c
	
allocDealPackage.o:allocDealPackage.c global.h
	gcc -c -g allocDealPackage.c	
	
dealData.o:dealData.c global.h
	gcc -c -g dealData.c
	
EpollCtl.o:EpollCtl.c global.h
	gcc -c -g EpollCtl.c
	
echoFunc.o:echoFunc.c global.h
	gcc -c -g echoFunc.c	

nReadOperator.o:nReadOperator.c global.h
	gcc -c -g nReadOperator.c

writePackage.o:writePackage.c global.h
	gcc -c -g writePackage.c

EpollDo.o:EpollDo.c global.h
	gcc -c -g EpollDo.c

client.o:client.c global.h
	gcc -c -g client.c

clean:
	rm -rf *.o client

epollServer:CAgent.o CRelayAgent.o CListenAgent.o CTask.o CLoginTask.o CMessageTask.o \
				CBuffer.o CSocketOperator.o CEpoll.o \
				COffLineManager.o CBufferManager.o CTaskManager.o CAgentManager.o main.o 				
	g++ -m32 -pthread -o epollServer CAgent.o CRelayAgent.o CListenAgent.o CTask.o CLoginTask.o CMessageTask.o \
				CBuffer.o CSocketOperator.o CEpoll.o \
				COffLineManager.o CBufferManager.o CTaskManager.o CAgentManager.o main.o


CAgent.o:CAgent.cpp CAgent.h global.h
	g++ -m32 -c -g CAgent.cpp
	
CRelayAgent.o:CRelayAgent.cpp CRelayAgent.h CAgent.h global.h
	g++ -m32 -Wpointer-arith -c -g CRelayAgent.cpp 
	
CListenAgent.o:CListenAgent.cpp CListenAgent.h CAgent.h global.h
	g++ -m32 -Wpointer-arith -c -g CListenAgent.cpp

CTask.o:CTask.cpp CTask.h global.h
	g++ -m32 -c -g CTask.cpp
	
CLoginTask.o:CLoginTask.cpp CLoginTask.h CTask.h global.h
	g++ -m32 -c -g CLoginTask.cpp
	
CMessageTask.o:CMessageTask.cpp CMessageTask.h CTask.h global.h
	g++ -m32 -c -g CMessageTask.cpp
	
CBuffer.o:CBuffer.cpp CBuffer.h global.h
	g++ -m32 -c -g CBuffer.cpp
	
CSocketOperator.o:CSocketOperator.cpp CSocketOperator.h global.h
	g++ -m32 -c -g CSocketOperator.cpp
		
CEpoll.o:CEpoll.cpp CEpoll.h global.h
	g++ -m32 -c -g CEpoll.cpp
		
COffLineManager.o:COffLineManager.cpp COffLineManager.h global.h
	g++ -m32 -c -g COffLineManager.cpp
	
CBufferManager.o:CBufferManager.cpp CBufferManager.h global.h
	g++ -m32 -c -g CBufferManager.cpp
	
CTaskManager.o:CTaskManager.cpp CTaskManager.h global.h
	g++ -m32 -c -g CTaskManager.cpp
	
CAgentManager.o:CAgentManager.cpp CAgentManager.h global.h
	g++ -m32 -c -g CAgentManager.cpp
		
main.o:main.cpp global.h
	g++ -m32 -c -g main.cpp

clean:
	rm -rf *.o epollServer

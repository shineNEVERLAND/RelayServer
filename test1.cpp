#include<iostream>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>

using namespace std;

class A{
public:
	int * value;
	A();
	~A();
};

A :: A(){
	cout<<"A()"<<endl;
}

A :: ~A(){
	if(value){
		delete value;
		value = NULL;
	}
	cout<<"~A()"<<endl;
}


A a;
A * b;

void handle(int s){
	if( b ){
		cout<<"delete b"<<endl;
		delete b;
		b = NULL;
	}
	
	exit(0);
	
}

int main(){
	if( SIG_ERR == signal( SIGINT, handle ) ){
		cout<<"signal SIGINT error"<<endl;
	}
	
	a.value = new int;
	
	b = new A;
	cout<<"sizeof(a)"<<sizeof(a)<<endl;
	cout<<"sizeof(b)"<<sizeof(b)<<endl;
	
	sleep(20);
	
	return 1;
	
}
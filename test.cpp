#include <string.h>  // <cstring>和<string.h>相同
#include <vector> 
#include <iostream>
#include <stdlib.h>
 using namespace std;
int ar[10] = {  12, 45, 234, 64, 12, 35, 63, 23, 12, 55  };
 
typedef struct a {
	int data;
}a;
 vector<a *> g_test;
 
 
void bb(int fd, a* temp) {
	g_test[fd] = temp;
	cout << temp->data << endl;
	cout << g_test[fd]->data << endl;
}
 
int main(int argc, char* argv[])
{
	g_test.push_back(NULL);
	a *AAA = (a *)malloc(sizeof(a));
	AAA->data = 100;
	cout << AAA << endl;
	bb(10, AAA);
	
	g_test.push_back(AAA);
	bool result;
	result = g_test.empty();
	if(true == result)
		cout<<"TRUE"<<endl;
	else
		cout<<"FALSE"<<endl;
	// cout << AAA << endl;
  // std::vector <int> vec2(5,333);

  return 0;
}
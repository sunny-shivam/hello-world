#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

using namespace std;

class singleton{
	static singleton s;
	int i;
	singleton(int x): i(x){}
	void operator =(singleton&);
	singleton(const singleton&);
	
	public:
	static singleton& getHandle(){
			return s;
		}
	int getValue(){return i; }	
	void setValue(int x){i=x; }
	
};

singleton singleton::s(47);

void* f1(void* arg){
  singleton& first_obj = singleton::getHandle();
  printf("Thread 1: initial value = %d setting = 100\n", first_obj.getValue());
  first_obj.setValue(100);
  for(int i=0; i<10; i++){
	  usleep(10000);
    printf("Thread 1: %d\n", first_obj.getValue());
	}

  return NULL;
}

void* f2(void* arg){
  singleton& second_obj = singleton::getHandle();
  printf("Thread 2: initial value = %d setting = 200\n", second_obj.getValue());
  second_obj.setValue(200);
  for(int i=0; i<10; i++){
	  usleep(10000);
    printf("Thread 2: %d\n", second_obj.getValue());
	}

  return NULL;
}

int main(int argc, char **argv) {
  pthread_t th1, th2;

	singleton& first_obj = singleton::getHandle();
	cout<<"\n"<<first_obj.getValue()<<endl;
	
  pthread_create(&th1, NULL, f1, NULL);
  pthread_create(&th2, NULL, f2, NULL);

  /* Main will wait until th1 and th2 are finished */
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);

  pthread_exit(NULL);
}

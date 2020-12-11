#include <stdio.h>
#include <pthread.h>
#include<time.h>


void *thread_function1(void *);
void *thread_function2(void *);

pthread_barrier_t bar;
int  x = 0, y=0;

int main()
{
   pthread_t thread_id[2];
   int i, j;

   pthread_barrier_init(&bar, NULL, 2);

   pthread_create( &thread_id[0], NULL, thread_function1, NULL );
   pthread_create( &thread_id[1], NULL, thread_function2, NULL );
  
   
   pthread_join( thread_id[0], NULL); 
   pthread_join( thread_id[1], NULL); 

   pthread_barrier_destroy(&bar);
   return 0;  
}

void *thread_function1(void *dummyPtr)
{
     printf("Thread number %ld\n", pthread_self());
     x=1;
     printf("Function1 before barrier: x = %d\n",x);
     pthread_barrier_wait(&bar);
     printf("Function1 after barrier: x = %d\n",x);

}

void *thread_function2(void *dummyPtr)
{
     printf("Thread number %ld\n", pthread_self());
     printf("Function2 before barrier: y = %d, x = %d\n",y,x);
     pthread_barrier_wait(&bar);
     y=x;
     printf("Function2 before barrier: y = %d, x = %d\n",y,x);
}

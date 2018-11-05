#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

/*
信号量的主要函数有：

int sem_init(sem_t *sem,int pshared,unsigned int value);
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
sem_init用于对指定信号初始化，pshared为0，表示信号在当前进程的多个线程之间共享，value表示初始化信号的值。 
sem_wait可以用来阻塞当前线程，直到信号量的值大于0，解除阻塞。解除阻塞后，sem的值-1，表示公共资源被执行减少了。例如：如果你对一个值为2的信号量调用sem_wait(),线程将会继续执行，信号量的值将-1。当初始化value=0后，使用sem_wai会阻塞这个线程，这个线程函数就会等待其它线程函数调用sem_post增加了了这个值使它不再是0，才开始执行,然后value值-1。 
sem_post用于增加信号量的值+1，当有线程阻塞在这个信号量上时，调用这个函数会使其中的一个线程不在阻塞，选择机制由线程的调度策略决定。 
*/ 
sem_t semaphore;
//https://gist.github.com/tausen/4261887
void *threadfunc(void *) {
    while (1) {
        sem_wait(&semaphore); //1 --解除阻塞----> 0 
        printf("Hello from da thread!\n");
        sem_post(&semaphore);  // 0 --->  1  
        sleep(1);
    }
}

int main(void) {
    
    // initialize semaphore, only to be used with threads in this process, set value to 1
    sem_init(&semaphore, 0, 1);
    
   // pthread_t *mythread;
     
   // mythread = (pthread_t *)malloc(sizeof(*mythread));
     
     pthread_t mythread;
    // start the thread
    printf("Starting thread, semaphore is unlocked.\n");
    pthread_create(&mythread, NULL, threadfunc, NULL);
    
    getchar();
     printf("call Semaphore wait =============.\n");
    /*这里是减去1，等待正数出现吧*/
    sem_wait(&semaphore);  //等待信号,获取拥有权
    printf("Semaphore locked.\n");  //*子线程阻塞住，等待输入 
    
    // do stuff with whatever is shared between threads
    getchar();
    
    printf("Semaphore unlocked.\n");
    printf("call sem_post  =============.\n"); 
    sem_post(&semaphore); /*这里会加1的、*/   //发出信号即释放拥有权
    
    getchar();
    
    return 0;
}

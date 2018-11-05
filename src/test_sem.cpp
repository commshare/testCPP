#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

/*
�ź�������Ҫ�����У�

int sem_init(sem_t *sem,int pshared,unsigned int value);
int sem_wait(sem_t *sem);
int sem_post(sem_t *sem);
sem_init���ڶ�ָ���źų�ʼ����psharedΪ0����ʾ�ź��ڵ�ǰ���̵Ķ���߳�֮�乲��value��ʾ��ʼ���źŵ�ֵ�� 
sem_wait��������������ǰ�̣߳�ֱ���ź�����ֵ����0��������������������sem��ֵ-1����ʾ������Դ��ִ�м����ˡ����磺������һ��ֵΪ2���ź�������sem_wait(),�߳̽������ִ�У��ź�����ֵ��-1������ʼ��value=0��ʹ��sem_wai����������̣߳�����̺߳����ͻ�ȴ������̺߳�������sem_post�����������ֵʹ��������0���ſ�ʼִ��,Ȼ��valueֵ-1�� 
sem_post���������ź�����ֵ+1�������߳�����������ź�����ʱ���������������ʹ���е�һ���̲߳���������ѡ��������̵߳ĵ��Ȳ��Ծ����� 
*/ 
sem_t semaphore;
//https://gist.github.com/tausen/4261887
void *threadfunc(void *) {
    while (1) {
        sem_wait(&semaphore); //1 --�������----> 0 
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
    /*�����Ǽ�ȥ1���ȴ��������ְ�*/
    sem_wait(&semaphore);  //�ȴ��ź�,��ȡӵ��Ȩ
    printf("Semaphore locked.\n");  //*���߳�����ס���ȴ����� 
    
    // do stuff with whatever is shared between threads
    getchar();
    
    printf("Semaphore unlocked.\n");
    printf("call sem_post  =============.\n"); 
    sem_post(&semaphore); /*������1�ġ�*/   //�����źż��ͷ�ӵ��Ȩ
    
    getchar();
    
    return 0;
}

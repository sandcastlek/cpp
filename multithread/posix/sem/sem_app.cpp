
#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

bool bContinue;
sem_t  s_odd;
sem_t  s_even;

struct th_info
{
	sem_t* p_sem_to_wait;
	sem_t* p_sem_to_signal;
	int	   i_start;
	const char* pName;
};

void* my_print(void* arg) {
	th_info* pInfo = (th_info*)arg;

	while(bContinue) 
	{
		sem_wait(pInfo->p_sem_to_wait);

		std::cout << pInfo->pName << "," << pInfo->i_start << std::endl;
		pInfo->i_start += 2;
		sleep(1);

		sem_post(pInfo->p_sem_to_signal);
	}
}

int main(int argc, char* argv[])
{
	bContinue = true;

	pthread_t  th1, th2;
	th_info    th1_info, th2_info;

	sem_init(&s_odd,0,1);
	sem_init(&s_even,0,1);

	th1_info.p_sem_to_wait = &s_odd;
	th1_info.p_sem_to_signal = &s_even;
	th1_info.i_start = 1;
	th1_info.pName = "Th1";

	th2_info.p_sem_to_wait = &s_even;
	th2_info.p_sem_to_signal = &s_odd;
	th2_info.i_start = 2;
	th2_info.pName = "Th2";

	sem_wait(&s_even);
	pthread_create(&th1, NULL, my_print, (void*)&th1_info);
	pthread_create(&th2, NULL, my_print, (void*)&th2_info);

	sleep(40);
	bContinue = false;

	pthread_join(th1,NULL);
	pthread_join(th2,NULL);


	sem_destroy(&s_odd);
	sem_destroy(&s_even);

	return 0;
}

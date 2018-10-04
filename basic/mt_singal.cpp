#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

class TaskSequencer
{
public:
	TaskSequencer(int MaxSlots, int StartSlot) : 
		m_iMaxSlots(MaxSlots), m_itoDoSlot(StartSlot),
		m_bcontinue(true)
	{
		pthread_mutex_init(&mutx,NULL);
		//assert(m_iMaxSlots);
		m_pcondLst = new pthread_cond_t[m_iMaxSlots];
		for(size_t ictr=0; ictr < m_iMaxSlots; ++ictr) {
			pthread_cond_init(&m_pcondLst[ictr], NULL);
		}
	}

	int nextSlot(int this_slot) {
		return ( (m_iMaxSlots == (1+this_slot) ) ? 0 : ++this_slot);
	}
	
	~TaskSequencer() {
		delete[] m_pcondLst;
		m_pcondLst = NULL;
	}

public:
	int m_iMaxSlots;
	int m_itoDoSlot;
	bool m_bcontinue;
	pthread_cond_t* m_pcondLst;
	pthread_mutex_t mutx;
};


class WorkerTreadCtx
{
public:
	WorkerTreadCtx( TaskSequencer* ws, int thisSlot) :
		m_pObjWorkSlot(ws),
		m_slotId(thisSlot) 
	{

	}
public:
	TaskSequencer*    m_pObjWorkSlot;
	int               m_slotId;
};

void* worker_thread( void* in_param)
{
	WorkerTreadCtx* ctx = (WorkerTreadCtx*)in_param;
	TaskSequencer* sltInfo = ctx->m_pObjWorkSlot;
	
	printf("Begin Thread slot :%d \n", ctx->m_slotId);
	while( sltInfo->m_bcontinue )
	{
		pthread_mutex_lock(&(sltInfo->mutx));

		while(  ctx->m_slotId != sltInfo->m_itoDoSlot ) {
			pthread_cond_wait( &(sltInfo->m_pcondLst[ ctx->m_slotId ]), &(sltInfo->mutx) );
		}

		printf( " ... Working on Slot %d ... \n", ctx->m_slotId );
		sleep(3);

		sltInfo->m_itoDoSlot = sltInfo->nextSlot( ctx->m_slotId);
		
		pthread_cond_signal( &(sltInfo->m_pcondLst[ sltInfo->m_itoDoSlot]));

		pthread_mutex_unlock(&(sltInfo->mutx));
	}
	printf("Exit Thread slot :%d \n", ctx->m_slotId);
	delete ctx;
}

class CollaborativeTask
{
public:
	CollaborativeTask(int thread_count, TaskSequencer* ts) :
		m_thrdCnt(thread_count),
		m_ts(ts)
	{
		m_thrdLst = new pthread_t[m_thrdCnt];
		for(size_t ictr=0; ictr < m_thrdCnt; ++ictr) {
			pthread_create( &m_thrdLst[ictr], NULL, worker_thread, (void*)(new WorkerTreadCtx(m_ts, ictr))  );
		}
	}

	~CollaborativeTask() {
		m_ts->m_bcontinue = false;
		for(size_t ictr=0; ictr < m_thrdCnt; ++ictr) {
			pthread_join( m_thrdLst[ictr], NULL);
		}
	}

public:
	TaskSequencer* m_ts;
	pthread_t*  m_thrdLst;
	int         m_thrdCnt;
};

int main(int argc, char* argv[])
{
    int thrd_count = 3;
	TaskSequencer  ts(thrd_count,1);
	CollaborativeTask cs(thrd_count, &ts);
	printf("Exit Main\n");
	return 0;
}



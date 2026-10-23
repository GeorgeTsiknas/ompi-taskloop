#include <stdlib.h>
#define N 10
#define NTHREADS 4

int main(void)
{
	int lastpriv_var = 10;
	int shared_var = 0;
	int priv_var = 10;
	int firstpriv_var = 42;
	int task_flag = 1;
	
	#pragma omp parallel num_threads(NTHREADS)
	{
		#pragma omp single
		{
			#pragma omp taskloop lastprivate(lastpriv_var) shared(shared_var) \
			                     private(priv_var) firstprivate(firstpriv_var,task_flag)
			for(int i=0; i<N; i++)
			{
				if(task_flag == 1)
				{
					if(firstpriv_var != 42)
					{
						abort();
					}
					task_flag = 0;
				}
				firstpriv_var = i + 1;
				priv_var = i + 1;
				lastpriv_var = i + 1;  
				
				#pragma omp atomic 
				shared_var++;
			}
		}
		if(lastpriv_var != N || shared_var != N || priv_var != 10 || firstpriv_var != 42)
		{
			abort();
		}
	}
	return 0;
}
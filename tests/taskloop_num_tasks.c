#include <stdlib.h>
#include <omp.h>

#define N 100
#define TARGET_TASKS 4

int main(void)
{
	 
	int task_flag = 1;
	int total_tasks = 0;
	#pragma omp parallel num_threads(8)
	{
		#pragma omp single
		{
			#pragma omp taskloop num_tasks(TARGET_TASKS) shared(total_tasks) firstprivate(task_flag)
			for(int i=0; i<N; i++)
			{
				if(task_flag == 1)
				{
					#pragma omp atomic
					total_tasks++;
					task_flag = 0;
				}
			}
		}
	}
	if(total_tasks != TARGET_TASKS)
	{
		abort();
	}
	
	return 0;
}
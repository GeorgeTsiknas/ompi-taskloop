#include <stdlib.h>
#include <omp.h>
#include <stdio.h>

int main(void)
{
	int flag = 0;
	int completed_tasks = 0;

	#pragma omp parallel num_threads(4)
	{
		#pragma omp single
		{
			#pragma omp taskloop nogroup shared(flag, completed_tasks)
			for(int i=0; i<omp_get_num_threads(); i++)
			{
				while(flag == 0)
				{
					#pragma omp flush(flag)
				}
				#pragma omp atomic
				completed_tasks++;
			}
			flag = 1;
			#pragma omp flush(flag)
		}
	}

	if (completed_tasks != 4)
	{
		abort();
	}

	return 0;
}
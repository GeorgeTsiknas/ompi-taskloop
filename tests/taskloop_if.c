#include <stdlib.h>
#include <omp.h>

#define N 100000

int main(void)
{
	int master_thread_id = -1;
	int invalid_executions = 0;

	#pragma omp parallel num_threads(32)
	{
		#pragma omp single
		{
			master_thread_id = omp_get_thread_num();

			#pragma omp taskloop if(0) shared(invalid_executions)
			for (int i=0; i<N; i++)
			{
				if (omp_get_thread_num() != master_thread_id) {
					#pragma omp atomic
					invalid_executions++;
				}
			}
		}
	}

	if (invalid_executions != 0)
	{
		abort();
	}

	return 0;
}
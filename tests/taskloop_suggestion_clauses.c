#include <stdlib.h>
#include <omp.h>

#define N 100

int main(void)
{
	int count = 0;
	int prio = 5;

	#pragma omp parallel num_threads(4)
	{
		#pragma omp single
		{
			#pragma omp taskloop untied mergeable priority(prio) shared(count)
			for (int i=0; i<N; i++) 
			{
				#pragma omp atomic
				count++;
			}
		}
	}

	if (count != N)
	{
		abort();
	}

	return 0;
}
#include <stdlib.h>
#include <omp.h>

#define N 100

int main(void)
{
	int sum = 0;
	int expected = (N-1) * N / 2;
	#pragma omp parallel num_threads(4)
	{
		#pragma omp single
		{
			#pragma omp taskgroup task_reduction(+:sum)
			{
				#pragma omp taskloop in_reduction(+:sum)
				for(int i=0; i<N; i++)
				{
					sum += i;
				}
			}
		}
	}
	if(sum != expected)
	{
		abort();
	}
	return 0;
}
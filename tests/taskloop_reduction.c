#include <stdlib.h>

#define N 1000000

int main(void)
{
	long long sum = 0;
	long long expected = (long long)(N - 1) * N / 2;

	#pragma omp parallel num_threads(4)
	{
		#pragma omp single
		{
			#pragma omp taskloop  reduction(+:sum) grainsize(1)
			for (int i=0; i<N; i++) 
			{
				sum += i;
			}
		}
	}
	if(sum!=expected)
	{
		abort();
	}
	return 0;
}
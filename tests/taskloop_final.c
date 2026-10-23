#include <stdlib.h>
#include <omp.h>

int main(void)
{
	int final_execution_count = 0;

	#pragma omp parallel num_threads(4)
	{
		#pragma omp single
		{
			#pragma omp taskloop final(1)
			for (int i=0; i<20; i++) 
			{
				if (omp_in_final()) {
					#pragma omp atomic
					final_execution_count++;
				}
			}
		}
	}

	/* if final clause is ignored then the program will abort */
	if (final_execution_count != 20)
	{
		abort();
	}
	
	return 0;
}
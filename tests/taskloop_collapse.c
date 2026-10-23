#include <stdlib.h>
#define ROWS 10
#define COLS 10
#define EXPECTED_TASKS 20

int main(void)
{
	int matrix[ROWS][COLS] = {0};	
	int task_flag = 1;
	int tasks_created = 0;
	
	#pragma omp parallel num_threads(4)
	{
		#pragma omp single
		{
			#pragma omp taskloop collapse(2) num_tasks(20)\
			                     firstprivate(task_flag) shared(tasks_created)
			for(int i=0; i<ROWS; i++)
			{
				for(int j=0; j<COLS; j++)
				{
					if(task_flag == 1)
					{
						#pragma omp atomic
						tasks_created++;
						task_flag = 0;
					}
					matrix[i][j] = i*COLS + j;	
				}
			}
		}
	}
	/* 
	   If collapse(2) did not exist then we would be having ROWS number of tasks,
	   since no more tasks than the number of iterations can be created 
	*/
	if(tasks_created != EXPECTED_TASKS)
	{
		abort();
	}
	
	/* Data verification */
	for(int i=0; i<ROWS; i++)
	{
		for(int j=0; j<COLS; j++)
		{
			if(matrix[i][j] != (i*COLS) + j)
			{
				abort();
			}
		}
	}
	return 0;
}
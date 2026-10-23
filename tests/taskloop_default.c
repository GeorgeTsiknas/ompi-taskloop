int main(void)
{
	int count = 0;
	#pragma omp parallel num_threads(4)
	{
		#pragma omp single
		{
			#pragma omp taskloop default(none)
			for(int i=0; i<10; i++)
			{
				count++;
			}
		}
	}
	
	return 0;
}
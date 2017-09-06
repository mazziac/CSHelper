#include <stdio.h>
#include <stdlib.h>


/**
 * Takes in an array of integers and the number of elements in the array 
 * as arguments.
 * Then it will return the ratio of numbers of even elements and odd elements.
 */
float even_odd_ratio(int *arr, int size)
{
    float even=0,odd=0;
  for(int i=0;i<size;i++){
    //printf("Num, %d",arr[i]);
      if(arr[i]%2==0)
          even++;
      else
          odd++;
  }
  float ratio=even/odd;
  //printf("output from even count %f and odd count %f and total %d and ratio %f\n",even,odd,size,ratio);
  return(ratio);
}


/**
 * Takes in a random number and maps it to the
 * range [100 - 120)
 */
int get_iteration_count(int rand) { return ((rand % (150-100) + 100)*1); }

/**
 * Takes in a random number and maps it to the 
 * range [100 - 150)
 */
int get_arr_size(int rand){ return ((rand % (1500 -1000) +100)*1); }


/**
 * This is the method that you need to implement.
 * Implement the following steps in the given order.
 *
 *  1. Generate the number of iterations
 *      - Generate a random number. Map it to the range [100 - 120) using the 
 *      utility function 'get_iteration_count'.
 * 
 * 2. For each iteration:
 *      2.a Generate an array size - Generate a random number and map it to the range [100 - 150) using
 *          the utility function 'get_arr_size'.
 * 
 *      2.b Allocate memory for the array in the heap.
 *
 *      2.c Populate the array with random numbers.
 *
 *      2.d Get the ratio even/odd.
 *
 *      2.e Return the even/odd ratio.
 *
 *     
 *
 */

float get_running_ratio()
{
	int iterations = get_iteration_count(rand());
	printf("[CreateArray] Number of Iterations: %d\n", iterations);
	float total = 0; //Holds total of even odd ratio
	for(int i = iterations-1;i >= 0; i--){
		int arraySize = get_arr_size(rand());
		int* array = (int*) malloc(arraySize * sizeof(int)); //createArray
		for(int i = arraySize-1;i > 0; i--) //populateArray
			array[i] = rand();
		total += even_odd_ratio(array,arraySize); //updateTotal
		//Uncomment the next line in order to plug leak
		//free(array); 
	}
	return total/iterations;	
}	


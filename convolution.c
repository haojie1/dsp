#include<stdio.h>
#include<stdlib.h>

//The structure of the sequnce
typedef struct sequnce{
	int* sequnce;
	int first_index, length;
} * pSequnce, Sequnce;

void getSequnce(pSequnce sequnce);
void showSequnce(pSequnce sequnce);
void clearSpace(pSequnce sequnce);
pSequnce computeConvolution(pSequnce sequnce1, pSequnce sequnce2);
void reverse(pSequnce sequnce);
void shift(pSequnce sequnce, int distance);
int sumAtSamePoint(pSequnce sequnce1, pSequnce sequnce2);

int main(void)
{
	pSequnce sequnce1, sequnce2 ,result;

	sequnce1 = (pSequnce)malloc(sizeof(Sequnce));
	printf("Please input the first sequnce\n");
	getSequnce(sequnce1);
	showSequnce(sequnce1);

	sequnce2 = (pSequnce)malloc(sizeof(Sequnce));
	printf("Please input the second sequnce\n");
	getSequnce(sequnce2);
	showSequnce(sequnce2);

	result = (pSequnce)malloc(sizeof(Sequnce));
	result = computeConvolution(sequnce1, sequnce2);
	printf("the result is: \n");
	showSequnce(result);	
	
	clearSpace(sequnce1);
	clearSpace(sequnce2);
	clearSpace(result);
}

void getSequnce(pSequnce sequnce)
{
	int count;
	printf("the index of the sequnce: ");
	scanf("%d", &(sequnce->first_index));
	printf("the length of the sequnce: ");
	scanf("%d", &(sequnce->length));
	
	//malloc the space for the first sequnce
	sequnce->sequnce = (int*)malloc(sizeof(int) * sequnce->length);
	printf("please input the data of the sequnce: ");
	for(count=0; count<sequnce->length; count++)
	{
		scanf("%d", sequnce->sequnce+count);
	}
}

/*
 * format: first_index
 * data:   data1	data2 ...
 */
void showSequnce(pSequnce sequnce)
{
	int count;
	printf("index: ");
	for(count=0; count<sequnce->length; count++)
	{
		printf("%-5d",sequnce->first_index+ count); 
	}	

	printf("\ndata:  ");

	for(count=0; count<sequnce->length; count++)
	{
		printf("%-5d", *(sequnce->sequnce+count));
	}	
	
	printf("\n");
}

/*
 * clear the memory space 
 */
void clearSpace(pSequnce sequnce)
{
	free(sequnce->sequnce);
	free(sequnce);
}

/*
 * compute the convolution of sequnce1 and sequnce2
 */
pSequnce computeConvolution(pSequnce sequnce1, pSequnce sequnce2)
{
	int count, diff;
	pSequnce result = (pSequnce)malloc(sizeof(Sequnce));	

	//the length of reslut equals the first's length add the second's length minus one
	result->length = sequnce1->length + sequnce2->length -1;
	result->sequnce = (int*)malloc(sizeof(result->length));
	//the first index equals the first's add the second's
	result->first_index = sequnce1->first_index + sequnce2->first_index;
	//compute every point's value
	//step1 init the value
	for(count=0; count<result->length; count++)
	{
		*(result->sequnce+count) = 0;
	}
	//step2 revese the first sequnce
	reverse(sequnce1);
	
	shift(sequnce1, -(result->first_index));
	//diff = sequnce1->first_index;
	for(count=0; count<result->length; count++)
	{
		if(count==0)
		{
			shift(sequnce1, 0);
		}
		else
		{
			shift(sequnce1, -1);
		}
		//showSequnce(sequnce1);
		*(result->sequnce+count) = sumAtSamePoint(sequnce1, sequnce2);
	}
	//showSequnce(result);
	return result;
}


/*
 * reverse the sequnce
 */
void reverse(pSequnce sequnce)
{
	int count;
	//temp_array used to be store the data
	int* temp_array = (int*)malloc(sizeof(int)*sequnce->length);
	sequnce->first_index = -(sequnce->first_index + sequnce->length -1);
	for(count=0; count<sequnce->length; count++)
	{
		*(temp_array+count) = *(sequnce->sequnce+count);	
	}
	
	for(count=0; count<sequnce->length; count++)
	{
		*(sequnce->sequnce+count) = *(temp_array+sequnce->length-count-1);
	}
	free(temp_array);
}

/*
 * shift the sequnce
 */
void shift(pSequnce sequnce, int distance)
{
	sequnce->first_index = sequnce->first_index - distance;	
}

/*
 * sumAtSamePoint
 */
int sumAtSamePoint(pSequnce sequnce1, pSequnce sequnce2)
{
	int length, index1, index2, count, sum;
	int distance1, distance2;

	index1 = sequnce1->first_index > sequnce2->first_index ? sequnce1->first_index : sequnce2->first_index;
	index2 = sequnce1->first_index + sequnce1->length-1 < sequnce2->first_index + sequnce2->length-1 ? sequnce1->first_index + sequnce1->length-1 : sequnce2->first_index + sequnce2->length-1 ;

	sum = 0;
	length = index2 - index1 + 1;
	
	distance1 = index1-sequnce1->first_index;	
	distance2 = index1-sequnce2->first_index;	
	
	for(count=0; count<length; count++)
	{
		sum += *(sequnce1->sequnce+distance1+count) * *(sequnce2->sequnce+distance2+count);
	}
	return sum;
}

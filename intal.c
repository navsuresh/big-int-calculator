#include"intal.h"
#include<stdlib.h>
#include<string.h>



static void* remove_leading_zeroes(void* intal)
{
	int i;
	int count = 0;
	short int *arr = intal;
	if(arr[0] == 1)
		return arr;
	for(i = 1; i<=arr[0]; i++)
	{
		if(arr[i] != 0)
			break;
		else
			count++;
	}
	if(count == arr[0])
	{
		free(arr);
		short int *arr1 = (short int*)malloc(sizeof(short int)*2);
		arr1[0] = 1;
		arr1[1] = 0;
		return arr1;
	}
	short int *arr1 = (short int*)malloc(sizeof(short int)*(arr[0] - count + 1));
	for(i = count + 1; i<= arr[0]; i++)
	{
		arr1[i - count] = arr[i];
	}
	arr1[0] = arr[0] - count;
	free(arr);
	return arr1;
}

static void* add_leading_zeroes(void* intal, int n)
{
	short int *arr = intal;
	short int *arr1 = (short int *)malloc(sizeof(short int)*(arr[0] + n + 1));
	arr1[0] = arr[0] + n;
	int i;
	for(i = 1; i<=n; i++)
	{
		arr1[i] = 0;		
	}
	for(;i<=arr1[0]; i++)
	{
		arr1[i] = arr[i - n];
	}
	return arr1;
}

static void* left_shift(void* intal, int n)
{
	short int *arr = intal;
	short int *new_arr = (short int *)malloc(sizeof(short int)*(arr[0] + n + 1));
	new_arr[0] = arr[0] + n;
	int i;

	for(i = 1; i<=arr[0]; i++)
	{
		new_arr[i] = arr[i];		
	}
	
	for(;i<=new_arr[0]; i++)
	{
		new_arr[i] = 0;
	}
	return new_arr;
}

static void* term_splitter(void *intal, int mode) //mode == 1 =>first half, else (0) second half
{
	short int *arr = intal;
	short int *new_arr = NULL;
	int i;
	if(mode)
	{
		new_arr = (short int*)malloc((arr[0]/2 + 1)*sizeof(short int));
		new_arr[0] = arr[0]/2;
		for(i = 1; i<=arr[0]/2; i++)
		{
			new_arr[i] = arr[i];
		}
	}
	else
	{
		new_arr = (short int*)malloc((((arr[0]+1)/2)+1)*sizeof(short int));
		new_arr[0] = (arr[0] + 1)/2;
		for(i = 1; i<= new_arr[0]; i++)
		{
			new_arr[i] = arr[arr[0]/2 + i];
		}

	}
	return new_arr;
}

static void* copy_first_n(void* intal, int n)
{
	short int* arr1 = intal;
	short int* arr2 = (short int*)malloc(sizeof(short int)*(n+1));
	arr2[0] = n;
	int i;
	for(i = 1; i<=n; i++)
	{
		arr2[i] = arr1[i];
	}
	return arr2;
}

void* intal_create(const char* str)
{
	short int *arr = (short int *)malloc((strlen(str) + 1)*sizeof(short int));
	int i;
	arr[0] = strlen(str);
	for(i = 0; i < strlen(str); i++)
	{
		if(str[i] - 48 >=0 && str[i] - 48 <= 9)
			arr[i + 1] = str[i] - 48;
		else
		{
			free(arr);
			return NULL;
		}
	}
	if(arr[1]==0&&arr[0]!=1)
		return remove_leading_zeroes(arr);
	else
    	return arr;
}

char* intal2str(void* intal)
{
	if(intal == NULL)
	{
		char *print = (char *)malloc(sizeof(char)*4);
		print[0] = 'N';
		print[1] = 'a';
		print[2] = 'N';
		print[3] = '\0';
		return print;
	}
	short int *arr = intal;
	int i;
	char *print = (char *)malloc(sizeof(char)*(arr[0] + 1));
	for(i = 0; i < arr[0]; i++)
	{
		print[i] = arr[i+1] + 48;
	}
	print[i] = '\0';
	return print;
}


void intal_destroy(void* intal)
{
	if(intal!=NULL)
		free(intal);
}

void* intal_increment(void* intal)
{
	if(intal == NULL)
		return NULL;
	short int one[2] = {1,1};
	short int* res = intal_add(intal, one);
	free(intal);
	return res;
}

void* intal_decrement(void* intal)
{
	if(intal == NULL)
		return NULL;
	short int *arr = intal;
	if(arr[0] == 1 && arr[1] == 0)
		return arr;
	short int one[2] = {1,1};
	short int* res = intal_diff(intal, one);
	free(intal);
	return res;

}

void* intal_add(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL)
		return NULL;
		short int *arr1 = intal1;
	short int *arr2 = intal2;
	short int carry = 0;
	if(arr1[0]<arr2[0])
	{
		arr1 = intal2;
		arr2 = intal1;
	}
	
	int i;
	short int temp;
	short int *arr3 = (short int *)malloc(sizeof(short int)*(arr1[0]+1));
	arr3[0] = arr1[0];
	for(i = arr1[0]; i > arr1[0] - arr2[0]; i--)
	{
		temp = arr1[i] + arr2[i - (arr1[0]-arr2[0])];
		if(carry)
		{
			temp += 1;
			carry = 0;
		}
		if(temp>9)
		{
			arr3[i] = temp%10;
			carry = 1;
		}
		else
			arr3[i] = temp;

	}
	for(i = arr1[0] - arr2[0]; i>0; i--)
	{
		if(carry)
		{
			if(arr1[i] + 1 > 9)
			{
				carry = 1;
				arr3[i] = 0;
			}
			else 	
			{
				carry = 0;	
				arr3[i] = arr1[i] + 1;			
			}
		}
		else 
		{
			arr3[i] = arr1[i];
		}
	}
	if(carry)
	{
		short int *arr4 = (short int *)malloc((arr1[0] + 2)*sizeof(short int));
		for(i = arr3[0]; i>0;i--)
		{
			arr4[i+1] = arr3[i];
		}
		arr4[1] = 1;
		arr4[0] = arr3[0] + 1;
		free(arr3);
		if(arr4[1]==0 && arr4[0]!=1)
			return remove_leading_zeroes(arr4);
		else
			return arr4;
	}
	if(arr3[1]==0 && arr3[0]!=1)
		return remove_leading_zeroes(arr3);
	else return arr3;
}




int intal_compare(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL)
		return -2;
	short int *arr1 = intal1;
	short int *arr2 = intal2;
	if(arr1[0]!=arr2[0])
	{
		if(arr1[0]>arr2[0])
		{
			return 1;
		}
		else 
			return -1;
	}
	else
	{
		int i;
		for(i = 0; i<=arr1[0]; i++)
		{
			if(arr1[i]>arr2[i])
				return 1;
	
			else
				if(arr1[i]<arr2[i])
					return -1;

		}
		return 0;
	}
}

void* intal_diff(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL)
		return NULL;
	if(!intal_compare(intal1, intal2))
	{
		short int *arr3 = (short int*)malloc(2*sizeof(short int));
		arr3[0] = 1;
		arr3[1] = 0;
		return arr3;
	}
	short int *arr1 = (intal_compare(intal1, intal2) > 0) ? (intal1) : (intal2);
	short int *arr2 = (intal_compare(intal1, intal2) < 0) ? (intal1) : (intal2);
	int i;
	short int temp = 0;
	short int borrow = 0;
	short int *arr3 = (short int*)malloc(sizeof(short int)*(arr1[0] + 1));
	arr3[0] = arr1[0];
	int lim = arr1[0] - arr2[0];
	for(i = arr1[0]; i>lim; i--)
	{
		temp = arr1[i] - arr2[i - lim];

		if(borrow)
		{
			temp-=1;
			borrow = 0;
		}
		if(temp<0)
		{

			arr3[i] = temp+10;
			borrow = 1;
		}
		else
			arr3[i] = temp;
	}
	
	for(i = arr1[0] - arr2[0]; i>0; i--)
	{
		if(borrow)
		{
			if(arr1[i] == 0)
			{
				borrow = 1;
				arr3[i] = 9;;
			}
			else 	
			{
				borrow = 0;	
				arr3[i] = arr1[i] - 1;			
			}
		}
		else 
		{
			arr3[i] = arr1[i];
		}
	}
	if(arr3[1]==0 && arr3[0]!=1)
		return remove_leading_zeroes(arr3);
	else
		return arr3;
}


void* intal_multiply(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL)
		return NULL;

	short int *arr1 = intal1;
	short int *arr2 = intal2;
	
	short int *arr4 = NULL;
	int flag = 1;

	if(intal_compare(intal1, intal2) != 0)
	{
		if(intal_compare(intal1, intal2) == -1)
		{
			arr1 = intal2;
			arr2 = intal1;
		}
		if(arr1[0] - arr2[0] == 0)
		{
			flag = 0;
			arr4 = arr2;
		}
		else
			arr4 = add_leading_zeroes(arr2,arr1[0] - arr2[0]);

	}
	else
	{
		arr4 = arr2;
		flag = 0;
	}

	if(arr1[0] == 1)
	{
		short int product = arr1[1]*arr4[1];
		if(flag)
			free(arr4);
		if(product/10 == 0)
		{

			short int *arr3 = (short int*)malloc(sizeof(short int)*2);
			arr3[0] = 1;
			arr3[1] = product;
			return arr3;
		}
		else
		{
			short int *arr3 = (short int*)malloc(sizeof(short int)*3);
			arr3[0] = 2;
			arr3[1] = (product)/10;
			arr3[2] = (product)%10;
			return arr3;
		}
	}
	if(arr1[0] == 2)   //2nd base case to increase speed
	{
		long int op1 = arr1[2] + 10*arr1[1];
		long int op2 = arr4[2] + 10*arr4[1];
		long int product = op1*op2;


		if(flag)
			free(arr4);
		if(product/10 == 0)
		{

			short int *arr3 = (short int*)malloc(sizeof(short int)*2);
			arr3[0] = 1;
			arr3[1] = product;
			return arr3;
		}
		else
		{
			if(product/100 == 0)
			{
				short int *arr3 = (short int*)malloc(sizeof(short int)*3);
				arr3[0] = 2;
				arr3[1] = (product)/10;
				arr3[2] = (product)%10;
				return arr3;
			}
			else
			{
				if(product/1000 == 0)
				{
					short int *arr3 = (short int*)malloc(sizeof(short int)*4);
					arr3[0] = 3;
					arr3[3] = (product)%10;
					product /=10;
					arr3[2] = (product)%10;
					arr3[1] = (product)/10;
					
					return arr3;
				}
				else
				{
					short int *arr3 = (short int*)malloc(sizeof(short int)*5);
					arr3[0] = 4;
					arr3[4] = (product)%10;
					product /=10;
					arr3[3] = (product)%10;
					product/=10;
					arr3[2] = (product)%10;
					arr3[1] = (product)/10;
					
					return arr3;

				}
				

			}
		}
	}
	
	if(arr1[0] == 3)   //3rd base case to increase speed
	{
		long int op1 = arr1[3] + 10*arr1[2] + 100*arr1[1];
		long int op2 = arr4[3] + 10*arr4[2] + 100*arr4[1];
		long int product = op1*op2;
		if(flag)
			free(arr4);
		if(product/10 == 0)
		{

			short int *arr3 = (short int*)malloc(sizeof(short int)*2);
			arr3[0] = 1;
			arr3[1] = product;
			return arr3;
		}
		else
		{
			if(product/100 == 0)
			{
				short int *arr3 = (short int*)malloc(sizeof(short int)*3);
				arr3[0] = 2;
				arr3[1] = (product)/10;
				arr3[2] = (product)%10;
				return arr3;
			}
			else
			{
				if(product/1000 == 0)
				{
					short int *arr3 = (short int*)malloc(sizeof(short int)*4);
					arr3[0] = 3;
					arr3[3] = (product)%10;
					product /=10;
					arr3[2] = (product)%10;
					arr3[1] = (product)/10;
					
					return arr3;
				}
				else
				{
					if(product/10000 == 0)
					{
						short int *arr3 = (short int*)malloc(sizeof(short int)*5);
						arr3[0] = 4;
						arr3[4] = (product)%10;
						product /=10;
						arr3[3] = (product)%10;
						product/=10;
						arr3[2] = (product)%10;
						arr3[1] = (product)/10;
						
						return arr3;
					}
					else 
					{
						if(product/100000 == 0)
						{
							short int *arr3 = (short int*)malloc(sizeof(short int)*6);
							arr3[0] = 5;
							arr3[5] = (product)%10;
							product /=10;
							arr3[4] = (product)%10;
							product/=10;
							arr3[3] = (product)%10;
							product /=10;
							arr3[2] = (product)%10;
							arr3[1] = (product)/10;
							
							return arr3;
						}
						else
						{
							short int *arr3 = (short int*)malloc(sizeof(short int)*7);
							arr3[0] = 6;
							arr3[6] = (product)%10;
							product /=10;
							arr3[5] = (product)%10;
							product/=10;
							arr3[4] = (product)%10;
							product /=10;
							arr3[3] = (product)%10;
							product /=10;
							arr3[2] = (product)%10;
							arr3[1] = (product)/10;
							
							return arr3;
						}
					}



				}
				

			}
		}
	}


	

	if(arr1[0] == 4)   //4th base case to increase speed
	{
		long int op1 = arr1[4] + 10*arr1[3] + 100*arr1[2] + 1000*arr1[1];
		long int op2 = arr4[4] + 10*arr4[3] + 100*arr4[2] + 1000*arr4[1];
		long int product = op1*op2;
		if(flag)
			free(arr4);
		if(product/10 == 0)
		{

			short int *arr3 = (short int*)malloc(sizeof(short int)*2);
			arr3[0] = 1;
			arr3[1] = product;
			return arr3;
		}
		else
		{
			if(product/100 == 0)
			{
				short int *arr3 = (short int*)malloc(sizeof(short int)*3);
				arr3[0] = 2;
				arr3[1] = (product)/10;
				arr3[2] = (product)%10;
				return arr3;
			}
			else
			{
				if(product/1000 == 0)
				{
					short int *arr3 = (short int*)malloc(sizeof(short int)*4);
					arr3[0] = 3;
					arr3[3] = (product)%10;
					product /=10;
					arr3[2] = (product)%10;
					arr3[1] = (product)/10;
					
					return arr3;
				}
				else
				{
					if(product/10000 == 0)
					{
						short int *arr3 = (short int*)malloc(sizeof(short int)*5);
						arr3[0] = 4;
						arr3[4] = (product)%10;
						product /=10;
						arr3[3] = (product)%10;
						product/=10;
						arr3[2] = (product)%10;
						arr3[1] = (product)/10;
						
						return arr3;
					}
					else 
					{
						if(product/100000 == 0)
						{
							short int *arr3 = (short int*)malloc(sizeof(short int)*6);
							arr3[0] = 5;
							arr3[5] = (product)%10;
							product /=10;
							arr3[4] = (product)%10;
							product/=10;
							arr3[3] = (product)%10;
							product /=10;
							arr3[2] = (product)%10;
							arr3[1] = (product)/10;
							
							return arr3;
						}
						else
						{
							if(product/1000000 == 0)
							{
								short int *arr3 = (short int*)malloc(sizeof(short int)*7);
								arr3[0] = 6;
								arr3[6] = (product)%10;
								product /=10;
								arr3[5] = (product)%10;
								product/=10;
								arr3[4] = (product)%10;
								product /=10;
								arr3[3] = (product)%10;
								product /=10;
								arr3[2] = (product)%10;
								arr3[1] = (product)/10;
								
								return arr3;
							}
							else
							{
								if(product/10000000 == 0)
								{
									
									short int *arr3 = (short int*)malloc(sizeof(short int)*8);
									arr3[0] = 7;
									arr3[7] = (product)%10;
									product /=10;
									arr3[6] = (product)%10;
									product/=10;
									arr3[5] = (product)%10;
									product /=10;
									arr3[4] = (product)%10;
									product /=10;
									arr3[3] = (product)%10;
									product /=10;
									arr3[2] = (product)%10;
									arr3[1] = (product)/10;
									
									return arr3;
								}
								else
								{
									
									short int *arr3 = (short int*)malloc(sizeof(short int)*9);
									arr3[0] = 8;
									arr3[8] = (product)%10;
									product /=10;
									arr3[7] = (product)%10;
									product/=10;
									arr3[6] = (product)%10;
									product /=10;
									arr3[5] = (product)%10;
									product /=10;
									arr3[4] = (product)%10;
									product /=10;
									arr3[3] = (product)%10;
									product /= 10;
									arr3[2] = (product)%10;
									arr3[1] = (product)/10;
									
									return arr3;
								}

							}
						}
					}

				}
				
			}
		}
	}

	short int *lfh = term_splitter(arr1, 1); //longer first half...
	short int *lsh = term_splitter(arr1, 0);
	short int *sfh = term_splitter(arr4, 1);
	short int *ssh = term_splitter(arr4, 0);
	if(flag)
		free(arr4);

	short int *p1 =  intal_multiply(lfh, sfh);
	short int *p2 = intal_multiply(lsh, ssh);	
	short int *temp2 = intal_add(lfh, lsh);
	short int *temp3 = intal_add(sfh, ssh);
	free(lfh);
	free(sfh);
	free(lsh);
	free(ssh);
	short int *p3 = intal_multiply(temp2, temp3);
	free(temp2);
	free(temp3);
	short int *temp4 = intal_diff(p3,p1);
	short int *pf1 = left_shift(p1, ((arr1[0]+1)/2)*2 );
	free(p1);
	free(p3);
	short int *temp1 = intal_diff(temp4, p2);
	free(temp4);
	short int *pf2 = left_shift(temp1,(arr1[0]+1)/2);
	free(temp1);
	short int *temp5 = intal_add(pf1,pf2);
	free(pf1);
	free(pf2);
	short int *res = intal_add(temp5, p2);
	free(p2);
	free(temp5);
	return res;	
}


void* intal_divide(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL)
		return NULL;
	short int* arr1 = intal1;
	short int* arr2 = intal2;
	if(arr2[0] == 1 && arr2[1] == 0)
		return NULL;

	if(intal_compare(arr1, arr2)<0)
	{
		short int* zero = (short int*)malloc(sizeof(short int)*2);
		zero[0] = 1;
		zero[1] = 0;
		return zero;
	}

	
	
	short int* quotient = (short int*)malloc(sizeof(short int));
	quotient[0] = 0;

	short int* temp_dividend = copy_first_n(arr1, arr2[0]);
	int i = arr2[0];
	int flag = 0;
	while(i<=arr1[0])
	{
		while(intal_compare(temp_dividend, arr2)<0)
		{
			if(i == arr1[0])
			{
				quotient = (short int*)realloc(quotient, sizeof(short int)*(quotient[0]+2));
				quotient[0]++;
				quotient[quotient[0]] = 0;
				flag = 1;
				break;
			}
			if(arr1[i+1] != 0)
			{
				temp_dividend = (short int*)realloc(temp_dividend, sizeof(short int)*(temp_dividend[0]+2));
				temp_dividend[0]+=1;
				temp_dividend[temp_dividend[0]] = arr1[++i];
			}
			else
			{
				if(temp_dividend[1] != 0)
				{
				temp_dividend = (short int*)realloc(temp_dividend, (temp_dividend[0]+2)*sizeof(short int));
				temp_dividend[0]++;
				temp_dividend[temp_dividend[0]] = arr1[++i]; 
				temp_dividend = remove_leading_zeroes(temp_dividend);

				}
				else
					i++;
			}
			quotient = (short int*)realloc(quotient, sizeof(short int)*(quotient[0]+2));
			quotient[0]++;
			quotient[quotient[0]] = 0;
		}
		if(flag)
			break;
		int j;

		short int* prod = (short int*)malloc(sizeof(short int)*2);
		prod[0] = 1;
		prod[1] = 0;
		short int* prod1=NULL;
		for (j = 1; j<10; j++)
		{
			prod1 = copy_first_n(prod,prod[0]);
			free(prod);
			prod = intal_add(prod1, arr2);
			free(prod1);
			if(intal_compare(prod, temp_dividend)<=0)
			{
				if(intal_compare(prod, temp_dividend) == 0)
				{
					quotient = (short int*)realloc(quotient, sizeof(short int)*(quotient[0]+2));
					quotient[0]++;
					quotient[quotient[0]] = j;
					free(temp_dividend);
					temp_dividend = (short int*)malloc(sizeof(short int)*2);
					temp_dividend[0] = 1;
					temp_dividend[1] = 0;
					break;
				}
				short int* diff = intal_diff(temp_dividend, prod);
				if(intal_compare(diff, arr2)<0)
				{
					quotient = (short int*)realloc(quotient, sizeof(short int)*(quotient[0]+2));
					quotient[0]++;
					quotient[quotient[0]] = j;
					free(temp_dividend);
					temp_dividend = diff;
					break;
				}
					free(diff);
			}
		}
		free(prod);
	
		if(i!=arr1[0])
		{
			if(arr1[i+1]!=0)
			{
				temp_dividend = (short int*)realloc(temp_dividend, (temp_dividend[0]+2)*sizeof(short int));
				temp_dividend[0]++;
				temp_dividend[temp_dividend[0]] = arr1[++i]; 
				temp_dividend = remove_leading_zeroes(temp_dividend);
			}
			else
			{
				if(temp_dividend[1] != 0)
				{
				temp_dividend = (short int*)realloc(temp_dividend, (temp_dividend[0]+2)*sizeof(short int));
				temp_dividend[0]++;
				temp_dividend[temp_dividend[0]] = arr1[++i]; 
				temp_dividend = remove_leading_zeroes(temp_dividend);

				}
				else
					i++;
			}

		}
		else
			break;


	}
	free(temp_dividend);
	if(quotient[1]==0 && quotient[0]!=1)
		return remove_leading_zeroes(quotient);
	else
		return quotient;
}

void* intal_pow(void* intal1, void* intal2)
{
	if(intal1 == NULL || intal2 == NULL)
		return NULL;
	short int* arr1 = intal1;
	short int* arr2 = intal2;
	if(arr1[0] == 1 && arr1[1] == 0)
	{
		short int* zero = (short int*)malloc(sizeof(short int)*2);
		zero[0] = 1;
		zero[1] = 0;
		return zero;
	}
	if(arr2[0] == 1 && arr2[1] == 0)
	{
		short int* one = (short int*)malloc(sizeof(short int)*2);
		one[0] = 1;
		one[1] = 1;
		return one;
	}
	
	short int* two = (short int*)malloc(sizeof(short int)*2);
	two[0] = 1;
	two[1] = 2;
	
	if(arr2[arr2[0]]%2 == 0)
	{
		short int* arr2by2 = intal_divide(arr2, two);
		short int* powby2 = intal_pow(arr1, arr2by2);
		free(arr2by2);
		short int* res = intal_multiply(powby2, powby2);
		free(powby2);
		return res;
	}
	else
	{
		short int* arr2by2 = intal_divide(arr2, two);
		short int* powby2 = intal_pow(arr1, arr2by2);
		free(arr2by2);
		short int* res1 = intal_multiply(powby2, powby2);
		free(powby2);
		short int* res = intal_multiply(res1, arr1);
		free(res1);
		return res;

	}


}
#include<stdlib.h>
#include<stdio.h>

//¥Ú”° ˝◊È
void PrintArr(int* MyArr)
{
	for (int i = 0; i < 10; i++)
	{
		printf("%d",MyArr[i]);
	}
	printf("\n");
}

//√∞≈›≈≈–Ú
void BubbleSort(int * MyArr)
{
	for (int i = 0; i < 10-1; i++)
	{
		for (int j = 0; j < 10-i-1; j++)
		{
			if (MyArr[j] > MyArr[j+1])
			{
				int temp = MyArr[j+1];
				MyArr[j+1] = MyArr[j];
				MyArr[j] = temp;
			}
		}
	}
}

//—°‘Ò≈≈–Ú
void Select_Sort(int * MyArr)
{
	int min;
	for (int i = 0; i < 10; i++)
	{
		min = i;
		for (int j = i+1; j < 10  ; j++)
		{
			if (MyArr[min] > MyArr[j ])
			{
				min = j;
			}
		}
		if (min != i)
		{
			int temp = MyArr[i];
			MyArr[i] = MyArr[min];
			MyArr[min] = temp;
		}
	}
}

//≤Â»Î≈≈–Ú
void Insert_Sort(int* MyArr)
{
	for (int i = 1; i < 10; i++)
	{
		for (int j = i ; j > 0; j--)
		{
			if (MyArr[j] < MyArr[j-1])
			{
				int temp = MyArr[j];
				MyArr[j] = MyArr[j-1];
				MyArr[j-1] = temp;
			}
		}		
	}
}


int main()
{
	int arr[10] = { 3,9,1,4,6,7,8,2,5,10 };
	//BubbleSort(arr);
	//Select_Sort(arr);
	Insert_Sort(arr);
	PrintArr(arr);
	system("pause");
	return 0;
}
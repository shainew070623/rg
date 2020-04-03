#include<stdio.h>
int main()
{
	int arr[50];
	int n, i;
	scanf_s("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf_s("%d", &arr[i]);
	}
	int maxSum = arr[0];
	int curSum = arr[0];
	for (i = 1; i < n; i++)
	{
		if (curSum <= 0)
		{
			curSum = arr[i];
		}
		else
		{
			curSum += arr[i];
		}
		if (curSum > maxSum)
		{
			maxSum = curSum;
		}
	}
	printf("%d", maxSum);
}
#include<iostream>
using namespace std;

/*插入排序，只要有比较，就有移动*/
void insert_older(int arr[],size_t len)
{
	if(len <= 1)
	{
		return;
	}
	
	for(int index = 1;index < len;++index)
	{
		int values = arr[index];
		int  head = index - 1;
		while(head >= 0 && arr[head] > values)
		{
			arr[head + 1] = arr[head];
			--head;
		}
		arr[head + 1] = values;
	}
}


/*二分查找*/
size_t binary_find(int arr[],size_t first,size_t last,int values)
{
	if(first < last)
	{
		size_t middle = (first + last)/2;
		if(arr[middle] == values)
		{
			return middle;			
		}
		if(arr[middle] < values)
		{
			binary_find(arr,middle + 1,last,values);
		}			
		else
		{
			binary_find(arr,first,middle,values);
		}
	}
	else
	{
		return first;
	}
}
	
		

/*选择排序,减少移动操作*/
void select_older(int arr[],size_t len)
{
	if(len <= 1)
	{
		return;
	}
	
	for(int index = 0;index < len - 1;++index)
	{
		int lessIndex = index;
		int  next = index + 1;
		
		while(next < len)
		{
			if(arr[next] < arr[lessIndex])
			{
				lessIndex = next;
			}
			++next;			
		}
		
		int temp = arr[index];
		arr[index] = arr[lessIndex];
		arr[lessIndex] = temp;
	}
}

/*归并辅助函数*/
void asist_merge_sort(int arr[],size_t first,size_t middle,size_t last,int temp[])
{
	size_t head = first,next = middle + 1,tempIndex = 0;
	while(head <= middle && next <= last)
	{
		if(arr[head] <= arr[next])
		{
			temp[tempIndex] = arr[head];
			++tempIndex;
			++head;
		}
		else
		{
			temp[tempIndex] = arr[next];
			++tempIndex;
			++next;
		}
	}
	
	while(head <= middle)
	{
		temp[tempIndex] = arr[head];
		++tempIndex;
		++head;
	}
	
	while(next <= last)
	{
		temp[tempIndex] = arr[next];
		++tempIndex;
		++next;
	}
	
	for(head = first,tempIndex = 0;head <= last;++head,++tempIndex)
	{
		arr[head] = temp[tempIndex];
	}
}


/*归并辅助函数(用插入排序实现)*/
void asist_merge_sort_by_insert_sort(int arr[],size_t first,size_t last)
{
	if(last - first == 0)
	{
		return;
	}
	
	size_t head = first + 1;
	while(head <= last)
	{
		int values = arr[head];
		int index = head - 1;
		while(index >= first && arr[index] > values)
		{
			arr[index + 1] = arr[index];
			--index;
		}
		arr[index + 1] = values;
		++head;
	}
}


/*归并排序通过插入排序来实现*/
void merge_sort_by_insert_sort(int arr[],size_t first,size_t last)
{
	if(first < last)
	{
		size_t middle = (first + last)/2;
		merge_sort_by_insert_sort(arr,first,middle);
		merge_sort_by_insert_sort(arr,middle + 1,last);
		asist_merge_sort_by_insert_sort(arr,first,last);
	}
}


/*归并排序，归并，插入并用*/
void merge_sort_by_insert_sort_together(int arr[],size_t first,size_t last,int temp[])
{
	if(first < last)
	{
		size_t middle = (first + last)/2;
		merge_sort_by_insert_sort_together(arr,first,middle,temp);
		merge_sort_by_insert_sort_together(arr,middle + 1,last,temp);
		
		//n*(n-1)/2 < 2n
		if(last - first < 5)
		{
			asist_merge_sort_by_insert_sort(arr,first,last);
		}
		else
		{
			asist_merge_sort(arr,first,middle,last,temp);
		}
	}
}



/*归并排序*/
void merge_sort(int arr[],size_t first,size_t last,int temp[])
{
	if(first < last)
	{
		size_t middle = (first + last)/2;
		merge_sort(arr,first,middle,temp);
		merge_sort(arr,middle + 1,last,temp);
		asist_merge_sort(arr,first,middle,last,temp);
	}
}

/*冒泡排序*/
void buble_sort(int arr[],size_t len)
{
	if(len <= 1)
	{
		return;
	}
	
	for(size_t now = 0;now < len;++now)
	{
		for(size_t next = now + 1;next < len;++next)
		{
			if(arr[now] > arr[next])
			{
				int temp = arr[now];
				arr[now] = arr[next];
				arr[next] = temp;
			}
		}
	}
}

int main(void)
{
	int a[] = {5,3,2,6,7};
	int temp[5];
	buble_sort(a,sizeof(a)/sizeof(a[0]));
	for(int index = 0;index < sizeof(a)/sizeof(a[0]);++index)
	{
		cout<<"index:"<<index<<" values:"<<a[index]<<endl;
	}
	
	return 1;
}

#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;

int partition(int *a, int lb, int ub, int k, bool *hmap)
{
	/*cout<<endl<<"got array :";
	for(int i=lb;i<=ub;i++)
		cout<<a[i]<<' ';
	cout<<endl;*/

	srand(time(0));
	//cout<<"partition called for "<<lb<<' '<<ub<<endl;
	int pivot_ind = rand()%(ub-lb+1) + lb;
	//cout<<"pivot index "<<pivot_ind<<endl;
	int temp = a[pivot_ind];
	a[pivot_ind] = a[ub];
	a[ub] = temp;

	/*cout<<endl<<"partial array :";
	for(int i=lb;i<=ub;i++)
		cout<<a[i]<<' ';
	cout<<endl;*/

	int pivot = a[ub];

	int i, j;
	for(i=lb, j=ub-1; i<=j;)
	{
		if(a[i] > pivot)
		{
			//cout<<"swapping "<<a[i]<<' '<<a[j]<<endl;
			temp = a[i];
			a[i] = a[j];
			a[j] = temp;
			--j;

			/*cout<<endl<<"partial array during:";
			for(int lv=lb;lv<=ub;lv++)
				cout<<a[lv]<<' ';
			cout<<endl;*/
		}
		else
		{
			++i;
		}
	}

	j += 1;
	temp = a[ub];
	a[ub] = a[j];
	a[j] = temp;

	hmap[j] = true;

	/*cout<<endl<<"partial array after partition:";
	for(i=lb;i<=ub;i++)
		cout<<a[i]<<' ';
	cout<<endl;*/

	if(j == k)
	{
		//hmap[k] = true;
		return a[j];
	}

	else
	{
		if(k < j)
			return partition(a, lb, j-1, k, hmap);
		else
			return partition(a, j+1, ub, k, hmap);
	}


}

int quicksort(int *arr, int n, int k, bool *hmap)
{
	int lb, ub;
	for(lb=k; lb >-1; lb--)
		if(hmap[lb] == true)
			break;

	for(ub=k; ub < n; ub++)
		if(hmap[ub] == true)
			break;

	/*if(lb+2 == ub)
	{
		hmap[lb+1] = true;
		return arr[lb+1];
	}*/
	int ans = partition(arr, lb+1, ub-1, k, hmap);

}

int main()
{
	int n, lv, quer, k;
	clock_t start, end;
	double tc=0, ts=0, stc = 0, sts = 0;
	cout<<"Number of elements :";
	cin>>n;
	int arr[n] ;   //1 3 4 5 6 8 9
	int barr[n];
	//n = 7;
	bool hashmap[n];
	memset(hashmap, 0, sizeof(bool)*n);
	cout<<"\nEnter elements :";
	for(lv=0;lv<n;lv++)
	{
		cin>>arr[lv];
		barr[lv] = arr[lv];
	}

	cout<<"\nEnter number of queries :";
	cin>>quer;
	int q = quer;

	while(quer--)
	{
		cout<<"\nEnter value of k :";
		cin>>k;
		start = clock();
		cout<<"nth smallest is :";
		if(hashmap[k-1] == true)
			cout<<arr[k-1];

		else
		{
			cout<<quicksort(arr, n, k-1, hashmap);
		}
		end = clock();
		tc = double(end-start)/CLOCKS_PER_SEC;
		cout<<"\nTime taken by custom function :"<<double(tc);
		stc += tc;
		cout<<"\n\ncalling std::nth element\n";
		start = clock();
		nth_element(&barr[0], &barr[k-1], &barr[n-1]);
		cout<<"nth smallest is :"<<barr[k-1]<<endl;
		end = clock();
		ts = double(end-start)/CLOCKS_PER_SEC;
		cout<<"Time taken by std::nth_element function :"<<double(ts);
		sts += ts;
		cout<<endl<<endl;

	}

	cout<<"\n\nAvg time per query of\n";
	cout<<"custom function :"<<(double)stc/q;
	cout<<"\nstandard function :"<<double(sts/q)<<endl;
}
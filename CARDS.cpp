#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


bool isGood(vector<int>&c)
{
	int sum = c[0];

	for(int i=1;i<(int)c.size();i++)
	{
		if(c[i] > 0 && i>sum)
		{
			//cout<<i<<" ddd "<<sum<<endl;
			return false;
		}
		sum+=c[i];
	}
	return true;
}

int main()
{
	int t;
	cin>>t;
	while(t-->0)
	{
		int n;
		cin>>n;
		vector<int>a(n);
		vector<int>c(n+1);
		for(int i=0;i<n;i++)
		{
			cin>>a[i];
			c[a[i]]++;
		}

		if(!isGood(c))
		{
			cout<<"0"<<endl;
			continue;
		}
		sort(a.begin(),a.end());
		for(int i=0;i<n;i++)
		{
			a[i] = n - a[i];
		}

		for(int i=0;i<n;i++)
		{
			a[n-1-i] -=i;
		}

		const int MOD = 1000000007;
		long long prod = 1;
		for(int i=0;i<n;i++)
		{
			prod = prod * a[i];
			prod%=MOD;
		}
		cout<<prod<<endl;
	}

	return 0;
}

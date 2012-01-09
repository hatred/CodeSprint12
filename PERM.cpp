#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
using namespace std;


bool isSorted(vector<int>& a)
{
	for(int i=0;i<(int)a.size()-1;i++)
	{
		if(a[i]>a[i+1])
			return false;
	}
	return true;
}

bool isDecr(vector<int>&a)
{
	for(int i=0;i<(int)a.size()-1;i++)
	{
		if(a[i]<a[i+1])
			return false;
	}

	return true;
}

map<pair<vector<int>,bool>,bool>dp;
bool solve(vector<int>a,bool turn)
{
	pair<vector<int>,bool> p = make_pair(a,turn);
	if(dp.find(p) != dp.end())
		return dp[p];
	pair<vector<int>,bool> np = make_pair(a,1-turn);
	if(dp.find(np) != dp.end())
		return 1-dp[np];
	if(turn == 1 && isSorted(a))
		return true;
	if(turn == 0 && isSorted(a))
		return false;
	
	if(turn == 0 && isDecr(a))
	{
		if((int)a.size()%2==0)
			return true;
		else
			return false;
	}
	if(turn == 1 && isDecr(a))
	{
		if((int)a.size()%2==0)
			return false;
		else
			return true;
	}

	bool willWin = false;
	bool willLoose = true;
	for(int i=0;i<(int)a.size();i++)
	{
		vector<int>b;
		for(int j=0;j<(int)a.size();j++)
		{
			if(j==i)
				continue;
			b.push_back(a[j]);
		}
	
		bool t = solve(b,1-turn);
	//	for(int j=0;j<(int)b.size();j++)
	//	{
	//		cout<<b[j]<<" ";
	//	}
	//	cout<<endl;
	//	cout<<"Turn now is of "<<1-turn<<" "<<t<<endl;
		willWin |= t;
		if(turn == 0 && willWin)
			break;
		willLoose &= t;
		if(turn==1 && !willLoose)
			break;
	}

	dp[p] = turn == 0 ? willWin : willLoose;
	dp[np] = 1 - dp[p];
	return turn == 0 ? willWin : willLoose;
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

		for(int i=0;i<n;i++)
		{
			cin>>a[i];
		}

		if(solve(a,0))
			cout<<"Alice"<<endl;
		else	
			cout<<"Bob"<<endl;
	}

	return 0;
}
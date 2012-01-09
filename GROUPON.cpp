#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<sstream>

using namespace std;

struct orders{
	string oid; // order id
	string did; // deal id
	string email; // email
	string stadd; // street address
	string city;
	string state;
	string zipcode;
	string cno;
};

string toString(int n)
{
	stringstream s1;
	s1<<n;
	return s1.str();
}

orders make_order(string& oid,string& did,string& email,string& stadd,string& city,string& state,string& zipcode, string& cno)
{
	orders order;

	order.oid = oid;
	order.did = did;
	order.email = email;
	order.stadd = stadd;
	order.city = city;
	order.state = state;
	order.zipcode = zipcode;
	order.cno = cno;

	return order;
}

string parsemail(string& s)
{
	for(int i=0;i<(int)s.length();i++)
	{
		s[i] = tolower(s[i]);
	}

	string retVal;
	bool ignoreDot = true;
	for(int i=0;i<(int)s.length();i++)
	{
		if(s[i]=='.' && ignoreDot)
			continue;
		if(s[i] == '@')
			ignoreDot = false;
		if(s[i]=='+')
		{
			int index = i;
			while(s[index]!='@')
			{
				index++;
			}
			index--;
			i = index;
			continue;
		}
		retVal+=s[i];
	}
	//cout<<retVal<<endl;
	return retVal;
}

string parseadd(string& s)
{
	for(int i=0;i<(int)s.length();i++)
	{
		s[i] = tolower(s[i]);
	}
	string abbr[] = {"st.","rd."};
	string fullname[] = {"street","road"};

	for(int i=0;i<2;i++)
	{
		string orig = abbr[i];
		string rep = fullname[i];
		
		int newfinder = 0;
		while(true)
		{
			int finder = s.find(orig,newfinder);
			if(finder==string::npos)
				break;
//			if(finder+(int)orig.length()>=(int)s.length() || (finder+(int)orig.length() <(int)s.length() && s[finder+(int)orig.length()] == ' '))
//			{
//				if(finder-1>0 && s[finder-1]!=' ')
//			{
//				}
//				else
			if(finder + (int)rep.length()  <= (int)s.length())
			{
				if(s.substr(finder,(int)rep.length()) == rep)
				{
					newfinder = finder + 2;
					continue;
				}
			}
					s = s.substr(0,finder) + rep + s.substr(finder+orig.length(),(int)s.length()-finder-orig.length());
			//	s.replace(finder,finder+(int)orig.length(),rep);
//			}
			newfinder = finder + 2;
			//cout<<s<<endl;
		}
	}
	//cout<<s<<endl;
	return s;
}

string parseState(string& s)
{
	for(int i=0;i<(int)s.length();i++)
	{
		s[i] = tolower(s[i]);
	}

	string st[] = {"il","ca","ny"};
	string stU[] = {"illinois","california","new york"};
	for(int i=0;i<3;i++)
	{
		if(s==st[i])
			s = stU[i];
	}
	//cout<<s<<endl;
	return s;
}

orders parse(string& s)
{
	vector<string>a(8);

	int index = 0;
	int finder = 0;
	while(true)
	{
		int nextFind = s.find(",",finder);
		if(nextFind == string::npos)
			break;
		a[index++] = s.substr(finder,nextFind-finder);
		finder = nextFind+1;
		//cout<<a[index-1]<<" ddd "<<endl;
	}

	a[index] = s.substr(finder,(int)s.length()-finder);
	
	//for(int i=0;i<(int)a.size();i++)
//	{
//		cout<<a[i]<<" ";
//	}
//	cout<<endl;
	string email = parsemail(a[2]);
	string stadd = parseadd(a[3]);
	string state = parseState(a[5]);
	return make_order(a[0],a[1],email,stadd,a[4],state,a[6],a[7]);
}

int toInt(string& s)
{
	stringstream s1;
	s1<<s;
	int n;
	s1>>n;
	return n;
}

string toLower(string s)
{
	for(int i=0;i<(int)s.length();i++)
		s[i] = tolower(s[i]);
	return s;
}

int main()
{
	int n;
	cin>>n;
	string s;

	getline(cin,s);
	set<int>ans;

	/* make two maps one for rule 1 and the other for rule2*/

	map<string, pair<string,string> > p;
	map<string, pair<string,string> > q;
	for(int i=0;i<n;i++)
	{
		getline(cin,s);
		orders o = parse(s);
		string addDid = toLower(o.email + "// " + o.did);
		string card = o.cno;
		if(p.find(addDid) != p.end())
		{
			string c = p[addDid].second;
	
			if(c!=card)
			{
				ans.insert(toInt(o.oid));
				ans.insert(toInt(p[addDid].first));
			}
		}
		else
		{
			p.insert(make_pair(addDid,make_pair(o.oid,o.cno)));
		}

		// rule 2
		string addDid2 = toLower(o.stadd + "// " + o.city + "// " + o.state + "// " + o.zipcode + "// " + o.did);
		if(q.find(addDid2) != q.end())
		{
			string c = q[addDid2].second;
			if(c!=card)
			{
				ans.insert(toInt(o.oid));
				ans.insert(toInt(q[addDid2].first));
			}
		}
		else
		{
			q.insert(make_pair(addDid2, make_pair(o.oid,o.cno)));
		}
	}
	
	set<int>::iterator it;

	string retVal;
	for(it = ans.begin(); it!=ans.end();it++)
	{
		retVal = retVal + toString(*it) + ",";
	}
	if((int)retVal.length()>=1)
		retVal.erase((int)retVal.length()-1,1);
	cout<<retVal<<endl;
	
	return 0;
}

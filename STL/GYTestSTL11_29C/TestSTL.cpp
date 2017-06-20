#include<list>
#include<iostream>

using namespace std;

//#include"yhp_vector.h"

template<class Con>
void Print(Con &c)
{
	typename Con::iterator it = c.begin();
	cout<<typeid(it).name()<<endl;
	for(; it != c.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
}
void main()
{
	int ar[] = {12, 10, 23, 20, 33, 44, 55, 53};
	list<int> mylist(ar, ar+8);
	mylist.sort();
	Print(mylist);
	//yhp::vector<int> mylist(10,23);
	//Print(mylist);
	////cout<<typeid(yhp::vecotr<int>::iterator).name()<<end;

}
/*
#include"yhp_list.h"
void main()
{
	int ar[]={12,23,34,45,56,67,78,89,90,100};
	int n = sizeof(ar)/sizeof(ar[0]);
	yhp::list<int> mylist;
	yhp::list<int> youlist;

	youlist.insert(youlist.end(),ar,ar+n);
	mylist.insert(mylist.begin(),youlist.begin(),youlist.end());
	yhp::list<int>::iterator it = mylist.begin();
	for(;it != mylist.end(); ++it)
	{
		cout<<*it<<" ";
	}
	cout<<endl;
	int x = 0;
	int y = int();

}
*/
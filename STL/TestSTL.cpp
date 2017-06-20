
#include<iostream>

using namespace std;

#include"yhp_vector.h"
#include"yhp_list.h"
class Test
{
private:
	int value;
public:
	Test(int x=0):value(x) {}
	~Test(){ cout<<"Destroy Test"<<this<<endl;}
};
template<>
struct yhp::__type_traits<Test>
{
	//__type_traits() {}
    typedef __false_type has_trivial_default_constructor;
	typedef __true_type has_trivial_copy_constructor;
	typedef __true_type has_trivial_assignment_operator;
	typedef __false_type has_trivial_destructor;
	typedef __true_type is_POD_type;//???
};

void main()
{
	Test t1;
	yhp::list<Test> tlist(10,t1);
	tlist.clear();
}

/*
void main()
{
	int ar[10]={12,23,34,45,56,67,78,89,90,100};
	yhp::list<int> mylist(ar,ar+10);
	yhp::list<int>::iterator F = mylist.begin();
	yhp::list<int>::iterator L = mylist.end();
	int n = yhp::distance(F,L);
	cout<<n<<endl;
	n = yhp::distance(ar,ar+5);
}
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
	yhp::vector<int> mylist(10,23);
	Print(mylist);
	//cout<<typeid(yhp::vecotr<int>::iterator).name()<<end;

}

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
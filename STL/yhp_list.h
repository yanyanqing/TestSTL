
#include<malloc.h> // mempool // new 

#ifndef YHP_LIST_H
#define YHP_LIST_H
#include"yhp_iterator.h"
#include"yhp_construct.h"
namespace yhp
{

template<class _Ty>
void swap(_Ty &a, _Ty &b)
{
	_Ty c = a;
	a = b;
	b = c;
}
template<class _Ty>
class list
{
protected:
	struct _Node;
	typedef struct _Node * _Nodeptr;
	struct _Node
	{
		_Nodeptr _Prev,_Next;
		_Ty      _Value;
	};
	struct _Acc;
	struct _Acc
	{
		 typedef struct _Node *& _Nodepref;
		 typedef _Ty          &  _Vref;
		 static _Nodepref _Prev(_Nodeptr _P)
		 {
			 return (*_P)._Prev;
		 }
		 static _Nodepref _Next(_Nodeptr _P)
		 {
			 return (*_P)._Next;
		 }
		 static _Vref _Value(_Nodeptr _P)
		 {
			 return (*_P)._Value;
		 }
	};
public:
	typedef list<_Ty>    _Myt;

	typedef _Ty          value_type;
	typedef _Ty *        _Tptr;
	typedef const _Ty *  _Ctptr;
	typedef _Ty &        reference;
	typedef const _Ty &  const_reference;

	typedef int          difference_type;
	typedef unsigned int size_type;
public:
	class const_iterator; // const type *;
	class iterator;        // type *;
	class const_iterator : public _Bidit<_Ty,difference_type>
	{
	public:
		const_iterator(_Nodeptr _P = NULL):_Ptr(_P) {}
		const_reference operator*() const
		{
			return _Acc::_Value(_Ptr);
		}
		_Ctptr operator->() const
		{
			return &**this;
		}// const_iterator it;
		const_iterator & operator++()
		{
			_Ptr = _Acc::_Next(_Ptr);
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator _tmp = *this;
			++*this;
			return _tmp;
		}

		const_iterator & operator--()
		{
			_Ptr = _Acc::_Prev(_Ptr);
			return *this;
		}
		const_iterator operator--(int)
		{
			const_iterator _tmp = *this;
			--*this;
			return _tmp;
		}
		bool operator==(const const_iterator &_X) const
		{
			return _Ptr == _X._Ptr;
		}
		bool operator!=(const const_iterator &_X) const
		{
			return !(*this == _X);
		}

		_Nodeptr _Mynode() const
		{
			return _Ptr;
		}
	protected:
		_Nodeptr _Ptr;
	};

	class iterator : public const_iterator
	{
	public:
		iterator(_Nodeptr _P = NULL):const_iterator(_P) {}
		reference operator*() const
		{
			return _Acc::_Value(_Ptr);
		}
		_Tptr operator->() const
		{
			return &**this;
		}// const_iterator it;
		iterator & operator++()
		{
			_Ptr = _Acc::_Next(_Ptr);
			return *this;
		}
		iterator operator++(int)
		{
			iterator _tmp = *this;
			++*this;
			return _tmp;
		}

		iterator & operator--()
		{
			_Ptr = _Acc::_Prev(_Ptr);
			return *this;
		}
		iterator operator--(int)
		{
			iterator _tmp = *this;
			--*this;
			return _tmp;
		}
		bool operator==(const iterator &_X) const
		{
			return _Ptr == _X._Ptr;
		}
		bool operator!=(const iterator &_X) const
		{
			return !(*this == _X);
		}
	};
public:
	typedef const_iterator _It;
	list():_Head(_Buynode()),_Size(0) {}
	list(size_type _M ,const _Ty &_X = _Ty())
		:_Head(_Buynode()),_Size(0)
	{
		insert(begin(),_M,_X);
	}
	list(const _Ty *_F,const _Ty *_L)
		:_Head(_Buynode()),_Size(0)

	{
		insert(begin(),_F,_L);
	}
	list(const list<_Ty> &_X)
		:_Head(_Buynode()),_Size(0)
	{
		insert(begin(),_X.begin(),_X.end());
	}
	list(_It _F,_It _L):_Head(_Buynode()),_Size(0)
	{
		insert(begin(),_F,_L);
	}
	list<_Ty> & operator=(const list<_Ty> &_X)
	{
		if(this != &_X)
		{
			iterator _F1 = this->begin(), _L1 = this->end();
			const_iterator _F2 = _X.begin(), _L2 = _X.end();
			for(; _F1 != _L1 && _F2 != _L2; ++_F1 , ++_F2)
			{
				*_F1 = *_F2;
			}
			insert(_L1,_F2,_L2);
			erase(_F1,_L1);
		}
		return *this;
	}

	~list()
	{
		clear();
		_Freenode(_Head);
		_Head = NULL;
		_Size = 0;
	}

	void assign(const_iterator _F, const_iterator _L);
	void assign(size_type _N, const _Ty &_X = _Ty());

	reference back() { return *--end();}
	const_reference back() const { return *--end();}
	reference front() { return *begin();}
	const_reference front() const { return *begin();}

	size_type size() const { return _Size;}
	bool empty() const { return size() == 0;}
	void resize(size_type _N,const _Ty &_X = _Ty());


	iterator begin() { return iterator(_Acc::_Next(_Head));}
	iterator end() { return iterator(_Head); }
	const_iterator begin() const
	{
		return const_iterator(_Acc::_Next(_Head));
	}
	const_iterator end() const
	{
		return const_iterator(_Head);
	}
public:
	void push_back(const _Ty &_X)
	{
		insert(end(),_X);
	}
	void push_front(const _Ty &_X)
	{
		insert(begin(),_X);
	}
	void insert(iterator _P,size_type _M,const _Ty &_X = _Ty())
	{
		for(; _M > 0 ; --_M)
		{
			insert(_P,_X);
		}
	}
	void insert(iterator _P,_It _F, _It _L)
	{
		for(; _F != _L; ++_F)
		{
			insert(_P,*_F);
		}
	}
	void insert(iterator _P,const _Ty *_F,const _Ty *_L)
	{
		for(; _F != _L ;++_F)
		{
			insert(_P,*_F);
		}
	} // mylislt.insert(mylist.begin(),ar,ar+10);

	iterator insert(iterator _P,const _Ty &_X)
	{
		_Nodeptr _S = _P._Mynode();
		_Acc::_Prev(_S) = _Buynode(_Acc::_Prev(_S),_S);
		_S = _Acc::_Prev(_S);
		_Acc::_Next(_Acc::_Prev(_S)) = _S;
		//_Acc::_Value(_S) = _X;
		new (&_Acc::_Value(_S)) _Ty(_X);
		_Size+=1;
		return iterator(_S);
	}
	void clear()
	{
		destroy(begin(),end());
		iterator _F = begin(), _L = end();
		for(; _F != _L; )
		{
			_Nodeptr _S = _F++._Mynode();
			_Acc::_Next(_Acc::_Prev(_S)) = _Acc::_Next(_S);
			_Acc::_Prev(_Acc::_Next(_S)) = _Acc::_Prev(_S);
			_Freenode(_S);
		}
		_Size = 0;
	}
	void erase(iterator _F,iterator _L)
	{
		for(; _F != _L; )
		{
			erase(_F++);
		}
	}
	iterator erase(iterator _P)
	{
		_Nodeptr _S = _P++._Mynode();
		// _Nodeptr _S = _P.operator++(0)._Mynode();
		_Acc::_Next(_Acc::_Prev(_S)) = _Acc::_Next(_S);
		_Acc::_Prev(_Acc::_Next(_S)) = _Acc::_Prev(_S);
		(&_Acc::_Value(_S))->~_Ty();
		_Freenode(_S);
		_Size-=1;
		return _P;
	}
	void remove(const _Ty& _V)
	{
		iterator _F = begin(), _L = end();
		for(; _F != _L; )
		{
			if(_V == *_F)
			{
				erase(_F++);
			}else
			{
				++_F;
			}
		}
	}

	void swap(_Myt& _X)
	{
		swap(this->_Head,_X._Head);
		swap(this->_Size,_X._Size);
	}// mylist.swap(youlist);
	friend void swap(_Myt& _X, _Myt& _Y)
	{
		_X.swap(_Y);
	}
	void splice(iterator _P, _Myt& _X)
	{
		if (!_X.empty())
		{
			_Splice(_P, _X, _X.begin(), _X.end());
			_Size += _X._Size;
			_X._Size = 0; 
		}
	}
	void splice(iterator _P, _Myt& _X, iterator _F)
	{
	}
	void splice(iterator _P, _Myt& _X, iterator _F, iterator _L)
	{
		if (_F != _L)
		{
			if (&_X != this)
			{
				difference_type _N = 0;
				_Distance(_F, _L, _N);//
				_Size += _N;
				_X._Size -= _N;
			}
			_Splice(_P, _X, _F, _L); 
		}
	}// mylist.splice(mylist.begin(),mylist,mylist.begin());
	/*
	typedef binder2nd<not_equal_to<_Ty> > _Pr1;
	void remove_if(_Pr1 _Pr);
	void unique();
	typedef not_equal_to<_Ty> _Pr2;
	void unique(_Pr2 _Pr);
	void merge(_Myt& _X)
	{
		if (&_X != this)
			{iterator _F1 = begin(), _L1 = end();
			iterator _F2 = _X.begin(), _L2 = _X.end();
			while (_F1 != _L1 && _F2 != _L2)
				if (*_F2 < *_F1)
					{iterator _Mid2 = _F2;
					_Splice(_F1, _X, _F2, ++_Mid2);
					_F2 = _Mid2; }
				else
					++_F1;
			if (_F2 != _L2)
				_Splice(_L1, _X, _F2, _L2);
			_Size += _X._Size;
			_X._Size = 0; 
		}
	}
	typedef greater<_Ty> _Pr3;
	void merge(_Myt& _X, _Pr3 _Pr);
	void sort()//????
	{
		if (2 <= size())
		{
			const size_t _MAXN = 15;
			_Myt _X,, _A[_MAXN + 1];
			size_t _N = 0;
			while (!empty())
			{
				_X.splice(_X.begin(), *this, begin());
				size_t _I;
				for (_I = 0; _I < _N && !_A[_I].empty(); ++_I)
				{
					_A[_I].merge(_X);
					_A[_I].swap(_X); 
				}
				if (_I == _MAXN)
					_A[_I].merge(_X);
				else
				{
					_A[_I].swap(_X);
					if (_I == _N)
						++_N; 
				}
			}
			while (0 < _N)
				merge(_A[--_N]); 
		}
	}
	void sort(_Pr3 _Pr);
	void reverse();
	*/
private:
	static _Nodeptr _Buynode(_Nodeptr _Parg = NULL ,_Nodeptr _Narg = NULL)
	{
		_Nodeptr _S = (_Nodeptr)malloc(sizeof(_Node));
		if(NULL == _S) exit(1);
		_Acc::_Prev(_S) = _Parg == NULL? _S:_Parg;
		_Acc::_Next(_S) = _Narg == NULL? _S:_Narg;
		return _S;
	}
	static void _Freenode(_Nodeptr _P)
	{
		free(_P);
	}

	void _Splice(iterator _P, _Myt& _X, iterator _F, iterator _L)
	{
		_Acc::_Next(_Acc::_Prev(_P._Mynode())) = _F._Mynode();
		_Acc::_Next(_Acc::_Prev(_F._Mynode())) = _L._Mynode();
		_Acc::_Next(_Acc::_Prev(_L._Mynode())) = _P._Mynode();
		_Nodeptr _S = _Acc::_Prev(_P._Mynode());
		_Acc::_Prev(_P._Mynode()) = _Acc::_Prev(_L._Mynode());
		_Acc::_Prev(_L._Mynode()) = _Acc::_Prev(_F._Mynode());
		_Acc::_Prev(_F._Mynode()) = _S;
	}
	_Nodeptr _Head;
	size_type _Size;
};

};

#endif
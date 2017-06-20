

#ifndef YHP_VECTOR_H
#define YHP_VECTOR_H
namespace yhp
{
template<class _Ty>
class vector 
{
public:
	typedef vector<_Ty> _Myt;
	typedef _Ty          value_type;
	typedef _Ty *        _Tptr;
	typedef const _Ty *  _Ctptr;
	typedef _Ty &        reference;
	typedef const _Ty &  const_reference;

	typedef int          difference_type;
	typedef unsigned int size_type;
	class const_iterator
	{
	public:
		const_iterator(_Tptr _P = NULL):_Ptr(_P) {}
		const_reference operator*() const
		{
			return *_Ptr;
		}
		_Ctptr operator->() const
		{
			return _Ptr;// &**this;
		}
		const_iterator & operator++()
		{
			_Ptr = _Ptr + 1;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator _tmp = *this;
			++*this;
			return _tmp;
		}
		const_iterator &operator--()
		{
			_Ptr = _Ptr - 1;
			return *this;
		}
		const_iterator operator--(int)
		{
			const_iterator _tmp = *this;
			--*this;
			return _tmp;
		}
		const_iterator & operator+=(difference_type off)
		{
			_Ptr = _Ptr + off;
			return *this;
		}

		const_iterator & operator-=(difference_type off)
		{
			_Ptr = _Ptr - off;
			return *this;
		}
		const_iterator operator+(difference_type off) const
		{
			_Tptr _P = _Ptr + off;
			return const_iterator(_P);
		}

		const_iterator operator-(difference_type off) const
		{
			_Tptr _P = _Ptr - off;
			return const_iterator(_P);
		}
		const_reference operator[](difference_type off) const
		{
			return _Ptr[off];
		}
		bool operator==(const const_iterator &_X)const
		{
			return _Ptr == _X._Ptr;
		}
		bool operator!=(const const_iterator &_X)const
		{
			return !(*this == _X);
		}
		bool operator>(const const_iterator &_X)const
		{
			return _Ptr > _X._Ptr;
		}
		bool operator<=(const const_iterator &_X)const
		{
			return !(*this > _X);
		}
		bool operator<(const const_iterator &_X)const
		{
			return _Ptr < _X._Ptr;
		}
		bool operator>=(const const_iterator &_X)const
		{
			return !(this < _X);
		}
		size_type operator-(const const_iterator &_X) const
		{
			return _Ptr - _X._Ptr;
		}
		_Tptr _Mynode() const
		{
			return _Ptr;
		}
	protected:
		_Tptr _Ptr;
	};
	class iterator : public const_iterator
	{
	public:
		iterator(_Tptr _P = NULL):const_iterator(_P) {}

		reference operator*() const
		{
			return *_Ptr;
		}
		_Tptr operator->() const
		{
			return _Ptr;// &**this;
		}
		iterator & operator++()
		{
			_Ptr = _Ptr + 1;
			return *this;
		}
		iterator operator++(int)
		{
			iterator _tmp = *this;
			++*this;
			return _tmp;
		}
		iterator &operator--()
		{
			_Ptr = _Ptr - 1;
			return *this;
		}
		iterator operator--(int)
		{
			iterator _tmp = *this;
			--*this;
			return _tmp;
		}
		iterator & operator+=(difference_type off)
		{
			_Ptr = _Ptr + off;
			return *this;
		}

		iterator & operator-=(difference_type off)
		{
			_Ptr = _Ptr - off;
			return *this;
		}
		iterator operator+(difference_type off) const
		{
			_Tptr _P = _Ptr + off;
			return iterator(_P);
		}

		iterator operator-(difference_type off) const
		{
			_Tptr _P = _Ptr - off;
			return  iterator(_P);
		}
		reference operator[](difference_type off) const
		{
			return _Ptr[off];
		}
		bool operator==(const iterator &_X)const
		{
			return _Ptr == _X._Ptr;
		}
		bool operator!=(const iterator &_X)const
		{
			return !(*this == _X);
		}
		bool operator>(const  iterator &_X)const
		{
			return _Ptr > _X._Ptr;
		}
		bool operator<=(const  iterator &_X)const
		{
			return !(*this > _X);
		}
		bool operator<(const  iterator &_X)const
		{
			return _Ptr < _X._Ptr;
		}
		bool operator>=(const  iterator &_X)const
		{
			return !(this < _X);
		}
		size_type operator-(const iterator &_X) const
		{
			return _Ptr - _X._Ptr;
		}
	};
public:
	iterator begin() { return _First;}
	iterator end() { return _Last;}
	const_iterator begin() const { return _First;}
	const_iterator end() const { return _Last;} // _End;

public:
	typedef const_iterator _It;
	explicit vector():_First(NULL),_Last(NULL),_End(NULL) {}

	explicit vector(size_type _N, const _Ty& _V = _Ty())
	{
		_First = _Buynode(_N);
		_Last = _End = _First + _N;
		_Ufill(_First,_N,_V);
	}
	/*
	vector(const _Myt& _X)
	typedef const_iterator _It;
	vector(_It _F, _It _L);
	~vector();
	_Myt& operator=(const _Myt& _X);
	void reserve(size_type _N);
	size_type max_size() const;
	
	size_type capacity() const { return _End - _First;}
	size_type size() const { return _Last - _End;}
	void resize(size_type _N, const _Ty& _X = _Ty());
	
	
	bool empty() const { return size() == 0;}
	const_reference at(size_type _P) const;
	reference at(size_type _P);
	const_reference operator[](size_type _P) const;
	reference operator[](size_type _P);
	reference front() { return *_First;}
	const_reference front() const { return *_First;}
	reference back() { return * (_Last-1);}
	const_reference back() const *(_Last - 1);}

	void push_back(const _Ty& _X);
	void pop_back();
	void assign(_It _F, _It _L);
	void assign(size_type _N, const _Ty& _X = _Ty());
	
	iterator insert(iterator _P, const _Ty& _X = _Ty());
	void insert(iterator _P, size_type _M, const _Ty& _X);
	void insert(iterator _P, _It _F, _It _L);

	iterator erase(iterator _P);
	iterator erase(iterator _F, iterator _L);
	void clear();
	bool _Eq(const _Myt& _X) const;
	bool _Lt(const _Myt& _X) const;
	void swap(_Myt& _X);
	friend void swap(_Myt& _X, _Myt& _Y);
	*/
protected:
	_Tptr _Buynode(size_type n)
	{
		_Tptr _S = (_Tptr)malloc(sizeof(_Ty) *n );
		return _S;
	}
	void _Destroy(iterator _F, iterator _L)
	{
		for (; _F != _L; ++_F)
		{
			_F->~_Ty();
		}
	}
	iterator _Ucopy(const_iterator _F, const_iterator _L,
		iterator _P)
	{
		for (; _F != _L; ++_P, ++_F)
		{
			//allocator.construct(_P, *_F);
			new(&*_P) _Ty(*_F);
		}
		return (_P); 
	}
	void _Ufill(iterator _F, size_type _N, const _Ty &_X)
	{
		for (; 0 < _N; --_N, ++_F)
		{
			//allocator.construct(_F, _X); 
			new(&*_F) _Ty(_X);
		}
	}
	void _Xran() const
	{
		_THROW(out_of_range, "invalid vector<T> subscript"); 
	}


	iterator _First, _Last, _End;
};

};

#endif
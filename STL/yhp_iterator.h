#ifndef YHP_ITERATOR_H
#define YHP_ITERATOR_H

namespace yhp
{

typedef int ptrdiff_t;

			// ITERATOR TAGS (from <iterator>)
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag  {};

template<class _Cate,class _Ty,class _Dist = int,
         class _P = _Ty *, class _Ref = _Ty&>
struct iterator
{
	typedef _Cate   iterator_category;
	typedef _Ty     value_type;
	typedef _Dist   difference_type;
	typedef _P      pointer;
	typedef _Ref    reference;
};

//////////////////////////////////////////////////
// vc P.j.
template<class _Cate,class _Ty,class _Dist,class _P, class _Ref>
_Cate  _Iter_cat(const iterator<_Cate,_Ty,_Dist,_P,_Ref> &)
{
	return _Cate();
}
template<class T>
random_access_iterator_tag  _Iter_cat(const T *)
{
	return random_access_iterator_tag();
}

// traits  SGI
template<class Iterator>//
struct iterator_traits
{
	typedef typename Iterator::iterator_category iterator_category;
	typedef typename Iterator::value_type        value_type;
	typedef typename Iterator::difference_type   difference_type;
	typedef typename Iterator::pointer           pointer;
	typedef typename Iterator::reference         reference;
};

template<class T>//
struct iterator_traits<T*>
{
	typedef random_access_iterator_tag iterator_category;
	typedef T                          value_type;
	typedef int                        difference_type;
	typedef T                         *pointer;
	typedef T                         &reference;
};

template<class T>//
struct iterator_traits<const T*>
{
	typedef random_access_iterator_tag iterator_category;
	typedef T                          value_type;
	typedef int                        difference_type;
	typedef const T                   *pointer;
	typedef const T                   &reference;
};


template<class Iterator>
typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator &)
{
	typedef typename iterator_traits<Iterator>::iterator_category category;
	return category();
}
template<class Iterator>
typename iterator_traits<Iterator>::value_type *
value_type(const Iterator &)
{
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

template<class Iterator>
typename iterator_traits<Iterator>::difference_type *
difference_type(const Iterator &)
{
	return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}
//////////////////////////////////////////////////

template<class _Ty, class _D>
struct _Bidit : public iterator<bidirectional_iterator_tag,
		_Ty, _D> {};

template<class _Ty, class _D>
struct _Ranit : public iterator<random_access_iterator_tag,
		_Ty, _D> {};




template<class _II,class _Dist>
void __advance(_II &i,_Dist n,input_iterator_tag)
{
	while(n--) ++i;
}
template<class _FI,class _Dist>
void __advance(_FI &i,_Dist n,forward_iterator_tag)
{
	__advance(i,n,input_iterator_tag());
}

template<class _BI,class _Dist>
void __advance(_BI &i,_Dist n,bidirectional_iterator_tag)
{
	if(n >= 0)
	{
		while(n--) ++i;
	}else
	{
		while(n++) --i;
	}
}
template<class _RAI,class _Dist>
void __advance(_RAI &i,_Dist n,random_access_iterator_tag)
{
	i += n;
}
template<class _II,class _Dist>
void advance(_II &i,_Dist n)
{
	//cout<<typeid(_II).name()<<endl;
	//typedef typename iterator_traits<_II>::iterator_category cate;
	//cout<<typeid(cate).name()<<endl;
	//typedef typename iterator_traits<_II>::iterator_category cate; 
	//__advance(i,n,cate());
	__advance(i,n,_Iter_cat(i));
}

template<class _II>
typename iterator_traits<_II>::difference_type
__distance(_II _F, _II _L, input_iterator_tag)
{
	typename iterator_traits<_II>::difference_type n = 0;
	for(; _F != _L; ++_F,++n);
	return n;
}

template<class _II>
typename iterator_traits<_II>::difference_type
__distance(_II _F, _II _L,random_access_iterator_tag)
{
	return _L - _F;
}

template<class _II>
typename iterator_traits<_II>::difference_type
distance(_II _F, _II _L)
{
	cout<<typeid(iterator_category(_F)).name()<<endl;
	return __distance(_F,_L,iterator_category(_F));
}

	/*
template<class _II,class _Dist>
void advance_II(_II &i,_Dist n)
{
	while(n--) ++i;
}

template<class _BI,class _Dist>
void advance_BI(_BI &i,_Dist n)
{
	if(n >= 0)
	{
		while(n--) ++i;
	}else
	{
		while(n++) --i;
	}
}

template<class _RAI,class _Dist>
void advance_RAI(_RAI &i,_Dist n)
{
	i +=n;
}

template<class _II,class _Dist>
void advance(_II &i,_Dist n)
{
	if(is_random_access_iterator(i))
	{
		advance_RAI(i,n);
	}else if(is_bidirectional_iterator(i))
	{
		advance_BI(i,n);
	}else
	{
		advance_II(i,n);
	}
}

*/

};

#endif

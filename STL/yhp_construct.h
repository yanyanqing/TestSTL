
#ifndef YHP_CONSTRUCT_H
#define YHP_CONSTRUCT_H
#include"yhp_iterator.h"
#include"yhp_type_traits.h"

namespace yhp
{
template<class T1,class T2>
inline void construct(T1 *p,const T2 &value)
{
	new (p) T1(value);
}
template<class T>
inline void construct(T *p)
{
	new (p) T();
}

template<class T>
inline void destroy(T *pointer)
{
	pointer->~T();
}
template<class _FI>
inline void destroy(_FI _F,_FI _L)
{
	//cout<<typeid(_F).name()<<endl;
	//cout<<typeid(value_type(_F)).name()<<endl;
	__destroy(_F,_L,value_type(_F));
}

template<class _FI,class T>
inline void __destroy(_FI _F , _FI _L,T*)
{
	typedef typename __type_traits<T>::has_trivial_destructor  trivial_destructor;

	//__type_traits<T>();
	//cout<<typeid(trivial_destructor).name()<<endl;
	__destroy_aux(_F,_L,trivial_destructor());
}

template<class _FI>
inline void __destroy_aux(_FI _F , _FI _L,__false_type)
{
	for(; _F != _L; ++_F)
	{
		destroy(&*_F);
	}
}

template<class _FI>
inline void __destroy_aux(_FI _F , _FI _L,__true_type)
{}

inline void destroy(char *,char*) {}
inline void destroy(wchar_t *,wchar_t *) {}// ??

};

#endif
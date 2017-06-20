
#ifndef YHP_ALLOC_H
#define YHP_ALLOC_H
namespace yhp
{
#if 0
#include<new>
#define __THROW_BAD_ALLOC throw std::bad_alloc();
#elif !define (__THROW_BAD_ALLOC)
#include<iostream>
#define __THROW_BAD_ALLOC std::cerr<<"out of memory"<<std::endl; exit(1);
#endif

template<int inst>
class __malloc_alloc_template
{
private:
	static void *oom_malloc(size_t n)
	{

	}
	static void *oom_realloc(void *,size_t n)
	{
	}
	static void (*__malloc_alloc_oom_handler)();
public:
	static void *allocate(size_t n)
	{
		void *result = malloc(n);
		if(NULL == result) 
		{
			result = oom_malloc(n);
		}
		return result;
	}
	static void deallocate(void *p,size_t/* n*/)
	{
		free(p);
	}
	static void *reallocate(void *p,size_t /*old_sz*/,size_t new_sz)
	{
		void *result = realloc(p,new_sz);
		if(NULL == result)
		{
			result = oom_realloc(p,new_sz);
		}
		return result;
	}

	static void (*set_malloc_handler(void (*f)()))()
	{
		void (*old)() = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler  = f;
		return old;
	}

};

template<int inst>
void (__malloc_alloc_template<inst>::*__malloc_alloc_oom_handler)() = NULL;



};

#endif
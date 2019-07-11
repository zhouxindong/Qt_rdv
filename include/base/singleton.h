/******************************************************************************/
/** @file singleton.h
@brief
	实现单体模式和不可复制对象。
@author 
	林万洪
	邓华 dehxya@163.com
@par 所属模块
	base
@par 相关文件
	无
@see ssa::xmUncopyable
@see ssa::xmSingleton
@par 修改记录
	@par
	2019.09.15
		-# 邓华，增加了以宏定义方式实现的单体。
	@par
	2014.03.03
		-# 林万洪，代码初次完成。
@copyright (C), 2011-2022, Gonna. All rights reserved.
*******************************************************************************/
#ifndef __SSA_BASE_SINGLETON_H
#define __SSA_BASE_SINGLETON_H
#include "exceptions.h"
#include "assertmsg.h"
#include "ptr.h"

namespace ssa
{
	/******************************************************************************/
	/** @class xmUncopyable
	@brief
		实现一个不可复制的对象
	@par 多线程安全
		不适用
	@par 示例
		@par
		@code
			class myClass : private xmUncopyable
			{
			public:
				myClass() : m_iParam(0){};
			private:
				int m_iParam;
			};

			myClass C1;		//	没问题
			myClass C2(C1);	//	编译错误。
		@endcode
	*******************************************************************************/
	class xmBASE_EXPORT xmUncopyable
	{
	protected:
		xmUncopyable(){};
		virtual ~xmUncopyable(){};
	private:
		xmUncopyable(const xmUncopyable&);
		xmUncopyable& operator=(const xmUncopyable&);
	};


	/******************************************************************************/
	/** @class xmSingleton
	@brief
		以模板的方式实现一个单体对象，当创建多个单子类实例的时候，会在运行时报异常。
	@par 多线程安全
		不适用
	@par 示例
		@par
		@code
			class myClass : public xmSingleton<myClass>
			{
			public:
				myClass(){};
			private:
				int m_iParam;
			};

			myClass C1;		//	没问题
			myClass C2;		//	编译没问题，运行时断言失败。
		@endcode
	*******************************************************************************/
	template <class T> 
	class xmSingleton : private xmUncopyable
	{
	protected:
		xmSingleton()
		{
			xmAssert(xmSingleton::Instance() == NULL);
			xmSingleton::Instance() = static_cast<T*>(this);
		}

		virtual ~xmSingleton()
		{
			xmAssert(xmSingleton::Instance() == static_cast<T*>(this));
			xmSingleton::Instance() = NULL;
		}

	private:
		inline static T*& Instance()
		{
			static T* m_sInst = NULL;
			return m_sInst;
		}
	};

	/******************************************************************************/
	/** @def xmSINGLETON_DECLARE
	@brief
		单体声明， xmSINGLETON_DECLARE 和 xmSINGLETON_DEFINE 共同以宏定义的方式实现一
		个单体对象，使用接口访问，如果定义实例将在编译时报错。
	@details
		使用中，单体类（如下例中的myClass）构造函数已经在xmSINGLETON_DECLARE宏中定义，
		用户可根据需要定义自己的析构函数。
	@par 多线程安全
		不适用
	@see xmSINGLETON_DEFINE
	@par 示例
		@par
		@code
			[myClass.h]
			class myClass
			{
				xmSINGLETON_DECLARE(myClass)
			public:
				~myClass()
				{
					printf("~myClass");
				};
				void say()
				{
					printf("Hello myClass!\n");
				}
			};

			[myClass.cpp]
			xmSINGLETON_DEFINE(myClass)

			[sample.cpp]
			#include "myClass.h"
			void main()
			{
				//	运行正常
				myClass::Instance()->say();
				//	编译报错
				//	myClass mc;
				return;
			}
		@endcode
	*******************************************************************************/
	#define	xmSINGLETON_DECLARE(sClass)		\
		public:								\
			static xmPtr<sClass>& Instance()\
			{								\
				if (__m_pInstance.IsNULL())	\
				{							\
					__m_pInstance = new sClass;\
				}							\
				return __m_pInstance;		\
			}								\
		private:							\
			sClass(){};						\
			static xmPtr<sClass> __m_pInstance;	

	/******************************************************************************/
	/** @def xmSINGLETON_DEFINE
	@brief
		单体定义
	@see xmSINGLETON_DECLARE
	*******************************************************************************/
	#define	xmSINGLETON_DEFINE(sClass)		\
		xmPtr<sClass> sClass::__m_pInstance;
}

#endif

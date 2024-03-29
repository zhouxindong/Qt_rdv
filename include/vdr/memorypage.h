#pragma once
#ifndef __SSA_VDR_MEMORYPAGE_H
#define __SSA_VDR_MEMORYPAGE_H

#include "../../include/base/sharememory.h"
#include <atomic>

namespace ssa
{
#define MAX_MEMORYPAGE_SIZE  1024*1024
#define MEMORYPAGE_HEAD_SIZE 128

	class xmMemoryPage
	{
	public:
		//根据用户制定创建共享内存块或者非共享内存块。
		xmMemoryPage();
		~xmMemoryPage(void);

		bool                 m_bIsShare;
		std::string          m_strName;
		unsigned int         m_nName;
		unsigned int         m_nParaCount;
		unsigned int         m_nVersion;

		typedef struct __tagMemoryInfo
		{
			__tagMemoryInfo(void) : m_uSize(0) {};
			unsigned int m_uSize;
		}__SMemoryInfo;

		__SMemoryInfo        m_MemoryInfo;

	public:
		byte*                GetPointer() const;
		unsigned int         GetSize() const;
		void                 Destroy();
		bool                 IsVaild() const;

		bool                 Make(unsigned int nName, unsigned int uLength, bool isShare = true);

		unsigned int         Read(unsigned int uOffset, void* pBuffer, unsigned int uLength, unsigned int uMaxWaitTime = INFINITE);
		unsigned int         ReadWithSign(unsigned int uOffset, void* pBuffer, unsigned int uLength, unsigned int uSignOffset, void* pSign, unsigned int uSignSize, unsigned int uMaxWaitTime = INFINITE);
		unsigned int         Write(unsigned int uOffset, const void* pBuffer, unsigned int uLength, unsigned int uMaxWaitTime = INFINITE);
		unsigned int         WriteWithSign(unsigned int uOffset, const void* pBuffer, unsigned int uLength, unsigned int uSignOffset, const void* pSign, unsigned int uSignSize, unsigned int uMaxWaitTime = INFINITE);

	private:
		bool                 CreateMemory(unsigned int uLength);

	private:
		mutable xmMutex  m_Mutex;
		bool     m_bCreater;

		//	内存映射文件句柄
#ifdef xmOS_WINDOWS
		HANDLE   m_hMapFile;
#else 
		key_t    m_hMapFile;
#endif
		//内存中开始存储用户值的指针地址在MEMORYPAGE_HEAD_SIZE之后，目前策划前面有128个字节的保留空间
		byte*    m_pBaseAddress;
	};
}

#endif //__SSA_VDR_MEMORYPAGE_H


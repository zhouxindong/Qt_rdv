#ifndef __SSA_UMSF_DLLLOADER_H
#define __SSA_UMSF_DLLLOADER_H
#include "mloader.h"

namespace ssa
{
	class xmDllLoader : public xmModelLoader
	{
	public:
		xmDllLoader(const xmString& strModelFile, xmIModelServer* pModelServer);
		virtual ~xmDllLoader();
	protected:
		virtual xmRet CreateModelInstance();

	private:
		xmLib m_ModelDll;

		typedef xmIModel* (*tCreateModel)(xmIModelServer* pServer);
		typedef void(*tDestroyModel)(xmIModel* pModel);
		tCreateModel m_pfnCreateModel;
		tDestroyModel m_pfnDestroyModel;
	};
}
#endif  //  __SSA_UMSF_DLLLOADER_H


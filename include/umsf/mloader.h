#ifndef __SSA_UMSF_MLOADER_H
#define __SSA_UMSF_MLOADER_H
#include "imodel.h"

namespace ssa
{
	class xmModelLoader
    {
	public:
		static xmModelLoader* Create(const xmString& strModelFile, xmIModelServer* pModelServer);
		static void Destroy(xmModelLoader* pLoader);
		virtual ~xmModelLoader() {};
	
		inline xmIModel* Model()
		{
			return m_pModel;
		}
	protected:
		const xmString m_strModelFile;
		xmIModelServer* const m_pModelServer;
		xmIModel* m_pModel;

		xmModelLoader(const xmString& strModelFile, xmIModelServer* pModelServer) : m_strModelFile(strModelFile), m_pModelServer(pModelServer), m_pModel(NULL){};
		virtual xmRet CreateModelInstance() = 0;
	};
}   //  namespace ssa
#endif  //  __SSA_UMSF_MLOADER_H


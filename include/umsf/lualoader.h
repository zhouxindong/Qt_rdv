#ifndef __SSA_UMSF_LUALOADER_H
#define __SSA_UMSF_LUALOADER_H
#include "mloader.h"

namespace ssa
{
	class xmLuaModel;
	class xmLuaLoader : public xmModelLoader
	{
	public:
		xmLuaLoader(const xmString& strModelFile, xmIModelServer* pModelServer) : xmModelLoader(strModelFile, pModelServer)	{};
		virtual ~xmLuaLoader()	{};
	protected:
		virtual xmRet CreateModelInstance();

	private:
		xmPtr<xmLuaModel> m_pLuaModel;
	};
}
#endif  //  __SSA_UMSF_LUALOADER_H


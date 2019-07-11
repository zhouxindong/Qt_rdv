#ifndef __SSA_UMSF_TSCRIPT_H
#define __SSA_UMSF_TSCRIPT_H
#include "luaengine.h"
#include "idefine.h"
namespace ssa
{
	class xmMrtc;
	//	ʹ��Lua�Ĵ������ű�
	class xmTriggerScript : public xmLuaEngine
	{
	public:
		xmTriggerScript(const char* strScript, xmMrtc* pMrtc);
		virtual ~xmTriggerScript() {};

		bool IsTriggered(const xmValue* pParam);
	private:
		bool call_trigger(const char* strFuncName);
	protected:
		static xmTriggerScript* get_this(lua_State *L)
		{
			return (xmTriggerScript*)read_pointer(L, "THIS");
		}
		static void set_return(lua_State *L, const xmValue& aValue, xmRWLock& rwl)
		{
			xmRWLock::ReadGuard rg(rwl);
			push_value(L, aValue);
		}
		static void set_return(lua_State *L, const xmValue& aValue)
		{
			push_value(L, aValue);
		}

		//	����ssa_*���������ǿɹ�LUA�ű����õĺ���
		static int ssa_getParam(lua_State *L);
		static int ssa_getValue(lua_State *L);
		static int ssa_getClick(lua_State *L);
		static int ssa_updateInputData(lua_State *L);
		static int ssa_updateOutputData(lua_State *L);
	private:
		//	ģ�����л���
		xmMrtc* const m_pMrtc;
		//	��������
		std::map<xmString, std::pair<xmEIOType, xmPtr<xmValue>>> m_mapValue;
		//	��������������Ϣ����
		xmPtr<xmValue> m_pParamValue;
	};
}
#endif
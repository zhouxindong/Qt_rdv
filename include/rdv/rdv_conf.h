#pragma once

#include "base.h"
#include "vdr.h"
#include "accesspoint.h"

#include <string>
#include <functional>
#include <array>
#include "sugar.h"
#include "tinyxml2.h"
#include "any_prop.h"
#include <basetsd.h>
#include <regex>
#include "any.h"

#ifdef RDV_EXPORTS
#define RDV_API __declspec(dllexport)
#define RDV_TEMPLATE_API __declspec(dllexport)
#else
#define RDV_API __declspec(dllimport)
#define RDV_TEMPLATE_API
#endif

namespace HJYD_GSA
{
	enum class eConfigText {
		_Unknown,
		_Xml,
		_Json,
		_Ini
	};

	/*
	** configuration used for rdv
	** you can call .ctor through methods below:
	** 1. parameters directly
	** 2. json text
	** 3. xml text
	** 4. ini text
	*/
	class RDV_API rdv_conf
	{
		_PROPERTY_READONLY_INIT(bool, clear_dataset, true)

	public:
		rdv_conf();

	private:
		void _Parse_xml(tinyxml2::XMLElement* _Node);
		void _Parse_xml(std::string s);
		void _Parse_json(std::string s);

	private:
		cpknife::any_prop _bag;

	public:

		UINT8 config_u8(const char* name);
		UINT16 config_u16(const char* name);
		std::string config_s(const char* name);

		void config_u8(const char* name, UINT8 val);
		void config_u16(const char* name, UINT16 val);
		void config_s(const char* name, std::string val);

		void Parse(std::string s, eConfigText t);

	public:
		const char* _XML_VDR_REGION		= "VDR_REGION";
		const char* _XML_VDR_ID			= "VDR_ID";
		const char* _XML_VDR_GROUP_IP	= "VDR_GROUP_IP";
		const char* _XML_VDR_GROUP_PORT = "VDR_GROUP_PORT";
		const char* _XML_VDR_LOCAL_IP	= "VDR_LOCAL_IP";
		const char* _XML_VDR_LOCAL_PORT = "VDR_LOCAL_PORT";

		const char* _XML_CTL_CMD		= "CTL_CMD";
		const char* _XML_CTL_SPEED		= "CTL_SPEED";
		const char* _XML_CMD_LOAD		= "CMD_LOAD";
		const char* _XML_CMD_INIT		= "CMD_INIT";
		const char* _XML_CMD_START		= "CMD_START";
		const char* _XML_CMD_FREEZE		= "CMD_FREEZE";
		const char* _XML_CMD_UNFREEZE	= "CMD_UNFREEZE";
		const char* _XML_CMD_SPEED		= "CMD_SPEED";
		const char* _XML_CMD_FINISH		= "CMD_FINISH";

		const char* _XML_INIT_ATTR		= "INIT";
	};

	/*
	** VDR buffer data wrapped
	*/
	class RDV_API wrap_buffer
	{
	public:
		ssa::xmValue* _value;

	public:
		wrap_buffer(UINT8 data[], size_t size)
		{
			_steam
				<< R"({)"
				<< R"("data":"BUFFER)"
				<< (INT32)size
				<< R"(", )"
				<< R"("size":"UINT32")"
				<< R"(})";

			_c = new ssa::xmClass(ssa::xmString(_steam.str().c_str()));

			_value = new ssa::xmValue(*_c);
			(*_value)["size"].u32() = size;
			for (int i = 0; i < size; i++)
			{
				(*_value)["data"].buffer().Set(i, xmB4(data[i]));
			}
		}

		~wrap_buffer() {

			delete _value;
			delete _c;
		}

	private:
		std::ostringstream _steam;
		ssa::xmClass *_c;
	};

	const std::regex REG_INT8("\\s*[I|i][N|n][T|t]8\\s*");
	const std::regex REG_UINT8("\\s*[U|u][I|i][N|n][T|t]8\\s*");
	const std::regex REG_INT16("\\s*[I|i][N|n][T|t]16\\s*");
	const std::regex REG_UINT16("\\s*[U|u][I|i][N|n][T|t]16\\s*");
	const std::regex REG_INT32("\\s*[I|i][N|n][T|t]3?2?\\s*");
	const std::regex REG_UINT32("\\s*[U|u][I|i][N|n][T|t]3?2?\\s*");
	const std::regex REG_INT64("\\s*[I|i][N|n][T|t]64\\s*");
	const std::regex REG_UINT64("\\s*[U|u][I|i][N|n][T|t]64\\s*");
	const std::regex REG_FLOAT("\\s*[F|f][L|l][O|o][A|a][T|t]\\s*");
	const std::regex REG_DOUBLE("\\s*[D|d][O|o][U|u][B|b][L|l][E|e]\\s*");
	const std::regex REG_BUFFER("\\s*[B|b][U|u][F|f][F|f][E|e][R|r]\\s*");
	const std::regex REG_STRING("\\s*[S|s][T|t][R|r][I|i][N|n][G|g]\\s*");

	ssa::xmEDataType ParseType(std::string name);

	struct _Xml_data
	{
		std::string _Name;
		std::string _Dataset_name;
		ssa::xmEDataType _Type;
		cpknife::any _Value;
		size_t _Size;
		bool _Watch;
	};

	struct _Xml_data_set
	{
		std::string _Name;
		bool _Watch;
		std::vector<_Xml_data> _Datas;
	};

	_Xml_data_set* ParseDataSet(tinyxml2::XMLElement* node);

	_Xml_data* ParseData(tinyxml2::XMLElement* n, bool pwatched);

	std::vector<UINT8> ParseBuffer(std::string& s, bool hex);

	void SetInitValue(tinyxml2::XMLElement* n, _Xml_data& data);
}

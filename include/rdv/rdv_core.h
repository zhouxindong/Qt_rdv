#pragma once

#include "base.h"
#include "vdr.h"
#include "accesspoint.h"
#include "rdv_conf.h"
#include <set>
#include <type_traits>
#include <initializer_list>
#include "any.h"
#include "any_bag.h"
#include "ajson.h"

#ifdef RDV_EXPORTS
#define RDV_API __declspec(dllexport)
#define RDV_TEMPLATE_API __declspec(dllexport)
#else
#define RDV_API __declspec(dllimport)
#define RDV_TEMPLATE_API
#endif

namespace HJYD_GSA
{
#pragma region rdv_exceptions

	/*
	** exceptions rdv
	*/
	class RDV_API rdv_exception
	{
	public:
		rdv_exception(const std::string msg = std::string("")) : _msg(msg) {}
		const std::string Msg() const { return _msg; }
	private:
		std::string _msg;
	};

	class RDV_API vdr_created_fail :		public rdv_exception {};
	class RDV_API dataset_not_found :		public rdv_exception {};
	class RDV_API data_redupli :			public rdv_exception {};
	class RDV_API node_redupli :			public rdv_exception {};
	class RDV_API datatype_unsupported :	public rdv_exception {};
	class RDV_API node_not_found :			public rdv_exception {};
	class RDV_API access_point_redupli :	public rdv_exception {};

	class RDV_API bad_operation :			public rdv_exception 
	{
		using rdv_exception::rdv_exception;
	};

#pragma endregion

	/*
	** simplify user to get data value
	*/
	class RDV_API valuer
	{
	public:
		valuer(std::function<void(cpknife::any&)> functor = 
			[](cpknife::any&) {})
			: _functor(functor) {}

		void call(cpknife::any& a) {
			_functor(a);
		}
	private:
		std::function<void(cpknife::any&)> _functor;
	};

	/*
	** provide APIs to simplify xmVDR
	*/
	class RDV_API rdv : public ssa::xmMsgHandler
	{
	public:
		rdv(const rdv_conf& conf, long time_out_ms = 15000)
			throw (vdr_created_fail);
		virtual ~rdv();

	public: // vdr 
		/*
		** add data set to vdr
		** @overrided = true, rebuild data set if exists
		*/
		bool add_dataset(std::string name, bool overrided = true);
		bool remove_dataset(std::string name);

		/*
		** add data to dataset
		** @data_type: all valuable and string
		** @size: effect when data_type is string
		*/
		bool add_basic_data(
			std::string data_name,
			std::string dataset_name,
			ssa::xmEDataType data_type,
			int size = 1024)
			throw (datatype_unsupported, dataset_not_found, data_redupli);

		/*
		** add UINT8[]
		** after add operation, data initialized complete
		*/
		bool add_buffer(
			std::string data_name,
			std::string dataset_name,
			UINT8 buf[],
			size_t size
		);

		/*
		** add customed data struct
		** just like a bag for properties
		** @size: data struct buffer
		*/
		bool add_struct(
			std::string data_name,
			std::string dataset_name,
			size_t size = 1024
		);

		/*
		** add customed class
		** you must defined class before
		*/
		bool add_class(
			std::string data_name,
			std::string dataset_name,
			size_t size = 1024
		);

		bool remove_data(std::string name);

		/*
		** add a node link to the special dataset
		*/
		bool add_node(
			std::string node_name,
			std::string dataset_name,
			ssa::xmENodeType node_type = ssa::xmENodeType::xmENT_WORK)
			throw (dataset_not_found, node_redupli);
		bool remove_node(std::string name);

		/*
		** add a access point to special node
		** full means full functions of AP
		*/
		bool add_full_access_point(
			std::string ap_name,
			std::string node_name)
			throw (node_not_found, access_point_redupli);

		/*
		** add a read-only access point
		** only can receive data from vdr
		*/
		bool add_read_access_point(
			std::string name
		);

		/*
		** get the AP by name(created youself before)
		*/
		ssa::xmAccessPoint* GetAP(std::string name);

		/*
		** get the read-only AP(you can call GetValue())
		*/
		ssa::xmAccessPoint* GetReadAP();

		/*
		** create|get the AP and attach to dataset
		** (so you can write the data of dataset)
		*/
		ssa::xmAccessPoint* GetAuthorizeAP(std::string dataset);

		/*
		** create|get the AP to the data, so you can write value
		*/
		ssa::xmAccessPoint* AuthorizeData(std::string data);

		/*
		** import data and dataset from xml
		*/
		ssa::xmAccessPoint* import_ds_xml(std::string xml_file);

		/*
		** config vdr time tick handler
		*/
		bool set_tick_handler();

		void set_response_cmd(bool b);

		/*
		** add data that you want to get value when it update
		** the data that others added and you only get value
		** call-back function get_value()
		*/
		bool watch(
			std::string watched_data,
			ssa::xmEDataType data_type,
			valuer get_value);

		void unwatch(
			std::string name);

		/*
		** add data that you want to dispatch() handle
		*/
		bool watch_dispatch(
			std::string watched_data);

		void watch_dispatch(std::initializer_list<std::string> list);

		/*
		** add all data in the dataset to watch
		*/
		void watch_dataset_dispatch(std::string dataset_name);

	public: // data get|set
		template <typename T>
		bool write_number(
			ssa::xmAccessPoint& ap,
			std::string name, T val) const;

		bool write_string(ssa::xmAccessPoint& ap,
			std::string name, std::string text) const;

		bool write_buffer(
			ssa::xmAccessPoint& ap,
			std::string name,
			UINT8 buf[],
			size_t size) const;

		bool write_struct(
			ssa::xmAccessPoint& ap,
			std::string name,
			cpknife::BAG_object prop_bag) const;

		template <typename _Ty>
		bool write_class(
			ssa::xmAccessPoint& ap,
			std::string name,
			_Ty o) const;

	public: // ÷∏¡ÓœÏ”¶
		virtual void on_load() {}
		virtual void on_init() {}
		virtual void on_start() {}
		virtual void on_freeze() {}
		virtual void on_unfreeze() {}
		virtual void on_speed(int step) {}
		virtual void on_finish() {}

	private:

		/*
		** detect dataset with speical name has exists in VDR
		*/
		std::pair<bool, ssa::xmDataSet> has_dataset(std::string name);

		bool has_data(std::string name);

		ssa::xmDataSet check_add(std::string data_name, std::string dataset_name);

		bool has_node(std::string name);

		bool has_access_point(std::string name);

		ssa::xmAccessPoint* get_access_point(std::string name);

		std::pair<valuer, ssa::xmEDataType> get_valuer(std::string data_name);

		/*
		** set initialize value for the data
		*/
		void init_data(
			ssa::xmData& data,
			ssa::xmEDataType data_type,
			int size = 1024
		) throw (datatype_unsupported);

		/*
		** get real data from MSGDataEvent
		*/
		cpknife::any extract(
			const ssa::xmMSGDataEvent& msg,
			ssa::xmEDataType data_type);

		/*
		** get data buffer
		*/
		cpknife::any extract_buffer(
			const ssa::xmValue& val_buf
		);

		/*
		** get struct
		*/
		cpknife::any extract_struct(
			const std::string json_text
		);

		cpknife::any extract_class(
			const std::string text
		);

		void _Add_buffer(_Xml_data& d);

	private:
		rdv_conf _conf;
		ssa::xmMCastVDRAttr _vdr_attr;
		ssa::xmVDR _vdr;

	public:
		ssa::xmVDR& raw_vdr() {
			return _vdr;
		}

	private:
		std::set<std::string> _datasets;
		std::set<std::string> _nodes;
		std::map<
			std::string,
			std::pair<ssa::xmAccessPoint*, bool>> _access_points;

	private:
		const std::string _INNER_TICK;
		const std::string _WATCH_AP;
		std::map<std::string,
			std::pair<valuer, ssa::xmEDataType>> _valuers;
		int _step{ 1 };

	public:
		/*
		** VDR tick handler
		*/
		virtual void OnTick(const ssa::xmMSGTimerClick& msg) {}

		/*
		** Data event handler
		*/
		void OnData(const ssa::xmMSGDataEvent& msg);
		/*
		** transfer raw data event
		*/
		virtual void dispatch_data(const ssa::xmMSGDataEvent& msg) {}

		//virtual void OnBulletin(const ssa::xmMSGBulletin& msg) {}

		xmCREATE_MESSAGE_MAP(rdv)
	};

	template<typename T>
	inline bool rdv::write_number(ssa::xmAccessPoint& ap,
		std::string name, T val) const
	{
		if (!std::is_arithmetic<T>::value)
			throw bad_operation("write_number() need a arithmetic parameter");

		auto tokened = ap.GetToken();
		if (!tokened) return false;
		auto op_rst = ap.SetValue(name.c_str(), val);
		return op_rst > 0;
	}

	template<typename _Ty>
	inline bool rdv::write_class(
		ssa::xmAccessPoint & ap, 
		std::string name, _Ty o) const
	{
		ostringstream oss;
		cpknife::save_to(oss, o);
		return write_string(ap, name, oss.str());
	}
}
	
﻿#ifndef CONFIGMGR_H
#define CONFIGMGR_H
#include "ChatMgrGlobal.h"
#include "Global.h"
#include <boost/filesystem.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
struct CHAT_MGR_EXPORT SectionInfo {
	SectionInfo() {}
	~SectionInfo() {
		_section_datas.clear();
	}

	SectionInfo(const SectionInfo &src) {
		_section_datas = src._section_datas;
	}

	SectionInfo &operator=(const SectionInfo &src) {
		if (&src == this) {
			return *this;
		}

		this->_section_datas = src._section_datas;
		return *this;
	}

	std::map<std::string, std::string> _section_datas;
	std::string operator[](const std::string &key) {
		if (_section_datas.find(key) == _section_datas.end()) {
			return "";
		}
		// 这里可以添加一些边界检查
		return _section_datas[key];
	}
};

class CHAT_MGR_EXPORT ConfigMgr {
public:
	ConfigMgr();
	~ConfigMgr() {
		_config_map.clear();
	}
	SectionInfo operator[](const std::string &section) {
		if (_config_map.find(section) == _config_map.end()) {
			return SectionInfo();
		}
		return _config_map[section];
	}

	ConfigMgr &operator=(const ConfigMgr &src) {
		if (&src == this) {
			return *this;
		}

		this->_config_map = src._config_map;
	};

	ConfigMgr(const ConfigMgr &src) {
		this->_config_map = src._config_map;
	}

private:
	// 存储section和key-value对的map
	std::map<std::string, SectionInfo> _config_map;
};

extern ConfigMgr gConfigMgr;
#endif
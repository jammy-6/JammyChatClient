﻿#pragma execution_character_set("utf-8")
#include "ConfigMgr.h"
#include <qdebug.h>
ConfigMgr::ConfigMgr(){
    // 获取当前工作目录  
    // boost::filesystem::path current_path = boost::filesystem::current_path();
    // // 构建config.ini文件的完整路径  
    // boost::filesystem::path config_path = current_path / "config.ini";
    std::string config_path = PROJECT_DIR + std::string("/Config.ini");
    qDebug() << "读取到配置文件如下：-----------------------";
    qDebug()<<QString::fromStdString(config_path);

    // 使用Boost.PropertyTree来读取INI文件  
    boost::property_tree::ptree pt;
    boost::property_tree::read_ini(config_path, pt);


    // 遍历INI文件中的所有section  
    for (const auto& section_pair : pt) {
        const std::string& section_name = section_pair.first;
        const boost::property_tree::ptree& section_tree = section_pair.second;

        // 对于每个section，遍历其所有的key-value对  
        std::map<std::string, std::string> section_config;
        for (const auto& key_value_pair : section_tree) {
            const std::string& key = key_value_pair.first;
            const std::string& value = key_value_pair.second.get_value<std::string>();
            section_config[key] = value;
        }
        SectionInfo sectionInfo;
        sectionInfo._section_datas = section_config;
        // 将section的key-value对保存到config_map中  
        _config_map[section_name] = sectionInfo;
    }

    // 输出所有的section和key-value对  
    for (const auto& section_entry : _config_map) {
        const std::string& section_name = section_entry.first;
        SectionInfo section_config = section_entry.second;
        qDebug() << "[" << QString::fromStdString(section_name) << "]";
        for (const auto& key_value_pair : section_config._section_datas) {
            qDebug() << QString::fromStdString(key_value_pair.first)
                << "=" << QString::fromStdString(key_value_pair.second);
        }
    }

}


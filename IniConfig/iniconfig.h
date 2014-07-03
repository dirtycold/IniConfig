#ifndef INICONFIG_H
#define INICONFIG_H

#include "export.h"
#include "global.h"
#include <map>
#include <iostream>

namespace rp
{

class IniConfig;
typedef std::map<std::string, std::string> stringmap;
typedef std::vector<double> dataseries;

}

class rp::IniConfig
{

public:
    /**
     * @brief 构造函数
     * @param filepath 指定配置文件的路径和文件名
     */
    INI IniConfig (const std::string &filepath);

    INI ~IniConfig ();
    /**
     * @brief 转换字符缓冲为配置关系表
     * @param stream 指定的字符缓冲
     * @note 默认为附加式读取，即现有配置不变
     * @warning 若键值与现有条目重复，会被忽略
     */
    INI void map (std::stringstream &stream);
    /**
     * @brief 重新转换配置关系表
     * @param stream 指定的字符缓冲
     * @warning 会清除现有条目
     */
    INI void remap (std::stringstream &stream);
    /**
     * @brief 清除现有配置关系表
     */
    INI void clear ();

    /**
     * @brief 取得特定键值的配置内容
     * @param key 指定的键值
     * @return 键值的内容
     */
    INI std::string value (const std::string &key);
    /**
     * @brief 取得特定键值的配置内容，并转换为双精度浮点数
     * @param key 指定的键值
     * @return 键值的内容
     */
    INI double doubleValue (const std::string &key);
    /**
     * @brief 取得特定键值的配置内容，并转换为整型
     * @param key 指定的键值
     * @return 键值的内容
     */
    INI int intValue (const std::string &key);
    /**
     * @brief 取得特定键值的配置内容，以花括号识别等号分割，并转换为数据序列
     * @param key 指定的键值
     * @return 键值的数据序列
     */
    INI rp::dataseries dataSeries(const std::string &key);

    /**
     * @brief 设定配置键值的内容
     * @param key 指定的键值
     * @param value 键值的内容
     */
    INI void set (const std::string &key, const std::string &value);
    /**
     * @brief 设定配置键值的内容
     * @param key 指定的键值
     * @param value 键值的内容,双精度浮点
     */
    INI void set (const std::string &key, const double &value);
    /**
     * @brief 设定配置键值的内容
     * @param key 指定的键值
     * @param value 键值的内容,整型
     */
    INI void set (const std::string &key, const int &value);
    /**
     * @brief 设定配置键值的数据序列
     * @param key 指定的键值
     * @param v 数据序列
     */
    INI void setDataSeries(const std::string &key, const rp::dataseries &v);
    /**
     * @brief 导出配置关系表到字符缓冲
     * @param stream 指定的字符缓冲
     * @param verbose 是否输出为调试格式
     * @note 调试格式仅用来调试,无法用于配置的保存
     */
    INI void dump(std::stringstream &stream, bool verbose = false);
    /**
     * @brief 导出现有配置关系表
     * @return 现有配置关系表的 const reference
     */
    INI const rp::stringmap &mapRef();

protected:
    /**
     * @brief 读取配置文件的内容,默认初始化动作
	 * @note 自动调用 map()
     */
    void read();
    /**
     * @brief 写入配置文件的内容,默认结束时动作
	 * @note  自动调用 dump()
     */
    void write();

protected:
    std::string m_filepath;
    rp::stringmap m_map;
};

#endif // INICONFIG_H

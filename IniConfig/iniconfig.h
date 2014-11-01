#ifndef INICONFIG_H
#define INICONFIG_H

#include <iostream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <cmath>

#ifdef _MSC_VER
#define INI __declspec(dllexport)
#else
#define INI __attribute__((visibility("default")))
#endif

namespace RP {
//namespace begin

class IniConfig;
class IniConfigPrivate;
typedef std::vector<std::string> StringList;
typedef std::map<std::string, std::string> StringMap;
typedef std::vector<double> DataSeries;

} // end of namespace

class RP::IniConfig
{

public:
	
	/**
	 * @brief 访问等级
	 * @enum ReadOnly 只读访问，最终不保存修改
	 * @enum ReadWrite 读写访问，最终保存修改，并格式化配置内容（去掉注释、键值排序等）
	 * 
	 */
    enum Access
    {
        ReadOnly,
        ReadWrite
    };

    /**
     * @brief 构造函数
     * @param filepath 指定配置文件的路径和文件名
     * @param readonly 指定是否为只读模式，避免文件写入操作
     */
    INI IniConfig (const std::string &filepath, Access access = ReadWrite);

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
    INI std::string value (const std::string &key) const;

    /**
     * @brief 取得特定键值的配置内容，并转换为双精度浮点数
     * @param key 指定的键值
     * @return 键值的内容
     */
    INI double doubleValue (const std::string &key) const;

    /**
     * @brief 取得特定键值的配置内容，并转换为整型
     * @param key 指定的键值
     * @param base 整数转换用的基值
     * @return 键值的内容
     */
    INI int intValue (const std::string &key, unsigned int base = 10) const;

	/**
     * @brief 取得特定键值的配置内容，并转换为整型
     * @param key 指定的键值
     * @return 键值的内容转换为bool变量，内部存储使用整型
     */
    INI bool boolValue(const std::string &key) const;

    /**
     * @brief 取得特定键值的配置内容，以花括号识别逗号分割，并转换为数据序列
     * @param key 指定的键值
     * @return 键值的数据序列
     */
    INI RP::DataSeries dataSeries(const std::string &key) const;

    /**
     * @brief 设定配置键值的内容
     * @param key 指定的键值
     * @param value 键值的内容
     * @warning 若以临时变量形式设定值，请务必使用 std::string 将其初始化，否则在 gcc 下可能被认定为 boolean 类型，导致存储错误的值
     */
    INI void set (const std::string &key, const std::string &value);

    /**
     * @brief 设定配置键值的内容
     * @param key 指定的键值
     * @param value 键值的内容，双精度浮点
     */
    INI void set (const std::string &key, const double &value);

    /**
     * @brief 设定配置键值的内容
     * @param key 指定的键值
     * @param value 键值的内容，整型
     * @warning 暂时不支持 10进制 之外基值的整数写入
     */
    INI void set (const std::string &key, const int &value);

    /**
     * @brief 设定配置键值的数据序列
     * @param key 指定的键值
     * @param v 数据序列
     */
    INI void set(const std::string &key, const DataSeries &data);

    /**
     * @brief 导出配置关系表到字符缓冲
     * @param stream 指定的字符缓冲
     * @param verbose 是否输出为调试格式
     * @note 调试格式仅用来调试，无法用于配置的保存
     */
    INI void dump(std::stringstream &stream, bool verbose = false) const;

    /**
     * @brief 导出现有配置关系表
     * @return 现有配置关系表的 const reference
     */
    INI const RP::StringMap &mapRef() const;

    /*
     * 注意：这两个方法本是构造函数和析构函数的一部分。
     * 现已声明为 public, 以便于使用此类的程序可以在任何时候进行读取和保存。
     * 请牢记，多个实例同时修改同一个配置文件将会得到不可预计的结果。这样会导致
     * 他们内部的配置关系表会存在差异，这也是一开始这两个方法被声明为 protected
     * 的原因。
     *
     * 简单来说：写入方法不是线程安全的。
     * 而且同线程内也是不安全的...
     *
     * 使用前请三思。
     */

    /**
     * @brief 读取配置文件的内容,默认初始化动作
	 * @note 自动调用 map()
     */
    INI void read();

    /**
     * @brief 写入配置文件的内容,默认结束时动作
     * @note 自动调用 dump()
     * @warning 不要多实例同时写入
     */
    INI void write();

protected:
    IniConfigPrivate *p;
};

#endif // INICONFIG_H

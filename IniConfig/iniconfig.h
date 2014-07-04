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
typedef std::vector<std::string> StringList;
typedef std::map<std::string, std::string> StringMap;
typedef std::vector<double> DataSeries;

// trimming

/*
 * derived from
 *
 * 1. http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
 *    by Evan Teran
 *
 * and
 *
 * 2. http://stackoverflow.com/questions/479080/trim-is-not-part-of-the-standard-c-c-library
 *    by BobbyShaftoe
 *
 */

static const std::string whiteSpaces( " \f\n\r\t\v;" );

// trim from start
static inline std::string &ltrim(std::string &s)
{
    s.erase(0 , s.find_first_not_of(whiteSpaces));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s)
{
    s.erase(s.find_last_not_of(whiteSpaces) + 1);
    return s;
}

// trim from both ends
static inline std::string trim(const std::string &s) {
    std::string t = s;
    return ltrim(rtrim(t));
}

// splitting

static inline StringList split(const std::string &s, char d)
{
    StringList list;
    std::istringstream stream(s);
    std::string line;

    while (std::getline(stream,line,d))
    {
        line = trim(line);
        if (!line.empty())
        {
            list.push_back(line);
        }
    }
    return list;
}

// converting

static inline double toDouble(const std::string &s)
{
    double d = strtod(s.c_str(),NULL);
    return d;
}

static inline int toInt(const std::string &s, unsigned int base = 10)
{
    int i = strtol(s.c_str(),NULL,base);
    return i;
}

static inline std::vector<double> toDataSeries(const std::string &s)
{
    std::vector<double> v;
    if (s.empty())
        return v;
    std::string s2 = s;
    s2 = trim(s2);
    if (s2.at(0) == '{' && s.at(s.size()-1) == '}')
    {
        s2 = s2.erase(0,1);
        s2 = s2.erase(s.size() -2,s.size()-1);
        StringList l = split(s2,',');
        for (unsigned int i = 0; i < l.size(); ++i)
        {
            v.push_back(toDouble(l.at(i)));
        }
    }
    return v;
}

template <typename T>
static inline std::string toString(T t){
    std::stringstream s;
    //ensure bool is bool :)
    s << std::boolalpha << std::setprecision (12) << t;
    return s.str();
}

// math
#ifdef _MSC_VER
// MSDN reference
static const unsigned long nan[2]={0xffffffff, 0x7fffffff};
static const double NaN = *(double *)nan;
#else
static const double NaN = NAN;
#endif

#ifdef _MSC_VER
static inline int round(double x)
{
    double xx = int(x);
    double r = x - xx;
    if (std::abs(r) < 0.5)
    {
        return int(xx);
    }
    else
    {
        return x>0?int(xx+1):int(xx-1);
    }
}
#else
#define round round
#endif

// variables
//unused variable
#define UNUSED(x) (void)x

} // end of namespace

class RP::IniConfig
{

public:
    /**
     * @brief 构造函数
     * @param filepath 指定配置文件的路径和文件名
     * @param readonly 指定是否为只读模式，避免文件写入操作
     */
    INI IniConfig (const std::string &filepath, bool readonly = false);

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
    INI RP::DataSeries dataSeries(const std::string &key);

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
    INI void set(const std::string &key, const DataSeries &v);
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
    INI const RP::StringMap &mapRef();

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
    bool m_readonly;
    std::string m_filepath;
    RP::StringMap m_map;
};

#endif // INICONFIG_H

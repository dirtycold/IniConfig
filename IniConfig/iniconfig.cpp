#include "iniconfig.h"
#include <fstream>
#include <stdexcept>

// #define INI_CONFIG_NO_EXCEPTION

namespace RP {

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
    std::string s2 = trim(s);
    //s2 = trim(s2);
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

}

using namespace RP;

const std::string NonExistKeyString = "key not exist";

class RP::IniConfigPrivate
{
public:
    std::string m_filepath;
    bool m_readonly;
    RP::StringMap m_map;
};

IniConfig::IniConfig(const std::string &filepath, bool readonly)
{
    p = new IniConfigPrivate();
    p->m_filepath = filepath;
    p->m_readonly = readonly;
    read();
}

IniConfig::~IniConfig()
{
    if(!p->m_readonly)
        write();
    delete p;
}

void IniConfig::map(std::stringstream &stream)
{
    std::string line;
    RP::StringList list;
    char c;
    while (std::getline(stream,line))
    {
        //discard nested comments
        list = RP::split(line,'/');
        if (!list.empty())
        {
            //get comments removed
            line = list.at(0);
            //read key and value
            list = RP::split(line,'=');
            if (!list.empty())
            {
                c = list.front().at(0);
                if (c == '[' || c == '#' || c == '/')
                {
                    continue;
                }
                else if (list.size() == 2)
                {
                    p->m_map.insert(std::make_pair(list.front(),list.back()));
                }
            }
        }
    }
}

void IniConfig::remap(std::stringstream &stream)
{
    clear();
    map(stream);
}

void IniConfig::clear()
{
    p->m_map.clear();
}

std::string IniConfig::value(const std::string &key) const
{
    if (p->m_map.find(key) != p->m_map.end())
    {
        return p->m_map[key];
    }
    else
    {
#ifndef INI_CONFIG_NO_EXCEPTION
        throw std::invalid_argument(NonExistKeyString + ": " + "'" + key + "'");
#endif
        return "";
    }
}

double IniConfig::doubleValue(const std::string &key) const
{
    std::string s = value(key);
    if (!s.empty())
        return RP::toDouble(s);
    else
        return RP::NaN;
}

int IniConfig::intValue(const std::string &key, unsigned int base) const
{
    std::string s = value(key);
    if (!s.empty())
        return toInt(s,base);
    else
        return int(RP::NaN);
}

bool IniConfig::boolValue(const std::string &key) const
{
	int value = intValue(key);
	if (value == 0)
		return false;
	else
		return true;
}
DataSeries IniConfig::dataSeries(const std::string &key) const
{
    std::string line = value(key);
    return RP::toDataSeries(line);
}

void IniConfig::set(const std::string &key, const std::string &value)
{
    if (p->m_map.find(key) != p->m_map.end())
        p->m_map[key]=value;
    else
        p->m_map.insert(std::make_pair(key,value));
}

void IniConfig::set(const std::string &key, const double &value)
{
    set (key,RP::toString(value));
}

void IniConfig::set(const std::string &key, const int &value)
{
    set (key,RP::toString(value));
}

void IniConfig::set(const std::string &key, const RP::DataSeries &data)
{
    std::stringstream stream;
    if (data.empty())
    {
        return;
    }
    stream << "{";
    for (unsigned int i=0; i < data.size()-1; ++i)
    {
        stream << data.at(i) << ",";
    }
    stream << data.at(data.size()-1);
    stream << "}";
    set(key,stream.str());
}

void IniConfig::dump(std::stringstream &stream, bool verbose) const
{
    RP::StringMap::const_iterator it;
    std::string key;
    std::string value;
    if (verbose)
    {
        key = "key:";
        value = " value:";
    }
    else
    {
        key = "";
        value = "=";
    }

    for (it = p->m_map.begin();it!=p->m_map.end();it++)
    {
        stream << key + it->first << value << it->second << std::endl;
    }
}

const StringMap &IniConfig::mapRef() const
{
    return p->m_map;
}

void IniConfig::read()
{
    std::ifstream file;
    std::stringstream in;
    file.open(p->m_filepath.c_str());
    if(!file.is_open())
        return;
    in << file.rdbuf();
    map(in);
    file.close();
}

void IniConfig::write()
{
    // in case of wrong encoding etc.
    // this prevents removal of file content
    if (!p->m_map.empty())
    {
        std::ofstream file;
        std::stringstream in;
        file.open(p->m_filepath.c_str(),std::ios::out);
        if (!file.is_open())
            return;
        dump(in,false);
        file << in.rdbuf();
        file.close();
    }
}

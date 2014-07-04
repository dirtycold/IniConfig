#include "iniconfig.h"
#include <fstream>

using namespace RP;

IniConfig::IniConfig(const std::string &filepath, bool readonly)
    :m_filepath(filepath),m_readonly(readonly)
{
    read();
}

IniConfig::~IniConfig()
{
    if(!m_readonly)
        write();
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
                if (c == '[' || c == '#')
                {
                    continue;
                }
                else if (list.size() == 2)
                {
                    m_map.insert(std::make_pair(list.front(),list.back()));
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
    m_map.clear();
}

std::string IniConfig::value(const std::string &key)
{
    if (m_map.find(key) != m_map.end())
        return m_map[key];
    else
        return "";
}

double IniConfig::doubleValue(const std::string &key)
{
    std::string s = value(key);
    if (!s.empty())
        return RP::toDouble(s);
    else
        return RP::NaN;
}

int IniConfig::intValue(const std::string &key)
{
    std::string s = value(key);
    if (!s.empty())
        return toInt(s);
    else
        return int(RP::NaN);
}

DataSeries IniConfig::dataSeries(const std::string &key)
{
    std::string line = value(key);
    return RP::toDataSeries(line);
}

void IniConfig::set(const std::string &key, const std::string &value)
{
    if (m_map.find(key) != m_map.end())
        m_map[key]=value;
    else
        m_map.insert(std::make_pair(key,value));
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

void IniConfig::dump(std::stringstream &stream, bool verbose)
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

    for (it = m_map.begin();it!=m_map.end();it++)
    {
        stream << key + it->first << value << it->second << std::endl;
    }
}

const StringMap &IniConfig::mapRef()
{
    return m_map;
}

void IniConfig::read()
{
    std::ifstream file;
    std::stringstream in;
    file.open(m_filepath.c_str());
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
    if (!m_map.empty())
    {
        std::ofstream file;
        std::stringstream in;
        file.open(m_filepath.c_str(),std::ios::out);
        if (!file.is_open())
            return;
        dump(in,false);
        file << in.rdbuf();
        file.close();
    }
}

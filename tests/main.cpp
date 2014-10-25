#include "../IniConfig/iniconfig.h"
#include <stdexcept>

int main(int argc, char* argv[])
{
    RP::IniConfig ini ("config.cfg");
    ini.set ("interger",321);
    ini.set ("float",88.88);
    ini.set ("string",/*std::string*/("test string with whitespace."));
    ini.set ("boolean",true);
    ini.set ("boolean2",false);
    ini.set ("data series",std::string("{5,4,3,2,1}"));

    std::cout << "interger" << " " << ini.intValue ("interger",16) << std::endl;
    std::cout << "float" << " " << ini.doubleValue ("float") << std::endl;
    std::cout << "string" << " " << ini.value ("string") << std::endl;
    std::cout << std::boolalpha << "boolean" << " " << ini.boolValue ("boolean") << std::endl;
    std::cout << std::boolalpha << "boolean2" << " " << ini.boolValue ("boolean2") << std::endl;
    RP::DataSeries data = ini.dataSeries ("data series");
    RP::DataSeries::const_iterator it;
    std::cout << "data series" << std::endl;
    for (it = data.begin (); it != data.end (); ++it)
    {
        std::cout << *it << std::endl;
    }
    std::cout << std::endl;
    try
    {
        std::cout << ini.value ("non exist") << std::endl;
    }
    catch (std::invalid_argument e)
    {
        std::cout << e.what () << std::endl;
    }

}

#include "../IniConfig/iniconfig.h"

int main(int argc, char* argv[])
{
    // UNUSED(argc);
    // UNUSED(argv);

    RP::IniConfig ini ("config.cfg");
    RP::DataSeries data = ini.dataSeries("data");
    for (unsigned int i = 0; i < data.size(); ++i)
    {
        std::cout << data.at (i) << std::endl;
    }
    std::cout << ini.intValue("value") << " " << ini.doubleValue ("value2") << " " << ini.value ("token");
    std::cout << std::boolalpha << ini.boolValue ("b1") << ini.boolValue ("b2");
    ini.set ("data","{5,4,3,2,1}");
    ini.set ("value2",88.88);
    ini.set ("token","token_string");
    std::cout << std::endl;
    ini.set ("new",data);
    ini.set ("b1",true);
    ini.set ("b2",false);

    std::string s1="            Hello               ";
    std::cout << s1 << std::endl;
    std::string s2 = /*RP::trim*/(s1);
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    RP::DataSeries data1;
    data1.push_back(12.34);

    ini.set ("d1",data1);
}

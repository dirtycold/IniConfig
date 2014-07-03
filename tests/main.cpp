#include "../IniConfig/iniconfig.h"

int main(int argc, char* argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    IniConfig ini ("config.cfg");
    std::vector<double> data = ini.dataSeries("data");
    for (unsigned int i = 0; i < data.size(); ++i)
    {
        std::cout << data.at (i) << std::endl;
    }
    std::cout << ini.intValue("value") << " " << ini.doubleValue ("value2") << " " << ini.value ("token");
    ini.set ("data","{5,4,3,2,1}");
    ini.set ("value2",88.88);
    ini.set ("token","token_string");
    std::cout << std::endl;
    ini.setDataSeries ("new",data);

    std::string s1="            Hello               ";
    std::cout << s1 << std::endl;
    std::string s2 = rp::trim(s1);
    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::vector<double> data1;
    data1.push_back(12.34);

    ini.setDataSeries("d1",data1);
}


#ifndef INICONFIG_GLOBAL_H
#define INICONFIG_GLOBAL_H

#ifdef _MSC_VER
#define INI __declspec(dllexport)
#else
#define INI __attribute__((visibility("default")))
#endif

#endif // INICONFIG_GLOBAL_H

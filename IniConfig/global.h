#ifndef TOOLS_H
#define TOOLS_H

#include <vector>
#include <sstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iomanip>

namespace rp {

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

typedef std::vector<std::string> stringlist;

static inline stringlist split(const std::string &s, char d)
{
    stringlist list;
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

static inline int toInt(const std::string &s)
{
    return int(toDouble(s));
}

//static inline bool toBool(const std::string &s)
//{
//    if (s == "true")
//        return true;
//    else
//        return false;
//}

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
        stringlist l = split(s2,',');
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


}

#endif // TOOLS_H

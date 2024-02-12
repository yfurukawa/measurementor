#include <ctime>
#include <iostream>
#include <string>
#include <time.h>
#include "../FromISO8601String.hpp"

int main()
{
    std::string d0("20240210T123456Z");
    std::string d1("20240210T123456+0900");
    std::string d2("2024-02-10T21:34:56+09:00");
    std::string d3("20240210T123456-0900");
    std::string d4("2024-02-10T21:34:56-09:00");

    time_t t0 = ToTimePoint( d0 );
    time_t t1 = ToTimePoint( d1 );
    time_t t2 = ToTimePoint( d2 );
    time_t t3 = ToTimePoint( d3 );
    time_t t4 = ToTimePoint( d4 );
    
    std::cout << t0 << " : " << std::ctime(&t0) << std::endl;
    std::cout << t1 << " : " << std::ctime(&t1) << std::endl;
    std::cout << t2 << " : " << std::ctime(&t2) << std::endl;
    std::cout << t3 << " : " << std::ctime(&t3) << std::endl;
    std::cout << t4 << " : " << std::ctime(&t4) << std::endl;

}

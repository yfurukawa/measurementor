/*!
 @file      main.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <iostream>
#include <string>
#include "domain/PtsDataCollector.h"

int main(int argc, char* argv[])
{
  if (argc > 2)
  {
    std::cout << "引数に project または sprint を指定すること" << std::endl;
    exit(1);
  }
  measurementor::PtsDataCollector collector;
  
  if (argc == 1)
  {
    collector.collectAllData();
    collector.permanentProjectData();
    collector.permanentSprintData();
    exit(0);
  }

  std::string type(argv[1]);
  if (type == "project")
  {
    collector.collectAllData();
    collector.permanentProjectData();
  }
  else if (type == "sprint")
  {
    collector.collectAllData();
    collector.permanentSprintData();
  }
  else
  {
    std::cout << "引数に project または sprint を指定すること" << std::endl;
  }

  return 0;
}

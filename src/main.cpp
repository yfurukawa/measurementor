/*!
 @file      main.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include "domain/PtsDataCollector.h"

int main(int argc, char* argv[])
{
  measurementor::PtsDataCollector collector;
  collector.correctData();
  collector.permanentProjectData();
  collector.permanentSprintData();
  return 0;
}

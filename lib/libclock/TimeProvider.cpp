/*!
 @file      TimeProvider.cpp
 @attention 本コードは@usagiさんのQiita記事（https://qiita.com/usagi/items/ab8ec7014d1b1b1894d2）からの引用である
 @copyright Copyright 2016 Usagi Ito
*/
#include "TimeProvider.h"

TimeProvider::TimeProvider()
  : formatDateTime_("%FT%T")
  , formatTimeZone_("%z")
 {

 }

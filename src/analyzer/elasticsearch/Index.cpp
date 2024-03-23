/*!
 @file Index.cpp
 @copyright Copyright 2024 Yoshihiro Furukawa
*/
#include <algorithm>
#include <locale>
#include "Index.h"

namespace analyzer
{

analyzer::Index::Index(std::string index) : index_(index)
{
  this->convertCharactor();
}

std::string analyzer::Index::get() const
{
  return index_;
}

void analyzer::Index::convertCharactor()
{
  // White spaceは禁止なのでアンダースコアに変換
  std::transform( index_.begin(), index_.end(), index_.begin(), 
        [](unsigned char c) { return (c == ' ' ? '_' : c); }
    );

  // 大文字は禁止なので小文字に変換
  std::transform( index_.begin(), index_.end(), index_.begin(), 
        [](unsigned char c) { return std::tolower(c); }
    );

  // ハイフンは禁止なのでアンダースコアに変換
  std::transform( index_.begin(), index_.end(), index_.begin(), 
        [](unsigned char c) { return (c == '-' ? '_' : c); }
    );
}

}  // namespace analyzer

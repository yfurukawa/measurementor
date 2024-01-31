#include <regex>
#include "Hostname.h"

Hostname::Hostname(std::string hostname) : hostname_(std::move(hostname))
{
    // 最大255文字のホスト名を扱えるべきである。（RFC 1123 2.1項）
    if( hostname_.length() > 256 ) {
        std::__throw_invalid_argument("Hostname is to long");
    }

    // ホスト名はアルファベット、数字及びダッシュ(-)で構成されていなければならない
    std::regex invalidChar(R"([^a-zA-Z0-9-.])");
    if( std::regex_search(hostname_, invalidChar) ) {
        std::__throw_invalid_argument("Hostname must consist of letters, numbers and dashes (-)");
    }

    // ホスト名はダッシュ(-)で終わっていてはならない
    std::regex end(R"(.*-$)");
    if( std::regex_match(hostname_, end) ) {
        std::__throw_invalid_argument("Hostname does not have dash as end of charactor");
    }

    // ホスト名はピリオドで始まってはならない
    if( hostname_.find(".") == 0 ) {
        std::__throw_invalid_argument("Hostname does not start period");
    }

    // ホスト名がIPv4でないことを確認
    std::regex ipv4Regex(R"(^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$)");
    if( std::regex_match( hostname_, ipv4Regex) ) {
        std::__throw_invalid_argument("Hostname matches IPv4 format");
    }

}

std::string Hostname::get()
{
    return hostname_;
}

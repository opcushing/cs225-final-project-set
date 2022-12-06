#include "utilities.hpp"
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <vector>
#include <sstream>


// DONE: DecodeURL()
std::string DecodeURL(const std::string& url_str) {
  std::stringstream out;
  for (size_t i = 0; i < url_str.size(); ++i) {
    if (url_str[i] == '%') { // handle special character
      // dense code: takes the next two characters, converts to a base 16 int, 
      // then converts to a char, then stores in out
      out << (char)(std::stoi(url_str.substr(i+1, 2), nullptr, 16));
      i += 2; // skip the next two characters
    } else if (url_str[i] == '_') { // handle space
      out << (url_str[i+1] == '_' ? ": " : " ");
    } else {
      out << url_str[i];
    }
  }
  return out.str();
}

// All code below taken from CS225 mp_schedule utils.cc

std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

std::string TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of(" ") + 1);
}

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of(" "));
}

std::string Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}
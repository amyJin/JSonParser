#ifndef JSonObj_JSonObjParser_h
#define JSonObj_JSonObjParser_h

#include "JSonObj.h"

#include <string>

class JSonObjParser
{
private:
  JSonObjParser() {}

public:
  static bool Parse(std::string const &, JSonObj &);
  static bool ParseString(std::string &, JSonObj &);
  static bool PreProcess(std::string const &, std::string &);

private:
  //static bool PreProcess(std::string const &, std::string &);
  static void TrimSpace(std::string &);
};


#endif

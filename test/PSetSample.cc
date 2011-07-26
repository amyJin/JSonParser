#include <iostream>
#include "JSonObj.h"
#include "JSonObjParser.h"

int main()
{
  JSonObj pset;
  
  // parse a json string
  std::string storage;

  JSonObjParser::PreProcess("Sample.cfg", storage);

  JSonObjParser::ParseString(storage, pset);

  std::cout << "\npart = " << pset.getValue<int>("part") << "\n";

  std::cout << "\ntest = " << pset.getValue<bool>("test") << "\n";

  std::cout << "\ncode = " << pset.getValue<std::string>("code") << "\n";

  std::cout << "\nnames = ";
  std::vector<int> vs = pset.getVector<int>("names");
  std::vector<int>::const_iterator cit = vs.begin();
  while(cit!=vs.end()) {
    std::cout << *cit << ", ";
    ++ cit;
  }
  std::cout << "\n";

  std::cout << "\ncommands = \n";
  std::vector<JSonObj> vj = pset.getVector<JSonObj>("commands");
  std::vector<JSonObj>::const_iterator jit = vj.begin();
  while(jit != vj.end()) {
    JSonObj it = *jit;

    std::cout << "  command = " << it.getValue<std::string>("command") << "\n";
    std::cout << "  access key = " << it.getValue<std::string>("accessKey") << "\n";

    ++jit;
  }

  std::cout << "\n";

}

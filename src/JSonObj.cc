#include <iostream> // for print(). will be removed in future
#include <sstream>


#include "JSonObj.h"

#include "boost/lexical_cast.hpp"


typedef std::map<std::string, boost::any>   valuemap;
typedef std::vector<int>                    vint;
typedef std::vector<double>                 vdouble;
typedef std::vector<std::string>            vstring;
typedef std::vector<JSonObj>           		vJSonObj;

boost::any JSonObj::nil_obj;

namespace {

  bool isBool(boost::any const & obj)
       { return obj.type() == typeid(bool); }

  bool isJSonObj(boost::any const & obj)
       { return obj.type() == typeid(JSonObj); }

  bool isInt(boost::any const & obj)
       { return obj.type() == typeid(int); }

  bool isDouble(boost::any const & obj)
       { return obj.type() == typeid(double); }

  bool isString(boost::any const & obj)
       { return obj.type() == typeid(std::string); }

  bool isPrimitive(boost::any const & obj)
       { return obj.type() == typeid(std::string); }

  bool isVector(boost::any const & obj)
       { return obj.type() == typeid(std::vector<boost::any>); }

  void tab(int indent) 
       { for(int i=0;i<indent;++i) std::cout<<' ';}
}

bool JSonObj::insertEntryObj( 
       std::pair<std::string, boost::any> const & pair
     , bool overwrite)
{
  if (overwrite)
  {
    PSetMap.insert(pair);
    return true;
  }

  valuemap::iterator it = PSetMap.find(pair.first);

  if(it!=PSetMap.end())
    return false;

  PSetMap.insert(pair);
  return true;
}

boost::any * 
JSonObj::getJSonObjPtr(std::string const & name, bool bInsert)
{
  valuemap::iterator it = PSetMap.find(name);

  if(it!=PSetMap.end())
    return &(it->second);

  if(bInsert)
  {
    insertEntryObj(std::make_pair(name, boost::any()));
    return getJSonObjPtr(name, false);
  }
  else
  {
    throw std::runtime_error("Entry " + name + " not found!");
  }
}

boost::any  
JSonObj::getAnyJSonObj(std::string const & name) const
{
  valuemap::const_iterator it = PSetMap.find(name);

  if(it!=PSetMap.end())
    return it->second;

  return nil_obj;
}
    
template <typename T>
bool JSonObj::insertEntry(std::string const & name, T const & val, bool overwrite) 
{
  boost::any obj = val;

  if (overwrite)
  {
    PSetMap.insert(std::make_pair(name, obj));
    return true;
  }

  valuemap::iterator it = PSetMap.find(name);

  if(it!=PSetMap.end())
    return false;

  PSetMap.insert(std::make_pair(name, obj));
  return true;
}

vstring JSonObj::getNameList() const
{
  vstring names;

  valuemap::const_iterator it = PSetMap.begin();
  while(it!=PSetMap.end())
  {
    names.push_back(it->first);
    ++it;
  }

  return names;    
}

vstring JSonObj::getJSonObjNameList() const
{
  vstring names;

  valuemap::const_iterator it = PSetMap.begin();
  while(it!=PSetMap.end())
  {
    if(isJSonObj(it->second))  names.push_back(it->first);
    ++it;
  }

  return names;
}


// Get type
std::string JSonObj::getType(std::string const & name) const
{
  boost::any obj = getAnyJSonObj(name);

  return getType(obj);
}

std::string JSonObj::getType(boost::any const & obj) const
{
  if(isBool(obj))
    return "bool";

  if(isInt(obj))
    return "int";

  if(isDouble(obj))
    return "double";

  if(isString(obj))
    return "string";

  if(isVector(obj))
    return "vector";

  if(isJSonObj(obj))
    return "JSonObj";

  return "null";
}

// Print the JSonObj Object
void JSonObj::print(int indent) const
{
  valuemap::const_iterator it = PSetMap.begin();

  for(; it!=PSetMap.end(); ++it)
  {
    std::string name = it->first;
    boost::any obj   = it->second;

    tab(indent);
    //std::cout << getType(obj) << " ";
    std::cout << name << " : ";
    printElement(obj, indent);
    std::cout << "\n";
  }

}

void JSonObj::printElement(boost::any const & obj, int indent)
{
  if(obj.empty())
  {
    std::cout << "nil";
  }
  else if(isBool(obj))
  {
    std::cout << (boost::any_cast<bool>(obj) == 1? "true" : "false") ;
  }
  else if(isInt(obj))
  {
    std::cout << (boost::any_cast<int>(obj));
  }
  else if(isDouble(obj))
  {
    std::cout << (boost::any_cast<double>(obj));
  }
  else if(isString(obj))
  {
    std::cout << boost::any_cast<std::string>(obj);
  }
  //else if(isPrimitive(obj))
  //{
  //  std::cout << boost::any_cast<std::string>(obj);
  //}
  else if(isVector(obj))
  {
    std::vector<boost::any> v = boost::any_cast<std::vector<boost::any> >(obj);
    std::vector<boost::any>::const_iterator it = v.begin();

    std::cout << "[";

    for(; it!=v.end(); ++it)
    {
      printElement(*it);
      if(it<v.end()-1)
        std::cout << ", ";
    }

    std::cout << "]";
  }
  else if(isJSonObj(obj))
  {
    std::cout << "\n";
    tab(indent);
    std::cout << "{\n";
    boost::any_cast<JSonObj>(obj).print(indent+4);
    tab(indent);
    std::cout << "}";
  }
}



#ifndef JSonObj_NewJSonObj_h
#define JSonObj_NewJSonObj_h

//
// New JSonObj
//

#include "boost/any.hpp"

#include <string>
#include <vector>
#include <map>

#include <iostream>
#include <stdexcept>


class JSonObj
{
public:
  JSonObj() : PSetMap() {}
  ~JSonObj() {}

private:

  template <typename T>
  bool insertEntry(std::string const & name, T const & val, bool overwrite=true);
  bool insertEntryObj(
         std::pair<std::string, boost::any> const & pair
       , bool overwrite=true);

  boost::any * getJSonObjPtr(std::string const & name, bool bInsert);
  boost::any   getAnyJSonObj(std::string const & name) const;

  // Get Type
  std::string getType(boost::any const & obj) const;

  static void printElement(boost::any const &, int indent=0);

public:

  typedef std::vector<int>          vint;
  typedef std::vector<double>       vdouble;
  typedef std::vector<std::string>  vstring;
  typedef std::vector<JSonObj> vJSonObj;


  // Print out the JSonObj object
  void print(int indent=0) const;
 
  // Check if empty
  bool empty() const { return PSetMap.empty(); }

  // Get Type
  std::string getType(std::string const & name) const;

   // returns the list of parameter names
  vstring getNameList     () const;
  vstring getJSonObjNameList () const;
 
  // Get methods
  template <typename T>
  T getValue (std::string const & name) 
  {
    valuemap::const_iterator it = PSetMap.find(name);

    if(it==PSetMap.end())
      throw std::runtime_error("\""+name+"\" not found");

    try {
      T t = boost::any_cast<T>(it->second);
      return t;
    } catch (boost::bad_any_cast) {
      throw std::runtime_error("Incompatible type");
    } catch (...) {
      throw std::runtime_error("Unknow error");
    }
  }
  
  // an overloading getValue method with default_value
  template <typename T>
  T getValue (std::string const & name, T default_value) 
  {
    valuemap::const_iterator it = PSetMap.find(name);

    if(it==PSetMap.end())
      return default_value;

    try {
      T t = boost::any_cast<T>(it->second);
      return t;
    } catch (boost::bad_any_cast) {
      throw std::runtime_error("Incompatible type");
    } catch (...) {
      throw std::runtime_error("Unknow error");
    }
  }

  //getVector method
  template <typename T>
  std::vector<T> getVector (std::string const & name) 
  {
    valuemap::const_iterator it = PSetMap.find(name);

    if(it==PSetMap.end())
      throw std::runtime_error("\""+name+"\" not found");

    try {
      std::vector<boost::any> va
          = boost::any_cast<std::vector<boost::any> >(it->second);

      std::vector<T> vt;

      std::vector<boost::any>::const_iterator vit = va.begin();

      while(vit!=va.end()) {
        T t = boost::any_cast<T>(*vit);
        vt.push_back(t);
        ++vit;
      }

      return vt;

    } catch (boost::bad_any_cast) {
      throw std::runtime_error("Incompatible type of vector element");
    } catch (...) {
      throw std::runtime_error("Unknow error");
    }
  }
  
  //an overloading getVector method with default_value
  template <typename T>
  std::vector<T> getVector (std::string const & name, std::vector<T> default_value) 
  {
    valuemap::const_iterator it = PSetMap.find(name);

    if(it==PSetMap.end())
	  return default_value;

    try {
      std::vector<boost::any> va
          = boost::any_cast<std::vector<boost::any> >(it->second);

      std::vector<T> vt;

      std::vector<boost::any>::const_iterator vit = va.begin();

      while(vit!=va.end()) {
        T t = boost::any_cast<T>(*vit);
        vt.push_back(t);
        ++vit;
      }

      return vt;

    } catch (boost::bad_any_cast) {
      throw std::runtime_error("Incompatible type of vector element");
    } catch (...) {
      throw std::runtime_error("Unknow error");
    }
  }

 
private:
  typedef std::map<const std::string, boost::any>   valuemap;

  valuemap  PSetMap;
  static boost::any nil_obj;

  // Make the PSetParser class friend to allow the access of private members
  template<typename Iterator> friend class PSetParser;

};



#endif

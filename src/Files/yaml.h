#ifndef __grbllib__yaml__
#define __grbllib__yaml__

#include <regex>
#include <vector>
#include <string>

/*
 * parses YAML files into YAMLObjects
 * could be replaced with the official YAML library, but this was less of a pain to get working at the time
 */
class YAMLObject{
protected:
	int type=TYPEOBJ;
	std::string value;
	size_t line;
	std::vector<YAMLObject> chldrn;
public:
	YAMLObject(const int t, const std::string& s, const size_t l);//Constructs a YAMLObject from a type and a value
	void addChild(YAMLObject y);//adds a YAMLObject as a child
	YAMLObject& lastChild();//gets a reference to last child object
    int getType() const;//gets type
	const std::string& getValue() const;//gets value
	size_t getLine() const;//gets line
	const std::vector<YAMLObject>& getChildren() const;//gets a vector of children

	static std::vector<YAMLObject> parseFile(const std::vector<std::string>& vs);//static function that takes a vector of strings and parses it into a YAMLObject tree
	static void parse(const std::vector<std::string>& vs, size_t& i, YAMLObject& parent, int l);//actual parser for moving through the file
	static YAMLObject parseArray(const std::string& s, size_t i);//support function for YAML arrays
	static YAMLObject parseList(const std::string& s, size_t i);//support function for YAML lists
	static YAMLObject parseString(const std::string& s, size_t i);//support function for YAML strings

	static int TYPEOBJ;
	static int TYPEFIL;
	static int TYPERRY;
	static int TYPELST;
	static int TYPESTR;

	static std::regex RXBOF;
	static std::regex RXEOF;
	static std::regex RXINDENT;
	static std::regex RXLIST;
	static std::regex RXARRAY;
	static std::regex RXCOMMENT;
	static std::regex RXNEWLINE;
};
/*
exception class for dealing with YAML specific errors
*/
class YAMLException:public std::exception{
	char* buffer = nullptr;
public:
	YAMLException(int t, size_t i);//constructor with type
	~YAMLException();//destructor to get rid of char*
	const char* what() const noexcept;//override of inherited function
	static int PARSE;
	static int TYPE;
};

#endif

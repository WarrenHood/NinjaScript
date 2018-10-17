#include <iostream>
#include <string>
#include <vector>
#define TEST
#ifndef PARSE_CPP_
#define PARSE_CPP_
class TreeNode{
		private:
			static const int Integer = 0;
			static const int String = 1;
			static const int Function = 2;
			int intval;
			std::string strval;
			void* ptrfunc;
			TreeNode* pParent;
			std::vector<TreeNode> children;
		public:
			int type;
			void addNode(TreeNode& otherNode){
				this->children.push_back(otherNode);
				otherNode.setParent(*this);
			};
			int getIVal() const{
				return this->intval;
			};
			std::string getSVal() const{
				return this->strval;
			};
			void* getFVal() const{
				return this->ptrfunc;
			};
			void setParent(TreeNode& otherNode){
				this->pParent = &otherNode;
			};
			TreeNode& getParent(){
				return *(this->pParent);
			};
			void setSVal(std::string s){
				this->strval = s;
				this->type = String;
			};
			void setIVal(int i){
				this->intval = i;
				this->type = Integer;
			};
			void setFVal(void* ptr){
				this->ptrfunc = ptr;
				this->type = Function;
			};

};
void operator+=(std::vector<char>& v,char e){
	v.push_back(e);
}
std::vector<std::vector<char>> lex(char* cp,std::vector<char> splits,std::vector<char> ignores){
	std::vector<std::vector<char>> tokens;
	std::vector<char> current;
	for(;*cp != '\0';cp++){
		bool found_in_splits = false;
		bool found_in_ignores = false;
		//Check if char is in splits vec
		for(char sym:splits){
			if(sym == static_cast<char>(*cp)){found_in_splits = true; break;}
		}
		//Check if char is in ignores vec
		if(!found_in_splits) for(auto sym:ignores){
			if(sym == *cp){found_in_ignores=true; break;}
		}
		//If char was in ignores
		if(found_in_ignores){
			//Push current into tokens
			if(current.size())tokens.push_back(current);
			//Set current to empty new vec
			current = *(new std::vector<char> {});
		}
		//If char was in splits
		if(found_in_splits){
			//Push current into tokens
			if(current.size())tokens.push_back(current);
			//Push the char into tokens
			tokens.push_back(std::vector<char>{*cp});
			//Set current to empty new vec
			current = *(new std::vector<char> {});
		}
		else if(!found_in_ignores) current.push_back(static_cast<char>(*cp));
	}
	if(current.size())tokens.push_back(current);
	return tokens;
};
bool operator==(const std::vector<char>& v, char* c){
	for(char ch:v){
		if(*c == '\0' || ch != *c)return false;
		c++;
	}
	if(*c != '\0')return false;
	return true;
}
bool operator==(char* c,const std::vector<char>& v){
	return operator==(v,c);
}
std::ostream& operator<<(std::ostream& os,std::vector<std::vector<char>> v){
	os << "{";
	if(v.size())for(auto ch:v[0])os << "\"" << ch << "\"";
	for(int i=1; i<v.size(); i++){
		os << " , ";
		os << "\"";
		for(auto ch:v[i])os<<ch;
		os << "\"";
	}
	os << "}";
	return os;
}
/*
TreeNode& parse(const std::vector<std::vector<char>& v){
	TreeNode root;
	for(std::vector<char> token : v){

	}
}
*/
#endif
#ifdef TEST
/*
	main is a test.
	define TEST to run it.
*/
int main(int argc,char** argv){
	char parse_string[] = "<int> x=1; <int> y=2; print.{x+y};";
	std::cout << lex(parse_string,{'<','>','{','}',';','=','.','+','-'},{' ','\r','\n'});
}
#endif

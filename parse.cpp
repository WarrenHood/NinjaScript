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
std::vector<TreeNode> lex(const std::string& cp,std::vector<std::string> splits,std::vector<std::string> ignores){
	std::vector<std::string> tokens;
	std::string current = "";
	for(int i=0; i<cp.size(); i++){
		bool found_in_splits = false;
		bool found_in_ignores = false;
		for(auto sym:splits){
			if(sym == cp[i]){found_in_splits = true; break;}
		}
		if(!found_in_splits) for(auto sym:ignores){
			if(sym == cp[i]){found_in_ignores=true; break;}
		}
		if(found_in_ignores){
			tokens.push_back(current);
			current = "";
		}
		else current += cp[i];
		if(found_in_splits){
			tokens.push_back(current);
			current = "";
		}
	}
};
std::ostream& operator<<(std::ostream& os,std::vector<std::string> v){
	os << "{";
	if(v.size())os<<v[0];
	for(int i=1; i<v.size(); i++)os << "," << v[i];
	os << "}";
	return os;
}
#endif
#ifdef TEST
/*
	main is a test.
	define TEST to run it.
*/
int main(int argc,char** argv){
	std::string parse_string = "<int> x=1; <int> y=2; print.{x+y};";
	std::cout << lex(parse_string);
}
#endif
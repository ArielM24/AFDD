//#include<iostream>
//#include<stdlib.h>
//#include<math.h>
//#include<vector>
//#include<time.h>
//#include"NumericBase.h"
using namespace std;
class Alphabet{
	private:
		string chars;
	public:
		Alphabet();
		Alphabet(string);
		Alphabet(char,char);
		Alphabet(int,int);
		~Alphabet();
		string getChars();
		void setChars(string);
		void setCharsRange(char,char);
		string getWord(string);
		bool insert(char);
		bool erase(char);
		void print();
		bool isWord(string);
		bool isPrefix(string,string);
		bool isOwnPrefix(string,string);
		bool isPostfix(string,string);
		bool isOwnPostfix(string,string);
		bool isInfix(string,string);
		bool isOwnInfix(string,string);
		bool isSubsecuence(string,string);
		string reverse(string);
		string Pow(string,int);
		int ocurrences(char,string);
		bool isPalindrome(string);
		void Pow(int);
		bool contains(vector<string>,string);
		void insert(vector<string>*,string);
		vector<string> crossProduct(string,string);
		string randomWord();
		string randomWord(int);
};
Alphabet::Alphabet(){
	chars="default";
}
Alphabet::Alphabet(string _chars){
	string cad("");
	if(_chars.size()>=2){
		for (int i = 0; i < _chars.size();i++){
			if(cad.find(_chars[i])==string::npos){
				cad+=_chars[i];
			}
		}
	}else{
		cad="default";
	}
	chars=cad;
}
Alphabet::Alphabet(char begin,char end){
	string _chars("");
	if(((int)end-(int)begin)>=2){
		for (int i = (int)begin; i <=(int)end;i++){
			_chars+=(char)i;
		}
		chars=_chars;
	}else chars="default";
}
Alphabet::Alphabet(int begin,int end){
	string _chars("");
	if((end-begin)>=2){
		for (int i = begin; i <= end;i++){
			_chars+=(char)i;
		}
		chars=_chars;
	}else chars="default";
}
Alphabet::~Alphabet(){}
string Alphabet::getChars(){
	return chars;
}
void Alphabet::setChars(string _chars){
	string cad("");
	if(_chars.size()>=2){
		for (int i = 0; i < _chars.size();i++){
			if(cad.find(_chars[i])==string::npos){
				cad+=_chars[i];
			}
		}
	}else{
		cad="default";
	}
	chars=cad;
}
void Alphabet::setCharsRange(char begin,char end){
	string cad("");
	if(((int)end-(int)begin)>=2){
		for (int i = (int)begin; i <= (int)end;i++){
			cad+=(char)i;
		}
		chars=cad;
	}else{
		chars="default";
	}
}
string Alphabet::getWord(string msg){
	string cad;
	do{
		cout<<msg;
		cin>>cad;
	}while(!isWord(cad));
	return cad;
}
bool Alphabet::insert(char c){
	if(chars.find(c)==string::npos){
		chars+=c;
		return true;
	}else return false;
}
bool Alphabet::erase(char c){
	if(chars.find(c)==string::npos){
		return false;
	}else{
		chars.replace(chars.find(c),1,"");
		return true;
	}
}
void Alphabet::print(){
	cout<<"A={";
	for (int i = 0; i < chars.size(); i++){
		cout<<chars[i];
		if(i!=chars.size()-1){
			cout<<",";
		}
	}
	cout<<"}"<<endl;
}
bool Alphabet::isWord(string word){
	bool cheked=true;
	for (int i = 0; i < word.size(); i++){
		if((chars.find(word[i]))==string::npos){
			cheked=false;
			break;
		}
	}
	return cheked;
}
bool Alphabet::isPrefix(string prefix,string word){
	bool cheked=true;
	if(prefix.size()!=0){
		if(prefix.size()<=word.size()){
			if(word.substr(0,prefix.size())!=prefix){
				cheked=false;
			}
		}else{
			cheked=false;
		}
	}
	return cheked;
}
bool Alphabet::isOwnPrefix(string prefix,string word){
	if(prefix.size()==0||prefix==word)
		return false;
	else return isPrefix(prefix,word);
}
bool Alphabet::isPostfix(string postfix,string word){
	bool cheked=true;
	if(postfix.size()!=0){
		if(postfix.size()<=word.size()){
			if(word.substr(word.size()-postfix.size(),word.size())!=postfix){
				cheked=false;
			}
		}else{
			cheked=false;
		}
	}
	return cheked;
}
bool Alphabet::isOwnPostfix(string postfix,string word){
	if(postfix.size()==0||postfix==word)
		return false;
	else return isPostfix(word,postfix);
}
bool Alphabet::isInfix(string infix,string word){
	if(word.find(infix)!=string::npos)
		return true;
	else return false;
}
bool Alphabet::isOwnInfix(string infix,string word){
	if(infix.size()==0||infix==word)
		return false;
	else return isInfix(infix,word);
}
bool Alphabet::isSubsecuence(string subsecuence,string word){
	bool cheked=true;
	Alphabet aux(word);
	string cad=word;
	if(subsecuence.size()<=word.size()&&aux.isWord(subsecuence)){
		for(int i=0;i<subsecuence.size();i++){
			if(cad.find(subsecuence[i])!=string::npos){
				//*determinar order
				if(i<=cad.find(subsecuence[i])||i<=word.find(subsecuence[i])){
					cad.erase(cad.find(subsecuence[i]),1);
				}else{
					cheked=false;
					break;
				}
			}else{
				cheked=false;
				break;
			}
		}
	}else cheked=false;
	return cheked;
}
string Alphabet::reverse(string word){
	string cad("");
	for (int i = word.size()-1; i>=0;i--){
		cad+=word[i];
	}
	return cad;
}
string Alphabet::Pow(string word,int power){
	string cad("");
	if(power){
		if(power>0){
			for(int i=0;i<power;i++){
				cad+=word;
			}
		}else{
			for(int i=0;i<-power;i++){
				cad+=Alphabet::reverse(word);
			}
		}
	}else cad+="\u03BB";
	return cad; 
}
int Alphabet::ocurrences(char _char,string word){
	int ocurrences=0;
	for (int i = 0; i < word.size(); i++){
		if(word[i]==_char){
			ocurrences++;
		}
	}
	return ocurrences;
}
bool Alphabet::isPalindrome(string word){
	return word==reverse(word);
}
void Alphabet::Pow(int power){
	NumericBase base = NumericBase(chars);
	for(int i=0;i<pow(chars.size(),power);i++){
		cout<<"\e[92m"<<base.fillFormat(base.toBase(i),power)<<"\e[0m";
		if(i!=pow(chars.size(),power)-1){
			cout<<"\e[93m,\e[0m";
		}
	}
	base.~NumericBase();
}
bool Alphabet::contains(vector<string> vec,string cad){
	bool cheked = false;
	for(int i=0;i<vec.size();i++){
		if(vec[i]==cad){
			cheked=true;
			break;
		}
		cout<<i<<endl;
	}
	return cheked;
}
void Alphabet::insert(vector<string>* vec,string cad){
	for(int i=0;i<vec[0].size();i++){
		if(vec[0][i].compare(cad)>0){
			cout<<"ad "<<cad<<endl;
			vec[0].insert(vec[0].begin()+i,cad);
			break;
		}
	}
}
vector<string> Alphabet::crossProduct(string str1,string str2){
	vector<string> cross(str1.size()*str2.size());
	string aux("");
	int k=0;
	for(int i=0;i<str1.size();i++){
		for(int j=0;j<str2.size();j++){
			aux.push_back(str1[i]);
			aux.push_back(str2[j]);
			cross[k]=aux;
			aux="";
			k++;
		}
	}
	return cross;
}
string Alphabet::randomWord(){
	int size = (rand()%16)+1;
	string word("");
	for(int i=0;i<size;i++){
		word.push_back(chars[rand()%chars.size()]);
	}
	return word;
}
string Alphabet::randomWord(int size){
	string word("");
	for(int i=0;i<size;i++){
		word.push_back(chars[rand()%chars.size()]);
	}
	return word;
}
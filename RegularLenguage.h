//#include<iostream>
//#include<stdlib.h>
//#include<math.h>
//#include<vector>
//#include<time.h>
//#include<fstream>
//#include"NumericBase.h"
//#include"Alphabet.h"
//#include"NumericString.h"
class RegularLenguage{
	private:
		Alphabet alphabet;
		vector<string> words;
	public:
		RegularLenguage();
		RegularLenguage(Alphabet);
		RegularLenguage(Alphabet,vector<string>);
		RegularLenguage(Alphabet,int,int);
		RegularLenguage(string);
		~RegularLenguage();
		Alphabet getAlphabet();
		vector<string> getWords();
		void print();
		bool containsWord(string);
		RegularLenguage RegularLenguageUnion(RegularLenguage,RegularLenguage);
		RegularLenguage RegularLenguageConcat(RegularLenguage,RegularLenguage);
		RegularLenguage RegularLenguageSubstract(RegularLenguage,RegularLenguage);
		void printPow(int);
		void addWord(string);
		string randomWord(int);
		Alphabet onlyUsedAlphabet();
};
RegularLenguage::RegularLenguage(){	
	alphabet= Alphabet();
	words = vector<string>(5);
	for(int i=0;i<5;i++){
		words[i]=alphabet.randomWord(4);
	}
}
RegularLenguage::RegularLenguage(Alphabet _alphabet){
	alphabet=_alphabet;
	words= vector<string>(5);
	for(int i=0;i<5;i++){
		words[i]=alphabet.randomWord(4);
	}
}
RegularLenguage::RegularLenguage(Alphabet _alphabet,vector<string> _words){
	alphabet=_alphabet;
	words = vector<string>(_words.size());
	for(int i=0;i<_words.size();i++){
		if(alphabet.isWord(_words[i])&&!containsVectorString(words,_words[i]))
			words[i]=_words[i];
		else 
			words[i]=alphabet.randomWord(_words[i].size());
	}
}
RegularLenguage::RegularLenguage(Alphabet _alphabet, int numberOfWords,int sizeOfWords){
	alphabet=_alphabet;
	if(numberOfWords>permutation(_alphabet.getChars().size(),sizeOfWords)){
		words=vector<string>(0);
	}else{
		string word;
		words= vector<string>(numberOfWords);
		for(int i=0;i<numberOfWords;i++){
			do{
				word = alphabet.randomWord(sizeOfWords);
			}while(!containsWord(word));
			words[i]= word;
		}
	}
}
RegularLenguage::RegularLenguage(string fileInput){
	ifstream fi;
	fi.open(fileInput,ios::in);
	if(!fi.fail()){
		words = vector<string>(0);
		string alphabetType;
		getline(fi,alphabetType);
		if(alphabetType[0]=='d'){
			alphabet=Alphabet();
		}else if(alphabetType[0]=='s'){
			string _alphabet;
			getline(fi,_alphabet);
			alphabet=Alphabet(_alphabet);
		}else if(alphabetType[0]=='i'){
			int first,last;
			fi>>first;
			fi>>last;
			alphabet=Alphabet(first,last);
		}else if(alphabetType[0]=='c'){
			char first,last;
			fi>>first;
			fi>>last;
			alphabet=Alphabet(first,last);
		}
		while(!fi.eof()){
			string word("");
			getline(fi,word);
			if(word.size()){
				addWord(word);
			}
		}
	}else{
		cout<<"File rl error"<<endl;
		exit(1);
	}
	fi.close();
}
RegularLenguage::~RegularLenguage(){}
Alphabet RegularLenguage::getAlphabet(){
	return alphabet;
}
vector<string> RegularLenguage::getWords(){
	return words;
}
void RegularLenguage::print(){
	alphabet.print();
	cout<<"L = {";
	for(int i=0;i<words.size();i++){
		cout<<words[i];
		if(i!=words.size()-1)
			cout<<",";
	}
	cout<<"}"<<endl;
}
bool RegularLenguage::containsWord(string word){
	for(int i=0;i<words.size();i++){
		if(words[i]==word){
			return true;
			break;
		}
	}
	return false;
}
RegularLenguage RegularLenguage::RegularLenguageUnion(RegularLenguage l1,RegularLenguage l2){
	vector<string> wordsUnion = l1.getWords();
	for(int i=0;i<l2.getWords().size();i++){
		if(!l1.containsWord(l2.getWords()[i])){
			wordsUnion.push_back(l2.getWords()[i]);
		}
	}
	return RegularLenguage(l1.getAlphabet(),wordsUnion);
}
RegularLenguage RegularLenguage::RegularLenguageConcat(RegularLenguage l1,RegularLenguage l2){
	vector<string> crossWords(0);
	for(int i=0;i<l1.getWords().size();i++){
		for(int j=0;j<l2.getWords().size();j++){
			crossWords.push_back(l1.getWords()[i]+l2.getWords()[j]);
		}
	}
	return RegularLenguage(l1.getAlphabet(),crossWords);
}
RegularLenguage RegularLenguage::RegularLenguageSubstract(RegularLenguage l1,RegularLenguage l2){
	vector<string> substractWords(0);
	for(int i=0;i<l1.getWords().size();i++){
		if(!l2.containsWord(l1.getWords()[i])){
			substractWords.push_back(l1.getWords()[i]);
		}
	}	
	return RegularLenguage(l1.getAlphabet(),substractWords);
}
void RegularLenguage::printPow(int power){
	NumericString base = NumericString(words);
	vector<string> convert;
	cout<<"L={";
	for(int i=0;i<pow(words.size(),abs(power));i++){
		convert=base.fillFormat(base.toBase(i),abs(power));
		if(power<0)
			cout<<alphabet.reverse(base.stringBase(convert));
		else
			cout<<base.stringBase(convert);
		if(i<pow(words.size(),abs(power))-1){
			cout<<",";
		}
	}
	cout<<"}\n";
	base.~NumericString();
}
void RegularLenguage::addWord(string word){
	if(alphabet.isWord(word)){
		if(!containsVectorString(words,word)){
			words.push_back(word);
		}
	}
}
string RegularLenguage::randomWord(int size){
	string word("");
	for(int i=0;i<size;i++){
		int random = rand()%words.size();
		word+=words[random];
	}
	return word;
}
Alphabet RegularLenguage::onlyUsedAlphabet(){
	string _chars("");
	for(int i=0;i<words.size();i++){
		_chars+=words[i];
	}
	return Alphabet(_chars);
}
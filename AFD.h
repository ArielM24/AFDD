//#include<iostream>
//#include<stdlib.h>
//#include<math.h>
//#include<vector>
//#include<time.h>
//#include<fstream>
//#include"NumericBase.h"
//#include"Alphabet.h"
//#include"NumericString.h"
//#include"RegularLenguage.h"
//#include"Matrix.h"
using namespace std;
class AFD{
	private:
		Alphabet alphabet;
		vector<int> states;
		int initialState;
		vector<int> finalSates;
		int actualState;
		int** transitionFunction;
		int** convertTransitionFunction(string,int,int);
		int** convertTransitionFunction(string,int,int,string);
		void fillTransition(int**,int,int,int);
		void copyTransition(int**);
		void addTransition(AFD,int**);
		int** mergeTransition(AFD,int,char);
		Alphabet getAlphabetFile(string);
	public:
		AFD();
		AFD(Alphabet);
		AFD(Alphabet,int,int,vector<int>,int**);
		AFD(string,int,int,string,string);
		AFD(string,int,int,string,string,string);
		AFD(string);
		AFD(RegularLenguage);
		~AFD();
		Alphabet getAlphabet();
		vector<int> getStates();
		int getInitialState();
		vector<int> getFinalStates();
		int getActualState();
		int** getTransitionFunction();
		void setAlphabet(Alphabet);
		void setStates(vector<int>);
		void setStates(int);
		void setInitialState(int);
		void setFinalStates(vector<int>);
		void setActualState(int);
		void setTransitionFunction(int**);
		void transition(char);
		bool evaluation(string);
		void restart();
		void print();
		AFD mergeAFD(AFD,int,char);
};
AFD::AFD(){
	alphabet=Alphabet();
}
AFD::AFD(Alphabet _alphabet){
	alphabet=_alphabet;
}
AFD::AFD(Alphabet _alphabet,int numberOfStates,int _initialState,vector<int> _finalStates,int** _transitionFunction){
	alphabet=_alphabet;
	states = vector<int>(0);
	for(int i=0;i<numberOfStates;i++){
		states.push_back(i);
	}
	initialState=_initialState;
	finalSates=_finalStates;
	actualState=_initialState;
	transitionFunction=_transitionFunction;
}
AFD::AFD(string _alphabet,int numberOfStates,int _initialState,string _finalStates,string _transitionFunction){
	alphabet=Alphabet(_alphabet);
	states = vector<int>(0);
	for(int i=0;i<numberOfStates;i++){
		states.push_back(i);
	}
	initialState=_initialState;
	finalSates=getStringNumbers(_finalStates);
	transitionFunction=convertTransitionFunction(_transitionFunction,alphabet.getChars().size(),numberOfStates);
}
AFD::AFD(string _alphabet,int numberOfStates,int _initialState,string _finalStates,string _transitionFunction,string consider){
	alphabet=Alphabet(_alphabet);
	setStates(numberOfStates);
	initialState=_initialState;
	finalSates=getStringNumbers(_finalStates);
	transitionFunction=convertTransitionFunction(_transitionFunction,alphabet.getChars().size(),numberOfStates,consider);
}
Alphabet AFD::getAlphabetFile(string fileInput){
	ifstream fi;
	fi.open(fileInput,ios::in);
	Alphabet _Alphabet;
	if(!fi.fail()){
		string alphabetType;
		getline(fi,alphabetType);
		getline(fi,alphabetType);
		getline(fi,alphabetType);
		if(alphabetType[0]=='d'){
			_Alphabet=Alphabet();
		}else if(alphabetType[0]=='s'){
			string _alphabet;
			getline(fi,_alphabet);
			_Alphabet=Alphabet(_alphabet);
		}else if(alphabetType[0]=='i'){
			int first,last;
			fi>>first;
			fi>>last;
			_Alphabet=Alphabet(first,last);
		}else if(alphabetType[0]=='c'){
			char first,last;
			fi>>first;
			fi>>last;
			_Alphabet=Alphabet(first,last);
		}
	}else{
		cerr<<"File afd error"<<endl;
		exit(1);
	}
	fi.close();
	return _Alphabet;
}
AFD::AFD(string fileAFD){
	ifstream fileInput;
	fileInput.open(fileAFD,ios::in);
	if(!fileInput.fail()){
		string _consider,_chars,_numberOfStates,_initialState,_finalStates,aux(""),_transitionFunction(""),alphabetType;
		getline(fileInput,_consider);
		getline(fileInput,_chars);
		alphabet = getAlphabetFile(fileAFD);
		getline(fileInput,alphabetType);
		if(alphabetType=="i"||alphabetType=="c"){
			getline(fileInput,aux);
			getline(fileInput,aux);
		}else if(alphabetType=="s"){
			getline(fileInput,aux);
		}
		getline(fileInput,_numberOfStates);
		getline(fileInput,_initialState);
		getline(fileInput,_finalStates);
		while(!fileInput.eof()){
			getline(fileInput,aux);
			_transitionFunction+=aux;
		}
		setStates(atoi(_numberOfStates.c_str()));
		initialState=atoi(_initialState.c_str());
		finalSates=getStringNumbers(_finalStates);
		if(_consider[2]=='f'){
			transitionFunction=convertTransitionFunction(_transitionFunction,alphabet.getChars().size(),
			atoi(_numberOfStates.c_str()));
		}else{
			transitionFunction=convertTransitionFunction(_transitionFunction,alphabet.getChars().size(),
			atoi(_numberOfStates.c_str()),_chars);	
		}
	}else{
		cout<<"File afd error"<<endl;
		exit(1);
	}
	fileInput.close();
}
AFD::AFD(RegularLenguage rl){
	int count=0,_actualState=0,numberOfStates=rl.getWords().size(),character=0;
	Alphabet _alphabet = rl.onlyUsedAlphabet();
	Matrix transition = newMatrix(1,_alphabet.getChars().size());
	fillMatrix(&transition,-1);
	vector<int> _final = vector<int>(0);
	for(int i = 0; i<numberOfStates; i++){
		string actualword = rl.getWords()[i];
		for(int j = 0; j<actualword.size(); j++){
			character=_alphabet.getChars().find(actualword[j]);
			if(transition.numbers[_actualState][character] == -1){
				transition.numbers[_actualState][character] = (count+1);
				count++;
				_actualState = count;
				appendRow(&transition,-1);
			}else{
				_actualState=transition.numbers[_actualState][character];
			}
		}
		_final.push_back(count);
		_actualState=0;
	}
	appendRow(&transition,-1);
	replaceMatrixNumber(&transition,-1,count+1);
	alphabet=_alphabet;
	finalSates=_final;
	setStates(count+2);
	initialState=0;
	transitionFunction=getIntNumbers(transition);
}
AFD::~AFD(){}
Alphabet AFD::getAlphabet(){
	return alphabet;
}
vector<int> AFD::getStates(){
	return states;
}
int AFD::getInitialState(){
	return initialState;
}
vector<int> AFD::getFinalStates(){
	return finalSates;
}
int AFD::getActualState(){
	return actualState;
}
int** AFD::getTransitionFunction(){
	return transitionFunction;
}
void AFD::setAlphabet(Alphabet _alphabet){
	alphabet=_alphabet;
}
void AFD::setStates(vector<int> _states){
	states=_states;
}
void AFD::setStates(int _states){
	states = vector<int>(_states);
	for(int i=0;i<_states;i++){
		states[i]=i;
	}
}
void AFD::setInitialState(int _initialState){
	initialState=_initialState;
}
void AFD::setFinalStates(vector<int> _finalStates){
	finalSates=_finalStates;
}
void AFD::setActualState(int _actualState){
	actualState=_actualState;
}
void AFD::setTransitionFunction(int** _transitionFunction){
	transitionFunction=_transitionFunction;
}
void AFD::transition(char character){
	int i=alphabet.getChars().find_first_of(character);
	if(i!=string::npos){
		actualState=transitionFunction[actualState][i];
	}
}
bool AFD::evaluation(string cad){
	actualState=initialState;
	if(alphabet.isWord(cad)){
		for(int i=0;i<cad.size();i++){
			transition(cad[i]);
		}
		if(containsVectorInt(finalSates,actualState)){
			return true;
		}else return false;
	}else return false;
}
void AFD::restart(){
	actualState=initialState;
}
void AFD::print(){
	cout<<"\t|";
	for(int j=0;j<alphabet.getChars().size();j++){
		cout<<alphabet.getChars()[j]<<"\t";
	}
	cout<<endl;
	for(int i=0;i<(alphabet.getChars().size()+1)*8;i++){
		cout<<"-";
	}
	cout<<endl;
	for(int i=0;i<states.size();i++){
		if(states[i]==initialState&&containsVectorInt(finalSates,states[i])){
			cout<<"*->q"<<states[i]<<"\t|";
		}else if(states[i]==initialState){
			cout<<"->q"<<states[i]<<"\t|";
		}else if(containsVectorInt(finalSates,states[i])){
			cout<<"*q"<<states[i]<<"\t|";
		}else{
			cout<<"q"<<states[i]<<"\t|";
		}
		for(int j=0;j<alphabet.getChars().size();j++){
			cout<<transitionFunction[i][j]<<"\t";
		}
		cout<<endl;
	}
}
int** AFD::convertTransitionFunction(string function,int chars,int states){
	int** transition = (int**)malloc(sizeof(int*)*states);
	int counter=1;
	for(int i=0;i<states;i++){
		transition[i]=(int*)malloc(sizeof(int)*chars);
	}
	for(int i=0;i<states;i++){
		for(int j=0;j<chars;j++){
			transition[i][j]=getStringNumber(function,counter);
			counter++;
		}
	}
	return transition;
}
int** AFD::convertTransitionFunction(string function,int chars,int states,string consider){
	int** transition = (int**)malloc(sizeof(int*)*states);
	int counter=1;
	for(int i=0;i<states;i++){
		transition[i]=(int*)malloc(sizeof(int)*chars);
	}
	for(int i=0;i<states;i++){
		for(int j=0;j<chars;j++){
			int found=consider.find(alphabet.getChars()[j]);
			if(found!=string::npos){
				transition[i][j]=getStringNumber(function,(found+1)+(consider.size()+1)*(i));
			}else{
				transition[i][j]=getStringNumber(function,(consider.size()+1)*(i+1));
			}
			counter++;
		}
	}
	return transition;
}
void AFD::fillTransition(int** transition,int states,int symbols,int state){
	for(int i=0;i<states;i++){
		for(int j=0;j<symbols;j++){
			transition[i][j]=state;
		}
	}
}
void AFD::copyTransition(int** transition){
	for(int i=0;i<states.size();i++){
		for(int j=0;j<alphabet.getChars().size();j++){
			transition[i][j]=transitionFunction[i][j];
		}
	}
}
void AFD::addTransition(AFD afd,int** transition){
	Alphabet aux=Alphabet(alphabet.getChars()+afd.getAlphabet().getChars());
	int found;
	int ** afdTransition=afd.getTransitionFunction();
	for(int i=0;i<afd.getStates().size();i++){
		for(int j=0;j<afd.getAlphabet().getChars().size();j++){
			found=aux.getChars().find(afd.getAlphabet().getChars()[j]);
			if(found!=string::npos){
				transition[i+states.size()][found]=afdTransition[i][j]+states.size();
			}else{
				transition[i+states.size()][j+alphabet.getChars().size()]=afdTransition[i][j]+states.size();
			}
		}
	}
}
int** AFD::mergeTransition(AFD afd,int state,char symbol){
	int numberOfStates = states.size()+afd.getStates().size()+1;
	int** newTransition = (int**)malloc(sizeof(int*)*numberOfStates);
	Alphabet aux=Alphabet(alphabet.getChars()+afd.getAlphabet().getChars());
	int symbols = aux.getChars().size();
	for(int i=0;i<numberOfStates;i++){
		newTransition[i]=(int*)malloc(sizeof(int*)*symbols);
	}
	fillTransition(newTransition,numberOfStates,symbols,numberOfStates-1);
	copyTransition(newTransition);
	addTransition(afd,newTransition);
	NumericBase base = NumericBase(aux.getChars());
	newTransition[state][base.getDigit(symbol).value]=states.size();
	base.~NumericBase();
	return newTransition;
}
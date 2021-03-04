//#include<iostream>
//#include<vector>
//#include<math.h>
//#include"Alphabet.h"
using namespace std;
struct StringDigit{
	string character;
	int value;
};
long factorial(int number){
	long result=1;
	if(number>20){
		return result;
	}
	for(int i=1;i<=number;i++){
		result*=i;
	}
	return result;
}
long descendetProduct(int n,int k){
	long result=1;
	if(n<k){
		return 1;
	}
	for(int i=k+1;i<=n;i++){
		result*=i;
	}
	return result;
}
long permutation(int n,int k){
	if(n<k){
		return 0;
	}else{
		return descendetProduct(n,(n-k));
	}
}
vector<string> get_Strings(int numberOfStrings){
	vector<string> strings(numberOfStrings);
	string cad("");
	for(int i=0;i<numberOfStrings;i++){
		cout<<i<<":\t";
		cin>>cad;
		strings[i]=cad;
	}
	return strings;
}
void printVectorString(vector<string> vec,string begin,string separator,string end){
	cout<<begin;
	for(int i=0;i<vec.size();i++){
		cout<<vec[i];
		if(i!=vec.size()-1){
			cout<<separator;
		}
	}
	cout<<end;
}
void printVectorInt(vector<int> vec,string begin,string separator,string end){
	cout<<begin;
	for(int i=0;i<vec.size();i++){
		cout<<vec[i];
		if(i!=vec.size()-1){
			cout<<separator;
		}
	}
	cout<<end;
}
bool containsVectorString(vector<string> vec,string cad){
	for(int i=0;i<vec.size();i++){
		if(vec[i]==cad){
			return true;
			break;
		}
	}
	return false;
}
int getVectorString(vector<string> vec,string cad){
	if(containsVectorString(vec,cad)){
		for(int i=0;i<vec.size();i++){
			if(vec[i]==cad){
				return i;
				break;
			}
		}
	}else return -1;
}
bool containsVectorInt(vector<int> vec,int number){
	for(int i=0;i<vec.size();i++){
		if(vec[i]==number){
			return true;
			break;
		}
	}
	return false;
}
int getStringNumber(string stringNumber){
	string number("0");
	for(int i=0;i<stringNumber.size();i++){
		if(stringNumber[i]>='0'&&stringNumber[i]<='9'){
			number+=stringNumber[i];
		}else{
			break;
		}
	}
	return atoi(number.c_str());
}
int getStringNumber(string stringNumber,int substring){
	string number("0");
	bool cad = true;
	int counter = 0;
	stringNumber+=";";
	for(int i=0;i<stringNumber.size();i++){
		if(stringNumber[i]>='0'&&stringNumber[i]<='9'){
			number+=stringNumber[i];
			if(cad){
				counter++;
				cad=false;
			}
		}else if(counter==substring){
			break;
		}else{
			cad = true;
			number="0";
		}
	}
	return atoi(number.c_str());
}
vector<int> getStringNumbers(string numbers){
	vector<int> _numbers = vector<int>(0);
	vector<int> result = vector<int>(0);
	int maxNumber;
	if(numbers.size()%2==0){
		maxNumber=numbers.size()/2;
	}else{
		maxNumber=(numbers.size()/2)+1;
	}
	for(int i=0;i<maxNumber;i++){
		_numbers.push_back(getStringNumber(numbers,i+1));
	}
	for(int i=0;i<_numbers.size();i++){
		int pos = numbers.find(to_string(_numbers[i]));
		if(pos!=string::npos){
			result.push_back(_numbers[i]);
			numbers.erase(pos,to_string(_numbers[i]).size());
		}
	}
	return result;
}
vector<int> addVectorInt(vector<int> v,int n){
	vector<int> result = vector<int>(0);
	for(int i=0;i<v.size();i++){
		result.push_back(v[i]+n);
	}
	return result;
}
vector<int> mergeVectorInt(vector<int> a,vector<int> b){
	vector<int> result = vector<int>(0);
	for(int i=0;i<a.size();i++){
		if(!containsVectorInt(result,a[i])){
			result.push_back(a[i]);
		}
	}
	for(int i=0;i<b.size();i++){
		if(!containsVectorInt(result,b[i])){
			result.push_back(b[i]);
		}
	}
	return result;
}
vector<int> pushVectorInt(vector<int> a,vector<int> b){
	vector<int> c = a;
	for(int i=0;i<b.size();i++){
		c.push_back(b[i]);
	}
	return c;
}
class NumericString{
	private:
		vector<string> digitsDefault();
		vector<StringDigit> Digits;
		int Base;
		vector<StringDigit> fillBase(vector<string>);
	public:
		NumericString();
		~NumericString();
		NumericString(vector<string>);
		vector<StringDigit> getDigits();
		int getBase();
		StringDigit getDigit(int);
		StringDigit getDigit(string);
		vector<string> toBase(int);
		int toDecimal(vector<string>);
		vector<string> fillFormat(vector<string>,int);
		void print();
		NumericString reverse();
		string stringBase(vector<string>);
};
vector<string> NumericString::digitsDefault(){
	vector<string> aux(16,"");
	for(int i=0;i<10;i++){
		cout<<(char)(48+i)<<endl;
		aux[i].push_back((char)(48+i));
	}
	for(int i=0;i<6;i++){
		aux[i+10].push_back((char)(65+i));
	}
	return aux;
}
vector<StringDigit> NumericString::fillBase(vector<string> _digits){
	vector<StringDigit> Digits(_digits.size());
	for (int i = 0; i < _digits.size();i++){
		StringDigit aux = {_digits[i],i};
		Digits[i]=aux;
	}
	return Digits;
}	
NumericString::NumericString(){
	Digits = fillBase(digitsDefault());
	Base = 16;
}
NumericString::NumericString(vector<string> _digits){
	if(_digits.size()>1){
		Digits=fillBase(_digits);
		Base=_digits.size();
	}else{
		Digits=fillBase(digitsDefault());
		Base=16;
	}
}
NumericString::~NumericString(){}
vector<StringDigit> NumericString::getDigits(){
	return Digits;
}
int NumericString::getBase(){
	return Base;
}
StringDigit NumericString::getDigit(int number){
	if(number>=0&&number<=Base){
		for(int i=0;i<Digits.size();i++){
			if(number==Digits[i].value){
				return Digits[i];
			}
		}
	}else return Digits[0];
}
StringDigit NumericString::getDigit(string character){
	for(int i=0;i<Digits.size();i++){
		if(character==Digits[i].character){
			return Digits[i];
		}
	}
	return Digits[0];
}
vector<string> NumericString::toBase(int decimal){
	vector<string> result(0);
	int div,mod;
	vector<StringDigit> _digits(0);
	do{
		div=decimal/Base;
		mod=decimal%Base;
		_digits.push_back(getDigit(mod));
		decimal=div;
	}while(div>=Base);
	if(div)
		_digits.push_back(getDigit(div));
	for(int i=_digits.size()-1;i>=0;i--){
		result.push_back(_digits[i].character);
	}
	return result;
}
int NumericString::toDecimal(vector<string> number){
	int result=0,i=0,j=number.size()-1;
	for(i=0;i<number.size();i++){
		result+=(getDigit(number[i]).value)*pow(Base,j--);
	}
	return result;
}
vector<string> NumericString::fillFormat(vector<string> number,int extension){
	vector<string> aux(0),aux1(extension);
	if(number.size()<extension){
		for(int i=0;i<extension-number.size();i++){
			aux.push_back(Digits[0].character);
		}
		for(int i=0;i<aux.size();i++){
			aux1[i]=aux[i];
		}
		for(int i=0;i<number.size();i++){
			aux1[i+aux.size()]=number[i];
		}
		return aux1;
	}else return number;	
}
void NumericString::print(){
	for(int i=0;i<Base;i++){
		cout<<Digits[i].character<<": "<<Digits[i].value<<endl;
	}
}
NumericString NumericString::reverse(){
	vector<string> vec(Digits.size());
	Alphabet a1('0','1');
	for(int i=0;i<Digits.size();i++){
		vec[i]=a1.reverse(Digits[i].character);
	}
	a1.~Alphabet();
	return NumericString(vec);
}
string NumericString::stringBase(vector<string> number){
	string cad("");
	for(int i=0;i<number.size();i++){
		cad+=number[i];
	}
	return cad;
}
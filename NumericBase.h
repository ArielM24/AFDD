//#include<iostream>
//#include<vector>
//#include<math.h>
using namespace std;
struct Digit{
	char character;
	int value;
};
class NumericBase{
private:
	vector<Digit> Digits;
	int Base;
	vector<Digit> fillBase(string);
public:
	NumericBase();
	NumericBase(string);
	~NumericBase();
	vector<Digit> getDigits();
	int getBase();
	Digit getDigit(int);
	Digit getDigit(char);
	string toBase(int);
	int toDecimal(string);
	string fillFormat(string,int);
	void print();
};
vector<Digit> NumericBase::fillBase(string _digits){
	vector<Digit> _Digits(_digits.size());
	for(int i=0;i<_digits.size();i++){
		Digit aux = {_digits[i],i};
		_Digits[i]=aux;
	}
	return _Digits;
}
NumericBase::NumericBase(){
	Digits=fillBase("0123456789ABCDEF");
	Base=16;
}
NumericBase::NumericBase(string _digits){
	if(_digits.size()>1){
		Digits=fillBase(_digits);
		Base =_digits.size();
	}else{
		Digits=fillBase("0123456789ABCDEF");
		Base=16;
	}
}
NumericBase::~NumericBase(){}
vector<Digit> NumericBase::getDigits(){
	return Digits;
}
int NumericBase::getBase(){
	return Base;
}
Digit NumericBase::getDigit(int number){
	if(number>=0&&number<=Base){
		for(int i=0;i<Digits.size();i++){
			if(number==Digits[i].value){
				return Digits[i];
			}
		}
	}else return Digits[0];
}
Digit NumericBase::getDigit(char character){
	for(int i=0;i<Digits.size();i++){
		if(character==Digits[i].character){
			return Digits[i];
		}
	}
	return Digits[0];
}
string NumericBase::toBase(int decimal){
	string result("");
	int div,mod;
	vector<Digit> _digits(0);
	do{
		div=decimal/Base;
		mod=decimal%Base;
		_digits.push_back(getDigit(mod));
		decimal=div;
	}while(div>=Base);
	if(div)
		_digits.push_back(getDigit(div));
	for(int i=_digits.size()-1;i>=0;i--){
		result+=_digits[i].character;
	}
	return result;
}
int NumericBase::toDecimal(string number){
	int result=0,i=0,j=number.size()-1;
	for(i=0;i<number.size();i++){
		result+=(getDigit(number[i]).value)*pow(Base,j--);
	}
	return result;
}
string NumericBase::fillFormat(string number,int extension){
	string aux("");
	if(number.size()<extension){
		for(int i=0;i<extension-number.size();i++){
			aux+=Digits[0].character;
		}
		number=aux+number;
	}
	return number;
}
void NumericBase::print(){
	for(int i=0;i<Base;i++){
		cout<<Digits[i].character<<": "<<Digits[i].value<<endl;
	}
}
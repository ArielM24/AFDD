bool isSeparator(char c);
bool isOperator(char c);
bool isOperator(string c);
bool containDigits(string s);
bool isLogicalOperator(char c);
vector<string> tokens(string tok);
bool existInVector(vector<string> v, string s);
bool quote(string s);
bool onlyNumbers(string);
vector<string> numericsConstant(vector <string> tokens);
vector<string> operadores(vector<string> tokens);
vector<string> concatenadores(vector<string>);
vector<string> IncDec(vector<string>);
bool isOperator(char c){
	return ((c=='+')||(c=='%')||(c==':')||(c=='*') || (c=='/') || (c=='[') || (c==']') || (c=='(')|| (c==')')|| (c=='}')|| (c=='{') || (c=='=')|| (c=='<')|| (c=='>'));
}

bool isOperator(string c){
	if (c.size()>1) return false;
	else 
		return ((c[0]=='*') || (c[0]=='/') || (c[0]=='[') || (c[0]==']') || (c[0]=='(')|| (c[0]==')')|| (c[0]=='}')|| (c[0]=='{') || (c[0]=='=')|| (c[0]=='<')|| (c[0]=='>'));
}

bool isSeparator(char c){
	return ((c==' ') || (c=='\n') || (c=='\t') || (c==','));
}

bool isLogicalOperator(char c){
	return ((c=='&') || (c=='|') || (c=='<') || (c=='!'));
}

bool isLogicalOperator(string c){
	return ((c[0]=='&') || (c[0]=='|') || (c[0]=='<') || (c[0]=='!'));
}

vector<string> tokens(string tok){
	string aux="";
	char c;
	vector<string> constant;
	for (int i=0; i<tok.size(); i++)
		{
			c=tok[i];
			if (!isSeparator(c)){
				if ((c=='/') && (tok[i+1]=='/')){
					aux=aux+c;
					aux=aux+tok[i+1];
					i+=2;
					while ((tok[i]!='\n') && (i<tok.size())) {
						aux=aux+tok[i];
						i++;
					}
					constant.push_back(aux);
					aux="";
				}
				else if (c=='"'){
					aux=aux+c;
					i++;
					while ((tok[i]!='"')&&(i<tok.size())){
						aux=aux+tok[i];
						i++;
					}
					aux=aux+tok[i];
					i++;
					constant.push_back(aux);
					aux="";
				}
				else if ((c=='/') && (tok[i+1]=='*')){
					aux=aux+c; 
					aux=aux+tok[i+1];
					i+=2;
					while (i<tok.size()){
						aux=aux+tok[i];
						if ((tok[i]=='*') && (tok[i+1]=='/')){
							aux=aux+tok[i+1];
							i+=2;
							break;
						}
						else
							i++;
					}
					constant.push_back(aux);
					aux="";
				}
				else if (isOperator(c) || c==';' || isLogicalOperator(c)){
					if(aux!="")
						constant.push_back(aux);
					aux=c;
					constant.push_back(aux);
					aux="";
				}
				
				else 
					aux=aux+c;				
			}
			else {
				if(aux!="")
					constant.push_back(aux);
				aux="";
			}
				
	}

	return constant;
}

bool containDigits(string s){
	for(int i=0; i<s.size(); i++){
		if ((s[i]>='0') && (s[i]<='9'))
			return true;
	}
	return false;		
}

bool existInVector(vector<string> v, string s){
	for (int i=0; i<v.size(); i++){
		if (v[i]==s)
			return true;
	}
	return false;
}



bool quote(string s){
	return s[0]=='"';
}
bool onlyNumbers(string token){
	for(int i=0;i<token.size();i++){
		if(!(token[i]>='0'&&token[i]<='9')){
			return false;
		}
	}
	return true;
}
vector<string> numericsConstant(vector<string> tokens){
	vector <string> numbers; 
	vector <string> finalNumbers;
	
	for (int i=0; i<tokens.size(); i++){
	 //revisa: tenga digitos   el guardado antes que él sea operador o que ya este guardado, es decir, sea numero pero que no esté seguido por un (int i=0, h8;) ; que no esté entre comillado y que despues de él no siga una igualación (int e6=0)
		if ((containDigits(tokens[i])) && ( isOperator(tokens[i-1]) || (existInVector(numbers, tokens[i-1])
			|| isLogicalOperator(tokens[i-1])) && tokens[i+1][0]!=';') && (!quote(tokens[i])) && (tokens[i+1][0]!='=')
			||onlyNumbers(tokens[i])||(i>0&&tokens[i-1]=="case")){
			numbers.push_back(tokens[i]);
		}
	}
	int n=numbers.size();
	for (int i=0; i<n; i++){
		for(int j=0; j<numbers[i].size(); j++){
			if  ((numbers[i][j]=='-') || (numbers[i][j]=='+')){
				if ((j!=0) && ((numbers[i][j-1]!='e') && (numbers[i][j-1]!='E'))){
					numbers.push_back(numbers[i].substr(j, (numbers[i].size())-j)); 
					numbers[i]=(numbers[i].substr(0, j));
					n=numbers.size();
				}
			}
		}
	}
	
	//elimina los operadores
	for (int i=0; i<numbers.size(); i++){
		if(numbers[i].size()!=1)
			finalNumbers.push_back(numbers[i]);
		else if ((numbers[i][0]!='+') && (numbers[i][0]!='-'))
			finalNumbers.push_back(numbers[i]);
	}
	
	
	return finalNumbers;
}

vector<string> operadores(vector<string> tokens){
	vector<string> tok = vector<string>(0);
	string aux1("");
	for(int i=0;i<tokens.size();i++){
		if(i&&(tokens[i-1]=="<"||tokens[i-1]==">"||tokens[i-1]=="="||tokens[i-1]=="!")&&tokens[i]=="="){
			aux1=tokens[i-1]+tokens[i];
			tok.erase(tok.begin()+i);
			tok.push_back(aux1);
		}else{
			tok.push_back(tokens[i]);
		}
	}
	return tok;
}
vector<string> concatenadores(vector<string> tokens){
	vector<string> tok = vector<string>(0);
	string aux1("");
	for(int i=0;i<tokens.size();i++){
		if(tokens[i].size()>1){
			if(tokens[i][0]=='+'&&tokens[i][1]=='"'){
				tok.push_back("+");
				aux1=tokens[i];
				aux1.erase(0,1);
				tok.push_back(aux1);
			}else{
				tok.push_back(tokens[i]);
			}
		}else{
			tok.push_back(tokens[i]);
		}
	}
	return tok;
}
vector<string> IncDec(vector<string> tokens){
	vector<string> tok = vector<string>(0);
	string aux1("");
	for(int i=0;i<tokens.size();i++){
		if(tokens[i].size()>2){
			if(tokens[i][tokens[i].size()-1]=='+'&&tokens[i][tokens[i].size()-2]=='+'){
				tok.push_back("++");
				aux1=tokens[i];
				aux1.erase(tokens[i].size()-2,2);
				tok.push_back(aux1);
			}else if(tokens[i][tokens[i].size()-1]=='-'&&tokens[i][tokens[i].size()-2]=='-'){
				tok.push_back("--");
				aux1=tokens[i];
				aux1.erase(tokens[i].size()-2,2);
				tok.push_back(aux1);
			}
			else{
				tok.push_back(tokens[i]);
			}
		}else{
			tok.push_back(tokens[i]);
		}
	}
	return tok;
}
vector<string> tokensJava(string tok){
	vector<string> Tokens = tokens(tok);
	Tokens=operadores(Tokens);
	Tokens=concatenadores(Tokens);
	Tokens=IncDec(Tokens);
	return Tokens;
}
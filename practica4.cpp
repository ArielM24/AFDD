#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<vector>
#include<time.h>
#include<fstream>
#include"NumericBase.h"
#include"Alphabet.h"
#include"NumericString.h"
#include"RegularLenguage.h"
#include"Matrix.h"
#include"AFD.h"
#include"tokens.h"

using namespace std;
string capturaCodigo(string);
void afdEvalua(AFD,string,int);
void evaluaConstantes(string);

int main(void){
	string op,codigo=capturaCodigo("AFDs/constantesJava.java");
	cout<<"Evaluacion de constantes:\n";
	evaluaConstantes("AFDs/constantesJava.java");
	cout<<"Precione una tecla para continuar\n";
	getline(cin,op);
	RegularLenguage RLControl = RegularLenguage("AFDs/control.rl");
	AFD afdControl = AFD(RLControl);
	RegularLenguage RLComparadores = RegularLenguage("AFDs/comparadores.rl");
	AFD afdComparadores = AFD(RLComparadores);
	RegularLenguage RLOperadores = RegularLenguage("AFDs/operadores.rl");
	AFD afdOperadores = AFD(RLOperadores);
	AFD afdConstantes = AFD("AFDs/constantesJava.afd");
	AFD afdIdentificadores = AFD("AFDs/etiquetas.afd");
	RegularLenguage RLPalabrasReseradas = RegularLenguage("AFDs/palabrasReservadasJava.rl");
	AFD afdPalabrasReservadas = AFD(RLPalabrasReseradas);
	AFD afdComentarios = AFD("AFDs/comentarios.afd");
	AFD afdCadenas = AFD("AFDs/cadenas.afd");
	AFD afdMetodos = AFD("AFDs/metodos.afd");
	vector<string> Tokens = tokensJava(codigo);
	bool correcto = false;
	ofstream fileLog;
	fileLog.open("analizador.txt",ios::out);
	if(fileLog.fail()){
		cout<<"Error Log\n";
		exit(1);
	}
	for(int i=0;i<Tokens.size();i++){
		bool _control = afdControl.evaluation(Tokens[i]);
		bool _comparador = afdComparadores.evaluation(Tokens[i]);
		bool _operador = afdOperadores.evaluation(Tokens[i]);
		bool _constante = afdConstantes.evaluation(Tokens[i]);
		bool _identificador = afdIdentificadores.evaluation(Tokens[i]);
		bool _reservada = afdPalabrasReservadas.evaluation(Tokens[i]);
		bool _comentario = afdComentarios.evaluation(Tokens[i]);
		bool _cadena = afdCadenas.evaluation(Tokens[i]);
		bool _metodo = afdMetodos.evaluation(Tokens[i]);
		fileLog<<"Token: "<<Tokens[i]<<endl;
		fileLog<<"AFDs: "<<endl;
		if(_control){
			fileLog<<"Control"<<endl;
		}
		if(_comparador){
			fileLog<<"Comparadores"<<endl;
		}
		if(_operador){
			fileLog<<"Operadores"<<endl;
		}
		if(_constante){
			fileLog<<"Constante"<<endl;
		}
		if(_identificador){
			fileLog<<"Identificador"<<endl;
		}
		if(_reservada){
			fileLog<<"Reservada"<<endl;
		}
		if(_comentario){
			fileLog<<"Comentarios"<<endl;
		}
		if(_cadena){
			fileLog<<"Cadenas"<<endl;
		}
		if(_metodo){
			fileLog<<"Metodo"<<endl;
		}
		correcto=_control||_comparador||_operador||_constante||
			_identificador||_reservada||_comentario||_cadena||_metodo;
		if(!correcto){
			cout<<"Error: "<<Tokens[i]<<endl;
		}
	}
	return 0;
}
string capturaCodigo(string ruta){
	string x="";
	char c;
	ifstream archivo("AFDs/constantesJava.java");
	if(archivo.fail())
		cerr << "Error al abrir el archivo .java!" << endl;
	else {

		while(!archivo.eof())
		{
			archivo.get(c);
			x=x+c;
		}
	}
	return x;
}
void afdEvalua(AFD afd1,string constante,int linea){
	if(!afd1.evaluation(constante)){
		if(afd1.getActualState()==14){
			cout<<"Error decimal en la linea: "<<linea<<": "<<constante<<endl;
		}else if(afd1.getActualState()==15){
			cout<<"Constante invalida en la linea: "<<linea<<": "<<constante<<endl;
		}else if(afd1.getActualState()==16){
			cout<<"Error octal en la linea: "<<linea<<": "<<constante<<endl;
		}else if(afd1.getActualState()==17){
			cout<<"Error hexadecimal en la linea: "<<linea<<": "<<constante<<endl;
		}else if(afd1.getActualState()==18){
			cout<<"Error real en la linea: "<<linea<<": "<<constante<<endl;
		}else if(afd1.getActualState()==19){
			cout<<"Error notacion exponencial en la linea: "<<linea<<": "<<constante<<endl;
		}else{
			cout<<"Constante invalida en la linea: "<<linea<<": "<<constante<<endl;
		}
	}
}
void evaluaConstantes(string ruta){
	ifstream archivo;
	archivo.open(ruta,ios::in);
	if(!archivo.fail()){
		AFD afdConstantes = AFD("AFDs/constantesJava.afd");
		int contadorLinea=1;
		string linea("");
		while(!archivo.eof()){
			getline(archivo,linea);
			vector<string> constantes = numericsConstant(tokens(linea));
			for(int i=0;i<constantes.size();i++){
				afdEvalua(afdConstantes,constantes[i],contadorLinea);
			}
			contadorLinea++;
		}
	}else{
		cerr<<"No se pudo abrir: "<<ruta<<endl;
		exit(1);
	}
}
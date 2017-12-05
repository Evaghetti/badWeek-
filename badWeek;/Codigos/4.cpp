#include<iostream>
#include<string>
using namespace std;
main(){
	int caso=0;
	string procura,frase;
	while((cin>>procura)!=0){
		int cont=0;
		size_t pos=0;
		cin>>frase;
		while((pos=frase.find(procura,pos))!=std::string::npos){
			cont++;
			pos+=procura.size();
		}
		int ultpos=frase.rfind(procura)+1;
		cout<<"Caso #"<<++caso<<":"<<endl;
		if(cont>0){
			cout<<"Qtd.Subsequencias: "<<cont<<endl;
			cout<<"Pos: "<<ultpos<<endl<<endl;
		}else{
			cout<<"Nao existe subsequencia"<<endl<<endl;
		}
	}
}
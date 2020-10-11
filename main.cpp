#include<iostream>
#include<cstring>
#include<cstdio>
#include<fstream>
#include<vector>
#include "LinkedList.h"
#define BITACORA "bitacora.txt"
#define REPORTE "reporte.txt"

using namespace std;

//Realiza el trabajo del operador "<" para los vectores que contienen la ip
//Entrada: 2 ip
//Salida si ip1_l<ip2_l regresa true, de otro modo false
//O(1)
bool ipLessThan(LinkedList<string> ip1_l, LinkedList<string> ip2_l){
  vector<int> ip1,ip2;
  string ip1_s = ip1_l[3];
  string ip2_s = ip2_l[3];
  char * str1 = new char[ip1_s.length()+1];
  char * str2 = new char[ip2_s.length()+1];
  strcpy(str1,ip1_s.c_str());
  strcpy(str2,ip2_s.c_str());
  
  char * pch;
  pch = strtok (str1," ,.-");
 
  while (pch != NULL)
  {
  	ip1.push_back(atoi(pch));
    pch = strtok (NULL, ".:");
  }
  pch = strtok (str2," ,.-");
  while (pch != NULL)
  {
  	ip2.push_back(atoi(pch));
    pch = strtok (NULL, ".:");
  }
  int i = 0;
  while(ip1[i]==ip2[i]&&i<5)++i;
  if(i!=5&&ip1[i]<ip2[i]) return true;
  return false;
}

//Hace el último paso después de ordenar por mergesort recursivamente
// Parámetros:
// array: vector de datos a ordenar
// l: limite izquierdo
// m: punto medio
// r: limite derecho
// Valor de retorno: no hay
// Big Omega: Omega(n) El mejor caso es cuando el vector ya está ordenado así que solo se ejecutan n/2 + 1 pasos,
// pues la otra mitad de los datos se inserta de golpe
// Big Theta: Theta(n)
// Big O: O(n) el peor caso es cuando el vector está intercalado y se tienen que insertar un dato de un subconjunto y otro del otro
// donde se deben de hacer n pasos
void merge(LinkedList<LinkedList<string>>&array, const int &l, const int &m, const int &r) {
   int i, j, k, nl, nr,aux;
   nl = m-l+1; nr = r-m; 
   LinkedList<LinkedList<string>> larr, rarr;
   LinkedList<string> v;
   for(int i = 0;i<5;i++) v.append("");
   aux=nl;
   while(aux--){
   		larr.append(v);
   }
   aux=nr;
   while(aux--){
   		rarr.append(v);
   }
   //cout<<"Merge\n";
   for(i = 0; i<nl; i++)
      larr.update(i,array[l+i]);
   for(j = 0; j<nr; j++)
      rarr.update( j,array[m+1+j]);
   i = 0; j = 0; k = l;
   while(i < nl && j<nr) {
      if(ipLessThan(larr[i],rarr[j])){
         array.update(k,larr[i]);
         i++;
      }else{
         array.update(k,rarr[j]);
         j++;
      }
      k++;
   }
   while(i<nl) {      
      array.update(k,larr[i]);
      i++; k++;
   }
   while(j<nr) {     
      array.update(k,rarr[j]);
      j++; k++;
   }
}

//Ordena recursivamente con mergeSort
// Parámetros:
// array: vector de datos a ordenar
// p: limite izquierdo
// r: limite derecho
// Valor de retorno: no hay
// Big Omega: Omega(n lg(n)) El mejor caso es cuando el vector ya está ordenado así que solo se ejecutan n/2 + 1 pasos,
// pues la otra mitad de los datos se inserta de golpe, pero aún así se dividen en dos el número de elementos 
// Big Theta: Theta(n lg(n))
// Big O: O(n lg(n)) el peor caso es cuando el vector está intercalado y se tienen que insertar un dato de un subconjunto y otro del otro
// donde se deben de hacer n pasos, pero aún así se dividen en dos el número de elementos
void mergeSort(LinkedList<LinkedList<string>>&list,const int&p,const int&r){
	//cout<<"MergeSort\n";
	if(p<r){
		int q=(p+r)/2;
		mergeSort(list,p,q);
		mergeSort(list,q+1,r);
		merge(list,p,q,r);
	}
}

//Se encarga de pedir las ip begin y end
//Entrada:
// begin: ip inicial
// end: ip final
// O(n)
void ipRequest(string& begin, string& end){
	cout<<"Ingrese la ip de inicio: (Ejemplo 9.94.941.41:5600 )\n";
	cin>>begin;

	cout<<"Ingrese la la fecha final: (Ejemplo 933.55.453.35:5546) \n";
	cin>>end;
}

// Encuentra la primera ocurrencia de ip
// Entrada:
// binnacle: LinkedList que contiene la bitacora
// ip: ip que se busca
// O(n) ya que hace una búsqueda lineal
int firstOf(LinkedList<LinkedList<string>>&binnacle, const string& ip){
	for(int i = 0; i<binnacle.getSize();++i){
		if(binnacle[i][3]==ip) return i;
	}
}

// Encuentra la última ocurrencia de ip
// Entrada:
// binnacle: LinkedList que contiene la bitacora
// ip: ip que se busca
// O(n) ya que hace una búsqueda lineal

int lastOf(LinkedList<LinkedList<string>>&binnacle, const string& ip){
	for(int i = binnacle.getSize()-1; i>=0;--i){
		if(binnacle[i][3]==ip) return i;
	}
}
// Lee la bitacora y la almacena en una LinkedList
void readBinnacle(LinkedList<LinkedList<string>>&bitacora){
	ifstream archivoBitacora;
	archivoBitacora.open(BITACORA,ios::in);
	string linea, mes, dia, hora, ip;
	LinkedList<string>aux;
	while(!archivoBitacora.eof()){
		aux.clear();
		mes = dia = hora="";
		archivoBitacora>>mes;
		archivoBitacora>>dia;
		archivoBitacora>>hora;
		archivoBitacora>>ip;
		aux.append(mes);
		aux.append(dia);
		aux.append(hora);
		aux.append(ip);
		getline(archivoBitacora,linea);
		linea.erase(linea.begin(),linea.begin()+1);
		aux.append(linea);
		bitacora.append(aux);
	}
	archivoBitacora.close();
}

// Llena el reporte con la información solicitada
//Entrada:
// binnacle: LinkedList ordenado de la bitacora
// inicio: ip inicial
// fin: ip final
void fillReport(LinkedList<LinkedList<string>>&binnacle, const int &inicio, const int &fin){
	ofstream reporte(REPORTE,ios::out);
	for(int i=inicio;i<=fin;i++){
		for(int j=0;j<5;j++){
			reporte<<binnacle[i][j]<<" ";
		}
		reporte<<"\n";
	}
}

int main(){
	LinkedList<LinkedList<string>>binnacle;
	string ipBegin,ipEnd;
	ipRequest(ipBegin, ipEnd);
	readBinnacle(binnacle);
	mergeSort(binnacle,0,binnacle.getSize()-1);
	int begin = firstOf(binnacle, ipBegin);
	int end = lastOf(binnacle, ipEnd);
	fillReport(binnacle,begin,end);
	for(int i = begin; i<= end;++i){
		for(int j=0;j<binnacle[i].getSize();++j) cout<<binnacle[i][j]<<" ";
		cout<<"\n";
  	}
		
	return 0;
	
}

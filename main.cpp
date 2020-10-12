#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<fstream>
#include<vector>
#include "LinkedList.h"
#define BITACORA "bitacora.txt"
#define REPORTE "reporte.txt"

using namespace std;

// Does the work of the operator "<" for the vectors that contain the ip
// Input: 2 ip
// Output if ip1_l <ip2_l returns true, otherwise false
// OR (1)
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

// Does the last step after sorting by mergesort recursively
// Parmeters:
// array: vector of data to sort
// l: left limit
// m: midpoint
// r: right limit
// Return value: none
// Big Omega: Omega (n) The best case is when the vector is already ordered so only n / 2 + 1 steps are executed,
// because the other half of the data is inserted at once
// Big Theta: Theta (n)
// Big O: O (n) the worst case is when the vector is interleaved and a data from one subset and another from the other have to be inserted
// where to do n steps
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

// Sort recursively with mergeSort
// Par meters:
// array: vector of data to sort
// p: left limit
// r: right limit
// Return value: none
// Big Omega: Omega (n lg (n)) The best case is when the vector is already ordered so only n / 2 + 1 steps are executed,
// because the other half of the data is inserted at once, but still the number of elements is divided in two
// Big Theta: Theta (n lg (n))
// Big O: O (n lg (n)) the worst case is when the vector is interspersed and a data from one subset and another from the other have to be inserted
// where n steps must be done, but still divide the number of elements in two
void mergeSort(LinkedList<LinkedList<string>>&list,const int&p,const int&r){
	//cout<<"MergeSort\n";
	if(p<r){
		int q=(p+r)/2;
		mergeSort(list,p,q);
		mergeSort(list,q+1,r);
		merge(list,p,q,r);
	}
}

// It is in charge of asking the ip begin and end
//Entry:
// begin: initial ip
// end: final ip
// O (n)
void ipRequest(string& begin, string& end){
	cout<<"Ingrese la ip de inicio: (Ejemplo 9.94.941.41:5600 )\n";
	cin>>begin;

	cout<<"Ingrese la la fecha final: (Ejemplo 933.55.453.35:5546) \n";
	cin>>end;
}

// Find the first occurrence of ip
// Entry:
// binnacle: LinkedList that contains the log
// ip: ip to be searched
// O (n) since it does a linear search
int firstOf(LinkedList<LinkedList<string>>&binnacle, const string& ip){
	for(int i = 0; i<binnacle.getSize();++i){
		if(binnacle[i][3]==ip) return i;
	}
}

// Find the last occurrence of ip
// Entry:
// binnacle: LinkedList that contains the log
// ip: ip to be searched
// O (n) since it does a linear search

int lastOf(LinkedList<LinkedList<string>>&binnacle, const string& ip){
	for(int i = binnacle.getSize()-1; i>=0;--i){
		if(binnacle[i][3]==ip) return i;
	}
}
// Read the log and store it in a LinkedList
// O (n) since it goes through the whole log
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

// Fill in the report with the requested information
//Entry:
// binnacle: LinkedList ordered from the log
// start: initial ip
// end: final ip
// O (n) traverses the entire linked list
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

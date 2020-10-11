#ifndef LinkedList_H
#define LinkedList_H
#include "Node.h"
template<class T>
class LinkedList{
  private:
    Node<T> * head;
    Node<T> * feet;
    int size;
  public:
    LinkedList<T>();
    LinkedList<T>(const LinkedList<T>& myList);
    void append(const T& datum);
    void clear();
    void create(int index,const T& datum);
    void del(int index);
    Node<T> * getHead()const;
    Node<T> * getFeet()const;
    int getSize()const;
    void push(const T& datum);
    T  read(int index);
    T  readReverse(int index);
    void update(int index, const T& datum);
    T operator[](const int& index);
};
template<typename T>
LinkedList<T>::LinkedList():head(nullptr),feet(nullptr),size(0){}

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& myList):head(nullptr),feet(nullptr),size(0){
	if(!myList.size) return;
	head = new Node<T>(T{});
	head -> content = myList.head->content;
	Node<T> * auxboy = head;
	Node<T> * iter = myList.head->nextboy;
	Node<T> * holder = head;
	int index = myList.size-1;
	while(index--){
		Node<T> * pnewboy = new Node<T>(T{});
		pnewboy->content = iter->content;
		auxboy->nextboy = pnewboy;
		auxboy->prevboy = holder;
		holder = auxboy;
		auxboy = auxboy->nextboy;
		iter = iter->nextboy;
	}
	feet = auxboy;
	size = myList.size;
}

template<typename T>
void LinkedList<T>::append(const T& datum){
  Node<T> * pnewboy = new Node<T>(datum);
  Node<T> * pcurrentboy = feet;
  if(!feet){
    head=feet=pnewboy;
  }
  else {
    feet->nextboy = pnewboy;
	pnewboy->prevboy = feet;
	feet=pnewboy;
	}
  ++size;
}
template<typename T>
void LinkedList<T>::create(int index,const T& datum){
	Node<T>  * pnewboy = new Node<T>(datum);
	Node<T>  * pauxboy = head;
	Node<T>  * pauxholder = nullptr;
	while(index--){
		pauxholder=pauxboy;
		if(!pauxboy->nextboy){
			if(index>0) this->append(0);
			else{
				this->append(datum);
				return;
			}
		}
		pauxboy=pauxboy->nextboy;
	}
	if(pauxboy == head){
		pnewboy->nextboy=head;
		head->prevboy=pnewboy;
		head=pnewboy;
	}
	else{
		pauxholder->nextboy=pnewboy;
		pnewboy->prevboy=pauxholder;
		pnewboy->nextboy=pauxboy;
		pauxboy->prevboy=pnewboy;
	}
	++size;
}
template<typename T>
void LinkedList<T> :: clear(){
	Node<T> * pauxboy = head;
	Node<T> * pauxnext = nullptr;
	while(pauxboy){
		pauxnext = pauxboy->nextboy;
		delete pauxboy;
		pauxboy=pauxnext;
	}
	size=0;
	head=nullptr;
	feet=nullptr;	
}

template<typename T>
void LinkedList<T>::del(int index){
	Node<T> * pauxboy = head;
	Node<T>  * pauxholder = nullptr;
	while(index--){
		pauxholder=pauxboy;
		if(!pauxboy->nextboy) return;
		pauxboy=pauxboy->nextboy;
	}
	if(pauxboy == head) {
		head=head->nextboy;
		head->prevboy=nullptr;
	}
	else if(pauxboy == feet){
		feet=feet->prevboy;
		feet->nextboy=nullptr;
	}
	else {
		pauxholder->nextboy=pauxboy->nextboy;
		pauxboy->prevboy=pauxholder;
	}
	--size;
}
template<typename T>
Node<T>* LinkedList<T>::getHead()const{
  return this->head;
}
template<typename T>
Node<T>* LinkedList<T>::getFeet()const{
  return this->feet;
}
template<typename T>
int LinkedList<T>::getSize()const{
  return size;
}
template<typename T>
void LinkedList<T>::push(const T& datum){
  Node<T>  * pnewboy=new Node<T>(datum);
  pnewboy->nextboy=head;
  if(head){
  	head->prevboy=pnewboy;
  	head=pnewboy;
  }
  else{
  	feet=head=pnewboy;
  }

  size++;
}
template<typename T>
T LinkedList<T>::read(int index){
	Node<T>  * pauxboy = head;
	while(index--){
		if(!pauxboy->nextboy) return T{};
		pauxboy=pauxboy->nextboy;
	}
	return pauxboy->content;
}
template<typename T>
T LinkedList<T>::readReverse(int index){
	Node<T>  * pauxboy = feet;
	while(index--){
		if(!pauxboy->prevboy) return 0;
		pauxboy=pauxboy->prevboy;
	}
	return pauxboy->content;
}
template<typename T>
void LinkedList<T>::update( int index, const T& datum){
	Node<T>  * pauxboy = head;
	while(index--) {
		if(!pauxboy->nextboy) return;
		pauxboy=pauxboy->nextboy;
	}
	pauxboy->content=datum;
}

template<typename T>
T LinkedList<T>::operator[](const int& index){
	return this->read(index);
};

#endif

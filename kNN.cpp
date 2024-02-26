#include "kNN.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// ----------------- ArrayList -----------------

template<typename T>
void ArrayList<T>::arrayFull(){
    capacity = capacity *2; // double the capacity
    T* newArr = new T[capacity];
    for(int i = 0; i < size; i++){
        newArr[i] = data[i];
    }
    delete[] data;
    data = newArr; //copy the data to the new array
}

template<typename T>
void ArrayList<T>::push_back(T value){
    if(size == capacity){ //if the array is full
        arrayFull();
    }
    data[size] = value;
    size++;
}

template<typename T>
void ArrayList<T>::push_front(T value){
    if(size == capacity){ //if the array is full
        arrayFull();
    }
    
    for(int i = size; i > 0; i--){
        data[i] = data[i-1]; //shift the data to the right
    }
    data[0] = value;
    size++;
}

template<typename T>
void ArrayList<T>::insert(int index, T value){
    if (index < 0 || index > size){
        return;
    }
    if(size == capacity){ //if the array is full
        arrayFull();
    }
    if (index == size){ //if the index is the last element
        data[size] = value;
        size++;
        return;
    }
    for (int i = index; i < size; i++){
        data[i+1] = data[i]; //shift the data to the right
    }
    data[index] = value;
    size++;
}

template<typename T>
void ArrayList<T>::remove(int index){
    if (index < 0 || index >= size){
        return;
    }
    for(int i = index; i < size; i++){
        data[i] = data[i+1]; //shift the data to the left
    }
    size--;
}

template<typename T>
T& ArrayList<T>::get(int index) const{
    if (index < 0 || index >= size){
        throw out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
int ArrayList<T>::length() const{
    return size;
}

template<typename T>
void ArrayList<T>::clear(){
    delete [] data;
    capacity = 10;
    size = 0;
    data = new T[capacity];
}

template<typename T>
void ArrayList<T>::print() const{
    for(int i = 0; i < size; i++){
        cout << data[i];
        if (i != size-1){
            cout << " ";
        }
    }
}

template<typename T>
void ArrayList<T>::reverse(){
    T* newArr = new T[capacity];
    for(int i = 0; i < size; i++){
        newArr[i] = data[size-i-1];
    }
    delete[] data;
    data = newArr;
}
//----------------end of ArrayList---------------

// ----------------- Dataset -----------------
Dataset::Dataset(){
    data = new ArrayList<ArrayList<int>*>;
}

Dataset::~Dataset(){
    for(int i = 0; i < data->length(); i++){
        delete data->get(i);
    }
    delete data;
}

Dataset::Dataset(const Dataset& other){
    data = new ArrayList<ArrayList<int>*>;
    for(int i = 0; i < other.data->length(); i++){
        ArrayList<int>* temp = new ArrayList<int>;
        for(int j = 0; j < other.data->get(i)->length(); j++){
            temp->push_back(other.data->get(i)->get(j));
        }
        data->push_back(temp);
    }
}


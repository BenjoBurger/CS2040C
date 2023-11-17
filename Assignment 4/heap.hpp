#pragma once
#include <math.h>

#include <iostream>
using namespace std;

#ifndef HEAPHPP
#define HEAPHPP

template <class T>
void Heap<T>::_bubbleUp(int index) {
    if (index < 1) {
        return;
    }
    int parentIndex = floor((index - 1) / 2);
    if (_heap[index] > _heap[parentIndex]) {
        T temp = _heap[index];
        _heap[index] = _heap[parentIndex];
        _heap[parentIndex] = temp;
        _bubbleUp(parentIndex);
    }
}

template <class T>
void Heap<T>::_bubbleDown(int index) {
    int left = index * 2 + 1;
    int right = index * 2 + 2;
    if (right < _n) {
        if (_heap[right] > _heap[left]) {
            if (_heap[right] > _heap[index]) {
                T temp = _heap[index];
                _heap[index] = _heap[right];
                _heap[right] = temp;
                _bubbleDown(right);
            }
            if (_heap[left] > _heap[index]) {
                T temp = _heap[index];
                _heap[index] = _heap[left];
                _heap[left] = temp;
                _bubbleDown(left);
            }
        }
        else if (left < _n) {
            if (_heap[left] > _heap[index]) {
                T temp = _heap[index];
                _heap[index] = _heap[left];
                _heap[left] = temp;
                _bubbleDown(left);
            }
        }
    }
    else if (left < _n) {
        if (_heap[left] > _heap[index]) {
            T temp = _heap[index];
            _heap[index] = _heap[left];
            _heap[left] = temp;
            _bubbleDown(left);
        }
    }
}

template <class T>
void Heap<T>::insert(T item) {
    _heap[_n] = item;
    _bubbleUp(_n);
    _n++;
}

template <class T>
T Heap<T>::extractMax() {
    T max = _heap[0];
    _n--;
    _heap[0] = _heap[_n];
    _bubbleDown(0);
    //cout << "Heapsize: " << _n << endl;
	return max;
}


template <class T>
void Heap<T>::printHeapArray() {
	for (int i = 0; i < _n; i++)
		cout << _heap[i] << " ";
	cout << endl;
}

template <class T>
int Heap<T>::_lookFor(T x){ // not a very good implementation, but just use this for now.
    int i;
    for(i=0;i<_n;i++)
        if (_heap[i] == x)
            return i;
    
    return -1;
}

template <class T>
void Heap<T>::decreaseKey(T from, T to)
{
    int key = _lookFor(from);
    if (key == -1) {
        return;
    }
    _heap[key] = to;
    _bubbleDown(key);
}


template <class T>
void Heap<T>::increaseKey(T from, T to)
{
    int key = _lookFor(from);
    if (key == -1) {
        return;
    }
    _heap[key] = to;
    _bubbleUp(key);
}

template <class T>
void Heap<T>::deleteItem(T x)
{
    int key = _lookFor(x);
    if (key == -1) {
        return;
    }
    _n--;
    _heap[key] = _heap[_n];
    int index = floor((key - 1) / 2);
    if (_heap[index] > _heap[key] ) {
        _bubbleDown(key);
    }
    else {
        _bubbleUp(key);
    }
}

template <class T>
void Heap<T>::printTree() {
    int parity = 0;
	if (_n == 0)
		return;
	int space = pow(2,1 + (int) log2f(_n)),i;
	int nLevel = (int) log2f(_n)+1;
	int index = 0,endIndex;
    int tempIndex;
	
	for (int l = 0; l < nLevel; l++)
	{
		index = 1;
        parity = 0;
		for (i = 0; i < l; i++)
			index *= 2;
		endIndex = index * 2 - 1;
		index--;
        tempIndex = index;
        while (index < _n && index < endIndex) {
            for (i = 0; i < space-1; i++)
                cout << " ";
            if(index==0)
                cout << "|";
            else if (parity)
                cout << "\\";
            else
                cout << "/";
            parity = !parity;
            for (i = 0; i < space; i++)
                cout << " ";
			index++;
		}
        cout << endl;
        index=tempIndex;
		while (index < _n && index < endIndex) {
			for (i = 0; i < (space-1-((int) log10(_heap[index]))); i++)
				cout << " ";
			cout << _heap[index];
			for (i = 0; i < space; i++)
				cout << " ";
			index++;
		}
		
		cout << endl;
		space /= 2;
	}

}

#endif

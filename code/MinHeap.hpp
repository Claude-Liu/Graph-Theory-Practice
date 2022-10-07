#ifndef MINHEAP_HPP
#define MINHEAP_HPP
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;

// Min-heap class
//   arranged in an array starting from 0 upon
template <class Elem, class Comp> class MinHeap {
private:
	vector<Elem> heap;		// Pointer to the heap array
	int size;		// Maximum size of the heap
	int n;			// Number of elements now in the heap(not just in the array)
	void swap( vector<Elem> &h, int a, int b) 
	{ Elem tmp = h[a]; h[a] = h[b]; h[b] = tmp; }
	void shiftdown(int);	
public:
	MinHeap();
	MinHeap(vector<Elem> &h, int num, int max)
	{ heap = h; n = num; size = max; buildheap(); }
	int heapsize() const {return n; }
	bool isLeaf(int pos) const {return (pos>=n/2) && (pos<n); }
	int leftchild(int pos) const { return 2*pos+1; }
	int rightchild(int pos) const { return 2*pos+2; }
	int parent(int pos) const { return (pos-1)/2; }	
	bool insert(const Elem& val);
	Elem removemin();	//top()and pop()
	Elem top(){return heap[0];}	
	void buildheap()
	{ for (int i=n/2-1; i>=0; i--) shiftdown(i); }
	void heapprint();
};

template <class Elem, class Comp>
void MinHeap<Elem, Comp>::shiftdown(int pos){
	while(!isLeaf(pos)){
		int j = leftchild(pos);
		int rc = rightchild(pos);
		if ((rc<n) && Comp::gt(heap[j], heap[rc])) j = rc; 
		if (!Comp::gt(heap[pos], heap[j])) return; // no need to swap
		swap(heap, pos, j);
		pos = j;	// Move down
	}
}

template <class Elem, class Comp>
bool MinHeap<Elem, Comp>::insert(const Elem& val){
	if (n>=size) return false;	// Heap is full
	int curr = n++;
	if(n<=heap.size()) heap[curr] = val;//when the vector is not full, change the next element
	else heap.push_back(val);//when the vecctor is full, push an element
	// Sift upward until curr's parent >= curr
	while ((curr!=0) && (Comp::lt(heap[curr], heap[parent(curr)]))){
		swap(heap, curr, parent(curr));
		curr = parent(curr);
	}
	// Think why the Heap property can still be maintained after above while loop ?
	return true;
}
template <class Elem, class Comp>
Elem MinHeap<Elem, Comp>::removemin(){
	Elem min = heap[0];
	swap(heap, 0, --n);	// Swap min with the last value
	if (n != 0) shiftdown(0);
	return min;
}

template <class Elem, class Comp>
void MinHeap<Elem, Comp>::heapprint(){
	for(int i=0; i<n; i++){
		heap[i].Print();cout<<"||";
	}
	cout<<endl;
}
#endif


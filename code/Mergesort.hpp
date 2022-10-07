#ifndef MERGESORT_HPP
#define MERGESORT_HPP
#include<vector>
#include<algorithm>
#include<iostream>
#include<string>
#include "Edge.hpp"
using namespace std;

template <class Elem>
void Printvector(vector<Elem> &vect,int n=-1){
    if(n==-1) n=vect.size();
    for(int i=0; i<n; i++){vect[i].Print();cout<<"||";}
    cout<<endl;
}

void merge(vector<Edge> &edges, int left, int right, int len){
    if(left==right) return;
    int mid=(len/2)-1;
    vector<Edge> temp;
    for(int i=0;i<=right-left;i++){temp.push_back(edges[left+i]);}
    int i1=0; int i2=mid+1;
    for(int curr=left;curr<=right;curr++){
        if (i1 == mid+1) // Left exhausted
        edges[curr] = temp[i2++];
        else if (i2 > right-left) // Right exhausted
        edges[curr] = temp[i1++];
        else if (Edge::lt(temp[i1], temp[i2]))
        edges[curr] = temp[i1++];
        else edges[curr] = temp[i2++];
    }
}
// mergesort sort the array by modifying directly the array rather than return another
void mergesort(vector<Edge> &edges){
    int n=edges.size();
    int len=1;
    while(len<n){//the size of the merging part
        Printvector<Edge> (edges,n);
        len*=2;
        for(int j=0; j<n; j+=len){
            int k=min(j+len-1,n-1);//avoid to depass the range of the array
            merge(edges,j,k,len);
        }
    }
}
#endif
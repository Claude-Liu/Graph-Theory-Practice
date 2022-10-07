#include<vector>
#include<iostream>
#include "AdjacencyMatrix.hpp"
#include "AdjacencyList.hpp"
#include "Edge.hpp"
#include "MinHeap.hpp"
#include "MST.hpp"
#include "Mergesort.hpp"
#include "shortestpath.hpp"
#define HEAPSIZE 1000
using namespace std;

void PrintAM(Graphmatrix &AM){
    cout<<"print the adjacency matrix of this graph"<<endl;
    cout<<AM<<endl;
}
void PrintAL(Graphlist &AL){
    cout<<"print the adjecency list of this graph"<<endl;
    cout<<AL<<endl;
}
//sort the first N element of the source array and restore the result in target array.
template <class Elem>
void MinHeapSort(vector<Elem> &source, int N, vector<Elem> &target){
    MinHeap<Elem,Elem> sourceheap(source,N,HEAPSIZE);
    for(int i=0; i<N; i++){
        cout<<"step "<<i<<":"<<endl;
        sourceheap.heapprint();
        target.push_back(sourceheap.removemin());
    }
    cout<<"print the array after being sorted"<<endl;
    int n = target.size();
    Printvector<Elem>(target,n);cout<<endl;
}

int main(){
    //initialize the edges and vertices
    vector<Edge> Edgesinput;
    Edge edge1("WL","LS",120);
    Edgesinput.push_back(edge1);
    Edge edge2("WL","LZ",130);
    Edgesinput.push_back(edge2);
    Edge edge3("LZ","LS",111);
    Edgesinput.push_back(edge3);
    Edge edge4("CD","LS",110);
    Edgesinput.push_back(edge4);
    Edge edge5("LZ","CD",85);
    Edgesinput.push_back(edge5);
    Edge edge6("LZ","XA",84);
    Edgesinput.push_back(edge6);
    Edge edge7("XA","CD",87);
    Edgesinput.push_back(edge7);
    Edge edge8("XA","BJ",90);
    Edgesinput.push_back(edge8);
    Edge edge9("XA","WH",94);
    Edgesinput.push_back(edge9);
    Edge edge10("BJ","WH",100);
    Edgesinput.push_back(edge10);
    Edge edge11("CD","WH",99);
    Edgesinput.push_back(edge11);
    Edge edge12("CD","KM",86);
    Edgesinput.push_back(edge12);
    Edge edge13("CD","GZ",102);
    Edgesinput.push_back(edge13);
    Edge edge14("GZ","KM",101);
    Edgesinput.push_back(edge14);
    Edge edge15("GZ","WH",98);
    Edgesinput.push_back(edge15);
    Edge edge16("GZ","FZ",91);
    Edgesinput.push_back(edge16);
    Edge edge17("FZ","WH",95);
    Edgesinput.push_back(edge17);
    Edge edge18("FZ","SH",92);
    Edgesinput.push_back(edge18);
    Edge edge19("WH","SH",96);
    Edgesinput.push_back(edge19);
    Edge edge20("SH","TJ",93);
    Edgesinput.push_back(edge20);
    Edge edge21("TJ","WH",97);
    Edgesinput.push_back(edge21);
    Edge edge22("BJ","TJ",9);
    Edgesinput.push_back(edge22);
    Edge edge23("SY","BJ",88);
    Edgesinput.push_back(edge23);
    Edge edge24("SY","TJ",89);
    Edgesinput.push_back(edge24);
    string name[13] = {"WL","LZ","LS","XA","CD","KM","BJ","WH","GZ","SY","TJ","SH","FZ"};

    //begin the demo
    cout<<"-------------"<<"Task1"<<"----------------"<<endl;
    //initialize an instance of Graphmatrix and demo
    Graphmatrix Geograph1(Edgesinput,name,13); //a graph represented by its adjecency matrix
    Geograph1.printgraph();
    PrintAM(Geograph1);
    //initialize an instance of Graphlist and demo
    Graphlist Geograph2(Edgesinput,name,13);// a graph represented by its adjecency list
    Geograph2.printgraph();
    PrintAL(Geograph2);
    cout<<"-------------"<<"Task2"<<"----------------"<<endl;
    //demo the GetEdgeAM function
    vector<Edge> edges;
    edges = GetEdgeAM(Geograph1);
    int n=edges.size();
    cout<<"print the size of the edges array we get"<<endl;
    cout<<n<<endl;
    
    //demo the minheapsort
    cout<<"-------------"<<"Minheapsort"<<"----------------"<<endl;
    cout<<"Print the edges before sorted"<<endl;
    Printvector<Edge>(edges,n);cout<<endl;
    cout<<"print the intermediate configurations of the minheap during the execution of minheapsort"<<endl;
    vector<Edge>edgesorted;
    MinHeapSort<Edge>(edges,n,edgesorted);

    //demo the mergesort
    cout<<"-------------"<<"Mergesort"<<"----------------"<<endl;
    cout<<"Print the edges before sorted"<<endl;
    Printvector<Edge>(edges,n);cout<<endl;
    cout<<"print the intermediate sequence of the edges during the execution of mergesort"<<endl;
    mergesort(edges);
    cout<<"Print the edges after sorted"<<endl;
    Printvector<Edge>(edges,n);cout<<endl;

    cout<<"-------------"<<"Task3"<<"----------------"<<endl;
    //demo prim
    cout<<"MST prim"<<" ----------------"<<endl;
    vector<Edge> MST=GenMST(edges,PRIM);
    Printvector<Edge>(MST);cout<<endl;
    cout<<"MST krustal"<<" ----------------"<<endl;
    vector<Edge> MST2=GenMST(edges,KRUSTAL);
    Printvector<Edge>(MST2);cout<<endl;

    cout<<"--------------"<<"Task4"<<"--------------------"<<endl;
    string start="SY"; string end="LS";
    vector<Edge> minpath=DijkstraAM(Geograph1,start,end);
    Printvector<Edge>(minpath);
    return 0;
}
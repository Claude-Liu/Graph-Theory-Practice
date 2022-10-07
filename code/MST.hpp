#ifndef MST_HPP
#define MST_HPP
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include "Edge.hpp"
#include "AdjacencyList.hpp"
#include "MinHeap.hpp"
using namespace std;
#define HEAPSIZE 1000
#define PRIM 1
#define KRUSTAL 2

//if there is no input"n" defaut n as 0, then convert n to the size of the array
// when input n: check if x in the premier n element of  the array
template<class Elem>
bool in(vector<Elem> array, Elem x, int n=-1){
    if(n==-1) n=array.size();
    for(int i=0; i<n; i++){
        if(x==array[i]) return true;
    }
    return false;
}

// duplicate remove
template<class Elem>
vector<Elem> dremove(vector<Elem> array){
    vector<Elem> arrayout;
    int n=array.size();
    for(int i=0; i<n;i++){
        if(!in<Elem>(arrayout, array[i])) arrayout.push_back(array[i]);
    }
    return arrayout;
}

//convert an array of edges to an array of nodes(string) correspond, in order to initialize a graph.
vector<string> Edges2Nodes(vector<Edge> &edges){
    vector<string> nodesr;//raw
    vector<string> nodes;
    int n=edges.size();
    for (int i=0; i<n; i++){
        nodesr.push_back(edges[i].depart);
        nodesr.push_back(edges[i].destin);
    }
    nodes = dremove<string> (nodesr);
    return nodes;
}

//find MST with prim
vector<Edge> prim(vector<Edge> &edges){
    //get the nodes
    vector<string> inter=Edges2Nodes(edges);
    int len = inter.size();
    string nodes[len];
    for(int i=0; i<len; i++){nodes[i]=inter[i];}
    //establish the graphlist
    Graphlist graph(edges,nodes,len);// a graph represented by its adjecency list
    //begin the MST building
    bool Nvisited[len]={false};
    vector<Edge> Evoisin;
    MinHeap<Edge,Edge> EHvoisin(Evoisin,0,HEAPSIZE);
    vector<Edge> MST;
    int Ncurr=0;Nvisited[Ncurr]=true;
    for(int i=1; i<len; i++){
        for(int j=0; j<graph.list[Ncurr].size();j++){
            if(Nvisited[graph.nodeid[graph.list[Ncurr][j].first]]==false){
            Edge Etemp(graph.nodename[Ncurr],graph.list[Ncurr][j].first,graph.list[Ncurr][j].second);
            EHvoisin.insert(Etemp);}
        }
        Edge Ecurr=EHvoisin.removemin();
        // pop the node which have not been visited
        while(Nvisited[graph.nodeid[Ecurr.getdes()]]==true) {Ecurr=EHvoisin.removemin();}
        MST.push_back(Ecurr);
        Ncurr=graph.nodeid[Ecurr.getdes()];Nvisited[Ncurr]=true;
    }
    return  MST;
}

//use disajoint set union to describle the relation between vertices(if they are in them same MST)
int UFind(int uf[], int x){
    if(uf[x]==x) return x;
    else {
        // we can use: x=UFind(uf,uf[x]), but in this way, we can improve uf[](easier for next find)!!!
        uf[x]=UFind(uf,uf[x]);
        return uf[x];
    }
}

//find MST with Krustal
//Here we assume that edges have been sorted, (if not we use minheap)
vector<Edge> krustal(vector<Edge> &edges){
    vector<string> inter=Edges2Nodes(edges);
    int n = inter.size();
    string nodes[n];
    for(int i=0; i<n; i++){nodes[i]=inter[i];}
    //establish the graphlist
    Graphlist graph(edges,nodes,n);// a graph represented by its adjecency list
    vector<Edge> MST;
    int *uf = new int[n];//new an array
    for(int i=0; i<n; i++){uf[i]=i;}
    int size=0;
    int curr=0;//track the first valid element in the array(instead of pop the first each time)
    while(size<n-1){
        Edge Ecurr = edges[curr++];
        //cout<<size<<endl;
        int dep=graph.nodeid[Ecurr.getdep()]; int des=graph.nodeid[Ecurr.getdes()];
        int ACdep=UFind(uf,dep); int ACdes=UFind(uf, des);
        if(ACdep!=ACdes){// two vertices are not connected
            MST.push_back(Ecurr);
            uf[ACdes]=ACdep; //update the ancestor in disjoint set union
            size++;
        }
    }
    delete[] uf;
    return MST;
}

vector<Edge> GenMST(vector<Edge> &edges, int type=PRIM){
    vector<Edge> MST;//used to pass the variable MST
    if(type==PRIM) MST=prim(edges);
    if(type==KRUSTAL) MST=krustal(edges);
    return MST;
}
#endif


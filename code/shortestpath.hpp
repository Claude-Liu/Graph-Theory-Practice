#ifndef SHORTESTPATH_HPP
#define SHORTESTPATH_HPP
#include <cstdio>
#include <string>
#include <iostream>
#include <vector>
#include "Edge.hpp"
#include "AdjacencyList.hpp"
#include "AdjacencyMatrix.hpp"
#include "MinHeap.hpp"
#include "MST.hpp"
using namespace std;
#define HEAPSIZE 1000
//we define node in dijkstra
class Node{
    private:
    int node;// the id of the node
    int distance;// the current min-distance from startpoint to this node
    Edge chemin;//the edge lead to the node
    public:
    Node();
    Node( int node,int distance, Edge chemin){
        this->distance = distance;
        this->node = node;
        this->chemin = chemin;
    }
    int getnode(){return node;}
    int getdistance(){return distance;}
    void Print(){cout<<" to node: "<<node<<" of distance "<<distance;}
    Edge getchemin(){return chemin;}
    static bool lt(Node&x, Node&y){return x.distance<y.distance;}
    static bool gt(Node&x, Node&y){return x.distance>y.distance;}
};

vector<Edge> GetEdgeAM(Graphmatrix &AM){
    int len=AM.getedgenum();
    vector<Edge> edges;
    for (int i=0; i<len; i++){
        Edge temp;
        edges.push_back(temp);
    }
    AM.getedges(edges);
    return edges;    
}

Graphlist Matrix2List(Graphmatrix matrix){
    vector<Edge> edges=GetEdgeAM(matrix);
    vector<string> inter=Edges2Nodes(edges);
    int len = inter.size();
    string nodes[len];
    for(int i=0; i<len; i++){nodes[i]=inter[i];}
    Graphlist graph(edges,nodes,len);
    return graph;
}

//we can print the variables in loop when debug!!!
vector<Edge> DijkstraAM(Graphmatrix &Gmatrix, string st, string end){ 
    //vector<Edge> edges=GetEdgeAM(Gmatrix);
    Graphlist Glist = Matrix2List(Gmatrix);
    Glist.printnodes();
    int stid = Glist.nodeid[st]; int endid = Glist.nodeid[end];
    int n =Glist.getnodenum();
    bool Nvisited[n] = {false};
    vector<Node> Nodes;//intialize a vector of nodes in order to initialize a Minheap later 
    MinHeap<Node,Node> Nheap(Nodes,0,HEAPSIZE);
    vector<Edge> path;
    int Ncurr = stid;Nvisited[Ncurr]=true;
    int Dcurr = 0;
    int round=0;
    int heapsize = 0;
    while(Nvisited[endid]==false){
        //cout<<"---------------"<<Glist.nodename[Ncurr]<<endl;
        for(int j=0; j<Glist.list[Ncurr].size();j++){
            if(Nvisited[Glist.nodeid[Glist.list[Ncurr][j].first]]==false){
                Edge temp(Glist.nodename[Ncurr],Glist.list[Ncurr][j].first,Glist.list[Ncurr][j].second);
                int w = temp.getweight();
                //cout<<"---------------"<<round<<endl;
                Node Ntemp(Glist.nodeid[Glist.list[Ncurr][j].first],w+Dcurr,temp);
                Nheap.insert(Ntemp);
            }
        }
        cout<<"--------step--"<<round<<"----"<<": number of nodes in heap: "<<Nheap.heapsize()<<endl;
        Nheap.heapprint();
        Node Nodecurr = Nheap.removemin();
        while(Nvisited[Nodecurr.getnode()]==true) {
            Nodecurr = Nheap.removemin();
        }
        Edge Ecurr= Nodecurr.getchemin();
        path.push_back(Ecurr);
        //Ecurr.Print(); cout<<endl;
        Ncurr=Nodecurr.getnode();Nvisited[Ncurr]=true;
        //cout<<Ncurr<<endl;
        Dcurr=Nodecurr.getdistance();
        round++;
    }
    return path;
}
#endif

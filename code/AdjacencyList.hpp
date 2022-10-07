#ifndef ADJACENCYLIST_HPP
#define ADJACENCYLIST_HPP
#include <map>
#include <cstdio>
#include <string>
#include <utility>
#include <vector>
#include <cstdlib>
#include <utility>
#include <iostream>
#include "Edge.hpp"
using namespace std;

class Graphlist{
    private:
    vector<vector<pair<string,int> > > list; //the adjacency list
    vector<string> nodename;  //in order to query the name with index
    map<string,int> nodeid;  //in order to query the index with the name 
    int nodenum; //number of vertices
    int edgenum; //number of edges

    public:
    Graphlist();
    Graphlist(vector<Edge> &edges, string verticearr[], int len);
    void Nodes(string name[], int len);// initialize nodename with a array of string
    void Edges(vector<Edge> &edges);//edit the list with edge
    void Addedge(Edge edge);
    void printnodes() ;
    void printedges() ;
    void printgraph() ;//print the nodes and edges of the graph
    int getedgenum(){return edgenum;}
    int getnodenum(){return nodenum;}
    friend class Nodes;
    friend ostream &operator<< (ostream &out, const Graphlist L);//override the cout operation to cout the AL of the graph
    friend vector<Edge> prim(vector<Edge> &edges);// in order to visit the AL
    friend vector<Edge> krustal(vector<Edge> &edges);// in order to visit the AL
    friend vector<Edge> DijkstraAM(Graphmatrix &Gmatrix, string st, string end); //in order to visit the AL
};

void Graphlist::printnodes(){
    for (int i=0; i<nodenum; i++){
        cout<<nodename[i]<<"  "<<i<<endl;
    }
}
void Graphlist::printedges(){
    for (int i=0; i<nodenum; i++){
        if(list[i].size()==0) continue;
        for(int j=0; j<list[i].size(); j++){
            cout<<nodename[i]<<"--"<<list[i][j].first<<"the weight is "<<list[i][j].second<<endl;
        }
    }
}
//print all the vertices and edges of the graph
void Graphlist::printgraph(){
    cout<<"print the graph established by adjacency list"<<endl;
    cout<<"----------"<<"the output begin"<<"---------"<<endl;
    cout<<"print all the vertices: "<<endl;
    printnodes();
    cout<<"print all the edges: "<<endl;
    printedges();
    cout<<"----------"<<"the output end"<<"---------"<<endl;
}
//initial the vector of nodes
void Graphlist::Nodes(string name[], int len){
    nodenum = len;
    cout<<"---------"<<"the number of nodes"<<nodenum<<endl;
    for(int i=0; i<nodenum; i++){
        nodename.push_back(name[i]);
        nodeid[name[i]] = i;
    }
}
//use a vector of edges to update the matrix
void Graphlist::Edges(vector<Edge> &edges){
    edgenum = edges.size();
    cout<<"---------"<<"the number of edges"<<edgenum<<endl;
    for(int i=0; i<edgenum; i++){
        int dep = nodeid[edges[i].depart];
        int des = nodeid[edges[i].destin];
        pair<string,int> p2(edges[i].depart,edges[i].weight);
        pair<string,int> p1(edges[i].destin,edges[i].weight);
        list[dep].push_back(p1);
        list[des].push_back(p2);
    }
}
//add a edge which two endpoint included in the vector node name, and update the list
void Graphlist::Addedge(Edge edge){
    int dep=nodeid[edge.depart];
    int des=nodeid[edge.destin];
    pair<string,int> p2(edge.depart,edge.weight);
    pair<string,int> p1(edge.destin,edge.weight);
    list[dep].push_back(p1);
    list[des].push_back(p2);
}
Graphlist::Graphlist(vector<Edge> &edges, string verticearr[], int len){
    Nodes(verticearr,len);
    for(int i=0; i<nodenum; i++){
        vector<pair<string,int> > temp;
        list.push_back(temp);
    }
    Edges(edges);
}

//override the output operator to print the list
ostream &operator<< (ostream &out, const Graphlist L){
    for (int i=0; i<L.nodenum;i++){
        out<<L.nodename[i]<<"\t";
        for (int j=0; j<L.list[i].size(); j++){
            out<<"--->";
            out<<L.list[i][j].first<<" ("<<L.list[i][j].second<<")  ";
        }
        out<<" N"<<endl;
    }
    return out;
}
#endif
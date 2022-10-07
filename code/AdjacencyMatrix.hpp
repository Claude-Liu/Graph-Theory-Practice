#ifndef ADJACENCYMATRIX_HPP
#define ADJACENCYMATRIX_HPP
#include <map>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <utility>
#include <iostream>
#include "Edge.hpp"
using namespace std;

class Graphmatrix{
    private:
    vector<vector<int> > mat; //the adjacency matrix
    vector<string> nodename;  //in order to query the name with index
    map<string,int> nodeid;  //in order to query the index with the name 
    int nodenum; //number of vertices
    int edgenum; //number of edges

    public:
    Graphmatrix();
    Graphmatrix(vector<Edge> &edges, string verticearr[], int len);
    void Nodes(string name[], int len);// initialize nodename with a array of string
    void Edges(vector<Edge> &edges);
    int getnodenum(){return nodenum;}
    int getedgenum(){return edgenum;}
    void getedges(vector<Edge> &edges);
    void printnodes() ;
    void printedges() ;
    void printgraph() ;
    friend ostream &operator<< (ostream &out, const Graphmatrix matrix);
};


void Graphmatrix::getedges(vector<Edge> &edges){
    int curr=0;
    for (int i=0; i<nodenum; i++){
        for (int j=0; j<i; j++){
            if(mat[i][j]>0){
                Edge temp(nodename[i],nodename[j],mat[i][j]);
                edges[curr++]=temp;
            }
        }
    }
}

void Graphmatrix::printnodes(){
    for (int i=0; i<nodenum; i++){
        cout<<nodename[i]<<endl;
    }
}

void Graphmatrix::printedges(){
    for (int i=0; i<nodenum; i++){
        for (int j=0; j<i; j++){
            if(mat[i][j]>0) 
            cout<<nodename[i]<<"--"<<nodename[j]<<" weight is "<<mat[i][j]<<endl;
        }
    }
}

//print all the vertices and edges of the graph
void Graphmatrix::printgraph(){
    cout<<"print the graph established by adjacency matrix"<<endl;
    cout<<"----------"<<"the output begin"<<"---------"<<endl;
    cout<<"print all the vertices: "<<endl;
    printnodes();
    cout<<"print all the edges: "<<endl;
    printedges();
    cout<<"----------"<<"the output end"<<"---------"<<endl;
}

//initial the vector of nodes
void Graphmatrix::Nodes(string name[], int len){
    nodenum = len;
    cout<<"---------"<<"the number of nodes"<<nodenum<<endl;
    for(int i=0; i<nodenum; i++){
        nodename.push_back(name[i]);
        nodeid[name[i]]=i;
    }
}

//use a vector of edges to update the matrix
void Graphmatrix::Edges(vector<Edge> &edges){
    edgenum = edges.size();
    cout<<"---------"<<"the number of edges"<<edgenum<<endl;
    for (int i=0; i<edgenum; i++){
        int dep = nodeid[edges[i].depart];
        int des = nodeid[edges[i].destin];
        mat[dep][des]=edges[i].weight;
        mat[des][dep]=edges[i].weight;
    }
}

Graphmatrix::Graphmatrix(vector<Edge> &edges, string verticearr[], int len){
    Nodes(verticearr,len);
    for (int i=0;i<=nodenum;i++) {
            vector<int> tmp;
            for (int j=0;j<=nodenum;j++) {
                if (j==i) tmp.push_back(0); else tmp.push_back(-1);
            }
            mat.push_back(tmp);
        }
    Edges(edges);
}

// override the output operator to print the matrix
ostream &operator<< (ostream &out, const Graphmatrix matrix){
    out<<"\t";
    for (int i=0; i<matrix.nodenum; i++){
        out<<matrix.nodename[i]<<"\t";
    }
    out<<endl;
    for (int i=0; i<matrix.nodenum;i++){
        out<<matrix.nodename[i]<<"\t";
        for (int j=0; j<matrix.nodenum; j++){
            if(matrix.mat[i][j]==-1) out<<"N\t";
            else out<<matrix.mat[i][j]<<"\t";
        }
        out<<endl;
    }
    return out;
}
#endif

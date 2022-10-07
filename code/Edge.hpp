#ifndef EDGE_HPP
#define EDGE_HPP
#include<string>
using namespace std;
class Edge{
    private:
    string depart;
    string destin;
    int weight;

    public:
    //参数均
    Edge(string dep=" ", string des=" ", int w=0){
        this->depart=dep;
        this->destin=des;
        this->weight=w;
    }
    int getweight(){return weight;}
    string getdep(){return depart;}
    string getdes(){return destin;}
    static bool lt(Edge&x, Edge&y){return x.weight<y.weight;}
    static bool gt(Edge&x, Edge&y){return x.weight>y.weight;}
    void Print(){cout<<depart<<"-->"<<destin<<" = "<<weight;}
    friend class Graphmatrix; //in order to use the private members in Graphmatrix
    friend class Graphlist;  //in order to use the private members in Graphlist
    friend vector<string> Edges2Nodes(vector<Edge> &edges);
};
#endif
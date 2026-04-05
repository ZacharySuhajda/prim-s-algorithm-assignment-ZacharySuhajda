#pragma once
#include "prim.h"

class Edge {
private:
  int weight;
  Node *aNode;
  Node *bNode;
  Edge *nEdge;

public:
//Constructor

  Edge(Node zaNode, Node zbNode, int zWeight) {
    weight = zWeight;
    aNode = &zaNode;
    bNode = &zbNode;
    nEdge = nullptr;
  }

//Getters and Setters
  
  //index
  void set_weight(int n) {weight = n;}
  int get_weight() {return weight;}
  
  //aNode
  void set_aNode(Node n) {aNode = &n;}
  Node get_aNode() {return *aNode;}

  //bNode
  void set_bNode(Node n) {bNode = &n;}
  Node get_bNode() {return *bNode;}
  
  //nEdge
  void set_nEdge(Edge n) {nEdge = &n;}
  Edge get_nEdge() {return *nEdge;}
};

class Node {
private:
  int index;
  Node *nNode;
  Edge *nEdge;

public:
//Constructor

  Node(int zIndex) {
    index = zIndex;
    nNode = nullptr;
    nEdge = nullptr;
  }

//Getters and Setters
  
  //index
  void set_index(int n) {index = n;}
  int get_index() {return index;}
  
  //nNode
  void set_nNode(Node n) {nNode = &n;}
  Node get_nNode() {return *nNode;}
  
  //nEdge
  void set_nEdge(Edge n) {nEdge = &n;}
  Edge get_nEdge() {return *nEdge;}

};

class Graph {

};

/*
Overview

The Graph will be a linked list of Nodes
Each node will be a linked list of its Edges
Edges will have 2 ints for the index of the 2 Nodes
Edges will have a third int for the weight of the edge
Nodes will be numbered 0 - n as indexes of the list
*/
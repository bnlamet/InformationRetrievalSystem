#include <stdio.h>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include "Node.h"

using namespace std;

bool isLeaf(list<Node*> G, Node* x){
    return(x->neighboors.empty());
}

Node* search(list<Node*> G, string x){
    for(auto node = G.begin(); node != G.end(); node++){
        if((*node)->data == x){
            return *node;
        }else{
            
        }
    }
}

list<Node*> cite1(list<Node*> G, Node* x, int depth, int num){  
    /*
    Cites a number of subspecies of a given node within a maximum depth
    Parameters:
        G       : the graph in reference 
        x       : the node we are citing subspecies of 
        depth   : the maximum depth of the searching from the root node
        num     : the number of subspecies you wish to have in the list at maximum
    Output:
        list<Node*> : a list of node pointers, each of which being a descendent of the root node. generally num long
    How it works:
        generates an empty list. checks if the depth of the node is positive (if we should check this far from the root), 
        the num is positive (if we have listed enough already), and if the node is a leaf (no need to check the children).
        if any of these are not met, return. otherwise, iterate through the children (depth first )and push them into the list. 
        increment the num and recursively call this algorithm with depth-1 and the children until a condition is met.
    */
    list<Node*> listylist;
    if (depth > 0 && num > 0 && !isLeaf(G,x)){
        for(auto node = x->neighboors.begin(); node != x->neighboors.end(); node++){
            if(num > 0){
                listylist.push_back(*node);
                num--;
            }
            if(num > 0){
                listylist.merge(cite1(G,*node,depth-1,num));
                num -=cite1(G,*node,depth-1,num).size();
            }
        }
    }
    return listylist;           
}       //end cite1

list<Node*> cite2(list<Node*> G, Node* x, int depth){
    /*
    Cites all subspecies of a given node within a given depth
    Parameters:
        G       : the graph in reference 
        x       : the node we are citing subspecies of 
        depth   : the maximum depth of the searching from the root node
    Output:
        list<Node*> : a list of node pointers, each of which being a descendent of the root node.
    How it works:
        generates an empty list. checks if the depth of the node is positive (if we should check this far from the root), 
        and if the node is a leaf (no need to check the children). if either of these are not met, return. 
        otherwise, iterate through the children (depth first )and push them into the list. then 
        recursively call this algorithm with depth-1 and the children until a condition is met.
    */
    list<Node*> listylist;
    if (depth > 0 && !isLeaf(G,x)){
        for(auto node = x->neighboors.begin(); node != x->neighboors.end(); node++){
            listylist.push_back(*node);
            listylist.merge(cite2(G,*node,depth-1));
        }
    }
    return listylist;
}       //end cite2

int subspecies(list<Node*> G, Node* x){
    /*
    Returns the number of total subspecies of a given node x
    Parameters:
        G       : the graph in reference 
        x       : the node we are counting subspecies of 
    Output:
        int : the number of subspecies of the node x 
    How it works:
        creates a count set at 0. for every child in the adjacency list, increment the count by one
        and recursively call the function with that child. do this until you get to a leaf which will 
        pass up a 0. returns the total count
    */
    int count = 0;
    if(isLeaf(G,x)){
        return 0;
    }
    else{
        for(auto node = x->neighboors.begin(); node != x->neighboors.end(); ++node){
            count++;
            count += subspecies(G,*node);
        }
        return count;
    }
}       //end subspecies

Node* findLCA(Node ** root, string x, string y){
    /*
    Finds the lowest common ancestor of two things in the graph represented by strings
    Parameters:
        root   : pass by reference of the root node to search from
        x      : the first string
        y      : the second string
    Output:
        Node * : pointer to the lowest common ancestor node
    How it works:
        recursivly searches in a depth first search like algorithm to find the strings x and y
        then passes up the node pointer until a node has a path to both nodes with the strings
        that node will by the LCA node that is ultimatly returned
    */
    list<Node*> nodeList;
    int count = 0;
    
    if(root == NULL){
        return NULL;
    }
    
    if((*root)->data == x || (*root)-> data == y){
        return (*root);
    }
    else{
        for(auto it = (*root)->neighboors.begin(); it != (*root)->neighboors.end(); ++it){
            Node ** currNode = &(*it);
            nodeList.push_back(findLCA(currNode,x,y));
        }
        for(auto kt = nodeList.begin(); kt != nodeList.end(); ++kt){
            if (*kt != NULL){
                count += 1;
            }
        }
        if (count == 2){
            return *root;
        }
        else if(count == 1){
            for(auto kt = nodeList.begin(); kt != nodeList.end(); ++kt){
                if (*kt != NULL){
                    return *kt;
                }
            }
        }
        else if (count == 0){
            return NULL;
        }
        else{
            cout << "Something went wrong" <<endl; //just tells you if it does something not accounted for like count > 2 or negative
        }
    }
} //end findLCA()
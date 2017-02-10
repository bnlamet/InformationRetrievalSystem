#include <stdio.h>
#include <assert.h>
#include <iostream> //allows you to print stuff
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include "Node.cpp"
#include "functions.cpp"

using namespace std;

list<string> tokenizeData(char str[]);
list<Node*> makeGraph(string fileName);
int main2();

// This needs to read in the text file and create an appropriate adjacency list.
int main2(){
    
    list<Node*> graph = makeGraph("graph_hyponymy.txt");
    
    string input = "N";
    
    cout << "Would you like to see all nodes in the graph? (y/n)" << endl <<"Note: May not list everything correctly as cout may mess up." << endl;
    cin >> input;
    
    if(input == "y" || input == "Y"){
        //some tests for the graph
        //test all nodes were loaded in no repeats
        for(auto kt = graph.begin(); kt != graph.end(); ++kt){
            cout<<(*kt)->data<<endl;
        }
    }
    
    cout << "Would you like to check if neighboors are empty in the first node of the graph? (y/n)" << endl;
    cin >> input;
     if(input == "y" || input == "Y"){
         //test that address of front and back of neighboors same, which means empty
        cout << graph.front()->neighboors.front() <<endl; 
        cout << graph.front()->neighboors.back() <<endl;
    
        for(auto kt = graph.front()->neighboors.begin(); kt!= graph.front()->neighboors.end(); ++kt){
            cout << (**kt).data << endl; //test the back or front neighboors
        }//if different addresses, that means it's not empty.
    }
    
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    
    //preparation for test cases for cite and subspecies
    Node * placentalTest;
    Node * dogTest;
    Node * entityTest;
    for(auto node = graph.begin(); node != graph.end(); node++){
        if((*node)->data == "placental"){
            placentalTest = *node;
        }
        if((*node)->data == "dog"){
            dogTest = *node;
        }
        if((*node)->data == "entity"){
            entityTest = *node;
        }
    }
    
    
    cout << "Next several checks use assert and the specfic check can be changed in the code." << endl;
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    cout << "Would you like to check the cite1() function? Get descriptions of functions in documentation in functions.cpp (y/n)" << endl;
    cin >> input;
     if(input == "y" || input == "Y"){
        // cite1 test cases
        assert(cite1(graph,entityTest,2,7).size() == 7 && cite1(graph,entityTest,2,7).front()->data == "inert entity" && cite1(graph,entityTest,2,7).back()->data == "chromista");
    
        assert(cite1(graph,dogTest,1,4).size() == 4 && cite1(graph,dogTest,1,4).front()->data == "barker" && cite1(graph,dogTest,1,4).back()->data == "fido");
    
        assert(cite1(graph,placentalTest,3,12).size() == 12 && cite1(graph,placentalTest,3,12).front()->data == "carnivore" && cite1(graph,placentalTest,3,12).back()->data == "canidae");
     }
    
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    cout << "Would you like to check the cite2() function? (y/n)" << endl;
    cin >> input;
     if(input == "y" || input == "Y"){
    //cite2 test cases
    
        assert(cite2(graph,entityTest,2).size() == 10 && cite2(graph,entityTest,2).front()->data == "inert entity" && cite2(graph,entityTest,2).back()->data == "animalia");
    
        assert(cite2(graph,dogTest,1).size() == 11 && cite2(graph,dogTest,1).front()->data == "barker" && cite2(graph,dogTest,1).back()->data == "doberman");
    
        assert(cite2(graph,placentalTest,3).size() == 26 && cite2(graph,placentalTest,3).front()->data == "carnivore" && cite2(graph,placentalTest,3).back()->data == "herbivore");
     }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    cout << "Would you like to check the subspecies() function? (y/n)" << endl;
    cin >> input;
     if(input == "y" || input == "Y"){
    //subspecies test cases
    
        assert(subspecies(graph,entityTest) == 1777);
    
        assert(subspecies(graph,dogTest) == 11);

        assert(subspecies(graph,placentalTest) == 495);
    
     }
    
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    
    cout << "Would you like to check the LCA() function? (y/n)" << endl;
    cin >> input;
    if(input == "y" || input == "Y"){
        //test cases for the LCA algorithm
        Node * LCA = findLCA(&graph.front(), "fox", "pooch");
        assert((*LCA).data == "canidae");
    
        LCA = findLCA(&graph.front(), "quagga", "pooch");
        assert((*LCA).data == "placental");
    
        LCA = findLCA(&graph.front(), "fox", "dump truck");
        assert((*LCA).data == "entity");
     }
            
return 0;
} //end main function

list<string> tokenizeData(char str[]){
    /*
    takes the string from getLine and tokenizes them by colon and comma delimiters
    Parameters:
        str          : the character array to be tokenized
    Output:
        list<string> : the list of delimited strings
    How it works:
        uses strtok to seperate out the words
        removes extra spaces left and right of the word
        remove underscores and replaces with spaces
        makes every character lowercase
        adds to the list of strings
    */
    
    list<string> data;
    char * token;
    bool contCheck;
    int i;
    token = strtok(str,":,");
    while (token != NULL){ // tokenize each string
        string strToken = string(token);
        i = 0;
                
        //erase spaces and start and end of strTokens, converted to string for erase()
        contCheck = true;
        while (contCheck){
            if (strToken[0] == ' '){
                strToken.erase(0,1);
            }
                
            else if (strToken[strToken.length()-1] == ' '){
                strToken.erase(strToken.length() - 1 ,1);
            }
            else {
                contCheck = false;
            }
        }
        
        for (int i = 0; i < strToken.length(); i++){
            if (strToken[i] == '_'){
                strToken[i] = ' ';
            }
        }
                
        while (strToken[i]){ // set strToken to lowercase
            strToken[i] = tolower(strToken[i]);
            i++;
        }
                
        data.push_back(strToken);
                
        //cout << ("%s\n",strToken) << endl; //USE THIS TO CHECK THE TOKENS
        token = strtok (NULL, ":,");
    }
                
    return data;
}//end tokenizeData()

list<Node*> makeGraph(string fileName){
    /*
    gets the file name and reads in, making it into a graph
    Parameters:
        fileName     : the name of the file to read in
    Output:
        list<Node*>  : the list of node pointers, is the graph
    How it works:
        opens and file and reads in lines till it can no longer read in
        passes the line to tokenizeData() and then for each member of the resultant list checks if the string is a copy
        if it is not a copy, makes a new node
        if it is a coy, doesn't make a new node instead finds the existant node with the string
        if the the first word of the line, sets currNode to the node
        if not the first word, adds the neighboors of the currNode
        repeats for the whole file until the graph is done
    Total operation time:
        due to traversing the file and then checking for copies
        operation time somewhere between O(n) and O(n^2)
    */
     list<Node*> graph; // could've use a hasharray for O(1) time with good hashfunc
    
    ifstream myFile(fileName); //open file
    bool isEmpty = true; // bool check when the graph is empty
    if (myFile){ // this run for getting all the nodes with no repeats
        const int bufferSize = 25000; //need large size due to the length of the lines at 15000 for fish
        char str[bufferSize];// char[] buffer for string
        while (myFile.getline( str, 25000 )){// while you can still get lines
            bool isFirst = true; //the first string is the active one to add adjacenies to
            Node* currNode; //the current Node
            list<string> tokList = tokenizeData(str); //the token list of string
            
            //code here to handle each line
            for(auto jt = tokList.begin(); jt != tokList.end(); ++jt){
                Node* copyNode;
                bool isCopy = false;
                for(auto kt = graph.begin(); kt != graph.end() && !isEmpty; ++kt){
                    if(*jt == (*kt)->data){
                        isCopy = true;
                        copyNode = *kt;
                    }
                }
                isEmpty = false;
                if (!isCopy){// if the string was not a copy of a previous one, make a new node
                        
                    Node * newNode = new Node(*jt);
                    graph.push_back(newNode);
                    
                  if (isFirst){// if isFirst, need to set as currNode
                        currNode = newNode;
                        isFirst = false;
                    }
                    else {
                        currNode->neighboors.push_back(newNode);
                    }
                }
                else if (isCopy){//if the string was a copy of the previous one, get the pointer
                    if (isFirst){
                        currNode = copyNode;
                        isFirst = false;
                    }
                    else {
                        currNode->neighboors.push_back(copyNode);
                    }
                }
                   
            }
            
            memset(str, 0, sizeof(str));
        }
    }
    myFile.close(); //close file when done, because that's good coding practice
    return graph;
} //end makeGraph()

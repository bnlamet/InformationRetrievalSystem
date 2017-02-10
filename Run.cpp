//WRITE READ ME

#include <stdio.h>
#include <math.h>
#include <iostream> //allows you to print stuff
#include <cstring>
#include <list>
#include <set>  //those who do not use multisets are lame
#include "remStops.cpp" //contains function to remove stop words
#include "graphs.cpp"
#include "proj3funcs.cpp"

using namespace std;

list<multiset<string>> masterList;
double THRESH = 0.06;

int main(){
     /*  INPUTS:
            None.
            User inputs 1 to clean files, 2 to exit.
            User are then asked if they wish to query the database.
            All input queries are processed and the 6 nearest documents are returned with their first sentence.
        OUTPUTS:
            Cleaned files are written to the "corpus" folder. 
        DESCRIPTION:
            Main file that implements the project objectives.
            Line-by-line comments serve as a description.*/
            
            
    list<Node*> graph = makeGraph("graph_hyponymy.txt");
    
    string response;
    cout << "Type 1 if you want to clean data.\nType 2 if you wish to exit." << endl; //Ask user if the want to clean
    getline(cin, response);
    if (response == "1"){ //If 1, continue:
        cout << "Please wait..." << endl;
        set<string> stopset = makesets("stop_words.txt"); //make a string set of the stop words
        
        for(int i = 1; i <= 9;i++){ //for text files 1 to 9
            string num = to_string(i);
            string name = "txt0"+num;
            multiset<string> multisets = makemultisets(name+".txt"); //make string multiset from the file
            multisets = removeStops(multisets,stopset); //remove stop words
            //Assuming we had a stemming that worked, we would call that function here.
        
            //Now create the cleaned file and save it to the corpus
            masterList.push_back(multisets);                //add this multiset to the list of all document multisets
            string newname = "corpus/" + name + "_cleaned.txt";
            //for each string in multiset
            ofstream os(newname);
            for (multiset<string>::const_iterator i = multisets.begin(); i != multisets.end(); ++i) {
                string s = *i + "\n"; //add \n to dat string
                os<<s; //write dat string to dah file
            } //end writing to file
        } //end for 1 to 9    
    
        for(int i = 10; i <= 40;i++){ //for files 10 to 40
            string num = to_string(i);
            string name = "txt"+num;
            multiset<string> multisets = makemultisets(name+".txt"); //make string multiset from file
            multisets = removeStops(multisets,stopset); //remove stop words
            //stem...
            //new file...
            masterList.push_back(multisets);        //add multiset to master list of all multisets
            string newname = "corpus/" + name + "_cleaned.txt";
            //for each string in multiset
            ofstream os(newname);
            for (multiset<string>::const_iterator i = multisets.begin(); i != multisets.end(); ++i) {
                string s = *i + "\n"; //add \n to dat string
                os<<s; //write dat string to dah file
            } //end writing
        }    //end txt files 10 to 40

        double matrix[41][Master.size()];   //matrix of term frequencies
        int COUNT = 0;
        int WORD = 0;
        for(auto i = masterList.begin(); i != masterList.end(); i++){//for every multiset in the masterList
            for(auto j = Master.begin(); j != Master.end(); j++){//for every column of the list of all words
                matrix[COUNT][WORD] = count(*i,*j);//the term frequency at that row,column is the count of the set at that index
                WORD++;
            }COUNT++;WORD=0;
        }
        
        cout << "Would you like to make a query? (y/n)" << endl;
        getline(cin,response);
        
        while(response == "y" || response == "Y"){
            
            cout << "Input your query: " << endl;
            getline(cin,response);                          
            
            multiset<string> query = clean_input(response, stopset); //break input up by spaces, make it into a multiset, remove stopwords
            
            for(auto k = Master.begin(); k != Master.end(); k++){   //make it a matrix row, row 40 to be exact    
                matrix[40][WORD] = count(query,*k);  
                WORD++;                                     
            }
            WORD=0;                  
            double dists[40];       //make an array of distances, distances are from the query to each document
            for(int L = 0;L <= 39; L++){
                dists[L] = dist(matrix[L],matrix[40],3088);   //each distance is the Euclidian distance from the query vector to the document vector
            }                                   
            double sorted_dists[40];
            copy(dists, dists+40,sorted_dists); //make a copy to preserve the original's order, sort the copy smallest to largest
            sort(&sorted_dists[0],&sorted_dists[39]);
            if(sorted_dists[0] <= THRESH){               // if distance is near 0 then it was an empty search or matched nothing...
                                                        //so add elements from the graph and try again.
                set<string> add;
                for(auto x = query.begin(); x != query.end(); x++){ //for all words in query
                    Node* node = search(graph, *x);         //finds the node in the graph with that string
                    list<Node*> extras = cite1(graph, node, 1, 3);  //gets the 3 subtypes of that node
                    for(auto putin = extras.begin(); putin != extras.end(); putin++){   //insert subtypes into query via add
                        add.insert((*putin)->data);
                    }
                }
                for(auto y = add.begin(); y != add.end(); y++){
                    query.insert(*y);
                }
                
                for(auto k = Master.begin(); k != Master.end(); k++){   //update matrix row  40   
                    matrix[40][WORD] = count(query,*k);  
                    WORD++;                                     
                }
                WORD=0;
                
                for(int L = 0;L <= 39; L++){
                    dists[L] = dist(matrix[L],matrix[40],3088);  //update distances 
                }
                copy(dists, dists+40,sorted_dists);
                sort(&sorted_dists[0],&sorted_dists[39]);   //resort distances
            }                                   
            
            
            
            string arr[6];          //mark 6 lowest distances, get their documents
            
            int nullCount = 0;  //just for the number of empty texts that are the best search results
            for(int FUN = 0;FUN <= 5; FUN++){
                arr[FUN] = getDoc(dists, sorted_dists[FUN], 0); //in most cases, just find the first document that has that given distance
                if(sorted_dists[FUN] == 0){
                    arr[FUN] = getDoc(dists, sorted_dists[FUN], nullCount); //if there are some distances of 0, skip over previously mentioned texts
                    nullCount++;
                }
            }
            
            cout << "The 6 best results are: " << endl;
            for(int F = 0;F <= 5; F++){             //prints the first sentence of each document
                cout << arr[F] << ":\n ";
                string sample;
                ifstream infile(arr[F]); //open the document that has that name
                getline(infile, sample); //get the first line
                if(sample.size() != 0){
                    char c = sample[0];
                    int i = 0; //index iterator
                    while(c!='.'){
                        c = sample[i];
                        i++; //keeps track of length of substring
                    }
                   cout << "\t" << sample.substr(0,i) <<endl <<endl;
                }else{
                    cout << "..." << endl;
                }
                infile.close(); //close the document
            }
            
            cout << "Would you like to make another query? (y/n)" << endl;
            getline(cin,response);
        }
        
        cout<<"Thank you, good bye."<<endl;
    } //if
     if (response == "2"){ //If 2, quit.
        cout<<"Thank you, good bye."<<endl;
        return 0;
     }    
return 0;
} //end main function

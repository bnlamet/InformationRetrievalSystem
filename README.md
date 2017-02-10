How to run the code:

Open up the Run.cpp. Then run the code. It will prompt if you wish to clean the data. Type 1 if you wish to proceed, 2 if you do not.
If you proceed, it will ask if you wish to query the database. If you respond y or Y, it will go on to ask for your input.
Inputs are then processed and a list of best search results is output. You will be prompted again if you wish to query the database.
If you at any time respond no, it will say goodbye.

cpp Files:

graphs.cpp: Contains tests for the functions from project one. Makes a graph if we want it to
functions.cpp: Contains functions pertaining to the graph and project 1.
Node.cpp: Contains the class description of nodes in our graph
remStops.cpp: Contains the method to remove stopwords from sets/multisets as we needed in project 2
proj3funcs.cpp: Contains the functions used to make sets, multisets and work other things as needed by project 3
Run.cpp: Contains the main() method and runs the whole program. Mini-google...

Functions:

bool isLeaf(list<Node*> G, Node* x)
    Tells us if a node is a leaf.
    Input: G is a graph and x is a node in it.
    Output: T/F
    Description: If the adjacency list of the node is empty, return true.

Node* search(list<Node*> G, string x)
    Gives the node of a given string in the graph.
    Input: G is a graph, x is the string we look for
    Output: A Node* that holds our string in G
    Description: It checks every element in G for the string and returns the first node that matches the string.

list<Node*> cite1(list<Node*> G, Node* x, int depth, int num)  
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
        
list<Node*> cite2(list<Node*> G, Node* x, int depth)
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
    
int subspecies(list<Node*> G, Node* x)
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
    
Node* findLCA(Node ** root, string x, string y)
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
    
    
multiset<string> removeStops(multiset<string> data, set<string> stop_words)
    INPUTS:
        multiset<string> data - the string multiset version of a text file of data
        set<string> stop_word - the string set version of the stop words
    OUTPUTS:
        multiset<string> result - a string multiset of the text file with all stop words removed 
    DESCRIPTION:
        This function takes in the string multisets of the data file and the stop words
        and uses the set difference operation to remove all stop words from the text.
        This will remove each stop word once, but continue to iterate over this process
        until the intersection between the multiset input and the stopset is empty.
            
set<string> makesets(string fileName)
        INPUTS:
            string fileName - the text file to be read
        OUTPUTS:
            set<string> sets - a string set of the cleaned words from the file 
        DESCRIPTION:
            This function takes in the name of a text file and transforms the
            data in the text file into a set of strings of the cleaned words 
            from that file. This function reads in the text file word-by-word
            and calls upon the 'clean' function each time until the entire file
            has been converted into a clean set of strings of words.
            
multiset<string> makemultisets(string fileName)
        INPUTS:
            string fileName - the text file to be read
        OUTPUTS:
            multiset<string> multisets - a string multiset of the cleaned words from the file 
        DESCRIPTION:
            This function takes in the name of a text file and transforms the
            data in the text file into a multiset of strings of the cleaned words 
            from that file. This function reads in the text file word-by-word
            and calls upon the 'clean' function each time until the entire file
            has been converted into a clean multiset of strings of words.
            
set<string> clean(string dirty) 
        INPUTS:
            string dirty - a raw 'word' from the read of the text file
        OUTPUTS:
            multiset<string> ss - a multiset of the resulting cleaned words 
        DESCRIPTION:
            This function takes in a 'word', which is any string that was between
            spaces in the text file and therefore read as a word. It separates
            hyphenated words, removes function references, punctuation, nonsensical
            words and characters, non-alphabet characters, numbers, and multisets the
            word to all lowercase. The function then returns a string multiset of the
            resulting clean words from the original dirty 'word'. 
            
double count(multiset<string> set, string s)
        INPUTS:
        multiset<string> set - a multiset representing cleaned strings from a document
        string s - a string that we wish to count the frequency of in a given text (multiset)
        OUTPUTS:
        double d - the ratio of the number of occurences of a string s compared to the number of elements in the
        document (multiset).
        DESCRIPTION:
        Counts the number of times a string matches to an element of a multiset of strings. Then divides the count by the total size of the set.
        
string getDoc(double arr[],double a, int nullCount)
        INPUTS:
            double arr[] - an array of distance values stored as doubles. the index represents which document hods that distance
            double a - a distance value that we will determine to be related to one of those in document list
            int nullCount - a count of how many times we have already included an empty text in our list of best results
            to avoid an output of multiple identical texts
            
        OUTPUTS:
            string - the name of the first document (unless it is one of many empty texts) 
            to have the exact same Euclidian distance as the value a.
            
        DESCRIPTION:
            This takes an array of distances that represent separate texts in our knowledge base and a distance.
            This will then go through the array until it finds an index that matches the distance desired. 
            It will then convert the index of this occurrence to the text file name of the document that had that distance.
            In the case that our top 6 results have a few of the empty texts as results, we do not want to return multiples
            of the same text, so we include a nullCount that lets us skip a number of occurences of empty texts.
            We then return a built string representing the text.
             
double dist(double row[],double row2[],int stop)
        INPUTS:
        double row[] - one row of a matrix of doubles. each element of this should be a term frequency
        double row2[] - get this, it's another row from that matrix. each element is... wait for it... a term frequency
        int stop - the number of columns so we don't go over the end of a row
        OUTPUTS:
        double sum - the Euclidian distance between the two matrix rows.     
        DESCRIPTION:
        first the matrix goes column by column finding the difference between the rows.
        it then adds the squares of each difference to the sum
        The Euclidian distance is the square root of this sum so we take its root and return that.

multiset<string> clean_input(string response, set<string> stopset)
        INPUTS:
        string response - a string representing a query to be cleaned
        set<string> stopset - a set of strings representing words we wish to remove from the reponse because they are of minimal value
        OUTPUTS:
        multiset<string> query - a multiset of strings, each being a cleaned word that is not one of the stop words    
        DESCRIPTION:
        This function takes a string, often a line from an input consisting of multiple words, and parses
        through it, separating out by each space. It then cleans each section using the clean function
        and inserts that into the multiset query. when we reach the end of the string, clean that as well
        and insert it into the multiset query. finally, return query.
             
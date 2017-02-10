#include <stdio.h>
#include <math.h>
#include <iostream> //allows you to print stuff
#include <cstring>
#include <list>
#include <set>  //those who do not use multisets are lame

set<string> makesets(string fileName);
multiset<string> makemultisets(string fileName);
set<string> clean(string dirty);
double count(multiset<string> set, string s);
string getDoc(double arr[],double a, int nullCount);
double dist(double row[],double row2[],int stop);
multiset<string> clean_input(string response, set<string> stopset);

set<string> Master;

using namespace std;

set<string> makesets(string fileName){
   /*  INPUTS:
            string fileName - the text file to be read
        OUTPUTS:
            set<string> sets - a string set of the cleaned words from the file 
        DESCRIPTION:
            This function takes in the name of a text file and transforms the
            data in the text file into a set of strings of the cleaned words 
            from that file. This function reads in the text file word-by-word
            and calls upon the 'clean' function each time until the entire file
            has been converted into a clean set of strings of words.*/
    set<string> sets; 
    //Note: Using string sets means you automatically have unique elements only!
    
    ifstream myFile(fileName); //open file
    
    string word;
    while (myFile >> word){ //reads in file by words
        set<string> the = clean(word); //clean the word of unwanted elements
        for(auto i = the.begin(); i != the.end(); i++){ //for each word of the cleaned set
            sets.insert(*i); //adds word to set of strings
        }
    }
    myFile.close(); //close file when done, because that's good coding practice
    return sets;
} //end makesets()

multiset<string> makemultisets(string fileName){
   /*  INPUTS:
            string fileName - the text file to be read
        OUTPUTS:
            multiset<string> multisets - a string multiset of the cleaned words from the file 
        DESCRIPTION:
            This function takes in the name of a text file and transforms the
            data in the text file into a multiset of strings of the cleaned words 
            from that file. This function reads in the text file word-by-word
            and calls upon the 'clean' function each time until the entire file
            has been converted into a clean multiset of strings of words.*/
    multiset<string> multisets; 
    //Note: Using string multisets means you can have repetition of elements!
    
    ifstream myFile(fileName); //open file
    
    string word;
    while (myFile >> word){ //reads in file by words
        set<string> the = clean(word); //clean the word of unwanted elements
        for(auto i = the.begin(); i != the.end(); i++){ //for each word of the cleaned multiset
            if((*i).size()>=1){
                multisets.insert(*i); //adds word to multiset of strings
                Master.insert(*i);      //add them to to the set of all words in all files as well
            }
        }
    }
    myFile.close(); //close file when done, because that's good coding practice
    return multisets;
} //end makemultisets()

set<string> clean(string dirty){ //remove unwanted elements from the word string
    /*  INPUTS:
            string dirty - a raw 'word' from the read of the text file
        OUTPUTS:
            multiset<string> ss - a multiset of the resulting cleaned words 
        DESCRIPTION:
            This function takes in a 'word', which is any string that was between
            spaces in the text file and therefore read as a word. It separates
            hyphenated words, removes function references, punctuation, nonsensical
            words and characters, non-alphabet characters, numbers, and multisets the
            word to all lowercase. The function then returns a string multiset of the
            resulting clean words from the original dirty 'word'. */
            
    string s = dirty; //copy string so we can manipulate it
    set<string> ss;
    
    for (int i = 0; i < s.length(); i++){
        if(s[i] == '-'){ //words separated by hyphen are two words
            string word1 = s.substr(0,i);
            ss.insert(word1); //insert word before hyphen
            s = s.substr(i+1,s.length());//continue with the rest of the word as a new word
            i=0;
        }
        else if (s[i] == '['){ //removing references to sources of the form []
            int stops = i+1;
            while(s[stops] != ']'){
                stops++;
            }
            stops++;
            s.erase(i,stops);
            i--;
        }
        
        //remove things that are between / and / because they are internet nonsense
         else if (s[i] == '/'){ 
            int stops = i+1;
            while(s[stops] != '/'){
                stops++;
            }
            stops++;
            s.erase(i,stops);
            i--;
        }
        
        else if (ispunct(s[i])){ //remove all punctuation
            s.erase(i,i+1);
            i--;
        }
        else if(!isalpha(s[i])){ //removing non-alphabet letters
            s.erase(i,i+1);
            i--;
        }
        else if(isdigit(s[i])){ //removing nums
            s.erase(i,i+1);
            i--;
        }
        else if(isupper(s[i])){ //multiset the word to lowercase
            s[i] = tolower(s[i]);
        }
    }
    ss.insert(s);
    return ss;
}//end clean()

double count(multiset<string> set, string s){
        /*  INPUTS:
        multiset<string> set - a multiset representing cleaned strings from a document
        string s - a string that we wish to count the frequency of in a given text (multiset)
        OUTPUTS:
        double d - the ratio of the number of occurences of a string s compared to the number of elements in the
        document (multiset).
        DESCRIPTION:
        Counts the number of times a string matches to an element of a multiset of strings. Then divides the count by the total size of the set.
             */
    double c = 0;
    for(auto i = set.begin();i != set.end(); i++){  // for every element in the set
        if((*i) == s){                              //if the element matches the string, increment c
            c++;
        }
    }
    if(set.size() != 0){        //so long as the set is nonempty, return the count c divided by the number of elements in the set
        double d = c/set.size();
        return d;
    }
    else{
        return 0;       //if the set is empty, just return 0
    }
}

string getDoc(double arr[],double a, int nullCount){
     /*  INPUTS:
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
             */
    int index = 0;
    while((arr[index] != a || nullCount !=0) && index < 40){
        if(arr[index] == a){
            nullCount--;
        }
        index++;
    }
    if(index <= 8){
        return "txt0" + to_string(index+1) + ".txt"; 
    }else{
        return "txt" + to_string(index+1) + ".txt";
    }
}

double dist(double row[],double row2[],int stop){
     /*  INPUTS:
        double row[] - one row of a matrix of doubles. each element of this should be a term frequency
        double row2[] - get this, it's another row from that matrix. each element is... wait for it... a term frequency
        int stop - the number of columns so we don't go over the end of a row
        OUTPUTS:
        double sum - the Euclidian distance between the two matrix rows.     
        DESCRIPTION:
        first the matrix goes column by column finding the difference between the rows.
        it then adds the squares of each difference to the sum
        The Euclidian distance is the square root of this sum so we take its root and return that.
             */
    double delta;
    double sum = 0;
    for(int i = 0; i < stop; i++){
        delta = row[i] - row2[i];
        sum += (delta*delta);
    }
    return(sqrt(sum));
}

multiset<string> clean_input(string response, set<string> stopset){
     /*  INPUTS:
        string response - a string representing a query to be cleaned
        set<string> stopset - a set of strings representing words we wish to remove from the reponse because they are of minimal value
        OUTPUTS:
        multiset<string> query - a multiset of strings, each being a cleaned word that is not one of the stop words    
        DESCRIPTION:
        This function takes a string, often a line from an input consisting of multiple words, and parses
        through it, separating out by each space. It then cleans each section using the clean function
        and inserts that into the multiset query. when we reach the end of the string, clean that as well
        and insert it into the multiset query. finally, return query.
             */
    int index0 = 0;
    set<string> cleaner;    //a temporary set to use when cleaning word sections
    multiset<string> query;
    for(int let = 0; let <= response.size(); let++){    //for every element in the string
        if(response[let] == ' '){                       //if it is a space, clean and insert it
            cleaner = clean(response.substr(index0,let-index0));            
            for(auto Hun = cleaner.begin();Hun != cleaner.end(); Hun++){    
                if((*Hun).size() > 0){
                    query.insert(*Hun);
                }
            }
            index0 = let+1;     //then the next string will start after the space.
        }else if(let == response.size()){   //at the end of the string insert anything left over
            cleaner = clean(response.substr(index0));
            for(auto Hun = cleaner.begin();Hun != cleaner.end(); Hun++){
                if((*Hun).size() > 0){
                    query.insert(*Hun);
                }
            }
        }
    }
    query = removeStops(query,stopset); //remove stops because that is just what we do.
    return query;                       //return because that is the thing to do in Cisc courses.
}
#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <iterator>

using namespace std;

/*  INPUTS:
        multiset<string> data - the string multiset version of a text file of data
        set<string> stop_word - the string set version of the stop words
    OUTPUTS:
        multiset<string> result - a string multiset of the text file with all stop words removed 
    DESCRIPTION:
        This function takes in the string multisets of the data file and the stop words
        and uses the set difference operation to remove all stop words from the text.
        This will remove each stop word once, but continue to iterate over this process
        until the intersection between the multiset input and the stopset is empty.
            */

                                                                             
multiset<string> removeStops(multiset<string> data, set<string> stop_words){ 
    multiset<string> temp1;    //create a temp that will hold onto each iteration of stop word removal
    multiset<string> result;    //output of the multiset difference
    set<string> intersection;   //intersection of the multiset with the stop_words
    multiset<string> a = data; //text file we're cleaning
    set<string> b = stop_words; //stop words
    
    set_difference( a.begin(), a.end(), b.begin(), b.end(), inserter(temp1, temp1.begin()));
    result = temp1;  //hold on to the set difference so that if we need to remove more, we can still use the data
    temp1 = {};
    set_intersection(result.begin(),result.end(),b.begin(),b.end(), inserter(intersection,intersection.begin()));
    
    while(!(intersection.empty())){ // while we still have stop words in our multiset, remove them and repeat the procedure
        set_difference( result.begin(), result.end(), b.begin(), b.end(), inserter(temp1, temp1.begin()));
        result = temp1;
        temp1 = {};
        intersection = {};
        set_intersection(result.begin(),result.end(),b.begin(),b.end(), inserter(intersection,intersection.begin()));

    }
    return result;    //return the finished product
}

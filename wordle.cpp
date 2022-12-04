// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper(std::string, std::string, std::set<std::string>,std::set<std::string>&);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> toReturn;
    helper(in,floating,dict,toReturn);
    return toReturn;
}

// Define any helper functions here

void helper(std::string in, std::string floating, std::set<std::string> dict, std::set<std::string>& toReturn){
    if(in == "") return;
    int firstDash = in.find("-");
    if(firstDash == std::string::npos){
        if(dict.find(in) != dict.end()){
            toReturn.insert(in);
        }
    }
    else{
        if(floating.length() == 0){
            for(int i = 'a';i <= 'z';i++){
                string temp = in;
                temp[firstDash] = (char)i;
                helper(temp,floating, dict,toReturn);
            }
        }
        else{
            int numDashes = 0;
            for(int i = 0;i<(int)in.length();i++){
                if(in[i] == '-'){
                    numDashes++;
                } 
            }
            if(numDashes == (int)floating.length()){
                for(int i = 0;i<(int)floating.length();i++){
                    string temp = in;
                    temp[firstDash] = floating[i];
                    string tempFloating = floating.substr(0,i) + floating.substr(i+1);
                    helper(temp,tempFloating, dict,toReturn);
                }
            }
            else{
                for(int i = 'a';i <= 'z';i++){
                    int floatingIndex = floating.find((char)i);
                    string tempFloating = floating;
                    if(floatingIndex != std::string::npos){
                        tempFloating = floating.substr(0,floatingIndex) + floating.substr(floatingIndex+1);
                    }
                    string temp = in;
                    temp[firstDash] = (char)i;
                    helper(temp,tempFloating, dict,toReturn);
                }
            }
        }
    }
}
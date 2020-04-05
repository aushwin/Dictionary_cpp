#include<bits/stdc++.h>
#include<conio.h>
#include "ConsoleColor.h"
using namespace std;


class Dictionary {
    public:
    string key , value;
    map<string,string> hmap;
            void splitKeyValue(string str) { 
                string word = ""; 
                for (auto x : str) { 
                    if (x == ':') { 
                        //cout << word << endl;
                        key = word; 
                        word = ""; 
                    } 
                    else { 
                       word = word + x; 
                    } 
                }  
                //cout << word << endl;
                value = word; 
            } 

            void transferToMap(){
                hmap[key]=value;
                key=""; value="";
            }
};

int main() {
    //varaibles
    Dictionary d;
    fstream read;
    int x; string s; //to search for the word
    bool loopControl; 


    //reading from the wordlist
    read.open("sample.txt",ios::in);
    read.seekg(0, ios::beg);  //moving pointer to the first location
    while(read){ //reading the string and stroing value into the hashmap in the class model
        string s;
        getline(read,s);
        d.splitKeyValue(s);
        d.transferToMap();
    }


    map<string,string> hmap = d.hmap; //collectiond data from the model for easy acces
    map<string,string>::iterator it;
    

    //visible to user selection menu
option:
    loopControl = true;
    while(loopControl){
             loopControl = false;
             string control;
             cout<<red<<"Enter Word to search\n"<<white;//red is used from the header file ColorConsole.h
             cin>>s;    
             it = hmap.find(s); //storing pointer of the variable in an iterator if found else pointer after the last element is stored
             if(it == hmap.end()){ 
                 cout<<red<<"Not Found\n"<<white;
                 cout<<"Would you like to add\n"<<green<<"Yes\t"<<red<<"No\n"<<white;
                 cin>>control;
                 if(control == "Yes" || control == "yes" || control == "y" || control == "Y") goto addWord;
                askAgain: 
                 cout<<"Would you like to search another word \n"<<green<<"Yes\t"<<red<<"No\n"<<white;
                 cin>>control;
                 if(control == "Yes" || control == "yes" || control == "y" || control == "Y") goto option;
                 exit(0);
             } else{
                 cout<<green<<it->first<<" : "<<it->second<<white<<endl;
                 goto askAgain;
             }
    }
        

addWord: 
    string word , meaning , control;
             cout<<red<<"Enter the Word to add\n"<<white;
             fflush(stdin);
             getline(cin,word);
             fflush(stdin);
             cout<<red<<"Enter the meaning\n"<<white;
             getline(cin,meaning);
             fflush(stdin);
             transform(word.begin(), word.end(), word.begin(), ::tolower);
             transform(meaning.begin(), meaning.end(), meaning.begin(), ::tolower);
             hmap[word] = meaning;
                 cout<<green<<"Word succesfully added\n";
                 it = hmap.find(word);
                 cout<<red<<"added :- "<<white<<"\n"<<it->first<<" : "<<it->second<<"\n";
                 map<string,string> temp;
                 temp[word]=meaning;
                 read.close();
                 read.open("sample.txt",ios::app);
                 read.seekg(0,ios::beg);
                 for (auto itr =temp.begin(); itr != temp.end(); ++itr) { 
                    read <<endl<< itr->first<< ":" << itr->second; 
                }
                read.close();
            cout<<red<<"Would you like to search another word \n"<<green<<"Yes\t"<<red<<"No\n"<<white;
                 cin>>control;
                 if(control == "Yes" || control == "yes" || control == "y" || control == "Y") goto option;
                 exit(0);
}

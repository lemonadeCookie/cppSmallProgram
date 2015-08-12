// File Name:    pro8.cpp
// Author:       Luyao Wang
// Student Number: 3012218125
// Assignment:   #8
// Description:  This program will get some practice using the
//               STL and it's Algorithms. It will use some functions
//               like erase ,and the functor to use in the transform
//               function. The output will send to the screen and the
//               outfile.txt

#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <set>
#include <iterator>
#include <fstream>
#include <cstdlib>
using namespace std;

//sort the string from lower to upper
class AscDictSort{
 public:
     bool operator()(const string& elem1,const string& elem2)
     {
         string str1 = elem1;
         string str2 = elem2;
         string::iterator it1;
         for(it1= str1.begin(); it1 != str1.end(); ++it1)
         {
            if(isupper(*it1))
                *it1=tolower(*it1);
         }
         string::iterator it2;
         for(it2= str2.begin(); it2 != str2.end(); ++it2)
         {
            if(isupper(*it2))
                *it2=tolower(*it2);
         }
        return (str1 < str2);
     }
};
void remove_out(set<string,AscDictSort>& modSet,
                set<string,AscDictSort>& set1);
void outputFile(char filename[],set<string,AscDictSort>& set1);
void write_size(set<string,AscDictSort> set1,
                set<string,AscDictSort> set2,
                set<string,AscDictSort>modSet1,
                set<string,AscDictSort> modSet2);
string punctRemover(const string& strIn);
void read_in(char filename[],set<string,AscDictSort>& set);
int main()
{
    set<string,AscDictSort> set1, set2, set3, modSet1, modSet2;
    char file1[] = "file1.txt";
    read_in(file1, set1);
    char file2[] = "file2.txt";
    read_in(file2, set2);
    write_size(set1, set2, modSet1, modSet2);
    modSet1 = set1;
    modSet2 = set2;
    write_size(set1, set2, modSet1, modSet2);
    remove_out(modSet1, set2);
    remove_out(modSet2, set1);
    write_size(set1, set2, modSet1, modSet2);
    char outFile1[] = "outfile1.txt";
    char outFile2[] = "outfile2.txt";
    outputFile(outFile1,modSet1);
    outputFile(outFile2,modSet2);
    return 0;
}
//remove the punct
string punctRemover(const string& strIn)
{
    string str = strIn;
    string::iterator it;
    for(it = str.begin(); it != str.end(); ++it)
    {
        if(ispunct(*it))
        {
            it--;
            str.erase(it+1);
        }
    }
    return str;
}
//read in the file to the set
void read_in(char filename[],set<string,AscDictSort>& set)
{
    ifstream fin;
    fin.open(filename);
    if(fin.fail())
    {
        cout<<"ERROR"<<endl;
        exit(1);
    }
    transform(istream_iterator<string>(fin),
     istream_iterator<string>(),inserter(set,set.end()),punctRemover);
}
//cout the sets' size
void write_size(set<string,AscDictSort> set1,
                set<string,AscDictSort> set2,
                set<string,AscDictSort> modSet1,
                set<string,AscDictSort> modSet2)
{
      cout <<  "set1" << "  " << set1.size() <<endl;
      cout <<  "set2" << "  " << set2.size() <<endl;
      cout <<  "modSet1" << "  " << modSet1.size() <<endl;
      cout <<  "modSet2" << "  " << modSet2.size() <<endl;
}
//output the string
void outputFile(char filename[],set<string,AscDictSort>& set1)
{
    ofstream fout;
    fout.open(filename);
    if(fout.fail())
    {
        cout << "ERROR\n";
        exit(1);
    }
    copy(set1.begin(),set1.end(),ostream_iterator<string>(fout," "));

}
// move things from one set
void remove_out(set<string,AscDictSort>& modSet,
                set<string,AscDictSort>& set1)
{
    set<string,AscDictSort>::iterator p;
    for(p = set1.begin(); p != set1.end(); p++)
        modSet.erase(*p);
}
/*
set1  1589
set2  1225
modSet1  0
modSet2  0
set1  1589
set2  1225
modSet1  1589
modSet2  1225
set1  1589
set2  1225
modSet1  1059
modSet2  695

Process returned 0 (0x0)   execution time : 0.702 s
Press any key to continue.
*/

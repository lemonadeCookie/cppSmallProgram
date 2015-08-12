// File Name:    pro7.cpp
// Author:       Íõè´Ñþ w¨¢ng l¨´ y¨¢o
// Student Number: 3012218125
// Assignment:   #7
// Description:  In this program, the merge function in LkList.cpp has
//               been writen. And the function is tested in the main.cpp,
//               which will includes 7 tests. The output will show on
//               the screen.


#include "LkList.h"
#include <iostream>

using namespace std;

LkList::LkList(){
    head = NULL;
    tail = NULL;
    it = NULL;
    count = 0;
}

//LkList::~LkList(){}                       //
//LkList::LkList(const LkList& other){}
//LkList& LkList::operator=(const LkList& rhs){}

int LkList::size(){
    return count;
}

bool LkList::insert(int num ){
    if ( count == 0 ){                      // empty list
        head = tail = new Node( num );
    }
    else{                                   // >1 count, then add back
        Node* temp = new Node( num );
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
    }
    count++;
    return true;
}


void LkList::merge( LkList & src ) {

    if(count == 0){
        head = src.head;
        tail = src.tail;
        count = count + src.count;
        return;
    }
    if(src.count ==0)
        return;

    Node* frontPos = head;
    Node* behindPos = head->next;
    Node* srcFront = src.head;
    Node* srcBehind = src.head;

    if(srcFront->data <= head->data){
        while(srcBehind->data <= head->data && srcBehind->next != NULL)
            srcBehind = srcBehind->next;
        if(srcBehind->next == NULL){
            head = srcFront;
            behindPos->prev->prev = srcBehind;
            srcBehind->next = behindPos->prev;
            count = count + src.count;
            return;
        }
        else
            head = srcFront;

        behindPos->prev->prev = srcBehind->prev;
        srcBehind->prev->next = behindPos->prev;
        srcFront = srcBehind;
    }

    while((behindPos != NULL)&&(srcBehind != NULL)){

        while(srcBehind->data <= behindPos->data && srcBehind->next!= NULL)
            srcBehind = srcBehind->next;

        if(srcBehind->next == NULL){

            if(srcBehind->data <= behindPos->data){
                frontPos->next = srcFront;
                srcFront->prev = frontPos;
                behindPos->prev = srcBehind;
                srcBehind->next = behindPos;
            }
            else{
                frontPos->next = srcFront;
                srcFront->prev = frontPos;
                srcBehind->prev->next = behindPos;
                behindPos->prev = srcBehind->prev;
                srcBehind->next = behindPos->next;
                behindPos->next->prev = srcBehind;
                behindPos->next = srcBehind;
                srcBehind->prev = behindPos;
            }

            count = count + src.count;
            src.head=src.tail=src.it=NULL;
            return;
        }

        frontPos->next = srcFront;
        srcFront->prev = frontPos;
        behindPos->prev = srcBehind->prev;
        srcBehind->prev->next = behindPos;

        srcFront = srcBehind;
        frontPos = behindPos;
        behindPos = behindPos->next;
    }
    if(behindPos == NULL){

        tail->next = srcFront;
        srcFront->prev = tail;
        tail = src.tail;
        count = count + src.count;
        src.head=src.tail=src.it=NULL;
        return;
    }

    count = count + src.count;
    src.head=src.tail=src.it=NULL;
    // this is what you need to write.....
}  // end of merge function


void LkList::clear(){
    if (count == 0 )
        return;

    while(tail != head){
        tail = tail->prev;
        delete tail->next;
    }
    delete head;
    head = tail = NULL;
    count = 0;
}

void LkList::resetIterator(){
    it = head;
}

bool LkList::hasMore(){
    return (it != NULL );
}

int LkList::next(){
    int num = it->data;
    it = it->next;
    return num;
}

ostream& operator << (ostream & outStr, LkList & lst ){
    lst.resetIterator();
    while( lst.hasMore() )
        outStr << lst.next() << "  ";
    return outStr;
}

/*
Merge #1 (empty merge):

List size after merge: 0


Merge #2 (into an empty list):
0  10  20  30  40
List size after merge: 5


Merge #3 (from an empty list):
0  5  10  15  20  25  30  35  40
List size after merge: 9


Merge #4(source before destination):
0  1  3  3  6  9  12  15  18  40  47  54  61  68
List size after merge: 14


Merge #5(source after destination):
10  17  24  50  53  56  59  62  65
List size after merge: 9


Merge #6(source overlaps destination):
-6  -4  -2  0  0  2  4  5  6  8  10  10  12  14  15  16  18  20  20  22  24  25
 26  28  30  32  34
List size after merge: 27


Merge #7(source within destination):
-6  -2  2  6  10  10  13  14  16  18  19  22  26  30  34
List size after merge: 15



Process returned 0 (0x0)   execution time : 0.114 s
Press any key to continue.


*/


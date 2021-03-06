#ifndef GEEKS_BOOK_H
#define GEEKS_BOOK_H

#include <iostream>
#include <string>

using namespace std;


struct Book{

    string name;
    float points;

    bool operator<(const Book& otherBook){
        return points != otherBook.points ?
               points < otherBook.points : name < otherBook.name;
    }

    friend ostream& operator<<(ostream &os, const Book &Book){

        os<<"Book: "<<Book.name<<" "<<Book.points<<endl;
        return os;
    }
};

#endif //GEEKS_BOOK_H

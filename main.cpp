//
//  main.cpp
//  dynamicBookLibrary
//
//  Created by SamarthHalyal on 06/09/16.
//  Copyright © 2016 SamarthHalyal. All rights reserved.
//

/*
 * source.cpp
 *
 *  Created on: Jun 13, 2016
 *      Author: Zuckonit (Samarth halyal)
 */

#include<iostream>
#include<cstring>
#include<cstdlib>
#include<fstream>
#include<algorithm>
#include<iterator>
#include<vector>
#include<string>

using namespace std;

vector<int> ivec;

class BookLibrary {
public:
    void student_requests_book();
    void student_returns_book();
    int is_book_shelf(char str[]);
};

void BookLibrary::student_requests_book(){
    char taken_book[30];
    int value,m;
    cout<<"Which book do you want among these...."<<endl;
    
    ifstream file("number.txt");
    if(file){
        while(file >> value){
            ivec.push_back(value);
        }
    }
    file.close();
    
    ifstream is("LibraryBookShelf.txt");
    istream_iterator<string> start(is), end;
    vector<string> vec(start, end);
    copy(vec.begin(), vec.end(), ostream_iterator<string>(cout, "\n"));
    cout << endl;
    is.close();
    
lable:
    cout<<"Book name:"<<endl;
    cin>>taken_book;
    m = is_book_shelf(taken_book);
    if(ivec[m] == 0)
    {
        cout<<"Sorry sir all Books named "<<taken_book<<" are Out!"<<endl;
    }
    if(m+1 > 0 && ivec[m]) {
        cout<<"Here, Take the book."<<endl;
        ivec[m] -= 1;
    }
    if(m == -1)
    {
        cout<<"Sorry, sir Book not found!"<<endl<<endl
        <<"Pardon the book name please!"<<endl<<endl;
        goto lable;
    }
}

void BookLibrary::student_returns_book(){
    char returned_book[30];
    int value,n;
    ifstream file("number.txt");
    if(file){
        while(file >> value){
            ivec.push_back(value);
        }
    }
    file.close();
    
    ofstream f("LibraryBookShelf.txt",ios::app);
    cout<<"Book name:"<<endl;
    cin>>returned_book;
    n=is_book_shelf(returned_book);
    if(!(n+1)){
        cout<<"A new book named "<<returned_book<<" has been added to Library."<<endl;
        f << endl << returned_book;
        ivec.push_back(1);
        f.close();
    }
    else{
        ivec[n] += 1;
        cout<<"Thank You for returning the Book!"<<endl;
    }
}

int BookLibrary::is_book_shelf(char* check_book) {
    ifstream is("LibraryBookShelf.txt");
    int k;
    istream_iterator<string> start(is), end;
    vector<string> vec(start, end);
    vector<string>::iterator i;
    for(i = vec.begin(),k=0;i != vec.end(); ++i,++k) {
        if(*i == check_book) {
            return k;
        }
    }
    is.close();
    return -1;
}

int main(){
    int choice;
    BookLibrary s1;
    
    cout<<"So student, what would you like to do.."<<endl
    <<"1. Take a book."<<endl
    <<"2. Return a book."<<endl
    <<"Enter your choice:";
    cin>>choice;
    
    switch(choice) {
        case 1:
            s1.student_requests_book();
            break;
        case 2:cout<<"Student has come to return a Book!"<<endl;
            s1.student_returns_book();
            break;
    }
    
    ofstream file1("number.txt",ios::out);
    for(vector<int>::iterator l=ivec.begin() ; l!=ivec.end() ; ++l){
        file1 <<  *l << endl;
    }
    file1.close();
    return 0;
}

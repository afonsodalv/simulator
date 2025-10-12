//
// Created by afons on 07/10/2025.
//

#include "Buffer.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

using namespace std;

Buffer::Buffer(int row, int col){
    this->col = col;
    this->row = row;
    this->cursor[0] = 0;
    this->cursor[1] = 0;
    buffer = new char*[row];

    for(int i=0;i<row;++i)
        buffer[i] = new char[col];

    for(int i=0;i<row;++i) {
        for(int j=0;j<col;++j) {
            buffer[i][j] = ' ';
        }
    }

    reset_cursor();
}

Buffer::~Buffer() {

    for(int i=0;i<row;++i)
        delete[] buffer[i];
    delete[] buffer;
}

std::string Buffer::toString () const{

    ostringstream os;

    for(int i=0;i<row;++i) {
        for(int j=0;j<col;++j) {
            os << buffer[i][j] << " ";
        }
           os << endl;
    }

    return os.str();
}

int Buffer::get_row() const{
    return row;
}

int Buffer::get_col() const{
    return col;
}

void Buffer::reset() {

    for(int i=0;i<row;++i) {
        for(int j=0;j<col;++j) {
            buffer[i][j] = ' ';
        }
    }

    reset_cursor();
}

bool Buffer::move_cursor(int i, int j) {

    if(i>= 0 && i<row && j>=0 && j<col) {
        cursor[0]=i; cursor[1]=j;
        return true;
    }

    return false;
}

void Buffer::advance_cursor() {
    cursor[1]++;

    if(cursor[1] == col) {
        cursor[1] = 0;
        cursor[0]++;

        if(cursor[0]==row) {
            reset_cursor();
        }
    }
}


Buffer& Buffer::operator<<(char ch) {
    put_char(ch);
    return *this;
}
Buffer& Buffer::operator<<(const char* text) {

    for (int i = 0; text[i] != '\0'; ++i)
        put_char(text[i]);

    return *this;
}
Buffer& Buffer::operator<<(const std::string& text) {

    for(char c : text) {
        put_char(c);
    }
    return *this;
}
Buffer& Buffer::operator<<(int n) {

    std::string s = std::to_string(n);
    for(char c : s)
        put_char(c);

    return *this;
}
Buffer& Buffer::operator<<(double d) {
    std::string s = std::to_string(d);
    for(char c : s)
        put_char(c);
    return *this;
}

void Buffer::reset_cursor() {
    cursor[0] = 0;
    cursor[1] = 0;
}

void Buffer::print_string(const std::string& str) const {
    cout<<str<<endl;
}


std::ostream& operator<<(std::ostream& os, const Buffer& b) {

    for (int i = 0; i < b.get_row(); ++i) {
        for (int j = 0; j < b.get_col(); ++j)
            os << b.buffer[i][j] << ' ';
        os << '\n';
    }
    return os;
}

void Buffer::put_char(const char &c) {
    buffer[cursor[0]][cursor[1]] = c;
    advance_cursor();
}



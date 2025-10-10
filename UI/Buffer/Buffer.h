//
// Created by afons on 07/10/2025.
//

#ifndef BUFFER_H
#define BUFFER_H

#include <string>
#include <ostream>
#include <vector>

class Buffer {

  char** buffer;
  int col;
  int row;
  int cursor[2];

  void put_char(const char &c);

  public:

    Buffer(int row, int col);
    ~Buffer();

    std::string toString() const;

    int get_row() const;
    int get_col() const;

    void reset();
    void reset_cursor();

    bool move_cursor(int i, int j);

    void print_string(const std::string& str) const;
    void advance_cursor();

    Buffer& operator<<(char ch);
    Buffer& operator<<(const char* text);
    Buffer& operator<<(const std::string& text);
    Buffer& operator<<(int n);
    Buffer& operator<<(double d);

    friend std::ostream& operator<<(std::ostream& os, const Buffer& b);
};



#endif //BUFFER_H

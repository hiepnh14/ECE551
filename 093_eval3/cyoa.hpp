#ifndef __CYOA_HPP__
#define __CYOA_HPP__
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

void error(const string error);

bool isDigit(const string str);

class Page {
  size_t page_num;
  vector<string> content;
  char type;
  vector<pair<size_t, string> > choices;

 public:
  Page(size_t num, char type_in) : page_num(num), type(type_in) {}
  // To print the page
  void printPage() const;
  // To print the choices, notification when winning or losing
  void printFooter() const;
  // Add line to the content
  void addLine(istream & stream);
  // Add choice to the choices
  void addChoice(pair<size_t, string> choice);
  // Get page_num
  size_t getNum() const { return page_num; }
  // Get page type
  char getType() const { return type; }
};
/*
class NormalPage : public Page {
  vector<pair<size_t, string> > choices;

 public:
  NormalPage(size_t num) : Page(num) {}
  virtual void printFooter();
  virtual void addChoice(pair<size_t, string> choice);
};

class WinPage : public Page {
 public:
  WinPage(size_t num) : Page(num) {}
  virtual void printFooter();
};

class LosePage : public Page {
 public:
  LosePage(size_t num) : Page(num) {}
  virtual void printFooter();
};
*/
class Story {
  vector<Page> pages;

 public:
  void readStory(istream & input, string foldername);

  void addPage(string foldername, string pagefile, const Page & addingPage);

  void addChoices(size_t num_page, string choice, size_t linkPage);
  vector<Page> getPage() const { return pages; }
};
#endif

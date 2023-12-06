#ifndef __CYOA_HPP__
#define __CYOA_HPP__
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_set>
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
  vector<pair<string, long int> > choice_conditions;
  vector<pair<string, long int> > variables;

 public:
  Page(size_t num, char type_in) : page_num(num), type(type_in) {}
  // To print the page number and ===== for step 1
  void printHeader() const;
  // To print the page
  void printPage() const;
  // To print the choices, notification when winning or losing
  void printFooter(vector<pair<string, long int> > inventory) const;
  // Add line to the content
  void addLine(istream & stream);
  // Add choice to the choices
  void addChoice(pair<size_t, string> choice, pair<string, long int> condition);
  // Get page_num
  size_t getNum() const { return page_num; }
  // Get page type
  char getType() const { return type; }
  vector<pair<string, long int> > getVariables() const { return variables; }
  void updateVariable(pair<string, long int> variable) {
    for (size_t i = 0; i < variables.size(); i++) {
      if (variables[i].first.compare(variable.first) == 0) {
        variables[i].second = variable.second;
        return;
      }
    }
    variables.push_back(variable);
  }
  /*void addChoiceAndCondition(pair<size_t, string> choice,
    pair<string, long int> variable_condition); */
  vector<pair<size_t, string> > getChoices() const { return choices; }
  vector<pair<string, long int> > getCondition() const { return choice_conditions; }
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
  vector<pair<string, long int> > inventory;

 public:
  // Read the story.txt, include the foldername to read page files
  void readStory(istream & input, string foldername);
  // Add page to the Story
  void addPage(string foldername, string pagefile, const Page & addingPage);
  // Add choice to the page
  //void addChoices(size_t num_page, string choice, size_t linkPage);
  // Add choice and condition to the page
  void addChoices(size_t num_page,
                  string choice,
                  size_t linkPage,
                  pair<string, long int> condition);

  // Public functions to get the pages data
  vector<Page> getPage() const { return pages; }
  // Check if the conditions are satisfied?
  bool conditionCheck();
  // Find the page in pages variables
  Page findPage(size_t page_num);
  // Display the page with interaction
  void display(Page current);
  // Add variable to the page
  void addVariable_to_Page(size_t page_num, pair<string, long int> variable) {
    if (page_num >= pages.size())
      error("Adding variable to page out of range\n");
    pages[page_num].updateVariable(variable);
  }
  // Add variable to the inventory
  void addInventory(pair<string, long int> variable) {
    for (size_t i = 0; i < inventory.size(); i++) {
      if (inventory[i].first.compare(variable.first) == 0) {
        inventory[i].second = variable.second;  // update the value in the inventory
      }
    }
    inventory.push_back(variable);
  }
  vector<pair<string, long int> > getInventory() const { return inventory; }
};

void printAllPaths(Story main, size_t beginPage);
void printGraph(Story main);
#endif

#include "cyoa.hpp"

#include <string>
// Raise error message and exit
void error(const string error) {
  cerr << error << endl;
  exit(EXIT_FAILURE);
}
// check if the string are digits
bool isDigitsOrMinus(const string & digits) {
  string::const_iterator it = digits.begin();
  // ignore initial space
  while (it != digits.end() && (*it == ' ')) {
    ++it;
  }
  if (it != digits.end() && (isdigit(*it) || *it == '-')) {
    ++it;
  }
  else
    return false;
  while (it != digits.end() && (isdigit(*it))) {
    ++it;
  }
  if (!digits.empty() && it == digits.end())
    return true;
  else
    return false;
}
bool isDigits(const string & digits) {
  string::const_iterator it = digits.begin();
  //cout << digits << endl;
  //bool last_digit = false;
  // Ignore initial space
  while (it != digits.end() && (*it == ' ')) {
    ++it;
  }
  //while (it != digits.end() && (isdigit(*it) || *it == ' ')) {
  while (it != digits.end() && (isdigit(*it))) {
    //cout << "\n  " << *it;
    /*
    if (isdigit(*it))
      last_digit = true;
    else if (*it == ' ') {
      //cout << "space\n";
      last_digit = false;
      }*/
    ++it;
  }
  if (!digits.empty() && it == digits.end())
    return true;
  else
    return false;
}
// Print the page Header
void Page::printHeader() const {
  cout << "Page " << page_num << endl;
  cout << "==========" << endl;
}
// Print the main page
void Page::printPage() const {
  vector<string>::const_iterator it = content.begin();
  while (it != content.end()) {
    cout << *it << endl;
    ++it;
  }
}
// Check if the variable condition satisfies with current inventory
bool conditionSatisfy(vector<pair<string, long int> > inventory,
                      pair<string, long int> condition) {
  if (condition.first == "")  // when no condtion
    return true;
  for (size_t j = 0; j < inventory.size(); j++) {
    if (inventory[j] == condition) {
      return true;
    }
  }
  if (condition.second == 0) {
    for (size_t j = 0; j < inventory.size(); j++) {
      // When the value of the variables does not match
      if (condition.first == inventory[j].first &&
          condition.second != inventory[j].second)
        return false;
    }
    return true;
  }
  return false;
}
// Print Footer of the page (choice, win or lose notifications)
void Page::printFooter(vector<pair<string, long int> > inventory) const {
  if (type == 'W') {
    cout << endl;
    cout << "Congratulations! You have won. Hooray!" << endl;
  }
  else if (type == 'L') {
    cout << endl;
    cout << "Sorry, you have lost. Better luck next time!" << endl;
  }
  else if (type == 'N') {
    cout << endl;
    cout << "What would you like to do?" << endl;
    cout << endl;
    vector<pair<size_t, string> >::const_iterator it = choices.begin();
    size_t i = 1;
    while (it != choices.end()) {
      cout << " " << i << ".";
      bool match_condition = conditionSatisfy(inventory, choice_conditions[i - 1]);
      if (!match_condition)
        cout << "<UNAVAILABLE>" << endl;
      else
        cout << it->second << endl;
      i++;
      ++it;
    }
  }
}
// Add a new line to the content of the page
void Page::addLine(istream & stream) {
  string line;
  while (getline(stream, line)) {
    content.push_back(line);
  }
}
// Add choice and condition to choices and conditions
void Page::addChoice(pair<size_t, string> choice, pair<string, long int> condition) {
  if (type != 'N')
    error("Logic error when adding choice not to type 'N'\n");
  choices.push_back(choice);
  choice_conditions.push_back(condition);
}
// Update variables with name and value, add new one if not exist
void Page::updateVariable(pair<string, long int> variable) {
  for (size_t i = 0; i < variables.size(); i++) {
    if (variables[i].first.compare(variable.first) == 0) {
      variables[i].second = variable.second;
      return;
    }
  }
  variables.push_back(variable);
}
// Add new page to pages in story
void Story::addPage(const Page & addingPage) {
  pages.push_back(addingPage);
}

// Story:: add choice to the page[page_num]
void Story::addChoices(size_t page_num,
                       string choice,
                       size_t linkPage,
                       pair<string, long int> condition) {
  // for (size_t i = 0; i < pages.size(); i++) {
  if (pages[page_num].getNum() == page_num) {
    pair<size_t, string> addedChoice(linkPage, choice);
    pages[page_num].addChoice(addedChoice, condition);
    return;
  }
  //}
  error("No Page found for adding choice\n");
}
// Convert string to long int
long int toLong(string strNum) {
  long int ans;
  try {
    ans = stol(strNum);
  }
  catch (const invalid_argument & e) {
    error("Invalid string to convert to long int\n");
  }
  catch (const out_of_range & e) {
    error("Out of range error\n");
  }
  return ans;
}
// Convert string to size_t
size_t toSize_t(string strNum) {
  /*stringstream stream;
  stream << strNum;
  size_t ans = 0;
  stream >> ans;
  if (ans < numeric_limits<size_t>::min() && ans > numeric_limits<size_t>::max())
    error("Input digits exceed data type limits\n");
  */
  size_t ans;
  try {
    unsigned long num = stoul(strNum);
    ans = static_cast<size_t>(num);
  }
  catch (const invalid_argument & e) {
    error("Invalid string to convert to long int\n");
  }
  catch (const out_of_range & e) {
    error("Out of range error\n");
  }
  return ans;
}
// get the string item with delimiter delim1
string getItem(string line, char delim1, size_t & index) {
  string ans = "";
  while (index < (line.length()) && line[index] != delim1) {
    ans.push_back(line[index]);
    (index)++;
  }
  return ans;
}
// Get Page Number in size_t
size_t getPageNum(string line, size_t & index) {
  string page = "";
  while (index < line.length() && line[index] != ':' && line[index] != '@' &&
         line[index] != '$' && line[index] != '[' && line[index] != ']') {
    page.push_back(line[index]);
    index++;
  }
  //cout << page << endl;
  if (!isDigits(page)) {
    error("Invalid digits from story.txt for page \n");
  }
  size_t page_num = toSize_t(page);
  return page_num;
}
// Get value in long int for variable
long int getValue(string line, char delim, size_t & index) {
  string value_string = "";
  while (index < line.length() && line[index] != delim) {
    value_string.push_back(line[index]);
    index++;
  }
  // must take '-' minus as valid
  if (!isDigitsOrMinus(value_string))
    error("Invalid digits from story.txt for value \n");
  long int value = toLong(value_string);
  return value;
}
// Add variable to the page
void Story::addVariable_to_Page(size_t page_num, pair<string, long int> variable) {
  if (page_num >= pages.size())
    error("Adding variable to page out of range\n");
  pages[page_num].updateVariable(variable);
}
// Add variable to the inventory
void Story::addInventory(pair<string, long int> variable) {
  for (size_t i = 0; i < inventory.size(); i++) {
    if (inventory[i].first.compare(variable.first) == 0) {
      inventory[i].second = variable.second;  // update the value in the inventory
    }
  }
  inventory.push_back(variable);
}

// Read story.txt, store pages, choices, conditions
void Story::readStory(istream & input, string foldername) {
  string line;
  size_t orderCheck = 0;  // Ensure the page number is declared in order
  while (getline(input, line)) {
    if (line == "")
      continue;
    size_t i = 0;
    size_t & index = i;
    size_t page_num = getPageNum(line, index);
    // Add new page
    if (line[i] == '@') {
      i++;
      char type = line[i];
      if (type != 'N' && type != 'W' && type != 'L')
        error("Story page input format invalid");
      // Prasing the file
      i++;
      if (line[i] != ':')
        error("Format invalid\n");
      i++;
      string pagefile = getItem(line, '\n', index);
      if (page_num != orderCheck)
        error("Declaration order incorrect\n");
      orderCheck++;
      Page currentPage(page_num, type);
      ifstream file;
      string path = foldername;
      path.push_back('/');
      path.append(pagefile);
      const char * path1 = path.c_str();
      file.open(path1);

      if (!file.is_open())
        error("Fail to open File");
      currentPage.addLine(file);
      file.close();
      if (file.fail() && !file.eof())
        error("Fail to close page file\n");
      addPage(currentPage);
    }
    // Choice case with no condition
    else if (line[i] == ':') {
      if (page_num > orderCheck)
        error("Page is not yet declared\n");
      i++;
      size_t linkPage = getPageNum(line, index);
      if (line[i] == ':') {
        i++;
        string choiceText = getItem(line, '\n', index);
        pair<string, long int> noCondition;
        addChoices(page_num, choiceText, linkPage, noCondition);
      }
      else
        error("Invalid format for choice case with no condition\n");
    }
    // Add Variable to page '$'
    else if (line[i] == '$') {
      if (page_num > orderCheck)
        error("Page is not yet declared\n");
      i++;
      string variable_name = getItem(line, '=', index);
      if (line[i] != '=')
        error("Story.txt format for variable incorrect\n");
      i++;
      long int value_int = getValue(line, '\n', index);
      pair<string, long int> variable(variable_name, value_int);
      addVariable_to_Page(page_num, variable);
    }
    // Add Choice and Condition '['
    else if (line[i] == '[') {
      if (page_num > orderCheck)
        error("Page is not yet declared\n");
      i++;
      string variable_name = getItem(line, '=', index);
      if (line[i] != '=')
        error("Story.txt format for variable condition incorrect\n");
      i++;
      long int value_int = getValue(line, ']', index);
      if (line[i] != ']' && line[i + 1] != ':')
        error("Story.txt format for variable condition incorrect 2\n");
      i += 2;  // "]:"
      size_t linkPage = getPageNum(line, index);
      if (pages[page_num].getType() != 'N')
        error("Adding choice to Non-Normal page\n");
      if (line[i] == ':') {
        // Start parsing the choice message
        i++;
        string choiceText = getItem(line, '\n', index);
        pair<string, long int> variable_condition(variable_name, value_int);
        addChoices(page_num, choiceText, linkPage, variable_condition);
      }
      else
        error("Condition Choice format invalid\n");
    }
    //error("Invalid story line\n");
  }
}
// Find index of the item in a vector
long int findPageVector(vector<size_t> vector, size_t item) {
  for (size_t i = 0; i < vector.size(); i++) {
    if (vector[i] == item) {
      return i;
    }
  }
  return -1;
}
// Find the max page
size_t findMax(vector<size_t> vector) {
  size_t temp = 0;
  for (size_t i = 0; i < vector.size(); i++) {
    if (temp < vector[i])
      temp = vector[i];
  }
  return temp;
}
// Check condition for step 2
bool Story::conditionCheck() {
  vector<size_t> pageVector;
  vector<size_t> referencedVector;
  bool haveWin = false;
  bool haveLose = false;
  for (size_t i = 0; i < pages.size(); i++) {
    // Add the page to the vector
    pageVector.push_back(pages[i].getNum());
    // Checked if there is Win page
    if (pages[i].getType() == 'W')
      haveWin = true;
    // Checked if there is Lose Page
    if (pages[i].getType() == 'L')
      haveLose = true;
    for (size_t j = 0; j < pages[i].getChoices().size(); j++) {
      // Add the referenced page to the vector
      if (pages[i].getNum() != pages[i].getChoices()[j].first)
        referencedVector.push_back(pages[i].getChoices()[j].first);
    }
  }
  if (!haveWin)
    error("The story does not have a Win page\n");
  if (!haveLose)
    error("The story does not have a Lose page\n");

  size_t lastPage = findMax(pageVector);
  for (size_t i = 1; i <= lastPage; i++) {
    if (findPageVector(pageVector, i) == -1 ||
        findPageVector(referencedVector, i) == -1) {
      error("Page is missing or is not referenced\n");
    }
  }
  return true;
}
// find the page from pages
Page Story::findPage(size_t page_num) {
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i].getNum() == page_num)
      return pages[i];
  }
  error("Cannot find the page with page number\n");
  return pages[0];
}
// Display a page with main page, and footer, prompt user to input choices
void Story::display(Page current) {
  current.printPage();
  current.printFooter(inventory);
  if (current.getType() == 'W' || current.getType() == 'L')
    return;
  for (size_t i = 0; i < current.getVariables().size(); i++)
    addInventory(current.getVariables()[i]);
  bool satisfy = false;
  string input;
  while (!satisfy) {
    cin >> input;
    if (!cin.good())
      error("Input is not good\n");
    else if (isDigits(input)) {
      size_t next = toLong(input);
      if (next > 0 && next <= current.getChoices().size()) {
        if (conditionSatisfy(inventory, current.getCondition()[next - 1])) {
          display(findPage(current.getChoices()[next - 1].first));
          satisfy = true;
        }
        else {
          cout << "That choice is not available at this time, please try again" << endl;
          cin.clear();
        }
      }
      else
        cout << "That is not a valid choice, please try again" << endl;
      cin.clear();
    }
    else
      cout << "That is not a valid choice, please try again" << endl;
    cin.clear();
  }
}
// check if the node is visited or inside the vector
bool isVisited(const vector<size_t> & visited, size_t node) {
  for (size_t i = 0; i < visited.size(); i++) {
    if (visited[i] == node)
      return true;
  }
  return false;
}
// Generate a graph of pages that link with other pages from the story
vector<vector<size_t> > generateGraph(Story main) {
  vector<vector<size_t> > graph;

  for (size_t pageNum = 0; pageNum < main.getPage().size(); pageNum++) {
    // Find page that match the order number
    Page currentPage = main.findPage(pageNum);
    // Add all linked pages to the vector
    vector<size_t> linkPages;
    for (size_t choiceNum = 0; choiceNum < currentPage.getChoices().size(); choiceNum++) {
      if (!isVisited(linkPages, currentPage.getChoices()[choiceNum].first))
        // Only add to the linkpages when it hasnot existed
        linkPages.push_back(currentPage.getChoices()[choiceNum].first);
    }
    graph.push_back(linkPages);
  }

  return graph;
}
// Find all win pages for win paths
vector<size_t> findWinPages(Story main) {
  vector<size_t> winPages;
  for (size_t i = 0; i < main.getPage().size(); i++) {
    if (main.getPage()[i].getType() == 'W') {
      winPages.push_back(main.getPage()[i].getNum());
    }
  }
  return winPages;
}

// find the path from start to end
void findPath(const vector<vector<size_t> > & graph,
              size_t start,
              size_t end,
              vector<size_t> & path,
              vector<size_t> & visited,
              vector<vector<size_t> > & validPaths) {
  visited.push_back(start);
  path.push_back(start);

  if (start == end)
    validPaths.push_back(path);
  else {
    for (size_t i = 0; i < graph[start].size(); ++i) {
      size_t neighbor = graph[start][i];
      if (!isVisited(visited, neighbor))
        findPath(graph, neighbor, end, path, visited, validPaths);
    }
  }
  // Remove current node from teh path and visited vector
  path.pop_back();
  visited.pop_back();
}
// Find all Paths to all Win Pages
void findAllPaths(vector<size_t> winPages,
                  vector<vector<size_t> > graph,
                  size_t beginPage,
                  vector<vector<size_t> > & validPaths) {
  for (size_t i = 0; i < winPages.size(); i++) {
    size_t end = winPages[i];
    vector<size_t> path;
    vector<size_t> visited;
    findPath(graph, beginPage, end, path, visited, validPaths);
  }
}

void printGraph(const Story main) {
  vector<vector<size_t> > graph = generateGraph(main);
  for (size_t i = 0; i < graph.size(); i++) {
    cout << "{";
    for (size_t j = 0; j < graph[i].size(); j++) {
      cout << graph[i][j] << ", ";
    }
    cout << "}\n";
  }
}
// print a path
void printPath(const vector<vector<size_t> > graph, vector<size_t> validPath) {
  size_t sz = validPath.size();
  for (size_t i = 0; i < sz - 1; i++) {
    cout << validPath[i] << "(";

    //Search for the choice to the next page
    for (size_t choiceOrder = 0; choiceOrder < graph[validPath[i]].size();
         choiceOrder++) {
      if (graph[validPath[i]][choiceOrder] == validPath[i + 1]) {
        size_t choice = choiceOrder + 1;
        cout << choice;
      }
    }
    cout << "),";
  }
  cout << validPath[sz - 1] << "(win)" << endl;
}
// print all paths
void printAllPaths(const Story main, size_t beginPage) {
  vector<size_t> winPages = findWinPages(main);
  vector<vector<size_t> > graph = generateGraph(main);
  vector<vector<size_t> > validPaths;

  findAllPaths(winPages, graph, beginPage, validPaths);
  if (validPaths.size() == 0)
    cout << "This story is unwinnable!\n";
  for (size_t i = 0; i < validPaths.size(); i++) {
    printPath(graph, validPaths[i]);
  }
}

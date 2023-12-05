#include "cyoa.hpp"

void error(const string error) {
  cerr << error << endl;
  exit(EXIT_FAILURE);
}

bool isDigits(const string & digits) {
  string::const_iterator it = digits.begin();
  while (it != digits.end() && isdigit(*it)) {
    ++it;
  }
  if (!digits.empty() && it == digits.end())
    return true;
  else
    return false;
}
void Page::printHeader() const {
  cout << "Page " << page_num << endl;
  cout << "==========" << endl;
}
void Page::printPage() const {
  vector<string>::const_iterator it = content.begin();
  while (it != content.end()) {
    cout << *it << endl;
    ++it;
  }
}
void Page::printFooter() const {
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
      cout << " " << i << ". " << it->second << endl;
      i++;
      ++it;
    }
  }
}

void Page::addLine(istream & stream) {
  string line;
  while (getline(stream, line)) {
    content.push_back(line);
    //cout << line << endl;
  }
}
void Page::addChoice(pair<size_t, string> choice) {
  if (type != 'N')
    error("Logic error when adding choice not to type 'N'\n");
  choices.push_back(choice);
}

/*void NormalPage::addChoice(pair<size_t, string> choice) {
  choices.push_back(choice);
}

void NormalPage::printFooter() {
  cout << endl;
  cout << "What would you like to do?" << endl;
  cout << endl;
  vector<pair<size_t, string> >::const_iterator it = choices.begin();
  size_t i = 1;
  while (it != choices.end()) {
    cout << " " << i << ". " << it->second << endl;
    i++;
    ++it;
  }
}
*/

void Story::addPage(string foldername, string pagefile, const Page & addingPage) {
  pages.push_back(addingPage);
}

void Story::addChoices(size_t num_page, string choice, size_t linkPage) {
  //vector<Page>::iterator it = pages.begin();
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i].getNum() == num_page) {
      //cout << choice << endl;
      pair<size_t, string> addedChoice(linkPage, choice);
      pages[i].addChoice(addedChoice);
      return;
    }
  }
  error("No Page found for linkages\n");
}
size_t toLong(string strNum) {
  stringstream stream;
  stream << strNum;
  size_t ans = 0;
  stream >> ans;
  return ans;
}
string getItem(string line, char delim1, char delim2, size_t & index) {
  string ans = "";
  while (index < (line.length()) && line[index] != delim1 && line[index] != delim2) {
    ans.push_back(line[index]);
    (index)++;
  }
  return ans;
}

void Story::readStory(istream & input, string foldername) {
  string line;
  size_t orderCheck = 0;  // Ensure the page number is declared in order
  while (getline(input, line)) {
    if (line == "")
      continue;
    string page_num = "";

    string linkPage = "";
    string pagefile = "";
    string choiceText = "";
    size_t i = 0;
    size_t & index = i;
    char type;
    //while (i < (line.length() ) && line[i] != '@' && line[i] != ':') {
    //page_num.push_back(line[i]);
    //i++;
    //}
    page_num = getItem(line, '@', ':', index);
    if (!isDigits(page_num)) {
      error("Invalid digits from story.txt");
    }
    size_t num = toLong(page_num);
    if (line[i] == '@') {
      i++;
      type = line[i];
      if (type != 'N' && type != 'W' && type != 'L')
        error("Story page input format invalid");
      // Prasing the file
      i++;
      if (line[i] != ':')
        error("Format invalid\n");
      i++;
      pagefile = getItem(line, '\n', '\n', index);
      if (num != orderCheck)
        error("Declaration order incorrect\n");
      orderCheck++;
      Page currentPage(num, type);
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
      addPage(foldername, pagefile, currentPage);
    }
    // Choice case
    else if (line[i] == ':') {
      i++;
      linkPage = getItem(line, ':', ':', index);
      if (pages[num].getType() != 'N')
        error("Adding choice to Non-Normal page\n");

      if (!isDigits(linkPage))
        error("Link page invalid digit\n");
      if (line[i] == ':') {
        // Start parsing the choice message
        i++;
        choiceText = getItem(line, '\n', '\n', index);
        addChoices(num, choiceText, toLong(linkPage));
      }
    }
    //else
    //error("Invalid story line\n");
  }
}
long int findPageVector(vector<size_t> vector, size_t item) {
  for (size_t i = 0; i < vector.size(); i++) {
    if (vector[i] == item) {
      return i;
    }
  }
  return -1;
}
size_t findMax(vector<size_t> vector) {
  size_t temp = 0;
  for (size_t i = 0; i < vector.size(); i++) {
    if (temp < vector[i])
      temp = vector[i];
  }
  return temp;
}
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
    if (findPageVector(pageVector, i) == -1 &&
        findPageVector(referencedVector, i) == -1) {
      error("Page is missing or is not referenced\n");
    }
  }
  return true;
}
Page Story::findPage(size_t page_num) {
  for (size_t i = 0; i < pages.size(); i++) {
    if (pages[i].getNum() == page_num)
      return pages[i];
  }
  error("Cannot find the page with page number\n");
  return pages[0];
}
void Story::display(Page current) {
  current.printPage();
  current.printFooter();
  if (current.getType() == 'W' || current.getType() == 'L')
    return;
  bool satisfy = false;
  string input;
  while (!satisfy) {
    cin >> input;

    if (!cin.good())
      error("Input is not good\n");

    else if (isDigits(input)) {
      size_t next = toLong(input);
      if (next > 0 && next <= current.getChoices().size()) {
        satisfy = true;
        display(findPage(current.getChoices()[next - 1].first));
      }
    }
    else
      cout << "That is not a valid choice, please try again" << endl;
    cin.clear();
  }
  /*size_t input;

  while (!satisfy) {
    cin >> input;
    if (!cin.good()) {
      cin.clear();
      cout << "That is not a valid choice, please try again" << endl;
      continue;
    }
    else if (input > 0 && input <= current.getChoices().size()) {
      satisfy = true;
      display(findPage(current.getChoices()[input - 1].first));
    }
    else
      cout << "That is not a valid choice, please try again" << endl;
    cin.clear();
  }*/
}
// this function to generate a graph of pages that link with other pages from the story
vector<vector<size_t> > generateGraph(Story main) {
  vector<vector<size_t> > graph;

  for (size_t pageNum = 0; pageNum < main.getPage().size(); pageNum++) {
    // Find page that match the order number
    Page currentPage = main.findPage(pageNum);
    // Add all linked pages to the vector
    vector<size_t> linkPages;
    for (size_t choiceNum = 0; choiceNum < currentPage.getChoices().size(); choiceNum++) {
      linkPages.push_back(currentPage.getChoices()[choiceNum].first);
    }
    graph.push_back(linkPages);
  }

  return graph;
}
vector<size_t> findWinPages(Story main) {
  vector<size_t> winPages;
  for (size_t i = 0; i < main.getPage().size(); i++) {
    if (main.getPage()[i].getType() == 'W') {
      winPages.push_back(main.getPage()[i].getNum());
    }
  }
  return winPages;
}

void findPath(const vector<vector<size_t> > & graph,
              size_t start,
              size_t end,
              vector<size_t> & path,
              unordered_set<size_t> & visited,
              vector<vector<size_t> > & validPaths) {
  visited.insert(start);
  path.push_back(start);

  if (start == end) {
    validPaths.push_back(path);
  }
  else {
    for (int next : graph[start]) {
      if (visited.find(next) == visited.end()) {
        findPath(graph, next, end, path, visited, validPaths);
      }
    }
  }
  // Remove current node from the path and visited set
  path.pop_back();
  visited.erase(start);
}

void findAllPaths(vector<size_t> winPages,
                  vector<vector<size_t> > graph,
                  size_t beginPage,
                  vector<vector<size_t> > & validPaths) {
  for (size_t i = 0; i < winPages.size(); i++) {
    size_t end = winPages[i];
    vector<size_t> path;
    unordered_set<size_t> visited;
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

void printAllPaths(const Story main, size_t beginPage) {
  vector<size_t> winPages = findWinPages(main);
  vector<vector<size_t> > graph = generateGraph(main);
  vector<vector<size_t> > validPaths;

  findAllPaths(winPages, graph, beginPage, validPaths);
  if (validPaths.size() == 0)
    cout << "This story is unwinnable!";
  for (size_t i = 0; i < validPaths.size(); i++) {
    printPath(graph, validPaths[i]);
  }
}

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
/*
void WinPage::printFooter() {
  cout << endl;
  cout << "Congratulations! You have won. Hooray!" << endl;
}

void LosePage::printFooter() {
  cout << endl;
  cout << "Sorry, you have lost. Better luck next time!" << endl;
}
*/
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
  //cout << endl;
  //cout << pagefile << " closed" << endl;
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
      //while (i < line.length()) {
      //pagefile.push_back(line[i]);
      //i++;
      //}
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
      //while (i < (line.length() - 1) && line[i] != ':') {
      //linkPage.push_back(line[i]);
      //i++;
      //}
      if (!isDigits(linkPage))
        error("Link page invalid digit\n");
      if (line[i] == ':') {
        // Start parsing the choice message
        i++;
        choiceText = getItem(line, '\n', '\n', index);
        //while (i < line.length()) {
        //choiceText.push_back(line[i]);
        //i++;
        //}
        addChoices(num, choiceText, toLong(linkPage));
      }
    }
    else
      error("Invalid story line\n");
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
    if (pages[i].getType() == 'W')
      haveWin = true;
    if (pages[i].getType() == 'L')
      haveLose = true;
    for (size_t j = 0; j < pages[i].getChoices().size(); j++) {
      // Add the referenced page to the vector
      if (pages[i].getNum() != pages[i].getChoices()[j].first)
        referencedVector.push_back(pages[i].getChoices()[j].first);
    }
  }
  if (!haveWin || !haveLose)
    error("The story does not have a Win page or a Lose page\n");
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
    if (!isDigits(input)) {
      cout << "That is not a valid choice, please try again" << endl;
      continue;
    }
    size_t next = toLong(input);
    if (!cin.good())
      error("Input is not good\n");
    if (next > 0 && next <= current.getChoices().size()) {
      satisfy = true;
      display(findPage(current.getChoices()[next - 1].first));
    }
    else
      cout << "That is not a valid choice, please try again" << endl;
  }
}

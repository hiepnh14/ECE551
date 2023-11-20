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

void Page::printPage() const {
  cout << "Page " << page_num << endl;
  cout << "==========" << endl;

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
    char type;
    while (i < (line.length() - 1) && line[i] != '@' && line[i] != ':') {
      page_num.push_back(line[i]);
      i++;
    }

    if (!isDigits(page_num)) {
      //cerr << page_num << endl;
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
      while (i < line.length()) {
        pagefile.push_back(line[i]);
        i++;
      }
      Page currentPage(num, type);
      ifstream file;
      string path = foldername;
      path.append("/");
      path.append(pagefile);
      file.open(path);
      if (!file.is_open()) {
        //cerr << pagefile << endl;
        error("Fail to open File");
      }
      //cout << pagefile << " opening" << endl;
      currentPage.addLine(file);
      file.close();
      addPage(foldername, pagefile, currentPage);
    }
    // Choice case
    else if (line[i] == ':') {
      i++;
      while (i < (line.length() - 1) && line[i] != ':') {
        linkPage.push_back(line[i]);
        i++;
      }
      if (!isDigits(linkPage))
        error("Link page invalid digit\n");
      if (line[i] == ':') {
        // Start parsing the choice message
        i++;
        while (i < line.length() - 1) {
          choiceText.push_back(line[i]);
          i++;
        }
        // cout << choiceText << endl;
        addChoices(num, choiceText, toLong(linkPage));
      }
    }
    else
      error("Invalid story line\n");
  }
}

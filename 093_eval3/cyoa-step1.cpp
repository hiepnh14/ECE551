#include "cyoa.hpp"

int main(int argc, char ** argv) {
  if (argc != 2)
    error("Invalid input command\n");
  ifstream story_stream;
  string path = argv[1];
  path.append("/story.txt");
  story_stream.open(path, ios::in);
  if (!story_stream.is_open()) {
    error("Fail to open story.txt file\n");
  }
  Story main;
  main.readStory(story_stream, argv[1]);
  vector<Page> pages = main.getPage();
  vector<Page>::const_iterator it = pages.begin();
  while (it != pages.end()) {
    it->printPage();
    it->printFooter();
    ++it;
  }
  story_stream.close();
  //error("Fail to close story.txt file\n");

  return EXIT_FAILURE;
}

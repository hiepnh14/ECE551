#include "cyoa.hpp"

int main(int argc, char ** argv) {
  if (argc != 2)
    error("Invalid input command\n");
  ifstream story_stream;
  string path = argv[1];
  path.append("/story.txt");
  const char * path1 = path.c_str();
  story_stream.open(path1, ios::in);
  if (!story_stream.is_open()) {
    error("Fail to open story.txt file\n");
  }
  Story main;
  main.readStory(story_stream, argv[1]);
  //printGraph(main);
  bool check = main.conditionCheck();
  if (!check)
    error("No satisfied conditions in step 2\n");
  printAllPaths(main, 0);
  story_stream.close();
  if (story_stream.fail() && !story_stream.eof())
    error("Fail to close story.txt file\n");

  return EXIT_SUCCESS;
}

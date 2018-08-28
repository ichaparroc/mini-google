#ifndef INCLUDES_H
#define INCLUDES_H

#define INF 9999999999

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

typedef unsigned int uint;
typedef std::string  String;

struct Word{
    String      text;
    uint       index;
    bool  _bad=false;

    Word(String _txt, uint _id): text(_txt), index(_id){}
};

typedef std::vector<Word> Words;

#endif // INCLUDES_H
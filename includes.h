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
    String text;
    bool    key;
    bool   _bad=false;

    Word(String _txt, bool _key): text(_txt), key(_key){}
};

typedef std::vector<Word> Words;

#endif // INCLUDES_H
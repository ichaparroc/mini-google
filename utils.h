#ifndef UTILS_H
#define UTILS_H

#include "includes.h"

int getdir (String dir, std::vector<std::string> &files);
bool isKeyOfMap(String &key, Dict &_map);
uint findWord(Words &_words, String *_word);
void removeCharsFromString( String &str, String &charsToRemove );

template <typename A, typename B>
void zip(const std::vector<A> &a, const std::vector<B> &b, 
               std::vector<std::pair<A,B>> &zipped);

template <typename A, typename B>
void unzip(const std::vector<std::pair<A, B>> &zipped, 
           std::vector<A> &a, std::vector<B> &b);

#endif // UTILS_H
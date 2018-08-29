#include "utils.h"

int getdir ( String dir, std::vector<std::string> &files ){
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        std::cout << "Error(" << errno << ") opening " << dir << std::endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(String(dirp->d_name));
    }
    closedir(dp);
    return 0;
}


bool isKeyOfMap(String &key, Dict &_map){
    if (_map.count(key)>0)
      return true;
    else 
      return false;
}

uint findWord(Words &_words, String *_word){
    String *t;
    uint i;
    for (i=0; i<_words.size(); ++i) {
        t = &_words[i].text;
        if( t->size() == _word->size() ){
            if( t->at(0) == _word->at(0) ){
            if( t[0] == _word[0] ){
                return i;
            }
            }
        }
     }
     return _words.size();
}

void removeCharsFromString( String &str, String &charsToRemove ){
    for ( unsigned int i = 0; i < charsToRemove.size(); ++i ) {
      str.erase( remove(str.begin(), str.end(), charsToRemove[i]), str.end() );
   }
}
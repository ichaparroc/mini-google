

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
#ifndef GETTINGTXT_H
#define GETTINGTXT_H

#include "includes.h"
#include "utils.h"
#include "txt.h"

class GettingTxT
{
private:
    // Parameters
    std::vector<TxT> _articles;

    // Temporal
    std::ifstream _file;
    std::string _url, _id;

    bool getArticles();
    bool isEndOfArticle( std::string &line );

    bool createArticleFiles();
    
public:
    GettingTxT(){}
    GettingTxT(String pathTo);
    
    
        
    //~GettingTxT();
};

#endif // GETTINGTXT_H
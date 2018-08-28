#include "GettingTxT.h"

/*
 * Constructors
 */
GettingTxT::GettingTxT(std::string pathTo){
    std::vector<std::string> files;
    std::string line;
    bool endOfFile = false;

    getdir(pathTo,files);

    // Loop for files
    for(int i=0; i<files.size(); ++i){
    //
    //- Get lines
    //  ---------
        _file.open(files[i]);
        while ( this->getArticles() ){ }
        _file.close();
    }
}


/*
 * Get Articles
 * ------------
 */
bool GettingTxT::getArticles(){
    std::string line,word,
                title;
    std::size_t found, _endID,_startTitle,_endTitle;

    //
    // Title
    // =====

    // Busca la cabecera de la forma:
    // <doc id="32436" title="Ampolla" nonfiltered="4884" processed="4830" dbindex="14995">
    if( getline(_file,line) ){
        found = line.find("<doc id=");
        if( found != 0){
            return this->getArticles();
        }
    }
    else return false;
    _endID      = line.find("\"",9,1); // Ultima comilla
    _startTitle = line.find("title=") + 7;
    _endTitle   = line.find("\"",_startTitle+1,1);

    // Get id
    _id = line.substr(9,_endID-9);

    // Get title
    title = line.substr(_startTitle,_endTitle-_startTitle);

    // Get URL
    _url = title;
    std::replace( _url.begin(), _url.end(), ' ', '_');
    _url = "https://en.wikipedia.org/wiki/" + _url;

    // Create article
    TxT article( std::stoi( _id ), _url );

    // Word per word (title)
    std::istringstream iss(line);
    while (std::getline(iss, word,' ')){
        article.add(word);
    }

    //
    // Content
    // =======
    bool isgood = false;

    // Line per line
    while( !isEndOfArticle( line ) ){
        isgood = true;

        // Word per word (content)
        std::istringstream iss(line);
        while (std::getline(iss, word,' ')){
            article.add(word);
        }
    }

    // Add to vector
    _articles.push_back( article );
    
    return isgood;
}

/*
 * Is the end of article?
 * ----------------------
 */
bool GettingTxT::isEndOfArticle( std::string &line ){
    getline(_file,line);

    // Find the end
    if( line.size() < 16 ){
    if( line.find("ENDOFARTICLE") == 0 ){
        getline(_file,line);
        return true;
    }
    }
    return false;
}
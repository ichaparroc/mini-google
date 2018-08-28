#include "GettingTxT.h"

/*
 * Constructors
 */
GettingTxT::GettingTxT(String pathTo){
    std::vector<std::string> files;
    std::string line;

    getdir(pathTo,files);

    // Loop for files
    for(uint i=0; i<files.size(); ++i){
    //
    //- Get lines
    //  ---------
        if( files[i].size() > 5){
            std::cout << pathTo + "/" +files[i] << std::endl; 
            _file.open(pathTo + "/" +files[i]);
            //this->createArticleFiles();
            while ( this->createArticleFiles() ){ }
            _file.close();
        }
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


/*
 * Create Article Files
 * --------------------
 */
bool GettingTxT::createArticleFiles(){
    std::string line,word,
                id,title;
    std::size_t found, _endID,_startTitle,_endTitle;

    //
    // Title
    // =====

    // Busca la cabecera de la forma:
    // <doc id="32436" title="Ampolla" nonfiltered="4884" processed="4830" dbindex="14995">
    if( getline(_file,line) ){

        //std::cout << line << std::endl;

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
    id = line.substr(9,_endID-9);

    // Get title
    title = line.substr(_startTitle,_endTitle-_startTitle);

    // Create file
    std::ofstream outfile ("database/"+id+".txt");
    outfile << title << std::endl;

    //
    // Content
    // =======
    bool isgood = false;

    // Line per line
    while( !isEndOfArticle( line ) ){
        isgood = true;
        if( line.size()>0 ) outfile << line << std::endl;
    }

    outfile.close();
    return isgood;
}
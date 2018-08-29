#include "txt.h"

/*
 * Constructors
 */
TxT::TxT(){}
TxT::TxT(uint idDocument, String WebAddress): _idDoc(idDocument), _link(WebAddress){}


/*
 * Add text
 * --------
 */
void TxT::add(String &text, bool istitle){
    _w.push_back( Word( text, istitle ));
}


/*
 * Purge Numbers
 * -------------
 *  - char(48) = '0'
 *  - char(57) = '9'
 */ 
void TxT::purgeNumbers(){
    String *txt;
    uint i,c;

    for(i=0; i<_w.size(); ++i){
        c = 0;
        txt = &_w[i].text;
        while( c < txt->size()){
            // Is number?
            if(  txt->at(c) < 58   ){
                if(  txt->at(c) > 47   ){
                    _blacklist.push_back(i);
                } 
            }
            ++c;
        }

    }
}


/*
 * Purge Special Characters
 * ------------------------
 * Replace to a (97):
 *   - char([131-134,142,143,160])
 * 
 * Replace to e (101):
 *   - char([130,136-138,144])
 * 
 * Replace to i (105):
 *   - char([139-141,161])
 * 
 * Replace to o (111):
 *   - char([147-149,153,162])
 * 
 * Replace to u (117):
 *   - char([129,150,151,154,163])
 * 
 * Replace to n (110):
 *  - char([164,165]) 
 * 
 * Delete:
 *   - char([  0- 47])
 *   - char([ 58- 64])
 *   - char([ 91- 96])
 *   - char([123-128])
 * 
 * https://www.designvegetal.com/gadrat/c/caracteres/iso-8859-1.html
 * 
 */
void TxT::purgeSpecialCharacters(){
    //std::vector<uint> bad;
    String           *txt;
    char            _char;
    uint              i,c;

    for(i=0; i<_w.size(); ++i){
        c = 0;
        txt = &_w[i].text;
        while( c < txt->size()){
            _char = txt->at(c);

            // Is Special Characters?
            if( 47<_char && _char< 58 &&
                64<_char && _char< 91 &&
                96<_char && _char<123  ){
                // Es bueno
            }else{
                // a: char([131-134,142,143,160])
                if( _char=='\340' || _char=='\341' || _char=='\342'  || _char=='\343'  || _char=='\344' || _char=='\345' || _char=='\346' ||
                    _char=='\300' || _char=='\301' || _char=='\302'  || _char=='\303'  || _char=='\304' || _char=='\305' || _char=='\306' )
                //(130<_char && _char<135) || _char==142 || _char==143 || _char==160  || _char==181 )
                    txt->at(c) = 'a';
                
                // e: char([136-138,130,144])
                else if( _char=='\350' || _char=='\351' || _char=='\352' || _char=='\353' ||
                         _char=='\310' || _char=='\311' || _char=='\312' || _char=='\313' )
                //(135<_char && _char<139) || _char==130 || _char==144 || _char==-23 )
                    txt->at(c) = 'e';

                // i: char([139-141,161])
                else if( _char=='\354' || _char=='\355' || _char=='\356' || _char=='\357' ||
                         _char=='\314' || _char=='\315' || _char=='\316' || _char=='\317')
                //(138<_char && _char<142) || _char==161 || _char==214 )
                    txt->at(c) = 'i';

                // o: char([147-149,153,162])
                else if( _char=='\362' || _char=='\363' || _char=='\364' || _char=='\365' || _char=='\366' ||
                         _char=='\322' || _char=='\323' || _char=='\324' || _char=='\325' || _char=='\326')
                // (146<_char && _char<150) || _char==153 || _char==162  || _char==224 )
                    txt->at(c) = 'o';

                // u: char([129,150,151,154,163])
                else if( _char=='\371' || _char=='\372' || _char=='\373' || _char=='\374' ||
                         _char=='\331' || _char=='\332' || _char=='\333' || _char=='\334')
                //_char==129 || _char==150 || _char==151 || _char==154 || _char==163 || _char==23)
                    txt->at(c) = 'u';

                // n: char([164,165]) 
                else if( _char=='\361' || _char=='\321' )
                //_char==164 || _char==165)
                    txt->at(c) = 'n';

                // Bad :c
                else{
                    //bad.push_back(c);
                    //_blacklist.push_back(i);
                }
            }
            ++c;
        }
        /*
        // If there are bad boys
        if( bad.size() != 0 ){
            for(uint j=0; j<bad.size(); ++j){
                _w[i].text.erase (_w[i].text.begin() + bad[j] - j);
            }

            // Clear
            bad.clear();
        }
        */
    }
}



/*
 * Purge Uppercase
 * ---------------
 *  - char( 65) = 'A'      - char( 97) = 'a'
 *  - char( 90) = 'Z'      - char(122) = 'z'
 */
void TxT::purgeUppercase(){
    String *txt;
    uint i,c;

    for(i=0; i<_w.size(); ++i){
        c = 0;
        txt = &_w[i].text;
        while( c < txt->size() ){
            // Is Uppercase?
            if(  txt->at(c) < 91   ){
                if(  txt->at(c) > 64   ) txt->at(c) += 32;
            }
            ++c;
        }
    }
}


/*
 * Purge Bad Words
 * ---------------
 */
void TxT::purgeBadWords(){

}


/*
 * Purge Little Words
 * ------------------
 */
void TxT::purgeLittleWords(){
    String *txt;
    uint i;

    for(i=0; i<_w.size(); ++i){
        txt = &_w[i].text;
        if( txt->size()<3 ){
            _blacklist.push_back(i);
        } 
    }
}


/*
 * Run purge
 * ---------
 */
void TxT::runPurge(){
    // Purge!! D:
    this->purgeSpecialCharacters();
    this->purgeLittleWords      ();
    this->purgeBadWords         ();
    this->purgeUppercase        ();

    // Sorting blacklist
    std::sort (_blacklist.begin(), _blacklist.end());

    // Execute purge D:!
    for( unsigned i=0; i<_blacklist.size(); ++i){
        auto idx = _w.begin() + _blacklist[i] - i;
        _w.erase( idx );
    }

    _blacklist.clear();
}


/*
 * Analyze words
 * -------------
 */
void TxT::analyzeWords(){
    Words    __w;
    String *word;
    uint      id;

    _size = this->getSize();
    double coeff = 1/( (double)_size );

    for( unsigned i=0; i<_w.size(); ++i ){
        word = &_w[i].text;
        id = findWord(__w,word);

        // No esta en la nueva lista
        if( id == __w.size() ){
            _w[i].value += coeff;
            __w.push_back(_w[i]);

        // Se encuenta en la nueva lista
        }else{
            __w[id].value += coeff;
        }
    }

    // Update
    _w = __w;
}

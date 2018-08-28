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
void TxT::add(String &text){
    _w.push_back( Word( text,(uint)_w.size() ) );
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
        while( c < txt->size() && !_w[i]._bad ){
            // Is number?
            if(  txt->at(c) < 58   ){
                if(  txt->at(c) > 47   ) _w[i]._bad = true;
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
 */
void TxT::purgeSpecialCharacters(){
    String *txt;
    char _char;
    uint i,c;

    for(i=0; i<_w.size(); ++i){
        c = 0;
        txt = &_w[i].text;
        while( c < txt->size() && !_w[i]._bad ){
            _char = txt->at(c);

            // Is Special Characters?
            if( 47<_char && _char< 58 &&
                64<_char && _char< 91 &&
                96<_char && _char<123  ){
                // Es bueno
            }else{
                // a: char([131-134,142,143,160])
                if( (130<_char && _char<135) || _char==142 || _char==143 || _char==160 )
                    txt->at(c) = 'a';
                
                // e: char([136-138,130,144])
                else if( (135<_char && _char<139) || _char==130 || _char==144 )
                    txt->at(c) = 'e';

                // i: char([139-141,161])
                else if( (138<_char && _char<142) || _char==161 )
                    txt->at(c) = 'i';

                // o: char([147-149,153,162])
                else if( (146<_char && _char<150) || _char==153 || _char==162 )
                    txt->at(c) = 'o';

                // u: char([129,150,151,154,163])
                else if(_char==129 || _char==150 || _char==151 || _char==154 || _char==163)
                    txt->at(c) = 'u';

                // n: char([164,165]) 
                else if(_char==164 || _char==165)
                    txt->at(c) = 'n';

                // Bad :c
                else
                    _w[i]._bad = true;
            }
            ++c;
        }
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
        if( txt->size()<3 ) _w[i]._bad = true;
    }
}


/*
 * Run purge
 * ---------
 */
void TxT::runPurge(){
    
}

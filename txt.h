
#ifndef TXT_H
#define TXT_H

#include "includes.h"

class TxT
{
private:
    // Parameters
    Words  _w;
    uint   _idDoc;
    String _link;

    // Purge
    std::vector<int> _blacklist;
    
public:
    // Constructors
    TxT();
    TxT(uint idDocument, String WebAddress);

    // Basic operations
    void add(String &text);
    void setDocumentID(uint &idDocument){ _idDoc = idDocument; }
    void setWebAddress(uint &WebAddress){ _link  = WebAddress; }

    // Purge
    void purgeNumbers          ();
    void purgeSpecialCharacters();
    void purgeUppercase        ();
    void purgeBadWords         ();
    void purgeLittleWords      ();
    void runPurge();
    
    // Getting
    Words  getWords     (){ return _w;     }
    uint   getDocumentID(){ return _idDoc; }
    String getWebAddress(){ return _link;  }
};

#endif // TXT_H



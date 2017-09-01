#ifndef CSIGNATURECOLLECTION_H
#define CSIGNATURECOLLECTION_H

#include <QList>
#include <iterator>
#include "generaldefinitions.h"
#include "StringSurrogate.h"
#include "Signature.h"

//class CSignature;
class CLexicon;
class CParse;

class CSignatureCollection
{
protected:
    //QList<CSignature*> m_SignatureList;
    QMap<QString, CSignature*> m_SignatureMap;
    int m_CorpusCount;
    QString m_MemberName;
    CSignature** m_SortArray;
    bool m_SortValidFlag;
    enum eSortStyle m_SortStyle;

public:
    CSignatureCollection();
//    CSignatureCollection(CLexicon* Lex, QString MemberName = QString());
    ~CSignatureCollection();

// disable copy
private:
    CSignatureCollection(const CSignatureCollection& x);
    CSignatureCollection& operator=(const CSignatureCollection& x);

public:
    friend class CLexicon;
    CSignature* operator<< ( CParse* );
    CSignature* operator<< ( CStringSurrogate );
    CSignature* operator<< ( QString );
    CSignature* operator^= ( CParse* );
    CSignature* operator^= ( CStringSurrogate );
    CSignature* operator^= ( QString );
    CSignature* find ( QString); // same as operatorˆ=

    CSignature* GetAt( uint );
    int GetLength() const { return m_SignatureMap.size(); }
    QMap<QString, CSignature*> GetSignatures() const { return m_SignatureMap; }

//    QList<CSignature>::iterator GetBegin()   { return m_SignatureList.begin();  }
//    QList<CSignature>::iterator GetEnd()     { return m_SignatureList.end();  }

};
#endif // CSIGNATURECOLLECTION_H
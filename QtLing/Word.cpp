#include "Word.h"

CWord::CWord(CStringSurrogate ssWord) : CParse(ssWord), m_WordCount(0), m_Word(ssWord.GetKey())
{
//    m_Parses = QList<WordParse>();
}

CWord::CWord(CWord& word)
{
    m_WordCount = word.GetWordCount();
    m_Word      = word.GetWord();
//    m_Parses    = word.GetParses();
}

// Increment the word count
//
// Parameters:
//    n - amount to increment, default = 1

void CWord::IncrementWordCount (int n )
{
  m_WordCount += n;
  Q_ASSERT (m_WordCount > 0);
  Q_ASSERT (m_WordCount < 1000000);
}

void CWord::AddParse(CStem* stem, CSuffix* suffix, CSignature* signature)
{
    Parse parse;
    parse.p_stem = stem;
    parse.p_suffix = suffix;
    parse.p_signature = signature;
    m_Parses << parse;
}
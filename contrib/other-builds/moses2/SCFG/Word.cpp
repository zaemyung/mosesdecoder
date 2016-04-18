/*
 * Word.cpp
 *
 *  Created on: 23 Oct 2015
 *      Author: hieu
 */
#include <boost/functional/hash.hpp>
#include "Word.h"
#include "../legacy/Util2.h"

using namespace std;

namespace Moses2
{
namespace SCFG
{
void Word::CreateFromString(FactorCollection &vocab, const System &system,
    const std::string &str, bool doubleNT)
{
  vector<string> toks;

  if (str[0] == '[' && str[str.size() - 1] == ']') {
    isNonTerminal = true;

    if (doubleNT) {
      size_t startPos = str.find("[", 1);
      assert(startPos != string::npos);
      string str2 = str.substr(startPos + 1, str.size() - startPos - 2);
      toks = Tokenize(str2, "|");
    }
    else {
      string str2 = str.substr(1, str.size() - 2);
      toks = Tokenize(str2, "|");
    }
  }
  else {
    isNonTerminal = false;
    toks = Tokenize(str, "|");
  }

  // parse string
  for (size_t i = 0; i < toks.size(); ++i) {
    const string &tok = toks[i];
    //cerr << "tok=" << tok << endl;

    const Factor *factor = vocab.AddFactor(tok, system, false);
    m_factors[i] = factor;
  }
}

size_t Word::hash() const
{
  size_t ret = Moses2::Word::hash();
  boost::hash_combine(ret, isNonTerminal);
  return ret;
}

std::ostream& operator<<(std::ostream &out, const SCFG::Word &obj)
{
  if (obj.isNonTerminal) {
    out << "[";
  }
  out << (const Moses2::Word&) obj;
  if (obj.isNonTerminal) {
      out << "]";
  }

  return out;
}

}
}


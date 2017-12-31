#ifndef TT1_INFORMATION_RETRIEVAL_DOCUMENT_H
#define TT1_INFORMATION_RETRIEVAL_DOCUMENT_H

#include <string>
#include <map>
#include <vector>

using DocumentId = std::wstring;
using TermId = std::wstring;
using TermFrequencies = std::map<TermId, std::size_t>;
using TermWeights = std::map<TermId, double>;

struct Document
{
    DocumentId id;
    TermFrequencies termFrequencies;
    TermWeights termWeights;
    double euclideanNorm;
};

using DocumentList = std::map<DocumentId, Document>;

#endif //TT1_INFORMATION_RETRIEVAL_DOCUMENT_H
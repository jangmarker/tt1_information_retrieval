#ifndef TT1_INFORMATION_RETRIEVAL_DATABASE_H
#define TT1_INFORMATION_RETRIEVAL_DATABASE_H

#include <map>

using DocumentId = std::string;
using TermId = std::string;
using TermFrequencies = std::map<TermId, std::size_t>;
using TermWeights = std::map<TermId, double>;

struct Document
{
    DocumentId id;
    TermFrequencies termFrequencies;
    TermWeights termWeights;
};

using DocumentList = std::map<DocumentId, Document>;

class Database
{

public:
    void addDocument(Document&& document);
    void addDocument(const Document& document);
    void recalculateWeights();

    const DocumentList& documents() const;
    const TermFrequencies& termFrequencies() const;

private:
    DocumentList mDocuments;
    TermFrequencies mTermFrequency;
};

#endif //TT1_INFORMATION_RETRIEVAL_DATABASE_H

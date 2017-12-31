#ifndef TT1_INFORMATION_RETRIEVAL_DATABASE_H
#define TT1_INFORMATION_RETRIEVAL_DATABASE_H

#include "document.h"
#include "search.h"

#include <map>
#include <vector>

class Database
{

public:
    void addDocument(Document&& document);
    void addDocument(const Document& document);
    void addDocuments(std::vector<Document>&& documents);
    void recalculateWeights();

    SearchResults search(const Document& query);

    const DocumentList& documents() const;
    const TermFrequencies& termFrequencies() const;

private:
    DocumentList mDocuments;
    TermFrequencies mTermFrequency;
};

#endif //TT1_INFORMATION_RETRIEVAL_DATABASE_H

#include "database.h"

#include <cmath>

namespace
{
    double calculateWeight(std::size_t termFreqInDocument, std::size_t termDocumentCount, std::size_t documentCount)
    {
        return termFreqInDocument *
               std::log2(static_cast<double>(documentCount) / static_cast<double>(termDocumentCount));
    }
}

void Database::addDocument(Document&& document)
{
    for (const auto& termFrequency : document.termFrequencies) {
        mTermFrequency[termFrequency.first]++;
    }
    mDocuments.emplace(document.id, std::move(document));
}

void Database::addDocument(const Document& document)
{
    auto copy = document;
    addDocument(std::move(copy));
}

void Database::recalculateWeights()
{
    // C++17 structured bindings - Clion doesn't like them, yet :-(
    for (auto & [documentId, document] : mDocuments) {
        TermWeights& termWeights = document.termWeights;
        for (auto & [termId, frequency] : document.termFrequencies) {
            termWeights[termId] = calculateWeight(frequency, mTermFrequency[termId], mDocuments.size());
        }
    }
}

const DocumentList& Database::documents() const
{
    return mDocuments;
}

const TermFrequencies& Database::termFrequencies() const
{
    return mTermFrequency;
}

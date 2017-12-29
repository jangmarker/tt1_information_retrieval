#include "database.h"

#include "3rdparty/catch.h"

TEST_CASE("simple calculation of weight", "[database]") {
    Document doc1{L"doc1", {
            {L"abc", 2},
            {L"def", 1},
            {L"ghi", 1}
    }, {}};
    Document doc2{L"doc2", {
            {L"abc", 2},
            {L"def", 1}
    }, {}};

    Database db;
    db.addDocument(doc1);
    db.addDocument(doc2);

    db.recalculateWeights();

    auto documents = db.documents();
    auto frequencies = db.termFrequencies();

    REQUIRE(frequencies[L"abc"] == 2);
    REQUIRE(frequencies[L"ghi"] == 1);
    REQUIRE(documents[L"doc1"].termWeights[L"def"] == 0);
    REQUIRE(documents[L"doc1"].termWeights[L"ghi"] == 1);
};
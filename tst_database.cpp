#include "database.h"

#include "3rdparty/catch.h"

TEST_CASE("simple calculation of weight", "[database]") {
    Document doc1{"doc1", {
            {"abc", 2},
            {"def", 1},
            {"ghi", 1}
    }, {}};
    Document doc2{"doc2", {
            {"abc", 2},
            {"def", 1}
    }, {}};

    Database db;
    db.addDocument(doc1);
    db.addDocument(doc2);

    db.recalculateWeights();

    auto documents = db.documents();
    auto frequencies = db.termFrequencies();

    REQUIRE(frequencies["abc"] == 2);
    REQUIRE(frequencies["ghi"] == 1);
    REQUIRE(documents["doc1"].termWeights["def"] == 0);
    REQUIRE(documents["doc1"].termWeights["ghi"] == 1);
};
#include "database.h"

#include "3rdparty/catch.h"

#include <cmath>

TEST_CASE("two simple documents", "[database]") {
    Document doc1{L"doc1", {
            {L"abc", 2},
            {L"def", 1},
            {L"ghi", 1}
    }, {}};
    Document doc2{L"doc2", {
            {L"abc", 2},
            {L"def", 1}
    }, {}};
    Document query{L"query", {
            {L"ghi", 1}
    }};

    Database db;
    db.addDocument(doc1);
    db.addDocument(doc2);

    db.recalculateWeights();

    SECTION("basic calculations in documents") {
        auto documents = db.documents();
        auto frequencies = db.termFrequencies();

        REQUIRE(frequencies[L"abc"] == 2);
        REQUIRE(frequencies[L"ghi"] == 1);
        REQUIRE(documents[L"doc1"].termWeights[L"def"] == 0.0);
        REQUIRE(documents[L"doc1"].termWeights[L"ghi"] == 1.0);
        REQUIRE(documents[L"doc1"].euclideanNorm == 1.0);
    }

    SECTION("searching for a simple document") {
        auto result = db.search(query);

        REQUIRE(result[0].documentId == L"doc1");
        REQUIRE(result[0].similarity == 1.0);
    }

    SECTION("with a third document") {
        Document doc3{L"doc3", {
                {L"def", 1},
                {L"ghi", 2}
        }, {}};

        db.addDocument(doc3);
        db.recalculateWeights();

        SECTION("basic calculations in documents") {
            auto documents = db.documents();
            auto frequencies = db.termFrequencies();

            REQUIRE(frequencies[L"abc"] == 2);
            REQUIRE(frequencies[L"ghi"] == 2);
            REQUIRE(documents[L"doc1"].termWeights[L"def"] == 0.0);
            REQUIRE(documents[L"doc1"].termWeights[L"ghi"] == Approx(0.5849625007211562));
            REQUIRE(documents[L"doc1"].euclideanNorm == Approx(1.308015915900775));
            REQUIRE(documents[L"doc3"].termWeights[L"ghi"] == Approx(1.169925001442312));
            REQUIRE(documents[L"doc3"].euclideanNorm == Approx(1.169925001442312));
        }

        SECTION("searching for a simple document") {
            auto result = db.search(query);

            REQUIRE(result[0].documentId == L"doc1");
            REQUIRE(result[0].similarity == Approx(0.447213595499958));
        }
    }
}
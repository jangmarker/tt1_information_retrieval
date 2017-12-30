#include "test_helper.h"
#include "3rdparty/catch.h"

#include "database.h"
#include "fileaccess.h"

#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

TEST_CASE("read from files", "[database]") {
    LocaleSetter setLocale;

    Database db;
    fs::path self(__FILE__);
    fs::path schlag(self.parent_path() / fs::path("schlag"));

    SECTION("read single file") {
        fs::path peitsche(schlag / fs::path("Peitsche (Schlagwaffe).txt"));
        Document docPeitsche = FileAccess::documentFromFile(peitsche);

        REQUIRE(docPeitsche.id == L"Peitsche (Schlagwaffe)");
        REQUIRE(docPeitsche.termFrequencies[L"peitsche"] == 42);
    }

    SECTION("read directory") {
        db.addDocuments(FileAccess::documentsFromDirectory(schlag));

        REQUIRE(db.documents().size() == 21);
        const std::wstring idPeitsche = L"Peitsche (Schlagwaffe)";
        const auto& docPeitsche = db.documents().at(idPeitsche);
        REQUIRE(docPeitsche.id == idPeitsche);
        REQUIRE(docPeitsche.termFrequencies.at(L"peitsche") == 42);
    }
}
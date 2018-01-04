#include "cli.h"

#include "locale_names.h"
#include "database.h"
#include "fileaccess.h"

#include "3rdparty/CLI11.hpp"

#include <algorithm>
#include <experimental/filesystem>
#include <locale>

using namespace std::literals::string_literals;
namespace fs = std::experimental::filesystem;

int cli(int argc, char* argv[], std::wostream& ostream)
{
    setlocale(LC_ALL, DE_LOCALE);
    std::locale::global(std::locale(DE_LOCALE));

    CLI::App app{"Text Technologie 1 - Aufgabe 4 - Lösung Jan Marker"};

    static struct {
        std::string databaseFolder = "./"s;
        CLI::Option* printMatrix = nullptr;
        CLI::Option* saveMatrixCsv = nullptr;
        std::vector<std::string> query;
    } options;

    app.add_option("--db", options.databaseFolder, "Path to the directory where the texts are located.")
            ->check(CLI::ExistingDirectory);
    options.printMatrix = app.add_flag("--print-matrix", "Show database matrix");
    options.saveMatrixCsv = app.add_flag("--save-matrix-csv", "Save matrix to 'matrix.csv' in CSV format");
    app.add_option("query", options.query, "Query to the database")
            ->mandatory(true);

    CLI11_PARSE(app, argc, argv);

    Database db;
    db.addDocuments(FileAccess::documentsFromDirectory(fs::path(options.databaseFolder)));
    db.recalculateWeights();

    auto results = db.search(Query{options.query});

    std::sort(results.begin(), results.end());

    for (const auto& result : results) {
        ostream << result << std::endl;
    }

    if (*options.printMatrix) {
        ostream << std::endl;
        ostream << L"Matrix:" << std::endl;
        ostream << db << std::endl;
    }

    if (*options.saveMatrixCsv) {
        FileAccess::matrixToFile(db, "matrix.csv");

        ostream << std::endl;
        ostream << L"When importing 'matrix.csv', please note that the fixed point separator "
                << L"is in German style, i.e. ',' instead of '.'. Fields are separated by ';'."
                << std::endl;
    }

    return 0;
}
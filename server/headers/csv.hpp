#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using std::ifstream, std::string, std::stringstream, std::vector;

namespace csv {
/*
 * Simply loads a csv file (Doesn't look for escaped apostrophes)
 @param filename The filename to the csv file
 @returns A vector in the format of `{ { cell, cell }, { cell, cell } }`
 */
vector<vector<string>> load_csv(string filename) {
    string line;
    vector<vector<string>> table;
    ifstream file(filename);

    // Go through each line and store the cell values
    while (getline(file, line)) {
        vector<string> values;
        bool in_apostrophes = false;
        for (int i = 0, last_idx = 0; i <= line.length(); i++) {
            if (line[i] == '"') {
                // This doesn't handle double apostrophes,
                // but they aren't needed for now anyway
                in_apostrophes = !in_apostrophes;
            }

            if ((line[i] == ',' && !in_apostrophes) || i == string(line).length()) {
                string value;
                for (int j = last_idx; j < i; j++) {
                    value.push_back(line[j]);
                }

                // Remove all apostrophes
                size_t found = value.find("\"");
                while (found != string::npos) {
                    value.replace(found, 1, "");
                    found = value.find("\"");
                }

                values.push_back(value);
                last_idx = i + 1;
            }
        }
        table.push_back(values);
    }

    file.close();

    // Return the table
    return table;
}

/*
 * Returns a string based on the table
 @param open Opening bracket
 @param close Closing bracket
 @param whitespaces When true, this also adds
 * whitespaces to make it more readable
 @returns A string in the format of `{ { "cell", "cell" }, { "cell", "cell" } }`.
 * If you need a json compatible format, specify `open` as `'['` and `close` as `']'`
 */
string table_string(vector<vector<string>> table,
                    char open = '{',
                    char close = '}',
                    bool whitespaces = true) {
    // Convert open and close to strings
    const string space = whitespaces ? " " : "";
    const int erase_pos = whitespaces ? -2 : -1;

    // The result of what this function returns
    stringstream result;

    result << open << space;

    // Go through each row and append the result string
    for (const vector<string> row : table) {
        result << open << space;
        for (const string item : row) {
            result << "\"" << item << "\"," << space;
        }

        result.seekp(erase_pos, std::ios_base::cur);

        result << close << "," << space;
    }

    result.seekp(erase_pos, std::ios_base::cur);

    result << space << close;

    // Return the string
    return result.str();
}

}  // namespace csv

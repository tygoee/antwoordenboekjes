#include <crow.h>

#include <fstream>
#include <headers/csv.hpp>
#include <map>
#include <string>
#include <vector>

using std::ifstream, std::map, std::string, std::vector;

int main(int argc, char const* argv[]) {
    // Initialize the app
    crow::SimpleApp app;

    // Load the json file
    ifstream file("./static/json/vakken.json");
    string vakken((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Load boeken
    vector<vector<string>> boeken = csv::load_csv("db/boeken.csv");
    vector<string> boeken_h = boeken[0];
    boeken.erase(boeken.begin());

    // Setup the / route to load main.html
    CROW_ROUTE(app, "/")
    ([vakken] {
        crow::mustache::template_t page = crow::mustache::load("main.html");
        crow::mustache::context ctx({{"vakken", vakken}});

        return page.render(ctx);
    });

    // Get query results
    CROW_ROUTE(app, "/q/")
    ([boeken, boeken_h](const crow::request& req, crow::response& res) {
        const crow::query_string params(req.url_params);

        // Initialise single and multiple parameters
        const string single_param_keys[] = {"query", "sort"};
        const string multi_param_keys[] = {"niveau", "leerjaar", "vak", "methode"};

        map<string, char*> single_params;
        map<string, vector<string>> multi_params;

        // Assign params to single_params and
        // handle errors if they aren't passed
        for (const string param : single_param_keys) {
            try {
                single_params[param] = params.get(param);
            } catch (std::basic_string<char>::allocator_type::value_type) {
                ;  // Do nothing if parameter doesn't exist
            }
        }

        // Do the same for multi_params
        for (const string param : multi_param_keys) {
            try {
                const char* param_value = params.get(param);

                // Continue if param_value is a null pointer
                if (param_value == nullptr) {
                    continue;
                }

                string token;

                // Add all the comma-seperated values to multi_params
                for (int i = 0, last_idx = 0; i <= string(param_value).length(); i++) {
                    if (param_value[i] == ',' || i == string(param_value).length()) {
                        string value;
                        for (int j = last_idx; j < i; j++) {
                            value.push_back(param_value[j]);
                        }

                        multi_params[param].push_back(value);
                        last_idx = i + 1;
                    }
                }
            } catch (std::basic_string<char>::allocator_type::value_type) {
                ;  // Do nothing if parameter doesn't exist
            }
        }

        // Log all values
        if (false) {
            for (auto& [key, value] : single_params) {
                CROW_LOG_INFO << key;
                CROW_LOG_INFO << "|-- " << value;
            }
            for (auto& [key, values] : multi_params) {
                CROW_LOG_INFO << key;
                for (string value : values) {
                    CROW_LOG_INFO << "|-- " << value;
                }
            }
        }

        // Search the data for matching_values values
        vector<vector<string>> matching_values;

        // This doesn't work correctly at all, it
        // selects values if only 1 is true and has
        // other unexpected behavior
        for (auto&& [param, param_values] : multi_params) {
            // Get the boeken_h index of param
            vector<string>::const_iterator it = std::find(boeken_h.begin(), boeken_h.end(), param);
            if (it == boeken_h.end()) {
                continue;
            }

            // Assign it to idx
            const size_t idx = it - boeken_h.begin();

            // Add rows to the matching_values rows
            for (const vector<string> row : boeken) {
                for (const string param_value : param_values) {
                    const int elementidx = std::find(matching_values.begin(),
                                                     matching_values.end(),
                                                     row) != matching_values.end();

                    // If row[idx] is param_value and it
                    // isn't already in matching_values,
                    // add the row to matching_values
                    if (row[idx] == param_value && !elementidx) {
                        matching_values.push_back(row);
                    } else if (row[idx] != param_value && elementidx) {
                        // If it's found but doesn't match,
                        // rm the element from matching_values
                        // (doesn't work somehow)
                        matching_values.erase(matching_values.begin() + elementidx);
                    }
                }
            }
        }

        // Return the json
        res.add_header("Content-Type", "application/json");
        res.write(csv::table_string(matching_values, '[', ']'));

        res.end();
    });

    // TODO: Return image/text/styled text/?
    // per page of a requested document
    CROW_ROUTE(app, "/doc/<string>")
    ([](const string& docname) {
        return "";
    });

    // Run the server
    app.port(18080).multithreaded().run();

    return 0;
}

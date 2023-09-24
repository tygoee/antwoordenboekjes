#include <crow.h>

int main(int argc, char const* argv[]) {
    // Initialize the app
    crow::SimpleApp app;

    // Load the json file
    std::ifstream file("./static/json/vakken.json");
    std::string vakken((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    // Setup the / route to load main.html
    CROW_ROUTE(app, "/")
    ([&vakken] {
        auto page = crow::mustache::load("main.html");
        crow::mustache::context ctx({{"vakken", vakken}});

        return page.render(ctx);
    });

    // Run the server
    app.port(18080).multithreaded().run();

    return 0;
}

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <unordered_map>

using json = nlohmann::json;
using namespace std;

// Helper function to print JSON data with indentation
void print_json(const json& j) {
    cout << "JSON data:\n" << j.dump(4) << endl; // Print JSON with indentation of 4 spaces
}

// Function to modify theme colors using STL containers
void modify_theme_colors(json& j) {
    // Using std::unordered_map for theme colors
    unordered_map<string, string> color_changes = {
        {"background", "#000000"},  // Change background color to black
        {"text", "#FFFFFF"},        // Change text color to white
        {"highlight", "#00FF00"}    // Change highlight color to green
    };

    if (j.contains("theme")) {
        auto& theme = j["theme"];

        // Iterate through the unordered_map and update the JSON theme
        for (auto it = color_changes.begin(); it != color_changes.end(); ++it) {
            const string& color = it->first;
            const string& new_value = it->second;

            if (theme.contains(color)) {
                theme[color] = new_value;
            }
        }
    }
}

// Function to read JSON data from a file
json read_json_from_file(const string& filename) {
    ifstream input_file(filename);
    if (!input_file) {
        throw runtime_error("Error: Could not open file for reading.");
    }

    json j;
    try {
        input_file >> j; // Parse JSON from file
    }
    catch (json::parse_error& e) {
        throw runtime_error("Error: " + string(e.what()));
    }

    return j;
}

// Function to write JSON data to a file
void write_json_to_file(const string& filename, const json& j) {
    ofstream output_file(filename);
    if (!output_file) {
        throw runtime_error("Error: Could not open file for writing.");
    }

    output_file << j.dump(4); // Save JSON to file with indentation
}

int main() {
    try {
        // Read JSON from file
        json j = read_json_from_file("F:\\Visual_Studio_C++\\Projects\\JSON_Parser\\data.json");

        print_json(j); // Print original JSON data

        modify_theme_colors(j); // Modify theme colors

        print_json(j); // Print modified JSON data

        // Save modified JSON to file
        write_json_to_file("F:\\Visual_Studio_C++\\Projects\\JSON_Parser\\data_modified.json", j);

        cout << "Modified JSON has been saved to data_modified.json" << endl;

    }
    catch (const runtime_error& e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}

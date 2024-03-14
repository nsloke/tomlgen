#include <iostream>
#include <fstream>
#include <map>
#include <variant>
#include <vector>
#include <string>

// Define a variant type to hold different TOML values
using TomlValue = std::variant<int, double, bool, std::string>;

// Define a type for TOML table
using TomlTable = std::map<std::string, TomlValue>;

// Function to write TOML table recursively
void write_toml(std::ofstream& out, const TomlTable& table, int depth = 0) {
    for (const auto& pair : table) {
        for (int i = 0; i < depth; ++i)
            out << "    ";

        out << pair.first << " = ";

        std::visit([&out, depth](const auto& value) {
            using T = std::decay_t<decltype(value)>;
            if constexpr (std::is_same_v<T, int> || std::is_same_v<T, double> || std::is_same_v<T, bool>) {
                out << value << std::endl;
            } else if constexpr (std::is_same_v<T, std::string>) {
                out << "\"" << value << "\"" << std::endl;
            } else if constexpr (std::is_same_v<T, TomlTable>) {
                out << "{" << std::endl;
                write_toml(out, value, depth + 1);
                for (int i = 0; i < depth; ++i)
                    out << "    ";
                out << "}" << std::endl;
            }
        }, pair.second);
    }
}

int main() {
    // Create a TOML table
    TomlTable config;

    // Add key-value pairs
    config["name"] = "John Doe";
    config["age"] = 30;
    config["is_student"] = false;

    // Create a nested table for address
    TomlTable address;
    address["city"] = "New York";
    address["country"] = "USA";

    // Create a nested table for permanent address
    TomlTable permanentAddress;
    permanentAddress["city"] = "Los Angeles";
    permanentAddress["country"] = "USA";

    // Insert the permanent address into the address table
    address.insert(std::make_pair("permanent", permanentAddress));

    // Insert the address table into the main table
    config.insert(std::make_pair("address", address));

    // Write to TOML file
    std::ofstream file("config.toml");
    if (file) {
        write_toml(file, config);
        file.close();
        std::cout << "TOML file generated successfully.\n";
    } else {
        std::cerr << "Error creating file.\n";
        return 1;
    }

    return 0;
}

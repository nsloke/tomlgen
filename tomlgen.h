#ifndef TOMLGEN_H_INCLUDED
#define TOMLGEN_H_INCLUDED
#include <iostream>
#include <vector>
#include <sstream>

namespace toml {
    class TomlRoot;
    class TomlTable;
    class TomlElement;
    class TomlKey;
    class TomlValue;



    class TomlTable
    {
        private:
            std::string tablename;
            std::vector<toml::TomlElement> elements;
        public:
            TomlTable(std::string tablename);
            bool addElement(TomlElement element);
            std::vector<TomlElement> getAllElements();
            std::string getTableName();
    };



    class TomlKey
    {
        private:
            std::string keyObj;
        public:
            TomlKey();
            TomlKey(std::string key);
            std::string getKeyString();
    };

    class TomlValue
    {
        private:
            std::string stringVal;
            int intVal;
            float floatVal;
            bool boolVal;
            int valIndicator;



        public:
        TomlValue();
        TomlValue(const std::string& value,int lockbit);
        TomlValue(int value);
        TomlValue(float value);
        TomlValue(bool value);
        int getValueIndicator();
        std::string getStringValue();
        int getIntegerValue();
        float getFloatValue();
        bool getBoolValue();

    };

    class TomlElement
    {
        private:
            TomlKey key;
            TomlValue value;
        public:
            TomlElement();
            TomlElement(TomlKey key,TomlValue value);
            TomlKey getKey();
            TomlValue getValue();
    };



    class TomlRoot
    {
        private:
            toml::TomlElement element;
            bool elementSet=false;
            std::vector<toml::TomlTable> tables;
        public:
            TomlRoot();
            TomlRoot(toml::TomlTable table);
            TomlRoot(toml::TomlElement element);
            bool addTable(toml::TomlTable table);
            std::string toString();

    };

};


#endif // TOMLGEN_H_INCLUDED

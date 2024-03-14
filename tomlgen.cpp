#include "tomlgen.h"


//TOML Root Section STARTS
toml::TomlRoot::TomlRoot()
{
    this->elementSet=false;
}

toml::TomlRoot::TomlRoot(toml::TomlElement element)
{
    this->element=element;
    this->elementSet=true;
}

toml::TomlRoot::TomlRoot(toml::TomlTable table)
{
    this->tables.push_back(table);
}

bool toml::TomlRoot::addTable(toml::TomlTable table)
{
    this->tables.push_back(table);
    return true;
}

std::string toml::TomlRoot::toString()
{
    std::stringstream ss;
    if(this->elementSet==false)
    {
        for (size_t i = 0; i < tables.size(); ++i) {
            ss<<"\n\n["<<tables[i].getTableName()<<"]"<<std::endl;

            std::vector elems=tables[i].getAllElements();

                for(size_t j=0;j<elems.size ();j++)
                {

                 ss<<elems[j].getKey().getKeyString()<<"=";

                    if(elems[j].getValue().getValueIndicator()==0)
                    {
                        ss<<"\n";
                    }
                    else if(elems[j].getValue().getValueIndicator()==1)
                    {
                        //std::cout<<"\nValue as String is:"<<elems[j].getValue().getStringValue();
                        ss<<"\""<<elems[j].getValue().getStringValue()<<"\"\n";
                    }
                    else if(elems[j].getValue().getValueIndicator()==2)
                    {
                        ss<<elems[j].getValue().getIntegerValue()<<"\n";
                    }
                    else if(elems[j].getValue().getValueIndicator()==3)
                    {
                        ss<<elems[j].getValue().getFloatValue()<<"\n";
                    }
                    else if(elems[j].getValue().getValueIndicator()==4)
                    {
                        ss<<elems[j].getValue().getBoolValue()<<"\n";
                    }


                }



        }
    }
    else
    {

    }

    return ss.str();
}

//TOML Root Section ENDS



//TOML Table Section STARTS
toml::TomlTable::TomlTable(std::string tablename)
{
    this->tablename=tablename;
}

bool toml::TomlTable::addElement(TomlElement element)
{
    this->elements.push_back(element);
    return true;
}

std::vector<toml::TomlElement> toml::TomlTable::getAllElements()
{
    return this->elements;
}

std::string toml::TomlTable::getTableName()
{
    return this->tablename;
}

//TOML Table Section ENDS



//TOML ELEMENT STARTS
toml::TomlElement::TomlElement()
{

}

toml::TomlElement::TomlElement(toml::TomlKey key,toml::TomlValue value)
{
    this->key=key;
    this->value=value;
}

toml::TomlKey toml::TomlElement::getKey()
{
    return key;
}

toml::TomlValue toml::TomlElement::getValue()
{
    return value;
}
//TOML ELEMENT ENDS



//TOML Key STARTS
toml::TomlKey::TomlKey()
{
}
toml::TomlKey::TomlKey(std::string key)
{
    keyObj=key;
}
std::string toml::TomlKey::getKeyString()
{
    return keyObj;
}
//TOML Key ENDS



//TOML Value STARTS
toml::TomlValue::TomlValue()
{
    valIndicator=0;
}



toml::TomlValue::TomlValue(const std::string& value,int lockbit)
{
    stringVal=value;
    valIndicator=1;
}

toml::TomlValue::TomlValue(int value)
{
    intVal=value;
    valIndicator=2;
}

toml::TomlValue::TomlValue(float value)
{
    floatVal=value;
    valIndicator=3;
}

toml::TomlValue::TomlValue(bool value)
{
    boolVal=value;
    valIndicator=4;
}

int toml::TomlValue::getValueIndicator()
{
    return valIndicator;
}

std::string toml::TomlValue::getStringValue()
{
    return stringVal;
}

int toml::TomlValue::getIntegerValue()
{
    return intVal;
}

float toml::TomlValue::getFloatValue()
{
    return floatVal;
}

bool toml::TomlValue::getBoolValue()
{
    return boolVal;
}
//TOML Value ENDS

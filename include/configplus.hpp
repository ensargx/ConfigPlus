#pragma once

#include <cstddef>
#include <cstring>
#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <any>

#define CFG_ADD_BOOL(Name, DefaultValue) \
public: bool Name; \
private: Vars_t<bool, sizeof(#Name)> \
    m_Var##Name { TypeInfo::TypeBool, DefaultValue, &Name, #Name, m_Vars }; \
public:

#define CFG_ADD_INT(Name, DefaultValue) \
public: int Name; \
private: Vars_t<int, sizeof(#Name)> \
    m_Var##Name { TypeInfo::TypeInt, DefaultValue, &Name, #Name, m_Vars }; \
public:

class CConfigPlus
{
protected:
    enum class ConfigFormat : int
    {
        Json = 0,
        Toml,
        Yaml,
        Xml,
        End
    };
    void SaveToFile(ConfigFormat FormatType, const char* FileName);
    void LoadFromFile(ConfigFormat FormatType, const char* FileName)
    {
        std::map<std::string, std::string> Map = ReadFromFile(FormatType, FileName);


    }
    std::map<std::string, std::string> ReadFromFile(ConfigFormat format, const char* FileName)
    {
        if (format == ConfigFormat::Toml)
            return ReadToml(FileName);
        return {};
    }

protected:
    enum class TypeInfo : int
    {
        TypeBool = 0,
        TypeInt,
        TypeFloat,
        TypeString,
        TypeColor,
        TypeVector,
        TypeArray,
        TypeEnd
    };

protected:
    template <typename T, std::size_t SizeName>
    struct Vars_t
    {
        TypeInfo Type;
        T DefaultValue;
        T* pValue;
        char Name[SizeName];

        [[nodiscard]] constexpr std::size_t GetSizeName() const
        {
            return SizeName;
        }

        [[nodiscard]] virtual const char* GetName() const
        {
            return Name;
        }

        [[nodiscard]] T* GetValue() const
        {
            return pValue;
        }

        [[nodiscard]] T GetDefaultValue() const
        {
            return DefaultValue;
        }

        [[nodiscard]] TypeInfo GetType() const
        {
            return Type;
        }

        Vars_t(TypeInfo Type, T DefaultValue, T* pValue, const char* Name, std::map<std::string, void*>& Vars)
            : Type(Type), DefaultValue(DefaultValue), pValue(pValue)
        {
            std::strncpy(this->Name, Name, SizeName);
            Vars[Name] = this;
        }
    };

private:
    // this is not a toml parsing library so...
    std::map<std::string, std::string> ReadToml(const char* FileName)
    {
        std::map<std::string, std::string> Map;
        std::ifstream File(FileName);
        if (!File.is_open())
            return Map;

        std::string Line;
        while (std::getline(File, Line))
        {
            if (Line.empty())
                continue;

            if (Line[0] == '#')
                continue;

            std::size_t Pos = Line.find('=');
            if (Pos == std::string::npos)
                continue;

            std::string Key = Line.substr(0, Pos);
            std::string Value = Line.substr(Pos + 1);
            std::size_t Comment = Value.find('#');
            if (Comment != std::string::npos)
                Value = Value.substr(0, Comment);

            // string whitespace
            Key.erase(0, Key.find_first_not_of(" \t"));
            Key.erase(Key.find_last_not_of(" \t") + 1);

            Value.erase(0, Value.find_first_not_of(" \t"));
            Value.erase(Value.find_last_not_of(" \t") + 1);

            Map[Key] = Value;

            Vars_t<std::any, 1>* m_Var = static_cast<Vars_t<std::any, 1>*>(m_Vars[Key]);
            if (m_Var)
                std::cout << m_Var->GetName() << " = " << std::any_cast<std::string>(m_Var->GetValue()) << std::endl;
        }

        return Map;
    }

protected:
    std::map<std::string, void*> m_Vars;
};


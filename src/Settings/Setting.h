#pragma once

#include <string>

class Setting
{
public:
    Setting(const std::string& name, const std::string& value) 
        : m_name(name), m_value(value) 
    { 

    }

    const std::string& GetName() const { return m_name; }
    const std::string& GetValue() const { return m_value; }

private:
    const std::string m_name;
    const std::string m_value; // TODO: int might be better
};
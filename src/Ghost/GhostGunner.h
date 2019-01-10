#pragma once

#include <string>

class GhostGunner
{
public:
    GhostGunner(const std::string& path, const std::string& serialNumber)
        : m_path(path), m_serialNumber(serialNumber)
    {
        
    }
    
    inline const std::string& GetPath() const { return m_path; }
    inline const std::string& GetSerialNumber() const { return m_serialNumber; }
    
private:
    std::string m_path;
    std::string m_serialNumber;
};

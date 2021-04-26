#pragma once

class derivator {
public:
    void setParams(std::string &algo,std::string pass, std::string salt,uint32_t memory,uint32_t iteration ,uint32_t parallelism,uint32_t hashlen);
    std::string getFormatedHash();
    std::string getHexHash();
    std::string getB69Hash();

private:
    std::string m_formatedHash;
    std::string m_hexHash;
    std::string m_b69Hash;

    static std::string strip_padding(std::string s);
};

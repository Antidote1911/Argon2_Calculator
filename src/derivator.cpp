//
// Created by antidote on 25/04/2021.
//
#include <QString>

#include "derivator.h"
#include <botan/argon2.h>
#include <botan/hex.h>
#include <sstream>
#include <botan/base64.h>

using namespace std;
using namespace Botan;

void derivator::setParams(string &algo, string user_pass, string user_salt, uint32_t memory, uint32_t iteration,
                          uint32_t parallelism, uint32_t hashlen) {
    SecureVector<quint8> key_buffer(hashlen);

    SecureVector<char> pass_buffer(user_pass.begin(), user_pass.end());
    SecureVector<uint8_t> salt_buffer(user_salt.begin(), user_salt.end());

    auto pwdhash_fam{PasswordHashFamily::create(algo)};
    const auto default_pwhash{pwdhash_fam->from_params(memory, iteration, parallelism)};

    default_pwhash->derive_key(key_buffer.data(),
                               key_buffer.size(),
                               pass_buffer.data(),
                               pass_buffer.size(),
                               salt_buffer.data(),
                               salt_buffer.size());

    m_b69Hash = strip_padding(base64_encode(key_buffer));
    m_hexHash = hex_encode(key_buffer);

    std::ostringstream oss;

    if (algo == "Argon2i")
        oss << "$argon2i$";
    else if (algo == "Argon2d")
        oss << "$argon2d$";
    else
        oss << "$argon2id$";

    oss << "v=19$m=" << memory << ",t=" << iteration << ",p=" << parallelism << "$";
    oss << strip_padding(base64_encode(salt_buffer)) << "$" << m_b69Hash;

    m_formatedHash = oss.str();

}

string derivator::getFormatedHash() {
    return m_formatedHash;
}

string derivator::getHexHash() {
    return m_hexHash;
}

string derivator::getB69Hash() {
    return m_b69Hash;
}

string derivator::strip_padding(string s) {
    while (!s.empty() && s[s.size() - 1] == '=')
        s.resize(s.size() - 1);
    return s;
}
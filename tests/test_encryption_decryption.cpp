#include "cipher.h"
#include "print_hex.h"

#include <string>
#include <cstring>


bool test_encryption_decryption(std::string input)
{
    using namespace grain;
    Key key = random::key();
    InitVector iv = random::init_vector();
    Cipher encryptor{key, iv}, decryptor{key, iv};

    size_t length = input.length();
    uint8_t* data = reinterpret_cast<uint8_t*>(input.data());
    uint8_t* encrypted = new uint8_t[length];
    uint8_t* decrypted = new uint8_t[length];
    encryptor.encrypt(data, length, encrypted);
    decryptor.decrypt(encrypted, length, decrypted);

    printf("Original message: \n");
    utils::print_hex(data, length);

    printf("Encrypted message: \n");
    utils::print_hex(encrypted, length);

    printf("Decrypted message: \n");
    utils::print_hex(decrypted, length);

    if (std::memcmp(data, decrypted, length))
    {
        return false;
    }
    return true;
}


int main()
{
    char* buffer {"Hello, Grain-128a!"};

    return test_encryption_decryption(buffer);
}
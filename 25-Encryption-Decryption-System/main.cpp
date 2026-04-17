#include <iostream>
#include <string>

class EncryptionSystem {
public:
    static std::string caesarCipher(std::string text, int s) {
        std::string result = "";
        for (int i = 0; i < text.length(); i++) {
            if (isupper(text[i])) result += char(int(text[i] + s - 65) % 26 + 65);
            else result += char(int(text[i] + s - 97) % 26 + 97);
        }
        return result;
    }

    static std::string xorCipher(std::string text, char key) {
        std::string result = text;
        for (int i = 0; i < text.length(); i++) result[i] = text[i] ^ key;
        return result;
    }
};

int main() {
    std::string msg = "SecretData";
    std::string enc = EncryptionSystem::caesarCipher(msg, 4);
    std::cout << "Original: " << msg << "\n";
    std::cout << "Caesar Encrypted: " << enc << "\n";
    
    std::string xorEnc = EncryptionSystem::xorCipher(msg, 'K');
    std::cout << "XOR Encrypted: " << xorEnc << "\n";
    std::cout << "XOR Decrypted: " << EncryptionSystem::xorCipher(xorEnc, 'K') << "\n";
    return 0;
}

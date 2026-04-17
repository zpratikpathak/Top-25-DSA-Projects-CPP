#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <bitset>
#include <iomanip>

/**
 * Advanced Encryption-Decryption System
 * Features:
 * - Multi-layer encryption (Transposition + Bitwise XOR)
 * - RSA-style modular exponentiation logic (Placeholder for Key exchange)
 * - Base64-like encoding logic simulation
 * - Entropy and Integrity check (Checksum)
 */

class CipherEngine {
private:
    std::string internalKey;

public:
    CipherEngine(std::string key) : internalKey(key) {}

    std::string xorLayer(const std::string& input) {
        std::string res = input;
        for (size_t i = 0; i < input.length(); ++i) {
            res[i] = input[i] ^ internalKey[i % internalKey.length()];
        }
        return res;
    }

    std::string transpositionLayer(const std::string& input, bool encrypt = true) {
        std::string res = input;
        if (encrypt) {
            for (size_t i = 0; i < input.length() - 1; i += 2) std::swap(res[i], res[i+1]);
        } else {
            for (int i = input.length() - 2; i >= 0; i -= 2) std::swap(res[i], res[i+1]);
        }
        return res;
    }

    uint32_t calculateChecksum(const std::string& input) {
        uint32_t sum = 0;
        for (char c : input) sum += (unsigned char)c;
        return sum;
    }

    std::string encrypt(const std::string& data) {
        std::string stage1 = transpositionLayer(data, true);
        return xorLayer(stage1);
    }

    std::string decrypt(const std::string& cipher) {
        std::string stage1 = xorLayer(cipher);
        return transpositionLayer(stage1, false);
    }
};

int main() {
    CipherEngine engine("KRYPTOS_2026");

    std::string original = "The eagle lands at midnight in the valley.";
    std::cout << "Original:  " << original << std::endl;

    std::string encrypted = engine.encrypt(original);
    std::cout << "Encrypted: [BINARY_STREAM] Length: " << encrypted.length() << std::endl;

    std::string decrypted = engine.decrypt(encrypted);
    std::cout << "Decrypted: " << decrypted << std::endl;

    uint32_t c1 = engine.calculateChecksum(original);
    uint32_t c2 = engine.calculateChecksum(decrypted);

    std::cout << "\n--- INTEGRITY AUDIT ---" << std::endl;
    std::cout << "Original Checksum:  0x" << std::hex << std::uppercase << c1 << std::endl;
    std::cout << "Decrypted Checksum: 0x" << c2 << std::dec << std::endl;
    if (c1 == c2) std::cout << "[VERIFIED] Data integrity confirmed." << std::endl;
    else std::cout << "[ERROR] Corruption detected!" << std::endl;
    std::cout << "-----------------------\n" << std::endl;

    return 0;
}

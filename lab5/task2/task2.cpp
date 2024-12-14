#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdexcept>
#include <iterator>
#include <filesystem>

class encoder final{
private:
    std::vector<std::byte> key;
    std::vector<int> s;

    void initialize_s(){
        s.clear();
        for (int i = 0; i < 256; ++i){
            s.push_back(i);
        }
        int j = 0;
        for (int i = 0; i < 256; ++i){
            j = (j + s[i] + static_cast<int>(key[i % key.size()])) % 256;
            std::swap(s[i], s[j]);
        }
    }

    std::vector<std::byte> rc4(const std::vector<std::byte>& input){
        initialize_s();
        int i = 0, j = 0;
        std::vector<std::byte> result(input.size());
        for (size_t n = 0; n < input.size(); ++n) {
            i = (i + 1) % 256;
            j = (j + s[i]) % 256;
            std::swap(s[i], s[j]);
            int t = (s[i] + s[j]) % 256;
            result[n] = input[n] ^ static_cast<std::byte>(s[t]);
        }
        return result;
    }

public:
    encoder(const std::vector<std::byte>& t) : key(t){
        if (key.empty()){
            throw std::invalid_argument("Encryption key cannot be empty");
        }
    }

    void set_key(const std::vector<std::byte>& new_key){
        if (new_key.empty()){
            throw std::invalid_argument("New encryption key cannot be empty");
        }
        key = new_key;
    }

    void encode(const std::string& input_path, const std::string& output_path){

        std::filesystem::path path_1{input_path};
        std::filesystem::path path_2{output_path};

        if (std::filesystem::equivalent(path_1, path_2))
        {
            throw std::runtime_error("Equivalent file path");
        }

        std::ifstream input_file(input_path, std::ios::binary);
        if (!input_file.is_open()){
            throw std::runtime_error("Failed to open input file: " + input_path);
        }

        std::vector<char> temp_data(
                (std::istreambuf_iterator<char>(input_file)),
                std::istreambuf_iterator<char>()
        ); //считывать весь файл оч плохо, надо делать посимвольно

        std::vector<std::byte> input_data;
        for(char c : temp_data){
            input_data.push_back(static_cast<std::byte>(c));
        }
        input_file.close();

        auto output_data = rc4(input_data);

        std::ofstream output_file(output_path, std::ios::binary);
        if (!output_file.is_open()) {
            throw std::runtime_error("Failed to open output file: " + output_path);
        }

        output_file.write(reinterpret_cast<const char*>(output_data.data()), output_data.size());
        output_file.close();
    }
};

int main() {
    std::vector<std::byte> key = {std::byte(1), std::byte(2), std::byte(3), std::byte(4), std::byte(5)};

    encoder enc(key);

    std::string input_file = "input.txt";
    std::string encrypted_file = "encrypted.txt";
    std::string decrypted_file = "decrypted.txt";

    enc.encode(input_file, encrypted_file);
    std::cout << "File encrypted successfully!\n";

    enc.encode(encrypted_file, decrypted_file);
    std::cout << "File decrypted successfully!\n";
    return 0;
}

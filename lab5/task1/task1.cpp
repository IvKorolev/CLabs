#include <iostream>
#include <utility>

class binary_int final{
private:
    int value;

    static int negative(int n){
        return sum(~n, 1);
    }

    static int sum(int num1, int num2){
        int res = 0, carry = 0;
        res = num1 ^ num2;
        carry = (num1 & num2) << 1;
        while (carry) {
            int tmp = res;
            res = res ^ carry;
            carry = (tmp & carry) << 1;
        }
        return res;
    }

    static int subtraction(int a, int b){
        return sum(a, negative(b));
    }

    static int multiply(int num1, int num2){
        int result = 0;

        bool is_negative = false;
        if (num1 < 0){
            num1 = negative(num1);
            is_negative = !is_negative;
        }
        if (num2 < 0){
            num2 = negative(num2);
            is_negative = !is_negative;
        }
        while (num2 != 0){
            if (num2 & 1){
                result = sum(result, num1);
            }
            num1 <<= 1;
            num2 >>= 1;
        }
        return is_negative ? negative(result) : result;
    }


public:
    binary_int(int v = 0) : value(v){}

    binary_int operator-() const{
        return negative(value);
    }

    binary_int& operator++()& {
        value = sum(value, 1);
        return *this;
    }

    binary_int& operator--()& {
        value = subtraction(value, 1);
        return *this;
    }

    binary_int operator++(int){
        binary_int temp = *this;
        value = sum(value, 1);
        return temp;
    }

    binary_int operator--(int){
        binary_int temp = *this;
        value = subtraction(value, 1);
        return temp;
    }

    binary_int& operator+=(const binary_int& other)& {
        value = sum(value, other.value);
        return *this;
    }

    binary_int& operator-=(const binary_int& other)& {
        value = subtraction(value, other.value);
        return *this;
    }

    binary_int operator+(const binary_int& other) const{
        return binary_int(sum(value, other.value));
    }

    binary_int operator-(const binary_int& other) const{
        return binary_int(subtraction(value, other.value));
    }

    binary_int& operator*=(const binary_int& other)& {
        value = multiply(value, other.value);
        return *this;
    }

    binary_int operator*(const binary_int& other) const{
        return binary_int(multiply(value, other.value));
    }

    binary_int& operator<<=(int shift)& {
        value <<= shift;
        return *this;
    }

    binary_int operator<<(int shift) const{
        return binary_int(value << shift);
    }

    binary_int& operator>>=(int shift)& {
        value >>= shift;
        return *this;
    }

    binary_int operator>>(int shift) const{
        return binary_int(value >> shift);
    }

    std::pair<binary_int, binary_int> split() const{
        int upper = value & 0xFFFF0000;
        int lower = value & 0x0000FFFF;
        return {binary_int(upper), binary_int(lower)};
    }

    void print_binary() const{
        for (int i = 31; i >= 0; --i){
            std::cout << ((value >> i) & 1);
            if (i % 8 == 0) std::cout << " ";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const binary_int& b){
        b.print_binary();
        return os;
    }
};

int main(){
    binary_int a(42);
    binary_int b(-15);

    std::cout << "Binary representation of a:\n";
    std::cout << a << "\n";

    std::cout << "Binary representation of -a:\n";
    std::cout << -a << "\n";

    std::cout << "Prefix increment (++a):\n";
    std::cout << ++a << "\n";
    std::cout << "Postfix increment (a++):\n";
    std::cout << a++ << "\n";
    std::cout << "After postfix increment:\n";
    std::cout << a << "\n";

    std::cout << "\na + b:\n" << a + b << "\n";
    std::cout << "a * b:\n" << a * b << "\n";
    std::cout << "a - b:\n" << a - b << "\n";
    std::cout << "a:\n" << a << "\n";

    std::cout << "\na += b:\n";
    a += b;
    std::cout << a << "\n";
    std::cout << "a -= b:\n";
    a -= b;
    std::cout << a << "\n";
    std::cout << "a *= b:\n";
    a *= b;
    std::cout << a << "\n";

    std::cout << "\na <<= 2:\n";
    a <<= 2;
    std::cout << a << "\n";
    std::cout << "a << 2:\n" << (a << 2) << "\n";
    std::cout << "a:\n" << a << "\n";

    std::cout << "\na >>= 2:\n";
    a >>= 2;
    std::cout << a << "\n";
    std::cout << "a >> 2:\n" << (a >> 2) << "\n";
    std::cout << "a:\n" << a << "\n";

    std::cout << "\nSplitting a into upper and lower halves:\n";
    auto [upper, lower] = a.split();
    std::cout << "Upper half:" << "\n" << upper << "\n";
    std::cout << "Lower half:" << "\n" << lower << "\n";

    return 0;
}

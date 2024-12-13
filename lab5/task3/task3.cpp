#include <iostream>
#include <stdexcept>
#include <string>


class logical_values_array final{
private:
    unsigned int value;

public:
    logical_values_array(unsigned int v = 0) {value = v;}

    unsigned int get_value() const{
        return value;
    }

    logical_values_array inversion() const{
        return logical_values_array(~(value));
    }

    logical_values_array conjuction(const logical_values_array& value2) const{
        return logical_values_array(value && value2.get_value());
    }

    logical_values_array disjunction(const logical_values_array& value2) const{
        logical_values_array temp = value2.inversion();
        logical_values_array temp2 = this->inversion();
        return temp2.conjuction(temp).inversion();
    }

    logical_values_array implication(const logical_values_array& value2) const{
        return this->inversion().disjunction(value2);
    }

    logical_values_array coimplication(const logical_values_array& value2) const{
        return this->inversion().implication(value2);
    }

    logical_values_array mod2(const logical_values_array& value2) const{
        logical_values_array temp1, temp2, temp3;
        temp1 = this->inversion().conjuction(value2);
        temp3 = value2.inversion();
        temp2 = this->conjuction(temp3);
        return temp1.disjunction(temp2);
    }

    logical_values_array equivalence(const logical_values_array& value2) const{
        return this->mod2(value2).inversion();
    }

    logical_values_array Pirs(const logical_values_array& value2) const{
        return this->disjunction(value2).inversion();
    }

    logical_values_array Sheffer(const logical_values_array& value2) const{
        return this->conjuction(value2).inversion();
    }

    static bool equals(const logical_values_array &value1, const logical_values_array &value2){
        return value1.get_value() == value2.get_value();
    }

    bool get_bit(size_t position) const {
        if (position >= sizeof(value) * 8)
            throw "Incorrect position";

        return (1ul << position) & value;
    }

    void get_str_value(char *str_value) const{
        if (!str_value)
            throw "Null string";

        short count_bits = sizeof(value) * 8;

        for (int i = 0; i < count_bits; ++i)
        {
            str_value[count_bits - 1 - i] = ((1 << i) & value) ? '1' : '0';
        }
        str_value[count_bits] = '\0';
    }
};

int main(){
    char arr[128];
    logical_values_array a(112312011);
    logical_values_array b(112132021);

    a.get_str_value(arr);
    std::cout << "a: " << arr << std::endl;

    b.get_str_value(arr);
    std::cout << "b: " << arr << std::endl;

    logical_values_array c = a.inversion();
    c.get_str_value(arr);
    std::cout << "inversion a: " << arr << std::endl;

    c = a.conjuction(b);
    c.get_str_value(arr);
    std::cout << "conjunction: " << arr << std::endl;

    c = a.disjunction(b);
    c.get_str_value(arr);
    std::cout << "disjunction: " << arr << std::endl;

    c = a.implication(b);
    c.get_str_value(arr);
    std::cout << "implication: " << arr << std::endl;

    c = a.coimplication(b);
    c.get_str_value(arr);
    std::cout << "coimplication: " << arr << std::endl;

    c = a.mod2(b);
    c.get_str_value(arr);
    std::cout << "add_mod2: " << arr << std::endl;

    c = a.equivalence(b);
    c.get_str_value(arr);
    std::cout << "equal: " << arr << std::endl;

    c = a.Pirs(b);
    c.get_str_value(arr);
    std::cout << "pirs: " << arr << std::endl;

    c = a.Sheffer(b);
    c.get_str_value(arr);
    std::cout << "sheffer: " << arr << std::endl;

    try
    {
        bool bit = a.get_bit(1);
        std::cout << "a.get_bit(1) = " << bit << std::endl;
        bit = a.get_bit(5);
        std::cout << "a.get_bit(5) = " << bit << std::endl;
    }
    catch (const char *error_message)
    {
        std::cout << error_message << std::endl;
    }

    if (logical_values_array::equals(a, b))
    {
        std::cout << "a == b: True" << std::endl;
    }
    else
    {
        std::cout << "a == b: False" << std::endl;
    }
    return 0;
}
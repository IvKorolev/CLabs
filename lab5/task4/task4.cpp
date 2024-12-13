#include <iostream>
#include <cmath>

class complex final{
private:
    double deistv;
    double mnim;

public:
    complex(double a = 0, double b = 0) {deistv = a; mnim = b;}

    void sum(const complex& other){
        deistv += other.deistv;
        mnim += other.mnim;
    }

    void substraction(const complex& other){
        complex result;
        deistv -= other.deistv;
        mnim -= other.mnim;
    }

    void multiply(const complex& other){
        complex result;
        deistv = deistv * other.deistv - mnim * other.mnim;
        mnim = deistv * other.mnim + mnim * other.deistv;
    }

    void devision(const complex& other){
        complex result;
        double divider = (other.deistv * other.deistv + other.mnim * other.mnim);
        if (divider == 0)
            throw std::overflow_error("Divide by zero exception");
        deistv = (deistv * other.deistv + mnim * other.mnim) / divider;
        mnim = (mnim * other.deistv - deistv * other.mnim) / divider;
    }

    double module() const{
        return sqrt(deistv * deistv + mnim * mnim);
    }

    double argument() const{
        return atan(mnim / deistv) * 180 / M_PI;
    }

    double deistv_accerssor() const { return deistv; }
    double mnim_accessor() const { return mnim; }


    void info() const{
        std::cout << this->deistv_accerssor() << " + " << this->mnim_accessor() << "i; Argument = "
                  << this->argument() << "; Module = " << this->module() << std::endl;
    }
};

int main(){
    complex a(9.21, 1.21);
    complex b(0, 0);
    std::cout << "a = ";
    a.info();
    std::cout << "b = ";
    b.info();
    std::cout << "\nTest div:\n" << std::endl;
    try
    {
        a.devision(b);
    }
    catch (std::overflow_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    std::cout << "a = ";
    a.info();
    b = complex(1.22, 1421.22);
    std::cout << "b = ";
    b.info();

    try
    {
        a.devision(b);
        std::cout << "a = ";
        a.info();
    }
    catch (std::overflow_error &e)
    {
        std::cout << e.what() << std::endl;
    }

    a = complex(100, 100);
    b = complex(10, 15);
    std::cout << "\nnew a = ";
    a.info();
    std::cout << "new b = ";
    b.info();

    std::cout << "\nTest add:" << std::endl;
    a.sum(b);
    std::cout << "a = ";
    a.info();
    std::cout << "\nTest sub:" << std::endl;
    a.substraction(b);
    std::cout << "a = ";
    a.info();
    std::cout << "\nTest mult:" << std::endl;
    a.multiply(b);
    std::cout << "a = ";
    a.info();
    return 0;
}
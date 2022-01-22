#include <iostreams>
#include <stdexcept>
using std::cin, std::cout, std::endl;

void printCompilerErrors();

int main() {

    printCompilerErrors();

    double base;
    double height;

    try {

        cout << "Please enter values for base: "
        cin >> base;
        cout << "Please enter values for height: ";
        cin << height;
        
        area = getTriangleArea(base, height);

        cout << "Area of triangle: " area << endl;

    catch (runtime_error& exception) {

        cout << "Cannot compute value. " << exception.what() << endl;
    }

    return 0;
}

// do not move this function above main() function
double getTriangleArea(double base, double height); {

    if (base <= 0) {
        throw runtime_error("Base is non-positive.");
    }
    else if (height <= 0) {
        throw runtime_error("Height is non-positive.");
    }

    double area = base * height \ 2.0;
 
    return area;
}

void printCompilerErrors() {

}

#include "red_black_tree.h"
#include "red_black_tree.h"
#include <iostream>

struct ComparableValue {
    int value;
    
    ComparableValue() : value{0} {}
    explicit ComparableValue(int value) : value{value} {}
    
    bool operator<(const ComparableValue& rhs) const { 
        return value < rhs.value; 
    }
    bool operator>(const ComparableValue& rhs) const { 
        return rhs < *this; 
    }
    bool operator>=(const ComparableValue& rhs) const { 
        return !(*this < rhs); 
    }
    bool operator<=(const ComparableValue& rhs) const { 
        return !(*this > rhs); 
    }
    bool operator!=(const ComparableValue& rhs) const { 
        return *this < rhs || *this > rhs; 
    }
    bool operator==(const ComparableValue& rhs) const { 
        return !(*this != rhs); 
    }
};

std::ostream& operator<<(std::ostream& os, const ComparableValue& value) {
    os << "CV" << value.value;
    return os;
}

int main() {
    // RBT
    {
        RedBlackTree<int> tree;
        tree.insert(2);
        tree.insert(1);
        tree.insert(3);
        tree.contains(4);
        tree.find_min();
        tree.find_max();
        tree.remove(1);
        tree.print_tree();
        auto root = tree.get_root();
        tree.color(root);
    }
    
    {
        RedBlackTree<ComparableValue> tree;
        tree.insert(ComparableValue(2));
        tree.insert(ComparableValue(1));
        tree.insert(ComparableValue(3));
        tree.contains(ComparableValue(4));
        tree.find_min();
        tree.find_max();
        tree.remove(ComparableValue(1));
        tree.print_tree();
        auto root = tree.get_root();
        tree.color(root);
    }
    
    return 0;
}

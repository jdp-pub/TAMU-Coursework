#include "priority_queue.h"

int main() {
    // TODO(student): write at least 1000 lines of test
    
    {//construct, push, pop
        PriorityQueue<int> r;
        r.push(10);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(8);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(12);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(8);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(11);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(4);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(9);
        cout << "top: " << r.top() << endl;
        r.print_queue();

        r.pop();
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.pop();
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.pop();
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.pop();
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.pop();
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.pop();
        try{cout << "top: " << r.top() << endl;}
        catch(std::invalid_argument &e){cout << e.what() << endl;}
        r.print_queue();
        r.pop();
        
        try{cout << "top: " << r.top() << endl;}
        catch(std::invalid_argument &e){cout << e.what() << endl;}
        r.print_queue();

        r.push(10);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(8);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(12);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(8);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(11);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(4);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        r.push(9);
        cout << "top: " << r.top() << endl;
        r.print_queue();
        cout << "empty?: " << std::boolalpha << r.empty() << endl;
        cout << "size: " << r.size() << endl;
        r.make_empty();
        r.print_queue();
        r.make_empty();
        r.print_queue();
        cout << "empty?: " << std::boolalpha << r.empty() << endl;
        cout << "size: " << r.size() << endl;


    }
    

   /*
    copy assignment
    copy construct
    memory errors(probably performance)
    performance
   */
    {
        vector<int> v = {40,60,30,80,90,10,50,20,70};
        PriorityQueue<int> p(v);
        p.print_queue();
        p = p;

        PriorityQueue<int> g;
        g = p;
        p.print_queue();
        g.print_queue();

        g.pop();
        p.print_queue();
        g.print_queue();
        cout << g.size() << endl;
        cout << p.size() << endl;
    }
    return 0;
}

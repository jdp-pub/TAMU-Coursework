#include "priority_queue.h"

template <class Comparable>
struct GreaterThan {
    constexpr bool operator()(const Comparable& lhs, const Comparable& rhs) const {
        return rhs < lhs;
    }
};

int main() {
    // TODO(student): write at least 1000 lines of test
/*    
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
  */  

   /*
    copy assignment
    copy construct
    memory errors(probably performance)
    performance
   */
  /*
  {
      PriorityQueue<int> r;
      r.push(10);
      r.push(14);
      r.push(3);
      r.push(140);
      r.push(145);
      r.push(33);
      r.push(120);
      r.push(148);
      r.push(30);
      r.print_queue();

      PriorityQueue<int> p(r);

      r = p;

      for(size_t i = r.size(); i > 0; --i) {
          r.pop();
          
          r.print_queue();
          cout << "size: " << r.size() << endl;
          //cout << "top: " << r.top() << endl;
      }
  }
  */
    {
        std::vector<int> heap{150,80,40,30,10,70,110,100,20,90,60,50,120,140,130};
        heapify(heap);

        PriorityQueue<int> g(heap);

        g.print_queue();

        PriorityQueue<int> h(g);
        h.print_queue();

        PriorityQueue<int, vector<int>, GreaterThan<int>> l(heap);
        l.print_queue();
    }
    return 0;
}

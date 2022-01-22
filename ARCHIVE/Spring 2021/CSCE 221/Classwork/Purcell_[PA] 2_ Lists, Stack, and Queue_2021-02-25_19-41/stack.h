#ifndef STACK_H
#define STACK_H

#include "array_list.h"
#include <iostream>


template <typename Object>
class Stack {
   // TODO(student): implement Stack
   ArrayList<Object> AList = {};

   public:
   Stack(){}// - makes an empty stack
   //Rule of Three
   Stack(const Stack& other){
      if(other.getA().size() == 0) {}
      else{
      AList = other.getA();
      }
   } //- constructs a copy of the given stack
   ~Stack(){}// - destroys this stack
   Stack& operator=(const Stack& other) {
      if(other.getA().size() == 0) {}
      else{
      AList = other.getA();
      }
      return *this;
   }//- assigns a copy of the given stack
   void push(const Object& item) {
      AList.insert(AList.size(), item);
   }//complete //- add the given object to the top of the stack
   void pop(){ AList.remove(AList.size() - 1); } //- remove the top element from the stack, or throw std::out_of_range is the stack is empty.
   Object& top(){return AList[AList.size() - 1];} // complete
   //- return a reference to the element on top of the stack or throw std::out_of_range if the stack is empty.
   ArrayList<Object> getA() const{return AList;}
   void print() { 
      for(size_t i = 0; i < AList.size(); ++i) {
         std::cout << AList[i] << std::endl;
      }
   }
};

#endif  // STACK_H
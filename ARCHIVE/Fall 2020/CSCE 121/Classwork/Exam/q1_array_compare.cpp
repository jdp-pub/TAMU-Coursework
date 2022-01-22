bool array_compare(int A[], unsigned int size_A, int B[], unsigned int size_B) {
    /* PSUEDOCODE SOLUTION
    * 
    * returns true unless the boolean is flipped in the for loop
    * 
    * initialize boolean bCompare
    * initialize count
    * 
    * for i < size_a
    * compare A[i] and B[i]
    * if A[i] > B[i] return false
    * if i > size_B return false; break
    * if A[i] == B[i] count++
    * if size_a == size_b && count == size_b return false
    */

   bool bCompare = true;
   int count = 0;

   for(unsigned i = 0; i < size_A; ++i)
   {
       
       if (i > size_B)
       {
           bCompare = false;
           break;
       }
       if(A[i] > B[i])
       {
           bCompare = false;
           break;
       }
       if(A[i] == B[i])
       {
           ++count;
       }
       if(count == size_A && size_A == size_B)
       {
           bCompare = false;
       }
   }

    return bCompare;
}

#include <list>
#include <iostream>
#include <vector>
#include "roaring/roaring.hh"
#include "roaring/roaring64map.hh"

using uint = unsigned int;

int main(int argc, char* argv[]) {

    std::vector<Roaring> rbs;
    //Bnn
    rbs.emplace_back(Roaring());

    std::vector<uint> values;
    std::cout<<"Enter the number add to BSI (-1 means finish): ";
    
    int n;
    std::cin>>n;

    uint row_number = 1;

    while(n >= 0){ 

        std::list<uint> l;

        std::cout << "The value " << n << " to binary is: ";

        while (n != 0)
        {
            l.push_front(n % 2);
            n = n >> 1;
        }

        // auto increase rb to represent more bit of number base on binary
        if (rbs.size()-1 < l.size())
        {
            int need = l.size() - (rbs.size()-1);
            std::cout << "Increase rbs from " << rbs.size()-1 << " to " << l.size() << std::endl;

            for (int i = 0; i < need; i++)
                rbs.emplace_back(Roaring());
        }

        std::cout << "rbs's size is " << rbs.size() << std::endl;
        int index = l.size();
        for (auto iter = l.begin(); iter != l.end(); iter++)
        {
            auto & rb = rbs.at(index);
            if (*iter == 1)
            {
                rb.add(row_number);
            }
            index--;
        }
        rbs.at(0).add(row_number);
        row_number++;

        int rb_index = 0;

        for (Roaring rb : rbs)
        {
            if (rb_index == 0)
                std::cout<<"Bnn"<<std::endl<<rb.toString()<<std::endl;
            else
                std::cout<<"B["<<rb_index-1<<"]"<<std::endl<<rb.toString()<<std::endl;
            rb_index++;
        }

        std::cout<<"Enter the number add to BSI (-1 means finish): ";
        std::cin>>n;
    }

    int s;
    std::cout<<"Enter the number to search: ";
    std::cin>>s;
    int search_value = s;

    std::list<uint> l_s;
   
    //6  from 011->110 reverse
    while (s != 0)
    {
        l_s.emplace_front(s % 2);
        s = s >> 1;
    }

    int st = l_s.size();
    int binary_arr[st];

    int ix = 0;
    for (int x : l_s)
    {
        std::cout<<"x is "<<x<<std::endl;
        binary_arr[ix] = x;
        ix++;
    }

    for (int i = 0; i < st; i++)
        std::cout << binary_arr[i];
    std::cout << std::endl;

    roaring_bitmap_t * b_gt = roaring_bitmap_create() ;
    roaring_bitmap_t * b_lt = roaring_bitmap_create();
    roaring_bitmap_t * b_eq;

    b_eq = &(rbs.at(0).roaring);

    int slice_number = rbs.size()-1;
    int bit_index = l_s.size()-1;
    roaring_bitmap_t * bnn = &(rbs.at(0).roaring);

    std::cout<<"bitmap befor operators"<<std::endl;
    roaring_bitmap_printf(b_eq);
    std::cout << std::endl;
    roaring_bitmap_printf(b_lt);
    std::cout << std::endl;
    roaring_bitmap_printf(b_gt);
    std::cout << std::endl;
    

    for (int slice_index = slice_number; slice_index > 0; slice_index--)
    {
        std::cout<<"Bit slice number is "<<slice_index-1<<std::endl;
        roaring_bitmap_t* b_i = &(rbs.at(slice_index).roaring);
        if (!(st < slice_index) && binary_arr[slice_index - 1] == 1)
        {
            b_lt = roaring_bitmap_or(b_lt, roaring_bitmap_and(b_eq, roaring_bitmap_xor(b_i,bnn)));
            b_eq = roaring_bitmap_and(b_eq, b_i);
        }
        else
        {
            b_gt = roaring_bitmap_or(b_gt, roaring_bitmap_and(b_eq, b_i));
            b_eq = roaring_bitmap_and(b_eq, roaring_bitmap_xor(b_i,bnn));
        }
        
        roaring_bitmap_printf(b_eq);
        std::cout<<std::endl;
        roaring_bitmap_printf(b_lt);
        std::cout<<std::endl;
        roaring_bitmap_printf(b_gt);
        std::cout<<std::endl;

    }

    std::cout<<"The row equals "<<search_value<<" is "<<std::endl;
    roaring_bitmap_printf(b_eq);
    std::cout<<std::endl;
    std::cout<<"The row greate than "<<search_value<<" is "<<std::endl;
    roaring_bitmap_printf(b_gt);
    std::cout<<std::endl;
    std::cout<<"The row less than "<<search_value<<" is "<<std::endl;
    roaring_bitmap_printf(b_lt);
    std::cout<<std::endl;
    
    roaring_bitmap_t * b_le = roaring_bitmap_or(b_eq, b_lt);
    roaring_bitmap_t * b_ge = roaring_bitmap_or(b_eq, b_gt);

    return 0;
}
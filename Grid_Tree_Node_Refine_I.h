#ifndef GRIDTREE_RefineI_H
#define GRIDTREE_RefineI_H

#include<cassert>
#include<vector>
#include<cmath>
#include<exception>
#include<iostream>
#include"Grid_Tree_Base.h"


namespace knoblauch {

 class Grid_Tree_Node_Refine_I : public Grid_Tree_Base {

 public:

   Grid_Tree_Node_Refine_I() = delete;
   Grid_Tree_Node_Refine_I(Grid_Tree_Base* i_pos, Grid_Tree_Base* i_neg) :
    Child_I_Pos(i_pos),
    Child_I_Neg(i_neg) {}

   virtual Grid_Tree_Base* refine_in_I() {
     std::cout << "Can't refine this block";
     std::terminate();
   };
   virtual Grid_Tree_Base* refine_in_J() {
     std::cout << "Can't refine this block";
     std::terminate();
   }
   virtual Grid_Tree_Base* refine_in_I_and_J() {
     std::cout << "Can't refine this block";
     std::terminate();
   }

 protected:
    std::unique_ptr<Grid_Tree_Base> Child_I_Pos;
    std::unique_ptr<Grid_Tree_Base> Child_I_Neg;
 };  
 

}

#endif

#ifndef GRIDTREE_RefineJ_H
#define GRIDTREE_RefineJ_H

#include<cassert>
#include<vector>
#include<cmath>
#include"Grid_Tree_Base.h"


namespace knoblauch {

 class Grid_Tree_Node_Refine_J : public Grid_Tree_Base {

 public:

    Grid_Tree_Node_Refine_J() = delete;
    Grid_Tree_Node_Refine_J(Grid_Tree_Base* j_pos, Grid_Tree_Base* j_neg);

   virtual Grid_Tree_Base* refine_in_I() {
     std::cout << "Can't refine this block";
     terminate();
   };
   virtual Grid_Tree_Base* refine_in_J() {
     std::cout << "Can't refine this block";
     terminate();
   }
   virtual Grid_Tree_Base* refine_in_I_and_J() {
     std::cout << "Can't refine this block";
     terminate();
   }

 protected:
    std::unique_ptr<Grid_Tree_Base> Child_J_Pos;
    std::unique_ptr<Grid_Tree_Base> Child_J_Neg;
   };
 }

#endif


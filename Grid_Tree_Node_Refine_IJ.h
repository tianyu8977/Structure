#ifndef GRIDTREE_RefineIJ_H
#define GRIDTREE_RefineIJ_H

#include<cassert>
#include<vector>
#include<cmath>
#include"Grid_Tree_Base.h"


namespace knoblauch {

 class Grid_Tree_Node_Refine_IJ : public Grid_Tree_Base {

 public:

   Grid_Tree_Node_Refine_IJ() = delete;
   Grid_Tree_Node_Refine_IJ(Grid_Tree_Base* i_pos_j_pos, Grid_Tree_Base* i_neg_j_pos, Grid_Tree_Base* i_pos_j_neg, Grid_Tree_Base* i_neg_j_neg);

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
    std::unique_ptr<Grid_Tree_Base> Child_I_Pos;
    std::unique_ptr<Grid_Tree_Base> Child_I_Neg;
    std::unique_ptr<Grid_Tree_Base> Child_J_Pos;
    std::unique_ptr<Grid_Tree_Base> Child_J_Neg;

   };

}

#endif

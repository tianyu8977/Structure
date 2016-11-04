#ifndef REFINE_BLOCK2D_IJ_H
#define REFINE_BLOCK2D_IJ_H

#include<cassert>
#include<vector>
#include<cmath>
#include"../Block_2D.h"

namespace knoblauch {

  struct Block2D_Refined_IJ {
    
    std::unique_ptr<Block_2D> i_neg_j_neg;
    std::unique_ptr<Block_2D> i_pos_j_neg;
    std::unique_ptr<Block_2D> i_neg_j_pos;
    std::unique_ptr<Block_2D> i_pos_j_pos;

  };

  Block2D_Refined_IJ Refine_Block2D_In_IJ(const Block_2D& block);

}

#endif 


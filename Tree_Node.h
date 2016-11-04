#ifndef TREE_NODE_H
#define TREE_NODE_H

#include<cassert>
#include<vector>
#include<memory>
#include"../Write_Solution_VTK.h"

namespace knoblauch {

  class Tree_Node {

  public:

  Tree_Node(const Solution_Block_2D& block_in) :
    block(new Solution_Block_2D(block_in)) {}

  Tree_Node(Solution_Block_2D&& block_in) :
    block(new Solution_Block_2D(std::move(block_in))) {}

  Tree_Node(const Solution_Block_2D& block_in, Tree_Node* parent_in) :
    block(new Solution_Block_2D(block_in)) {}
      //parent(parent_in) {}


  Tree_Node(Solution_Block_2D&& block_in, Tree_Node* parent_in) :
    block(new Solution_Block_2D(std::move(block_in))) {}
      //parent(parent_in) {}

  void refine_in_I();
  void refine_in_J();
  void refine_in_IJ();
  void Give_Variables();
  void Give_Variables_Test();
  void Auto_Refine();
  void Auto_Refine_Test();
  void Complete_Refinement();
  void Complete_Refinement_Test();
  int Write_All_VTK(int i);
  error_norms Compute_Errors();

  protected:

    std::unique_ptr<Solution_Block_2D> block;
    std::unique_ptr<Tree_Node> refined_i_pos;
    std::unique_ptr<Tree_Node> refined_i_neg;
    std::unique_ptr<Tree_Node> refined_j_pos;
    std::unique_ptr<Tree_Node> refined_j_neg;
    std::unique_ptr<Tree_Node> refined_ip_jp;
    std::unique_ptr<Tree_Node> refined_ip_jn;
    std::unique_ptr<Tree_Node> refined_in_jp;
    std::unique_ptr<Tree_Node> refined_in_jn;
    
    //std::shared_ptr<Tree_Node> parent;

  };

}

//////////////////////////////////////////////
//////////////////////////////////////////////
void knoblauch::Tree_Node::refine_in_I() {
  assert(block);
  Block2D_Refined_I blocks = Refine_Block2D_In_I(*block);
  refined_i_pos = std::unique_ptr<Tree_Node>( new Tree_Node(std::move(*blocks.i_pos),this) );
  refined_i_neg = std::unique_ptr<Tree_Node>( new Tree_Node(std::move(*blocks.i_neg),this) );
  block.reset();
}

void knoblauch::Tree_Node::refine_in_J() {
  assert(block);
  Block2D_Refined_J blocks = Refine_Block2D_In_J(*block);
  refined_j_pos = std::unique_ptr<Tree_Node>( new Tree_Node(std::move(*blocks.j_pos),this) );
  refined_j_neg = std::unique_ptr<Tree_Node>( new Tree_Node(std::move(*blocks.j_neg),this) );
  block.reset();
}

void knoblauch::Tree_Node::refine_in_IJ() {
  assert(block);
  Block2D_Refined_IJ blocks = Refine_Block2D_In_IJ(*block);
  refined_ip_jp = std::unique_ptr<Tree_Node>( new Tree_Node(std::move(*blocks.i_pos_j_pos),this) );
  refined_ip_jn = std::unique_ptr<Tree_Node>( new Tree_Node(std::move(*blocks.i_pos_j_neg),this) );
  refined_in_jp = std::unique_ptr<Tree_Node>( new Tree_Node(std::move(*blocks.i_neg_j_pos),this) );
  refined_in_jn = std::unique_ptr<Tree_Node>( new Tree_Node(std::move(*blocks.i_neg_j_neg),this) );
  block.reset();
}


void knoblauch::Tree_Node::Give_Variables() {
  if(block) {
    block->give_value();
  } else if(refined_i_pos) {
    refined_i_pos->Give_Variables();
    refined_i_neg->Give_Variables();
  } else if(refined_j_pos) {
    refined_j_pos->Give_Variables();
    refined_j_neg->Give_Variables();
  } else if(refined_ip_jp) {
    refined_ip_jp->Give_Variables();
    refined_ip_jn->Give_Variables();
    refined_in_jp->Give_Variables();
    refined_in_jn->Give_Variables();
  }
}

void knoblauch::Tree_Node::Give_Variables_Test() {
  if(block) {
    block->give_value_test();
  } else if(refined_i_pos) {
    refined_i_pos->Give_Variables_Test();
    refined_i_neg->Give_Variables_Test();
  } else if(refined_j_pos) {
    refined_j_pos->Give_Variables_Test();
    refined_j_neg->Give_Variables_Test();
  } else if(refined_ip_jp) {
    refined_ip_jp->Give_Variables_Test();
    refined_ip_jn->Give_Variables_Test();
    refined_in_jp->Give_Variables_Test();
    refined_in_jn->Give_Variables_Test();
  }
}

void knoblauch::Tree_Node::Complete_Refinement() {
  assert(block);
  Refinement_Flag judge = block->decide_refine();
  if(judge==Refinement_Flag::refine_i) {
    refine_in_I();
    Give_Variables();
  }
  if(judge==Refinement_Flag::refine_j) {
    refine_in_J();
    Give_Variables();
  }
  if(judge==Refinement_Flag::refine_ij) {
    refine_in_IJ();
    Give_Variables();
  }
  if(judge==Refinement_Flag::none){
    // std::cout<<"This block do not need to be refined"<<std::endl;
  }
}

void knoblauch::Tree_Node::Complete_Refinement_Test() {
  assert(block);
  Refinement_Flag judge = block->decide_refine_test();
  if(judge==Refinement_Flag::refine_i) {
    refine_in_I();
    Give_Variables_Test();
  }
  if(judge==Refinement_Flag::refine_j) {
    refine_in_J();
    Give_Variables_Test();
  }
  if(judge==Refinement_Flag::refine_ij) {
    refine_in_IJ();
    Give_Variables_Test();
  }
  if(judge==Refinement_Flag::none){
    // std::cout<<"This block do not need to be refined"<<std::endl;
  }
}

void knoblauch::Tree_Node::Auto_Refine() {
  if(block) {
    Complete_Refinement();
  } else if(refined_i_pos) {
    refined_i_pos->Auto_Refine();
    refined_i_neg->Auto_Refine();
  } else if(refined_j_pos) {
    refined_j_pos->Auto_Refine();
    refined_j_neg->Auto_Refine();
  } else if(refined_ip_jp) {
    refined_ip_jp->Auto_Refine();
    refined_ip_jn->Auto_Refine();
    refined_in_jp->Auto_Refine();
    refined_in_jn->Auto_Refine();
  }
}

void knoblauch::Tree_Node::Auto_Refine_Test() {
  if(block) {
    Complete_Refinement_Test();
  } else if(refined_i_pos) {
    refined_i_pos->Auto_Refine_Test();
    refined_i_neg->Auto_Refine_Test();
  } else if(refined_j_pos) {
    refined_j_pos->Auto_Refine_Test();
    refined_j_neg->Auto_Refine_Test();
  } else if(refined_ip_jp) {
    refined_ip_jp->Auto_Refine_Test();
    refined_ip_jn->Auto_Refine_Test();
    refined_in_jp->Auto_Refine_Test();
    refined_in_jn->Auto_Refine_Test();
  }
}

int knoblauch::Tree_Node::Write_All_VTK(int i) {
  std::stringstream name;
  name<<"grid"<<i<<".vts";
  if(block) {
    write_solution_vtk(*block,name.str());
    return ++i;
  } else if(refined_i_pos) {
    i = refined_i_neg->Write_All_VTK(i);
    i = refined_i_pos->Write_All_VTK(i);
    return i;
  } else if(refined_j_pos) {
    i = refined_j_neg->Write_All_VTK(i);
    i = refined_j_pos->Write_All_VTK(i);
    return i;
  } else if(refined_ip_jp) {
    i = refined_in_jn->Write_All_VTK(i);
    i = refined_ip_jn->Write_All_VTK(i);
    i = refined_in_jp->Write_All_VTK(i);
    i = refined_ip_jp->Write_All_VTK(i);
    return i;
  } else {
    std::cout <<"Error in Write_All_VTK.  Should not get here." <<std::endl;
    return -1;
  }  
}

knoblauch::error_norms knoblauch::Tree_Node::Compute_Errors() {
  if(block) {
    error_norms para = block->compute_errors();
    return para;
  } else if(refined_i_pos) {
    error_norms para_0 = refined_i_pos->Compute_Errors();
    error_norms para_1 = refined_i_neg->Compute_Errors();
    error_norms para_2;
    para_2.L1 = para_0.L1+para_1.L1;
    para_2.L2 = para_0.L2+para_1.L2;
    para_2.L_inf = std::max(para_0.L_inf,para_1.L_inf);
    para_2.num_cells = para_0.num_cells+para_1.num_cells;
    return para_2;
  } else if(refined_j_pos) {
    error_norms para_0 = refined_j_pos->Compute_Errors();
    error_norms para_1 = refined_j_neg->Compute_Errors();
    error_norms para_2;
    para_2.L1 = para_0.L1+para_1.L1;
    para_2.L2 = para_0.L2+para_1.L2;
    para_2.L_inf = std::max(para_0.L_inf,para_1.L_inf);
    para_2.num_cells = para_0.num_cells+para_1.num_cells;
    return para_2;
  } else {
    error_norms para_4;
    error_norms para_0 = refined_ip_jp->Compute_Errors();
    error_norms para_1 = refined_ip_jn->Compute_Errors();
    para_4.L_inf = std::max(para_0.L_inf,para_1.L_inf);
    error_norms para_2 = refined_in_jp->Compute_Errors();
    para_4.L_inf = std::max(para_4.L_inf,para_2.L_inf);
    error_norms para_3 = refined_in_jn->Compute_Errors();
    para_4.L_inf = std::max(para_4.L_inf,para_3.L_inf);
    para_4.L1 = para_0.L1+para_1.L1+para_2.L1+para_3.L1;
    para_4.L2 = para_0.L2+para_1.L2+para_2.L2+para_3.L2;
    para_4.num_cells = para_0.num_cells+para_1.num_cells+para_2.num_cells+para_3.num_cells;
    return para_4;
  }  
}


#endif
    

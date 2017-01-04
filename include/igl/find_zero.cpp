#include "find_zero.h"
#include "for_each.h"
#include "any.h"

template <typename AType, typename DerivedI>
IGL_INLINE void igl::find_zero(
  const Eigen::SparseMatrix<AType> & A,
  const int dim,
  Eigen::PlainObjectBase<DerivedI> & I)
{
  assert((dim == 1 || dim == 2) && "dim must be 2 or 1");
  // Get size of input
  int m = A.rows();
  int n = A.cols();
  // I starts by containing guess where 0 might be
  I = DerivedI::Zero(dim==1?n:m);
  Eigen::Array<bool,Eigen::Dynamic,1> found = 
    Eigen::Array<bool,Eigen::Dynamic,1>::Zero(dim==1?n:m);
  const auto func = [&I,&found,&dim](int i, int j, const int v)
  {
    if(dim == 2)
    {
      std::swap(i,j);
    }
    // Coded as if dim == 1, assuming swap for dim == 2
    // Have we already found a zero?
    if(!found(j))
    {
      if(I(j) != i || v == 0)
      {
        // either there was an implicit zero between the last element and this
        // one, or this one is zero
        found(j) = true;
      }else
      {
        // If not found, then guess that next element will be zero
        I(j) = I(j)+1;
      }
    }
  };
  for_each(A,func);
}
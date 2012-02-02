#ifndef IGL_PER_CORNER_NORMALS_H
#define IGL_PER_CORNER_NORMALS_H
#include "igl_inline.h"
#include <Eigen/Core>
#include <vector>

namespace igl
{
  // Compute vertex normals via vertex position list, face list
  // Inputs:
  //   V  #V by 3 eigen Matrix of mesh vertex 3D positions
  //   F  #F by 3 eigne Matrix of face (triangle) indices
  //   corner_threshold  threshold in degrees on sharp angles
  // Output:
  //   CN  #F*3 by 3 eigen Matrix of mesh vertex 3D normals, where the normal
  //     for corner F(i,j) is at CN(i*3+j,:) 
  template <typename DerivedV, typename DerivedF>
  IGL_INLINE void per_corner_normals(
                                     const Eigen::PlainObjectBase<DerivedV>& V,
                                     const Eigen::PlainObjectBase<DerivedF>& F,
                                     const double corner_threshold,
                                     Eigen::PlainObjectBase<DerivedV> & CN);
  // Other Inputs:
  //   FN  #F by 3 eigen Matrix of face normals
  //   VF  map from vertices to list of incident faces
  template <typename DerivedV, typename DerivedF, typename IndexType>
  IGL_INLINE void per_corner_normals(
                                     const Eigen::PlainObjectBase<DerivedV>& V,
                                     const Eigen::PlainObjectBase<DerivedF>& F,
                                     const Eigen::PlainObjectBase<DerivedV>& FN,
                                     const std::vector<std::vector<IndexType> >& VF,
                                     const double corner_threshold,
                                     Eigen::PlainObjectBase<DerivedV> & CN);
}

#ifdef IGL_HEADER_ONLY
#  include "per_corner_normals.cpp"
#endif

#endif

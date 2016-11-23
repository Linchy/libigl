#include "qslim_optimal_collapse_edge_callbacks.h"
#include "quadric_binary_plus_operator.h"
#include <Eigen/LU>

IGL_INLINE void igl::qslim_optimal_collapse_edge_callbacks(
  Eigen::MatrixXi & E,
  std::vector<std::tuple<Eigen::MatrixXd,Eigen::RowVectorXd,double> > & 
    quadrics,
  int & v1,
  int & v2,
  std::function<void(
    const int e,
    const Eigen::MatrixXd &,
    const Eigen::MatrixXi &,
    const Eigen::MatrixXi &,
    const Eigen::VectorXi &,
    const Eigen::MatrixXi &,
    const Eigen::MatrixXi &,
    double &,
    Eigen::RowVectorXd &)> & cost_and_placement,
  std::function<bool(const int)> & pre_collapse,
  std::function<void(const int,const bool)> & post_collapse)
{
  typedef std::tuple<Eigen::MatrixXd,Eigen::RowVectorXd,double> Quadric;
  cost_and_placement = [&quadrics,&v1,&v2](
    const int e,
    const Eigen::MatrixXd & V,
    const Eigen::MatrixXi & /*F*/,
    const Eigen::MatrixXi & E,
    const Eigen::VectorXi & /*EMAP*/,
    const Eigen::MatrixXi & /*EF*/,
    const Eigen::MatrixXi & /*EI*/,
    double & cost,
    Eigen::RowVectorXd & p)
  {
    // Combined quadric
    Quadric quadric_p;
    quadric_p = quadrics[E(e,0)] + quadrics[E(e,1)];
    // Quadric: p'Ap + 2b'p + c
    // optimal point: Ap = -b, or rather because we have row vectors: pA=-b
    const auto & A = std::get<0>(quadric_p);
    const auto & b = std::get<1>(quadric_p);
    const auto & c = std::get<2>(quadric_p);
    p = -b*A.inverse();
    cost = p.dot(p*A) + 2*p.dot(b) + c;
    // Force infs and nans to infinity
    if(isinf(cost) || cost!=cost)
    {
      cost = std::numeric_limits<double>::infinity();
    }
  };
  // Remember endpoints
  pre_collapse = [&v1,&v2,&E](const int e)->bool
  {
    v1 = E(e,0);
    v2 = E(e,1);
    return true;
  };
  // update quadric
  post_collapse = [&v1,&v2,&quadrics](
    const int e, 
    const bool collapsed)
  {
    if(collapsed)
    {
      quadrics[v1<v2?v1:v2] = quadrics[v1] + quadrics[v2];
    }
  };
}

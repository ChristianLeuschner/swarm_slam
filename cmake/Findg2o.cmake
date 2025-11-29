# Findg2o.cmake
# Find the g2o includes and libraries

find_path(G2O_INCLUDE_DIR NAMES g2o/core/base_vertex.h
  PATHS /usr/include /usr/local/include
)

# Wir suchen nach den wichtigsten Libraries
find_library(G2O_CORE_LIB NAMES g2o_core)
find_library(G2O_STUFF_LIB NAMES g2o_stuff)
find_library(G2O_TYPES_SBA_LIB NAMES g2o_types_sba)
find_library(G2O_SOLVER_CHOLMOD_LIB NAMES g2o_solver_cholmod)
find_library(G2O_SOLVER_CSPARSE_LIB NAMES g2o_solver_csparse)
find_library(G2O_SOLVER_DENSE_LIB NAMES g2o_solver_dense)
find_library(G2O_SOLVER_EIGEN_LIB NAMES g2o_solver_eigen)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(g2o DEFAULT_MSG
  G2O_INCLUDE_DIR G2O_CORE_LIB G2O_STUFF_LIB G2O_TYPES_SBA_LIB)

if(g2o_FOUND)
  set(g2o_INCLUDE_DIRS ${G2O_INCLUDE_DIR})
  set(g2o_LIBRARIES 
    ${G2O_CORE_LIB} 
    ${G2O_STUFF_LIB} 
    ${G2O_TYPES_SBA_LIB}
    ${G2O_SOLVER_CHOLMOD_LIB}
    ${G2O_SOLVER_CSPARSE_LIB}
    ${G2O_SOLVER_DENSE_LIB}
    ${G2O_SOLVER_EIGEN_LIB}
  )
endif()
/**
 * \file error.hpp
 * \brief handles error very basically
 */

inline void error_handler(std::string err_msg="ERROR"){
  std::cerr << err_msg << std::endl;
  exit(1);
}

/**
 * \file error.hpp
 * \brief handles error very basically
 */

inline void error_handler() {
  std::cerr << "ERROR" << std::endl;
  exit(1);
}

inline void error_handler(std::string err_msg){
  std::cerr << err_msg << std::endl;
  exit(1);
}

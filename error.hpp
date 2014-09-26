/**
 * \file error.hpp
 * \brief handles error very basically
 */

inline void error_handler(std::string err_msg=""){
  if (err_msg == "") {
    std::cerr << "ERROR" << std::endl;
  } else {
    std::cerr << "ERROR: " << err_msg <<std::endl;
  }
  exit(1);
}

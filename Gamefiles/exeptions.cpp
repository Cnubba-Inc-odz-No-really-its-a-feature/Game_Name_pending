#include "exeptions.hpp"


unknown_pos::unknown_pos(const char c) { msg = c; };

const char* unknown_pos::what() const noexcept {
  std::cerr << "unknown_pos";
  return msg.c_str();
};


unknown_rad::unknown_rad(const char *msg) : msg(msg){};

const char* unknown_rad::what() const noexcept {
  std::cerr << "unknown_red";
  return msg;
};


unknown_color::unknown_color(const char *msg) : msg(msg){};

const char* unknown_color::what() const noexcept {
  std::cerr << "unknown_color";
  return msg;
};


end_of_file::end_of_file(const char *msg) : msg("eof"){};

const char* end_of_file::what() const noexcept { return msg; };


unknown_shape::unknown_shape(const char *msg) : msg(msg){};

const char* unknown_shape::what() const noexcept {
  std::cerr << "unknown_shape";
  return msg;
};

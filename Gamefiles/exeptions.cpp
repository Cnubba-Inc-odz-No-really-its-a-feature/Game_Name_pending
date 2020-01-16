#include "exeptions.hpp"


end_of_textures::end_of_textures(const char *c) {msg = c;};

const char* end_of_textures::what() const noexcept {
  return msg.c_str();
};

invalid_type::invalid_type(const char *c) {msg = c;};

const char* invalid_type::what() const noexcept {
  return msg.c_str();
};


unknown_textureKey::unknown_textureKey(const char *c) {msg = c;};

const char* unknown_textureKey::what() const noexcept {
  return msg.c_str();
};


unknown_pos::unknown_pos(const char c) { msg = c; };

const char* unknown_pos::what() const noexcept {
  return msg.c_str();
};


unknown_rad::unknown_rad(const char *msg) : msg(msg){};

const char* unknown_rad::what() const noexcept {
  return msg;
};


unknown_color::unknown_color(const char *msg) : msg(msg){};

const char* unknown_color::what() const noexcept {
  return msg;
};


end_of_file::end_of_file(const char *msg) : msg("eof"){};

const char* end_of_file::what() const noexcept { return msg; };


unknown_shape::unknown_shape(const char *msg) : msg(msg){};

const char* unknown_shape::what() const noexcept {
  return msg;
};
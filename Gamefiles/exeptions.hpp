#include <exception>
#include <iostream>
#include <string>

#ifndef EXEPTIONS_HPP
#define EXEPTIONS_HPP

/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class problem : public std::exception{

};

/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class invalid_UnitLane : public problem{
private:
  std::string msg;
public:
  invalid_UnitLane(std::string c);
  const char *what() const noexcept;
};

/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class invalid_Factory_Binds : public problem{
private:
  std::string msg;
public:
  invalid_Factory_Binds(const char *c);
  const char *what() const noexcept;
};

/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class end_of_textures : public problem{
private:
  std::string msg;
public:
  end_of_textures(const char *c);
  const char *what() const noexcept;  
};


/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class invalid_type : public problem{
private:
  std::string msg;
public:
  invalid_type(const char *c);
  const char *what() const noexcept;  
};

/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class unknown_textureKey : public problem{
private:
  std::string msg;
public:
  unknown_textureKey(const char *c);
  const char *what() const noexcept;  
};

/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class unknown_pos : public problem {
 private:
  std::string msg;

 public:
  unknown_pos(const char c);
  const char *what() const noexcept;
};

/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class unknown_rad : public problem {
 private:
  const char *msg;

 public:
  unknown_rad(const char *msg);
  const char *what() const noexcept;
};

/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class unknown_color : public problem {
 private:
  const char *msg;

 public:
  unknown_color(const char *msg);
  const char *what() const noexcept;
};

/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class end_of_file : public std::exception {
 private:
  const char *msg;

 public:
  end_of_file(const char *msg);
  const char *what() const noexcept;
};

/// \brief
/// Specific exceptions for better debug understanding and propper object factory functioning
class unknown_shape : public problem {
 private:
  const char *msg;

 public:
  unknown_shape(const char *msg);
  const char *what() const noexcept;
};

#endif  // EXEPTIONS_HPP
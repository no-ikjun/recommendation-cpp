#ifndef DATA_H
#define DATA_H

#define DIMENSION 20 // TODO: 

#include <string>
#include <array>

// Abstract class for any data type
class Data {
protected:
  Data(std::string id, std::string content);
  std::string getId();
  virtual std::string getContent() = 0;
  virtual void vectorEmbed() = 0;
private:
  std::string id;
  std::string content;
  std::array<double, DIMENSION> vectorEmbedding;
};

#endif
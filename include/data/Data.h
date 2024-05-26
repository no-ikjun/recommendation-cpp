#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>

// Abstract class for any data type
class Data {
protected:
  Data(std::string id, std::string content);

  std::string getId() const;
  void setId(std::string);

  virtual std::string getContent() = 0;
  void setContent(std::string);
  
  std::vector<double>& getFeatureVector() const;
  virtual void vectorEmbed() = 0;

private:
  std::string id;
  std::string content;
  std::vector<double> featureVector;
};

#endif
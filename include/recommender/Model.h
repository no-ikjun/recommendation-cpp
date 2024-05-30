#ifndef MODEL_H
#define MODEL_H

class Model {
public: 
  virtual std::vector<double> embed(std::string) = 0;
};

#endif
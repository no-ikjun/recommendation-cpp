#ifndef NEWSDATABASE_H
#define NEWSDATABASE_H

#include "db/Database.h"
#include "data/News.h"
#include <string>
#include <vector>

class NewsDatabase : public Database {
private:
  std::string filename;  // 뉴스 데이터를 저장할 파일 이름

public:
  // 생성자: 파일 이름을 사용하여 NewsDatabase를 초기화합니다.
  explicit NewsDatabase(const std::string& filename);

  // add 함수 구현: News 객체를 파일에 추가합니다.
  void add(void* item) override;

  // get 함수: 주어진 ID에 해당하는 뉴스를 반환합니다.
  News get(std::string id);

  // saveToFile 함수: 주어진 News 객체를 파일에 저장합니다.
  void saveToFile(const News& news);

  // loadFromFile 함수: 파일로부터 모든 뉴스를 불러와 std::vector<News>로 반환합니다.
  std::vector<News> loadFromFile();

  // 소멸자
  virtual ~NewsDatabase() {}
};

#endif // NEWSDATABASE_H

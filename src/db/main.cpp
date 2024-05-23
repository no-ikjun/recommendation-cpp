#include <iostream>
#include "../../lib/news/News.h"
#include "../../lib/category/Category.h"
#include "./database/include/NewsDatabase.h"
#include "./database/include/Logger.h"

int main() {
    // 데이터베이스 및 로거 인스턴스 생성
    NewsDatabase db;
    Logger logger;

    // 로거를 데이터베이스에 옵저버로 추가
    db.addObserver(&logger);

    // 샘플 뉴스 카테고리 생성
    Category techCategory("Technology");

    // 샘플 뉴스 항목 생성 및 데이터베이스에 추가
    News news1("1", "AI Advances", "New AI algorithms have been developed.", techCategory);
    db.add(&news1);

    // 샘플 뉴스 항목 갱신
    News updatedNews1("1", "AI Advances", "New AI algorithms show promising results in trials.", techCategory);
    db.update(&updatedNews1);

    return 0;
}

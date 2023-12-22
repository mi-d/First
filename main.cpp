#include <iostream>
#include <vector>
#include <string>
#include <iomanip>


class ReadingManager {
public:

    static const int MAX_USER_COUNT = 100001;
    static const int MAX_PAGE_NUMBER = 1000;

    ReadingManager() : users_pages_count_(MAX_PAGE_NUMBER, 0), user_page_(MAX_USER_COUNT, 0) {}

    void Read(int user_id, int page);
    double Cheer(int user_id);

private:
    int readers_ = 0;
    std::vector<int> users_pages_count_;
    std::vector<unsigned int> user_page_;
};

void ReadingManager::Read(int user_id, int page) {

    int prev_page_count = 0;

    user_page_[user_id] ? prev_page_count = user_page_[user_id] : ++readers_;

    user_page_[user_id] = page;
    for (int i = prev_page_count; i < page; ++i) {
        users_pages_count_[i] += 1;
    }
}

double ReadingManager::Cheer(int user_id) {
    int page_count = user_page_[user_id];
    if (!page_count) {
        return 0.0;
    }
    if (readers_ == 1) {
        return 1.0;
    }
    return (readers_ - users_pages_count_[page_count - 1]) * 1.0 / (readers_ - 1.0);
}

void RequestHandler(std::istream& input, std::ostream& output, ReadingManager& ebook) {

    std::string str;
    getline(input, str);
    int requests_count = std::stoi(str);
    for (int i = 0; i < requests_count; ++i) {
        std::string request_type;
        getline(input, request_type, ' ');
        if (request_type == "READ") {
            std::string user_id;
            getline(input, user_id, ' ');
            std::string pages;
            getline(input, pages);
            ebook.Read(std::stoi(user_id), std::stoi(pages));
        } else {
            std::string user_id;
            getline(input, user_id);
            output << std::setprecision(6) << ebook.Cheer(std::stoi(user_id)) << std::endl;
        }
    }
}

int main() {
    ReadingManager ebook;
    RequestHandler(std::cin, std::cout, ebook);
}
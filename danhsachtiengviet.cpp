#include <iostream>
#include <cstring>
using namespace std;

// Định nghĩa cấu trúc một node
struct WordNode {
    char word[50];   // Từ (lưu dưới dạng chuỗi ký tự)
    WordNode* next;  // Con trỏ tới node tiếp theo

    // Hàm khởi tạo
    WordNode(const char* w) : next(nullptr) {
        strncpy(word, w, sizeof(word));
        word[sizeof(word) - 1] = '\0'; // Đảm bảo kết thúc chuỗi
    }
};

// Định nghĩa danh sách liên kết đơn
struct WordList {
    WordNode* head;

    // Khởi tạo danh sách rỗng
    WordList() : head(nullptr) {}

    // Thêm một từ vào danh sách
    void addWord(const char* word) {
        WordNode* newNode = new WordNode(word);
        if (!head) {
            head = newNode;
        } else {
            WordNode* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // Xác định từ xuất hiện nhiều nhất
    const char* findMostFrequentWord() {
        if (!head) return nullptr;

        WordNode* current = head;
        int maxCount = 0;
        const char* mostFrequent = nullptr;

        while (current) {
            int count = 0;
            WordNode* temp = head;
            while (temp) {
                if (strcmp(current->word, temp->word) == 0) {
                    count++;
                }
                temp = temp->next;
            }
            if (count > maxCount) {
                maxCount = count;
                mostFrequent = current->word;
            }
            current = current->next;
        }
        return mostFrequent;
    }

    // Loại bỏ một từ nếu từ láy xuất hiện
    void removeRedundantRepeats() {
        if (!head) return;

        WordNode* current = head;
        WordNode* prev = nullptr;

        while (current) {
            if (prev && strcmp(prev->word, current->word) == 0) {
                prev->next = current->next;
                delete current;
                current = prev->next;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    // Đếm số từ vựng trong danh sách
    int countUniqueWords() {
        if (!head) return 0;

        int count = 0;
        WordNode* current = head;

        while (current) {
            bool isUnique = true;
            WordNode* temp = head;
            while (temp != current) {
                if (strcmp(temp->word, current->word) == 0) {
                    isUnique = false;
                    break;
                }
                temp = temp->next;
            }
            if (isUnique) {
                count++;
            }
            current = current->next;
        }
        return count;
    }

    // Hiển thị các từ trong danh sách
    void displayWords() {
        WordNode* current = head;
        while (current) {
            cout << current->word << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Giải phóng bộ nhớ
    ~WordList() {
        while (head) {
            WordNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Hàm kiểm tra chương trình
int main() {
    WordList wordList;

    // Thêm các từ vào danh sách
    wordList.addWord("xanh");
    wordList.addWord("xanh");
    wordList.addWord("đỏ");
    wordList.addWord("vàng");
    wordList.addWord("xanh");
    wordList.addWord("vàng");

    cout << "Danh sách các từ ban đầu:\n";
    wordList.displayWords();

    // Xác định từ xuất hiện nhiều nhất
    const char* mostFrequent = wordList.findMostFrequentWord();
    if (mostFrequent) {
        cout << "Từ xuất hiện nhiều nhất: " << mostFrequent << endl;
    }

    // Loại bỏ từ láy
    wordList.removeRedundantRepeats();
    cout << "Danh sách sau khi loại bỏ từ láy:\n";
    wordList.displayWords();

    // Đếm số từ vựng
    int uniqueCount = wordList.countUniqueWords();
    cout << "Số từ vựng duy nhất: " << uniqueCount << endl;

    return 0;
}

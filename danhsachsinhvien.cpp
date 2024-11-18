#include <iostream>
#include <ctime>
#include <iomanip>
#include <cstring>
using namespace std;

// Định nghĩa cấu trúc của một node
struct FileNode {
    char fileName[100];   // Tên file
    double fileSize;      // Kích thước file (tính bằng GB)
    time_t createdTime;   // Thời gian tạo file
    FileNode* next;       // Con trỏ tới node tiếp theo

    // Hàm khởi tạo
    FileNode(const char* name, double size, time_t time) 
        : fileSize(size), createdTime(time), next(nullptr) {
        strncpy(fileName, name, sizeof(fileName));
        fileName[sizeof(fileName) - 1] = '\0'; // Đảm bảo kết thúc chuỗi
    }
};

// Định nghĩa danh sách liên kết đơn
struct FileList {
    FileNode* head;

    // Khởi tạo danh sách rỗng
    FileList() : head(nullptr) {}

    // Hàm thêm file theo thứ tự thời gian
    void addFile(const char* fileName, double fileSize, time_t createdTime) {
        FileNode* newNode = new FileNode(fileName, fileSize, createdTime);
        if (!head || difftime(head->createdTime, createdTime) > 0) {
            newNode->next = head;
            head = newNode;
        } else {
            FileNode* current = head;
            while (current->next && difftime(current->next->createdTime, createdTime) < 0) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Tính tổng kích thước các file trong thư mục
    double calculateTotalSize() {
        double totalSize = 0.0;
        FileNode* current = head;
        while (current) {
            totalSize += current->fileSize;
            current = current->next;
        }
        return totalSize;
    }

    // Xóa file có kích thước nhỏ nhất
    void removeSmallestFile() {
        if (!head) return;

        FileNode* current = head;
        FileNode* prev = nullptr;
        FileNode* smallest = head;
        FileNode* smallestPrev = nullptr;

        while (current) {
            if (current->fileSize < smallest->fileSize) {
                smallest = current;
                smallestPrev = prev;
            }
            prev = current;
            current = current->next;
        }

        if (smallestPrev) {
            smallestPrev->next = smallest->next;
        } else {
            head = smallest->next;
        }

        delete smallest;
    }

    // Sao lưu file vào USB (tối đa 32GB)
    void backupToUSB(double usbSize = 32.0) {
        while (calculateTotalSize() > usbSize) {
            removeSmallestFile();
        }
    }

    // Hiển thị danh sách file
    void displayFiles() {
        FileNode* current = head;
        while (current) {
            cout << "File: " << current->fileName
                 << ", Size: " << fixed << setprecision(2) << current->fileSize << " GB"
                 << ", Created Time: " << ctime(&current->createdTime);
            current = current->next;
        }
    }

    // Giải phóng bộ nhớ
    ~FileList() {
        while (head) {
            FileNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Hàm kiểm tra
int main() {
    FileList fileList;

    // Thêm file vào danh sách
    fileList.addFile("file1.txt", 1.5, time(nullptr) - 1000); // File cũ hơn
    fileList.addFile("file2.txt", 0.8, time(nullptr) - 500);  // File mới hơn
    fileList.addFile("file3.txt", 5.2, time(nullptr));        // File mới nhất

    cout << "Danh sách file ban đầu:\n";
    fileList.displayFiles();

    // Tính tổng kích thước
    cout << "\nTổng kích thước file: " << fileList.calculateTotalSize() << " GB\n";

    // Sao lưu file vào USB
    cout << "\nSao lưu vào USB (tối đa 32GB)...\n";
    fileList.backupToUSB();

    // Hiển thị danh sách sau khi sao lưu
    cout << "\nDanh sách file sau khi sao lưu:\n";
    fileList.displayFiles();

    return 0;
}

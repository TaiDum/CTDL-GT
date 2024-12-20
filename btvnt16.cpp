#include <iostream>
#include <string>
using namespace std;

struct Node {
    string title;         // tieu de
    int page;             // so trang
    string type_of_node;  // the loai
    Node* children[10];   // mang con tro chua cac muc con
    int child_count;      // so luong muc con cua node hien tai

    // khoi tao
    Node(string t, int p, string type) {
        title = t;
        page = p;
        type_of_node = type;
        child_count = 0;  // ban dau khong co muc con
    }

    // ham tao muc con
    void add_child(Node* child) {
        if (child_count < 10) {
            children[child_count++] = child;
        } else {
            cout << "So muc con da dat toi da!" << endl;
        }
    }

    // cap nhat so trang 
    void update_pages(int page_offset) {
        page += page_offset;
        for (int i = 0; i < child_count; i++) {
            children[i]->update_pages(page_offset);
        }
    }

    // xoa mot muc con va cap nhat lai so trang
    bool delete_child(string target_title) {
        for (int i = 0; i < child_count; i++) {
            if (children[i]->title == target_title) {
                // di chuyen cac muc con len
                for (int j = i; j < child_count - 1; j++) {
                    children[j] = children[j + 1];
                }
                child_count--;  // giam so luong muc con
                return true;  // tra ve dung
            }
        }
        return false;  // tra ve khong tim thay
    }

    // xac dinh so chuong trong sach
    int count_chapters() {
        int count = 0;
        if (type_of_node == "chapter") {
            count = 1;
        }
        for (int i = 0; i < child_count; i++) {
            count += children[i]->count_chapters();
        }
        return count;
    }

    // tim chuong dai nhat
    Node* find_longest_chapter() {
        Node* longest = NULL;
        for (int i = 0; i < child_count; i++) {
            if (children[i]->type_of_node == "chapter") {
                if (longest == NULL || children[i]->page > longest->page) {
                    longest = children[i];
                }
            }
            Node* sub_longest = children[i]->find_longest_chapter();
            if (sub_longest != NULL && (longest == NULL || sub_longest->page > longest->page)) {
                longest = sub_longest;
            }
        }
        return longest;
    }
};

int main() {
    // Tao cac node
    Node root("Book", 1, "root");
    Node chapter1("Chapter 1", 1, "chapter");
    Node chapter2("Chapter 2", 30, "chapter");
    Node section1("Section 1.1", 5, "section");
    Node subsection1("Subsection 1.1.1", 6, "subsection");
    Node subsection2("Subsection 1.1.2", 10, "subsection");

    // cau truc cay
    root.add_child(&chapter1);
    root.add_child(&chapter2);
    chapter1.add_child(&section1);
    section1.add_child(&subsection1);
    section1.add_child(&subsection2);

    // xac dinh so chuong
    cout << "Sach co " << root.count_chapters() << " chuong!" << endl;

    // Tim chuong dai nhat
    Node* longest_chapter = root.find_longest_chapter();
    if (longest_chapter != NULL) {
        cout << "Chuong dai nhat la: " << longest_chapter->title << " co so trang: " << longest_chapter->page << endl;
    } else {
        cout << "Khong tim thay chuong." << endl;
    }

    // Xoa mot muc
    cout << "Xoa muc Subsection 1.1.1..." << endl;
    if (section1.delete_child("Subsection 1.1.1")) {
        cout << "Xoa thanh cong." << endl;
    } else {
        cout << "Khong tim thay muc de xoa." << endl;
    }

    // Kiem tra lai sau khi xoa
    cout << "Sau khi xoa sach con lai  " << root.count_chapters() << " chuong!" << endl;

    return 0;
}

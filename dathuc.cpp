#include <iostream>
using namespace std;

struct node {
    int soMu;
    double heSo;
    node *next;

    node(double heSoMoi, int soMuMoi) : heSo(heSoMoi), soMu(soMuMoi), next(NULL) {}
};

class daThuc {
private:
    node *head;

public:
    daThuc() : head(NULL) {} 

    void nhap() {
        int n;
        cout << "Nhap so luong phan tu: ";
        cin >> n;

        for (int i = 0; i < n; i++) {
            double heSo; 
            int soMu;
            cout << "Nhap he so va so mu: ";
            cin >> heSo >> soMu;

            if (heSo != 0) {
                node *newNode = new node(heSo, soMu);
                newNode->next = head;
                head = newNode;
            }
        }
    }

    void in() {
        node *current = head;
        if (!current) {
            cout << "Da thuc rong!" << endl;
            return;
        }
        while (current) {
            cout << current->heSo << "x^" << current->soMu;
            if (current->next) {
                cout << " + ";
            }
            current = current->next;
        }
        cout << endl;
    }

    ~daThuc() { 
        while (head) {
            node *temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    daThuc dt;
    dt.nhap();
    cout << "Da thuc da nhap: ";
    dt.in();
    return 0;
}

#include <iostream>
#include <queue>
#include <string>

using namespace std;

// Cấu trúc Node đại diện cho một giỏ hàng
struct Node {
    string product;  // Tên sản phẩm[]\=
    int quantity;    // Số lượng sản phẩm
    double price;    // Giá mỗi sản phẩm
    double total;    // Tổng giá trị của giỏ hàng (quantity * price)

    // Hàm khởi tạo node
    Node(string p, int q, double pr) {
        product = p;
        quantity = q;
        price = pr;
        total = quantity * price;
    }
};

// Hàm tính tổng số tiền thu được từ tất cả các giỏ hàng
double calculateTotal(queue<Node>& q) {
    double totalAmount = 0.0;
    queue<Node> tempQueue = q;  // Tạo một bản sao của hàng đợi để duyệt
    while (!tempQueue.empty()) {
        totalAmount += tempQueue.front().total;
        tempQueue.pop();
    }
    return totalAmount;
}

// Hàm đếm số lượng sản phẩm A bán được
int countProductA(queue<Node>& q) {
    int count = 0;
    queue<Node> tempQueue = q;  // Tạo một bản sao của hàng đợi để duyệt
    while (!tempQueue.empty()) {
        if (tempQueue.front().product == "A") {
            count += tempQueue.front().quantity;
        }
        tempQueue.pop();
    }
    return count;
}

// Hàm xử lý thanh toán cho một khách hàng
void processPayment(queue<Node>& q) {
    if (!q.empty()) {
        cout << "Khach hang thanh toan xong: " << q.front().product
             << ", So luong: " << q.front().quantity
             << ", Tong tien: " << q.front().total << endl;
        q.pop();  // Loai bo khách hàng khỏi hàng đợi
    } else {
        cout << "Hàng đợi rỗng!" << endl;
    }
}

int main() {
    queue<Node> q;  // Khai báo hàng đợi

    // Thêm các giỏ hàng vào hàng đợi
    q.push(Node("A", 5, 10.0));  
    q.push(Node("B", 3, 20.0));  
    q.push(Node("A", 2, 10.0));  
    q.push(Node("C", 1, 50.0)); 

    // Xử lý thanh toán cho các khách hàng
    processPayment(q);
    processPayment(q);

    // Tính tổng số tiền thu được từ các giỏ hàng còn lại
    double totalAmount = calculateTotal(q);
    cout << "Tong so tien thu duoc: " << totalAmount << endl;

    // Đếm số lượng sản phẩm A đã bán
    int countA = countProductA(q);
    cout << "So luong san pham A da ban: " << countA << endl;

    return 0;
}

#include <iostream>
using namespace std;

struct Node {
    int data;      // dâta cua node
    Node* left;    // con trai
    Node* right;   // con phai
    int height;    // chieu cao

    Node(int value) {
        data = value;
        left = right = NULL;
        height = 1;  // node co chieu cao la 1
    }
};

// ham tinh chieu cao cua node
int height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// ham tinh do checnh lech cua node
int balanceFactor(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Ham cap nhat chieu cao cua node
void updateHeight(Node* node) {
    node->height = (height(node->left) > height(node->right) ? height(node->left) : height(node->right)) + 1;
}

// Ham xoay trai
Node* rotateLeft(Node* z) {
    Node* y = z->right;
    z->right = y->left;
    y->left = z;
    updateHeight(z);  // cap nhat lai chieu cao cua z
    updateHeight(y);  // cap nhat lai chieu cao cua y
    return y;
}

// Ham xoay phai
Node* rotateRight(Node* z) {
    Node* y = z->left;
    z->left = y->right;
    y->right = z;
    updateHeight(z);  // cap nhat lai chieu cao cua z
    updateHeight(y);  // cap nhat lai chieu cao cua y
    return y;
}

// Ham xoay trai phai
Node* rotateLeftRight(Node* z) {
    z->left = rotateLeft(z->left);
    return rotateRight(z);
}

// Ham xoay phai trai
Node* rotateRightLeft(Node* z) {
    z->right = rotateRight(z->right);
    return rotateLeft(z);
}

// Them node vao AVL
Node* insert(Node* root, int key) {
    if (root == NULL) {
        return new Node(key);
    }

    // add data
    if (key < root->data) {
        root->left = insert(root->left, key);
    } else if (key > root->data) {
        root->right = insert(root->right, key);
    } else {
        return root;  // Gia tri trung thi khong chen
    }

    // Cap nhat chieu cao cua node bay gio
    updateHeight(root);

    // Check can bang chua
    int balance = balanceFactor(root);

    // Can bang sau khi chen trai
    if (balance > 1 && key < root->left->data) {
        return rotateRight(root);
    }

    // Can bang sau khi chen phai
    if (balance < -1 && key > root->right->data) {
        return rotateLeft(root);
    }

    // Can bang sau khi chen vao con phai cua trai
    if (balance > 1 && key > root->left->data) {
        return rotateLeftRight(root);
    }

    // caan bang chen vao trai cua con phai
    if (balance < -1 && key < root->right->data) {
        return rotateRightLeft(root);
    }

    return root;
}

// ham in 
void inOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    inOrder(root->left);       // duyet trai
    cout << root->data << " "; // in data
    inOrder(root->right);      // duyet phai
}

// tim chieu cao cua cay
int getHeight(Node* root) {
    return height(root);
}

int main() {
    Node* root = NULL;

    // Nhap mot day so de tao cay avl
    int n;
    cout << "So phan tu cua cay AVL: ";
    cin >> n;

    cout << "Nhap data cho node: ";
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        root = insert(root, num); // CHen gtri vao node cua cay
    }

    // in cay
    cout << "Cay AVL la: ";
    inOrder(root);
    cout << endl;

    // chieu cao cayy
    cout << "Chieu cao cua cay AVL la: " << getHeight(root) << endl;

    return 0;
}

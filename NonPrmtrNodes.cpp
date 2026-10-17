#include <iostream>
#include <string>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value, Node* l = nullptr, Node* r = nullptr) {
        data = value;
        left = l;
        right = r;
    }
};

class BinaryTree {
private:
    Node* root;
    void printNonPerimeter(Node* node, bool isLeftBorder, bool isRightBorder) {
        
        if(!node) return;
        printNonPerimeter(node->left,isLeftBorder,isRightBorder && node->right == nullptr);
        if (!isLeftBorder && !isRightBorder && (node->left != nullptr || node->right != nullptr)) cout << node->data << ' ';
        printNonPerimeter(node->right,isLeftBorder && node->left == nullptr,isRightBorder);
        
    }

public:
    BinaryTree() {
        root = nullptr;
    }

    void setRoot(Node* node) {
        root = node;
    }

    void printNonPerimeter() {
        printNonPerimeter(root, true, true);
        cout << endl;
    }
};

void runTest(int id, Node* root, const string& expected) {
    BinaryTree tree;
    tree.setRoot(root);

    cout << "===== TEST " << id << " =====" << endl;

    cout << "Salida:   ";
    tree.printNonPerimeter();

    cout << "Esperado: " << expected << endl;
    cout << endl;
}

int main() {

    /*
                                            50
                                   /               \
                          30                               70
                    /           \                       /     \
              20                      40             60          80
           /     \                 /   \           /  \        /    \
        10          25          35       45       55    65    75       90
         \        /  \        /  \              /                    /
           15    22    28    32    38          52                   85
    */
    Node* t1 = new Node(50,
        new Node(30,
            new Node(20,
                new Node(10, nullptr, new Node(15)),
                new Node(25, new Node(22), new Node(28))),
            new Node(40,
                new Node(35, new Node(32), new Node(38)),
                new Node(45))),
        new Node(70,
            new Node(60,
                new Node(55, new Node(52), nullptr),
                new Node(65)),
            new Node(80,
                new Node(75),
                new Node(90, new Node(85), nullptr))));

    runTest(1, t1, "25 35 40 55 60");


    /*
                                    8
                            /               \
                    4                               12
                /       \                       /       \
            2               6               10              14
          /   \           /   \           /   \           /   \
        1       3       5       7       9       11      13      15
    */
    Node* t2 = new Node(8,
        new Node(4,
            new Node(2, new Node(1), new Node(3)),
            new Node(6, new Node(5), new Node(7))),
        new Node(12,
            new Node(10, new Node(9), new Node(11)),
            new Node(14, new Node(13), new Node(15))));

    runTest(2, t2, "6 10");


    /*
                    10
                /     \
            5           15
          /   \           \
        2       7           20
    */
    Node* t3 = new Node(10,
        new Node(5, new Node(2), new Node(7)),
        new Node(15, nullptr, new Node(20)));

    runTest(3, t3, "(nada)");


    Node* t4 = new Node(10);

    runTest(4, t4, "(nada)");


    runTest(5, nullptr, "(nada)");


    /*
                    10
                  /
                5
              /
            3
          /
        1
    */
    Node* t6 = new Node(10,
        new Node(5,
            new Node(3,
                new Node(1))));

    runTest(6, t6, "(nada)");

    return 0;
}

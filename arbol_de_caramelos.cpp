#include <iostream>
using namespace std;


struct Node
{
    Node(int v)
    {
        val = v;
        balance = 0;
        mov = false;
        left = right = 0;
    }
    int val, balance;
    bool mov;
    Node *left, *right;
};

int calcularBalance(Node *root)
{
    if(!root) return 0;
    int l = calcularBalance(root->left);
    int r = calcularBalance(root->right);
    root->balance = root->val + l + r - 1;
    return root->balance;
}

void reiniciar(Node *root)
{
    if(!root) return;
    root->mov = false;
    reiniciar(root->left);
    reiniciar(root->right);
}

void distribuir(Node *root, bool &cambio)
{
    if(!root) return;
    distribuir(root->left, cambio);
    distribuir(root->right, cambio);

    if(root->left != nullptr && !root->mov && !root->left->mov)
    {
        if(root->left->balance > 0 && root->left->val > 1)
        {
            root->left->val--;
            root->val++;
            root->left->balance--;
            root->mov = true;
            root->left->mov = true;
            cambio = true;
        }
        else if(root->left->balance < 0 && root->val > 1)
        {
            root->val--;
            root->left->val++;
            root->left->balance++;
            root->mov = true;
            root->left->mov = true;
            cambio = true;
        }
    }
    if(root->right != nullptr && !root->mov && !root->right->mov)
    {
        if(root->right->balance > 0 && root->right->val > 1)
        {
            root->right->val--;
            root->val++;
            root->right->balance--;
            root->mov = true;
            root->right->mov = true;
            cambio = true;
        }
        else if(root->right->balance < 0 && root->val > 1)
        {
            root->val--;
            root->right->val++;
            root->right->balance++;
            root->mov = true;
            root->right->mov = true;
            cambio = true;
        }
    }
}

void distCandy(Node *root)
{
    calcularBalance(root);
    bool cambio;
    do
    {
        reiniciar(root);
        cambio = false;
        distribuir(root, cambio);
    } while(cambio);
}

void imprimir(Node *root)
{
    if(!root) return;
    cout << root->val << ' ';
    imprimir(root->left);
    imprimir(root->right);
}


int main()
{
    Node *root = new Node(5);
    root->left = new Node(0);
    root->right = new Node(0);
    root->right->left = new Node(0);
    root->right->right = new Node(0);

    cout << "ARBOL ANTES" << endl;
    imprimir(root);
    cout << endl;

    distCandy(root);

    cout << "ARBOL DESPUES" << endl;
    imprimir(root);
    cout << endl;

    return 0;
}

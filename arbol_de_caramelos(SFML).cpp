#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
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

void distCandy(Node *root, vector<vector<int>> &recorridos)
{
    calcularBalance(root);

    vector<int> estado;
    vector<Node*> pila;
    pila.push_back(root);

    while(!pila.empty())
    {
        Node *actual = pila.back();
        pila.pop_back();
        estado.push_back(actual->val);
        if(actual->right) pila.push_back(actual->right);
        if(actual->left) pila.push_back(actual->left);
    }
    recorridos.push_back(estado);
    bool cambio;
    do
    {
        reiniciar(root);
        cambio = false;
        distribuir(root, cambio);
        if(cambio)
        {
            estado.clear();
            pila.clear();
            pila.push_back(root);
            while(!pila.empty())
            {
                Node *actual = pila.back();
                pila.pop_back();

                estado.push_back(actual->val);

                if(actual->right) pila.push_back(actual->right);
                if(actual->left) pila.push_back(actual->left);
            }

            recorridos.push_back(estado);
        }

    } while(cambio);
}

void imprimir(Node *root)
{
    if(!root) return;
    cout << root->val << ' ';
    imprimir(root->left);
    imprimir(root->right);
}

Node* copiarArbol(Node *root)
{
    if(!root) return nullptr;
    Node *nuevo = new Node(root->val);
    nuevo->left = copiarArbol(root->left);
    nuevo->right = copiarArbol(root->right);
    return nuevo;
}

void dibujarLineas(sf::RenderWindow &window, Node *root, float x, float y, float sep)
{
    if(!root) return;
    if(root->left)
    {
        float nx = x - sep;
        float ny = y + 150;

        sf::VertexArray linea(sf::PrimitiveType::Lines, 2);
        linea[0].position = {x, y + 34};
        linea[1].position = {nx, ny - 34};
        linea[0].color = sf::Color(70, 60, 50);
        linea[1].color = sf::Color(70, 60, 50);

        window.draw(linea);
        dibujarLineas(window, root->left, nx, ny, sep / 2);
    }
    if(root->right)
    {
        float nx = x + sep;
        float ny = y + 150;

        sf::VertexArray linea(sf::PrimitiveType::Lines, 2);
        linea[0].position = {x, y + 34};
        linea[1].position = {nx, ny - 34};
        linea[0].color = sf::Color(70, 60, 50);
        linea[1].color = sf::Color(70, 60, 50);

        window.draw(linea);
        dibujarLineas(window, root->right, nx, ny, sep / 2);
    }
}

void centrarTexto(sf::Text &texto, float x, float y)
{
    sf::FloatRect bounds = texto.getLocalBounds();
    texto.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });

    texto.setPosition({x, y});
}

void dibujarNodos(sf::RenderWindow &window, Node *root, float x, float y, float sep, sf::Font &font, vector<int> &valores, int &pos)
{
    if(!root) return;

    sf::CircleShape nodo(34.f);
    nodo.setOrigin({34.f, 34.f});
    nodo.setPosition({x, y});
    nodo.setFillColor(sf::Color(248, 232, 190));
    nodo.setOutlineThickness(3.f);
    nodo.setOutlineColor(sf::Color(100, 65, 50));
    window.draw(nodo);

    sf::Text numero(font, to_string(valores[pos]), 27);
    pos++;
    numero.setFillColor(sf::Color(65, 40, 35));
    centrarTexto(numero, x, y);
    window.draw(numero);

    if(root->left) dibujarNodos(window, root->left, x - sep, y + 150, sep / 2, font, valores, pos);
    if(root->right) dibujarNodos(window, root->right, x + sep, y + 150, sep / 2, font, valores, pos);
}

void mostrarArbol(Node *original, vector<vector<int>> &recorridos)
{
    sf::RenderWindow window(
        sf::VideoMode({1100u, 700u}),
        "Árbol de Caramelos"
    );

    sf::Font font;

    if(!font.openFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        cout << "No se pudo cargar la fuente." << endl;
        return;
    }

    int recorrido = 0;

    while(window.isOpen())
    {
        while(const auto event = window.pollEvent())
        {
            if(event->is<sf::Event::Closed>())
                window.close();

            if(const auto *tecla = event->getIf<sf::Event::KeyPressed>())
            {
                if(tecla->code == sf::Keyboard::Key::Enter)
                {
                    if(recorrido < recorridos.size() - 1)
                        recorrido++;
                }

                if(tecla->code == sf::Keyboard::Key::Escape)
                    window.close();
            }
        }

        window.clear(sf::Color(250, 250, 250));

        int pos = 0;

        dibujarLineas(window, original, 550, 190, 220);

        dibujarNodos(window, original, 550, 190, 220,
                     font, recorridos[recorrido], pos);

        window.display();
    }
}

int main()
{
    Node *root = new Node(3);
    root->left = new Node(0);
    root->right = new Node(0);
    root->left->left = new Node(0);
    root->left->right = new Node(2);
    root->right->left = new Node(2);
    root->right->right = new Node(0);

    Node *original = copiarArbol(root);

    vector<vector<int>> recorridos;

    cout << "ARBOL ANTES" << endl;
    imprimir(root);
    cout << endl;

    distCandy(root, recorridos);

    cout << "ARBOL DESPUES" << endl;
    imprimir(root);
    cout << endl;

    mostrarArbol(original, recorridos);

    return 0;
}

#include <iostream>
#include <queue>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

struct Nodo
{
    Nodo(int v)
    {
        val = v;
        left = right = nullptr;
    }

    int val;
    Nodo *right, *left;
};

Nodo* crearArbol(int* ini, int* fin)
{
    if (ini == fin) return nullptr;

    queue<Nodo*> q;
    for (int* p = ini; p < fin; ++p) q.push(new Nodo(*p));

    while (q.size() > 1)
    {
        Nodo* izq = q.front();
        q.pop();

        Nodo* der = q.front();
        q.pop();

        Nodo* padre = new Nodo(izq->val + der->val);
        padre->left = izq;
        padre->right = der;

        q.push(padre);
    }

    return q.front();
}

void inorder(Nodo* n)
{
    if (!n) return;
    inorder(n->left);
    cout << n->val << ' ';
    inorder(n->right);
}

void dibujarEnlace(sf::RenderWindow& ventana, sf::Vector2f inicio, sf::Vector2f fin)
{
    sf::VertexArray linea(sf::PrimitiveType::Lines, 2);
    linea[0].position = inicio;
    linea[0].color = sf::Color::Black;
    linea[1].position = fin;
    linea[1].color = sf::Color::Black;

    ventana.draw(linea);
}

void dibujarArbol(sf::RenderWindow& ventana, const sf::Font& fuente, const Nodo* n, float izquierda, float derecha, float y)
{
    if (!n) return;

    const float radio = 22.f;
    const float distanciaVertical = 115.f;
    const sf::Color crema(255, 244, 218);
    const sf::Color guinda(116, 36, 57);

    const float x = (izquierda + derecha) / 2.f;
    const sf::Vector2f centro{x, y};
    const float yHijos = y + distanciaVertical;

    if (n->left)
    {
        const sf::Vector2f centroIzq{(izquierda + x) / 2.f, yHijos};
        dibujarEnlace(ventana, centro, centroIzq);
        dibujarArbol(ventana, fuente, n->left, izquierda, x, yHijos);
    }

    if (n->right)
    {
        const sf::Vector2f centroDer{(x + derecha) / 2.f, yHijos};
        dibujarEnlace(ventana, centro, centroDer);
        dibujarArbol(ventana, fuente, n->right, x, derecha, yHijos);
    }

    sf::CircleShape circulo(radio);
    circulo.setOrigin({radio, radio});
    circulo.setPosition(centro);
    circulo.setFillColor(crema);
    circulo.setOutlineColor(guinda);
    circulo.setOutlineThickness(2.f);
    ventana.draw(circulo);

    sf::Text texto(fuente, to_string(n->val), 18);
    texto.setFillColor(guinda);

    const sf::FloatRect limites = texto.getLocalBounds();
    texto.setOrigin(limites.position + limites.size / 2.f);
    texto.setPosition(centro);
    ventana.draw(texto);
}

int main()
{
    sf::Font fuente;
    if (!fuente.openFromFile("arial.ttf") && !fuente.openFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        cerr << "No se encontro Arial. Coloca arial.ttf en la carpeta de trabajo.\n";
        return 1;
    }

    const int n = 16;
    int A[n] = {2, 4, 7, 9, 10, 15, 3, 25, 38, 74, 1, 5, 10, 13, 11, 35};

    Nodo* root = crearArbol(A, A + n);
    inorder(root);
    cout << endl;

    const unsigned int ancho = 1120;
    const unsigned int alto = 600;

    sf::RenderWindow ventana(sf::VideoMode({ancho, alto}), "Arbol de sumas", sf::Style::Titlebar | sf::Style::Close);
    ventana.setFramerateLimit(60);

    while (ventana.isOpen())
    {
        while (const auto evento = ventana.pollEvent())
        {
            if (evento->is<sf::Event::Closed>())
            {
                ventana.close();
            }
        }

        if (!ventana.isOpen()) break;

        ventana.clear(sf::Color::White);
        dibujarArbol(ventana, fuente, root, 32.f, ancho - 32.f, 70.f);
        ventana.display();
    }

    return 0;
}

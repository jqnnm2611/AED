
#include <iostream>
#include <algorithm>
#include <SFML/Graphics.hpp>
using namespace std;

struct CNode
{
    CNode(int v)
    {
        value = v;
        height = 1;
        pintar = false;
        left = right = 0;
    }

    int value, height;
    bool pintar;
    CNode *left, *right;
};

class CAVL
{
public:
    CAVL();
    ~CAVL();

    void ins(int x);
    bool rem(int x);
    bool find(int x);
    void print();

    void marcarPrimos(int dato);
    CNode* getRoot();

private:
    CNode* root;

    int altura(CNode* p);
    int peso(CNode* p);
    void actualizar(CNode* p);

    CNode* rotarDerecha(CNode* p);
    CNode* rotarIzquierda(CNode* p);
    CNode* balancear(CNode* p);

    CNode* RecInsert(CNode* p, int dato);
    bool RecFind(CNode* p, int dato);

    bool brep;
    CNode** rep(CNode** p);
    CNode* RecRemove(CNode* p, int dato, bool& eliminado);

    void buscarNivel(CNode* p, int dato, int nivel,
                     CNode* padre, int& nivelDato,
                     CNode*& padreDato, CNode*& objetivo);

    void pintarPrimos(CNode* p, int nivel, CNode* padre,
                      int nivelDato, CNode* padreDato,
                      CNode* objetivo);

    void reiniciarPintado(CNode* p);
    void liberar(CNode* p);

    void inorder(CNode* p);
    void RecPrint(CNode* p, int nivel);
};

CAVL::CAVL()
{
    root = 0;
    brep = 0;
}

CAVL::~CAVL()
{
    liberar(root);
}

void CAVL::liberar(CNode* p)
{
    if(!p) return;

    liberar(p->left);
    liberar(p->right);
    delete p;
}

int CAVL::altura(CNode* p)
{
    return p ? p->height : 0;
}

int CAVL::peso(CNode* p)
{
    return altura(p->left) - altura(p->right);
}

void CAVL::actualizar(CNode* p)
{
    p->height = 1 + max(altura(p->left), altura(p->right));
}

CNode* CAVL::rotarDerecha(CNode* p)
{
    CNode* aux_new = p->left;
    CNode* aux_hijo = aux_new->right;

    aux_new->right = p;
    p->left = aux_hijo;

    actualizar(p);
    actualizar(aux_new);

    return aux_new;
}

CNode* CAVL::rotarIzquierda(CNode* p)
{
    CNode* aux_new = p->right;
    CNode* aux_hijo = aux_new->left;

    aux_new->left = p;
    p->right = aux_hijo;

    actualizar(p);
    actualizar(aux_new);

    return aux_new;
}

CNode* CAVL::balancear(CNode* p)
{
    actualizar(p);

    if(peso(p) > 1)
    {
        if(peso(p->left) < 0)
            p->left = rotarIzquierda(p->left);

        return rotarDerecha(p);
    }

    if(peso(p) < -1)
    {
        if(peso(p->right) > 0)
            p->right = rotarDerecha(p->right);

        return rotarIzquierda(p);
    }

    return p;
}

CNode* CAVL::RecInsert(CNode* p, int dato)
{
    if(!p) return new CNode(dato);

    if(dato < p->value)
        p->left = RecInsert(p->left, dato);

    else if(dato > p->value)
        p->right = RecInsert(p->right, dato);

    else
        return p;

    return balancear(p);
}

void CAVL::ins(int x)
{
    root = RecInsert(root, x);
}

bool CAVL::RecFind(CNode* p, int dato)
{
    if(!p) return false;

    if(p->value == dato) return true;

    return dato < p->value ?
        RecFind(p->left, dato) :
        RecFind(p->right, dato);
}

bool CAVL::find(int x)
{
    return RecFind(root, x);
}

CNode** CAVL::rep(CNode** p)
{
    CNode** q = p;

    if(brep == 1)
    {
        q = &((*q)->right);

        while((*q)->left)
            q = &((*q)->left);
    }
    else
    {
        q = &((*q)->left);

        while((*q)->right)
            q = &((*q)->right);
    }

    brep = !brep;

    return q;
}

CNode* CAVL::RecRemove(CNode* p, int dato, bool& eliminado)
{
    if(!p) return 0;

    if(dato < p->value)
        p->left = RecRemove(p->left, dato, eliminado);

    else if(dato > p->value)
        p->right = RecRemove(p->right, dato, eliminado);

    else
    {
        eliminado = true;

        if(!p->left || !p->right)
        {
            CNode* aux = p->left ? p->left : p->right;

            delete p;
            return aux;
        }

        bool derecha = brep;

        CNode** q = rep(&p);

        int valor = (*q)->value;
        p->value = valor;

        if(derecha)
            p->right = RecRemove(p->right, valor, eliminado);
        else
            p->left = RecRemove(p->left, valor, eliminado);
    }

    return balancear(p);
}

bool CAVL::rem(int x)
{
    bool eliminado = false;

    root = RecRemove(root, x, eliminado);

    return eliminado;
}

void CAVL::buscarNivel(CNode* p, int dato, int nivel,
                       CNode* padre, int& nivelDato,
                       CNode*& padreDato, CNode*& objetivo)
{
    if(!p) return;

    if(p->value == dato)
    {
        nivelDato = nivel;
        padreDato = padre;
        objetivo = p;
        return;
    }

    buscarNivel(p->left, dato, nivel + 1, p,
                nivelDato, padreDato, objetivo);

    if(!objetivo)
    {
        buscarNivel(p->right, dato, nivel + 1, p,
                    nivelDato, padreDato, objetivo);
    }
}

void CAVL::reiniciarPintado(CNode* p)
{
    if(!p) return;

    p->pintar = false;

    reiniciarPintado(p->left);
    reiniciarPintado(p->right);
}

void CAVL::pintarPrimos(CNode* p, int nivel, CNode* padre,
                        int nivelDato, CNode* padreDato,
                        CNode* objetivo)
{
    if(!p) return;

    if(nivel == nivelDato &&
       (p == objetivo || padre != padreDato))
    {
        p->pintar = true;
    }

    pintarPrimos(p->left, nivel + 1, p,
                 nivelDato, padreDato, objetivo);

    pintarPrimos(p->right, nivel + 1, p,
                 nivelDato, padreDato, objetivo);
}

void CAVL::marcarPrimos(int dato)
{
    reiniciarPintado(root);

    int nivelDato = -1;
    CNode* padreDato = 0;
    CNode* objetivo = 0;

    buscarNivel(root, dato, 0, 0,
                nivelDato, padreDato, objetivo);

    if(!objetivo)
    {
        cout << "El nodo " << dato << " no existe." << endl;
        return;
    }

    pintarPrimos(root, 0, 0,
                 nivelDato, padreDato, objetivo);
}

void CAVL::inorder(CNode* p)
{
    if(!p) return;

    inorder(p->left);
    cout << p->value << " ";
    inorder(p->right);
}

void CAVL::RecPrint(CNode* p, int nivel)
{
    if(!p) return;

    RecPrint(p->right, nivel + 1);

    for(int i = 0; i < nivel; i++)
        cout << "    ";

    cout << p->value << "(h" << p->height << ")";

    if(p->pintar)
        cout << " *";

    cout << endl;

    RecPrint(p->left, nivel + 1);
}

void CAVL::print()
{
    cout << "Impresion inorder: ";
    inorder(root);
    cout << endl;

    cout << "----------------" << endl;
    RecPrint(root, 0);
    cout << "----------------" << endl;
}

CNode* CAVL::getRoot()
{
    return root;
}


void dibujarLineas(sf::RenderWindow& ventana, CNode* p,
                   float izquierda, float derecha, float y)
{
    if(!p) return;

    const float x = (izquierda + derecha) / 2.f;
    const float distanciaVertical = 110.f;
    const float yHijos = y + distanciaVertical;

    if(p->left)
    {
        float nx = (izquierda + x) / 2.f;

        sf::VertexArray linea(sf::PrimitiveType::Lines, 2);

        linea[0].position = {x, y + 25.f};
        linea[1].position = {nx, yHijos - 25.f};

        linea[0].color = sf::Color(70, 60, 50);
        linea[1].color = sf::Color(70, 60, 50);

        ventana.draw(linea);

        dibujarLineas(ventana, p->left,
                      izquierda, x, yHijos);
    }

    if(p->right)
    {
        float nx = (x + derecha) / 2.f;

        sf::VertexArray linea(sf::PrimitiveType::Lines, 2);

        linea[0].position = {x, y + 25.f};
        linea[1].position = {nx, yHijos - 25.f};

        linea[0].color = sf::Color(70, 60, 50);
        linea[1].color = sf::Color(70, 60, 50);

        ventana.draw(linea);

        dibujarLineas(ventana, p->right,
                      x, derecha, yHijos);
    }
}


void centrarTexto(sf::Text& texto, float x, float y)
{
    sf::FloatRect limites = texto.getLocalBounds();

    texto.setOrigin({
        limites.position.x + limites.size.x / 2.f,
        limites.position.y + limites.size.y / 2.f
    });

    texto.setPosition({x, y});
}


void dibujarNodos(sf::RenderWindow& ventana, CNode* p,
                  float izquierda, float derecha, float y,
                  sf::Font& fuente)
{
    if(!p) return;

    const float radio = 25.f;
    const float distanciaVertical = 110.f;

    float x = (izquierda + derecha) / 2.f;
    float yHijos = y + distanciaVertical;

    sf::CircleShape circulo(radio);

    circulo.setOrigin({radio, radio});
    circulo.setPosition({x, y});
    circulo.setOutlineThickness(2.f);
    circulo.setOutlineColor(sf::Color(116, 36, 57));

    if(p->pintar)
        circulo.setFillColor(sf::Color(116, 36, 57));
    else
        circulo.setFillColor(sf::Color(255, 244, 218));

    ventana.draw(circulo);

    sf::Text texto(fuente, to_string(p->value), 18);

    if(p->pintar)
        texto.setFillColor(sf::Color::White);
    else
        texto.setFillColor(sf::Color(116, 36, 57));

    centrarTexto(texto, x, y);

    ventana.draw(texto);

    if(p->left)
        dibujarNodos(ventana, p->left,
                     izquierda, x, yHijos, fuente);

    if(p->right)
        dibujarNodos(ventana, p->right,
                     x, derecha, yHijos, fuente);
}


void mostrarArbol(CNode* root, const string& titulo)
{
    const unsigned int ancho = 1200;
    const unsigned int alto = 750;

    sf::RenderWindow ventana(
        sf::VideoMode({ancho, alto}),
        titulo
    );

    ventana.setFramerateLimit(60);

    sf::Font fuente;

    if(!fuente.openFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        cout << "No se pudo cargar Arial." << endl;
        return;
    }

    while(ventana.isOpen())
    {
        while(const auto evento = ventana.pollEvent())
        {
            if(evento->is<sf::Event::Closed>())
                ventana.close();
        }

        ventana.clear(sf::Color(250, 250, 250));

        dibujarLineas(ventana, root, 20.f,
                      ancho - 20.f, 65.f);

        dibujarNodos(ventana, root, 20.f,
                     ancho - 20.f, 65.f, fuente);

        ventana.display();
    }
}


int main()
{
    CAVL t;

    int datos[] = {
        50,
        30, 70,
        20, 40, 60, 80,
        10, 25, 35, 45, 55, 65, 75, 90
    };

    for(int x : datos)
        t.ins(x);

    mostrarArbol(t.getRoot(), "Arbol AVL original");

    int dato;

    cout << "Ingrese el nodo cuyos primos desea pintar: ";
    cin >> dato;

    t.marcarPrimos(dato);

    mostrarArbol(t.getRoot(), "Arbol AVL - Primos pintados");

    return 0;
}

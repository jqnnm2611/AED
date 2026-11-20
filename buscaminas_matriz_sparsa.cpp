#include <iostream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
using namespace std;

struct CNode
{
    CNode(int r, int c)
    {
        row = r;
        col = c;
        right = down = 0;
    }

    int row, col;
    CNode *right, *down;
};

class CSparseMatrix
{
public:
    CSparseMatrix(int n);
    ~CSparseMatrix();

    bool insert(int r, int c);
    bool find(int r, int c) const;
    bool valid(int r, int c) const;

    bool generate(int n);

    void print();
    int getSize();
    int maxMines();

private:
    int size, mines;
    CNode **rows;
    CNode **cols;

    CNode* getNode(int r, int c) const;

    bool remove(int r, int c);
    bool RecGenerate(int row, int remaining);
    bool tryRow(int row, int remaining);

    void clear();
};

CSparseMatrix::CSparseMatrix(int n)
{
    size = n;
    mines = 0;

    rows = new CNode*[size];
    cols = new CNode*[size];

    for(int i = 0; i < size; i++)
    {
        rows[i] = 0;
        cols[i] = 0;
    }
}

CSparseMatrix::~CSparseMatrix()
{
    clear();

    delete[] rows;
    delete[] cols;
}

void CSparseMatrix::clear()
{
    for(int i = 0; i < size; i++)
    {
        CNode* p = rows[i];

        while(p)
        {
            CNode* aux = p;
            p = p->right;
            delete aux;
        }

        rows[i] = 0;
        cols[i] = 0;
    }

    mines = 0;
}

CNode* CSparseMatrix::getNode(int r, int c) const
{
    if(r < 0 || r >= size || c < 0 || c >= size)
        return 0;

    CNode* p = rows[r];

    while(p && p->col < c)
        p = p->right;

    if(p && p->col == c)
        return p;

    return 0;
}

bool CSparseMatrix::find(int r, int c) const
{
    return getNode(r, c) != 0;
}

bool CSparseMatrix::valid(int r, int c) const
{
    if(r < 0 || r >= size || c < 0 || c >= size)
        return false;

    if(rows[r] || cols[c])
        return false;

    for(int i = -1; i <= 1; i++)
    {
        for(int j = -1; j <= 1; j++)
        {
            if(i == 0 && j == 0)
                continue;

            if(find(r + i, c + j))
                return false;
        }
    }

    return true;
}

bool CSparseMatrix::insert(int r, int c)
{
    if(!valid(r, c))
        return false;

    CNode* nuevo = new CNode(r, c);

    CNode** p = &rows[r];

    while(*p && (*p)->col < c)
        p = &((*p)->right);

    nuevo->right = *p;
    *p = nuevo;

    CNode** q = &cols[c];

    while(*q && (*q)->row < r)
        q = &((*q)->down);

    nuevo->down = *q;
    *q = nuevo;

    mines++;

    return true;
}

bool CSparseMatrix::remove(int r, int c)
{
    if(!find(r, c))
        return false;

    CNode** p = &rows[r];

    while((*p)->col != c)
        p = &((*p)->right);

    CNode* aux = *p;
    *p = aux->right;

    CNode** q = &cols[c];

    while(*q != aux)
        q = &((*q)->down);

    *q = aux->down;

    delete aux;

    mines--;

    return true;
}

bool CSparseMatrix::tryRow(int row, int remaining)
{
    int inicio = rand() % size;

    for(int i = 0; i < size; i++)
    {
        int c = (inicio + i) % size;

        if(insert(row, c))
        {
            if(RecGenerate(row + 1, remaining - 1))
                return true;

            remove(row, c);
        }
    }

    return false;
}

bool CSparseMatrix::RecGenerate(int row, int remaining)
{
    if(remaining == 0)
        return true;

    if(row >= size)
        return false;

    if(size - row < remaining)
        return false;

    if(tryRow(row, remaining))
        return true;

    if(RecGenerate(row + 1, remaining))
        return true;

    return false;
}

int CSparseMatrix::maxMines()
{
    if(size == 2)
        return 1;

    if(size == 3)
        return 2;

    return size;
}

bool CSparseMatrix::generate(int n)
{
    if(n < 0 || n > maxMines())
        return false;

    clear();

    if(n == 0)
        return true;

    if(!RecGenerate(0, n))
    {
        clear();
        return false;
    }

    return true;
}

void CSparseMatrix::print()
{
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(find(i, j))
                cout << "1 ";
            else
                cout << ". ";
        }

        cout << endl;
    }
}

int CSparseMatrix::getSize()
{
    return size;
}


void dibujarTablero(sf::RenderWindow& ventana,
                    CSparseMatrix& matriz,
                    const sf::Font& fuente)
{
    const float area = 760.f;
    const float cellSize = area / matriz.getSize();

    const float inicioX = 70.f;
    const float inicioY = 70.f;

    for(int i = 0; i < matriz.getSize(); i++)
    {
        for(int j = 0; j < matriz.getSize(); j++)
        {
            float x = inicioX + j * cellSize;
            float y = inicioY + i * cellSize;

            sf::RectangleShape celda({cellSize, cellSize});

            celda.setPosition({x, y});
            celda.setFillColor(sf::Color::White);
            celda.setOutlineColor(sf::Color::Black);
            celda.setOutlineThickness(1.f);

            ventana.draw(celda);

            if(matriz.find(i, j))
            {
                unsigned int tam = static_cast<unsigned int>(cellSize * 0.55f);

                if(tam < 8)
                    tam = 8;

                if(tam > 48)
                    tam = 48;

                sf::Text texto(fuente, "1", tam);

                texto.setFillColor(sf::Color::Black);

                const sf::FloatRect limites = texto.getLocalBounds();

                texto.setOrigin(limites.position + limites.size / 2.f);

                texto.setPosition({
                    x + cellSize / 2.f,
                    y + cellSize / 2.f
                });

                ventana.draw(texto);
            }
        }
    }
}

int main()
{
    srand(time(0));

    int N, n;

    cout << "Ingrese el tamano del tablero: ";
    cin >> N;

    if(N <= 0)
    {
        cout << "El tamano debe ser positivo." << endl;
        return 0;
    }

    cout << "Ingrese la cantidad de minas: ";
    cin >> n;

    CSparseMatrix matriz(N);

    if(n < 0 || n > matriz.maxMines())
    {
        cout << "Cantidad de minas invalida." << endl;
        cout << "Maximo permitido: " << matriz.maxMines() << endl;
        return 0;
    }

    if(!matriz.generate(n))
    {
        cout << "No se pudieron generar las minas." << endl;
        return 0;
    }

    sf::Font fuente;

    if(!fuente.openFromFile("arial.ttf") &&
       !fuente.openFromFile("C:/Windows/Fonts/arial.ttf"))
    {
        cout << "No se encontro Arial." << endl;
        return 1;
    }

    sf::RenderWindow ventana(
        sf::VideoMode({900, 900}),
        "Matriz dispersa",
        sf::Style::Titlebar | sf::Style::Close
    );

    ventana.setFramerateLimit(60);

    while(ventana.isOpen())
    {
        while(const auto evento = ventana.pollEvent())
        {
            if(evento->is<sf::Event::Closed>())
                ventana.close();
        }

        if(!ventana.isOpen())
            break;

        ventana.clear(sf::Color::White);

        dibujarTablero(ventana, matriz, fuente);

        ventana.display();
    }

    return 0;
}

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <queue>
#include <utility> 
#include <vector>

using namespace std;

// Función para verificar si una posición es válida
bool esValido(int x, int y, int filas, int columnas, int** matriz) {
    if (x >= 0 && x < columnas && y >= 0 && y < filas && matriz[y][x] == 0) {
        return true;
    }
    return false;
}

// Función para imprimir el laberinto
void imprimirLaberinto(int** matriz, int filas, int columnas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (matriz[i][j] == 1) {
                cout << "##"; // Paredes con #
            } else if (matriz[i][j] == 0) {
                cout << "  "; // Espacios vacíos
            } else if (matriz[i][j] == 2) {
                cout << ".."; // Camino visitado
            } else if (matriz[i][j] == 3) {
                cout << "XX"; // Posición actual
            }
        }
        cout << "\n";
    }
    cout << "\n";
}

// Función para resolver el laberinto usando BFS
void resolverLaberintoBFS(int** matriz, int filas, int columnas, int entradaX, int entradaY) {
    // Direcciones de movimiento: arriba, abajo, izquierda, derecha
    int movX[] = {0, 0, -1, 1};
    int movY[] = {-1, 1, 0, 0};

    // Cola para almacenar las posiciones a explorar
    queue<pair<int, int>> cola;
    cola.push({entradaY, entradaX}); // Añadir la entrada a la cola

    vector<vector<bool>> visitado(filas, vector<bool>(columnas, false));
    visitado[entradaY][entradaX] = true;

    // Mientras la cola no esté vacía
    while (!cola.empty()) {
        pair<int, int> actual = cola.front();
        cola.pop();

        matriz[actual.first][actual.second] = 3; // Marcar la posición actual

        // Explorar las direcciones de movimiento
        for (int i = 0; i < 4; i++) {
            int nuevoX = actual.second + movX[i];
            int nuevoY = actual.first + movY[i];

            // Verificar si hemos encontrado la salida
            if (nuevoX == columnas - 1 && matriz[nuevoY][nuevoX] == 0) {
                matriz[nuevoY][nuevoX] = 3; // Marcar la salida
                imprimirLaberinto(matriz, filas, columnas); // Imprimir el laberinto resuelto
                cout << "¡Salida encontrada en (" << nuevoY << ", " << nuevoX << ")!" << endl;
                return;
            }

            // Verificar si la nueva posición es válida y no ha sido visitada
            if (esValido(nuevoX, nuevoY, filas, columnas, matriz) && !visitado[nuevoY][nuevoX]) {
                visitado[nuevoY][nuevoX] = true;
                cola.push({nuevoY, nuevoX});
            }
        }
        matriz[actual.first][actual.second] = 2; // Marcar como visitado
    }

    cout << "No se encontró salida." << endl;
}

void generarLaberinto(int filas, int columnas, float densidad) {
    int **matriz;
    matriz = new int *[filas];

    int FParedes = densidad * 8; 
    densidad = filas*columnas*densidad / 4;

    for (int i = 0; i < filas; i++) {
        matriz[i] = new int[columnas];
    }
    //valores
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1) {
                matriz[i][j] = 1;
            }
            else {
                matriz[i][j] = 0; 
            }
        }
    }
    //laberinto 
    srand(time(NULL));
    for (int i = 0; i < densidad; i++) {
        int x = rand() % (columnas - 4) + 2; // 2 18 
        x = (x / 2) * 2; 
        int y = rand()% (filas - 4) + 2;
        y = (y / 2) * 2;
        matriz[y][x] = 1; 
        for (int j = 0; j < FParedes; j++) {
            int mx[4] = { x,  x,  x + 2, x - 2 };
            int my[4] = { y + 2,y - 2, y ,  y };
            int r = rand() % 4;
            if (matriz[my[r]][mx[r]] == 0) {
                matriz[my[r]][mx[r]] = 1; 
                matriz[my[r] +( y - my[r])/2][mx[r]+(x- mx[r])/2] = 1;
            }
                
        }
    }

    // Añadir entrada y salida
    int entrada = rand() % (filas - 2) + 1; // 1 a filas-2
    int salida = rand() % (filas - 2) + 1; // 1 a filas-2
    matriz[entrada][0] = 0; // Entrada en la pared izquierda
    matriz[salida][columnas - 1] = 0; // Salida en la pared derecha

    // Resolver el laberinto
    resolverLaberintoBFS(matriz, filas, columnas, 0, entrada); // Asumiendo que la entrada está en la columna 0

    // Liberar memoria
    for (int i = 0; i < filas; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
}

int main()
{
    generarLaberinto(30, 17, 2); 
}

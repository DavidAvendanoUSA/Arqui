#include <iostream>
#include <windows.h>   // Para Sleep en Windows

using namespace std;

volatile bool dispositivo_listo = false;

// Simula el dispositivo
void dispositivo_es() {
    cout << "El dispositivo se está preparando..." << endl;
    Sleep(2000);  // 2000 ms = 2 segundos
    dispositivo_listo = true;
    cout << "? Dispositivo listo para recibir datos." << endl;
}

// Controlador programado con timeout
void controlador_programado(int timeout) {
    while (!dispositivo_listo && timeout > 0) {
        cout << "? Esperando dispositivo... (" << timeout << " seg restantes)" << endl;
        Sleep(1000);  // 1000 ms = 1 segundo
        timeout--;
    }

    if (dispositivo_listo) {
        cout << "?? Enviando dato al dispositivo..." << endl;
    } else {
        cout << "? Error: Tiempo de espera agotado." << endl;
    }
}

int main() {
    dispositivo_es();            // Simula el dispositivo (se activa en 2s)
    controlador_programado(5);   // El controlador espera hasta 5s
    
    system("pause"); // ?? Pausa para que no se cierre la consola
    return 0;
}

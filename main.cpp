#include <iostream>
#include <thread>   // std::thread
#include <atomic>   // std::atomic<bool>
#include <chrono>   // std::chrono::seconds

using namespace std;

// Variable global compartida entre hilos
atomic<bool> dispositivo_listo(false);

// Simula el dispositivo en un hilo aparte
void simular_dispositivo() {
    cout << "El dispositivo se está preparando..." << endl;
    this_thread::sleep_for(chrono::seconds(2)); // simula retardo
    dispositivo_listo = true;
    cout << "✅ Dispositivo listo para recibir datos." << endl;
}

// Simula el controlador con polling + timeout
void controlador_programado(int timeout) {
    while (!dispositivo_listo && timeout > 0) {
        cout << "⌛ Esperando dispositivo... (" << timeout << " seg restantes)" << endl;
        this_thread::sleep_for(chrono::seconds(1));
        timeout--;
    }

    // ✅ Al salir del bucle volvemos a verificar
    if (dispositivo_listo) {
        cout << "📤 Enviando dato al dispositivo..." << endl;
    } else {
        cout << "❌ Error: Tiempo de espera agotado." << endl;
    }
}

int main() {
    // Crear hilo para simular el dispositivo
    thread dispositivo(simular_dispositivo);

    // Ejecutar controlador con timeout de 5 segundos
    controlador_programado(5);

    // Esperar a que termine el hilo del dispositivo
    dispositivo.join();

    return 0;
}

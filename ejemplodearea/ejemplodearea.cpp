// ejemplodearea.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "stdafx.h"
#include "triangulo.h"
//Implementacion de los metodos de la clase
//Declaracion del constructor
triangulo::triangulo(void)
{
	base = 4;
	altura = 3;
}
//Declaracion del destructor
triangulo::~triangulo(void)
{
}
//Declaración del metodo - funcion
float triangulo::calculararea(float b, float h)
{
	area = (b * h) / 2;
	return area;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln

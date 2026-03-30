#include <iostream>
#include <string>
using namespace std;

void   menu();
int    contarVocales(string s);
int    longitudString(string s);
string extraerParte(string s, int pos, int len);
void   intercambioString(string &s1, string &s2);
int    compararString(string s1, string s2);
void   encontrarCaracter(string s, char c);
string invertirString(string s);
int    esPalindromo(string s);
string quitarVocales(string s);

int main()
{
    menu();
    return 0;
}

void menu()
{
    int opcion;

    do
    {
        cout << endl << "   menu   " << endl;
        cout << "1) Contar vocales." << endl;
        cout << "2) Longitud de string." << endl;
        cout << "3) Extraer una parte." << endl;
        cout << "4) Intercambio de string." << endl;
        cout << "5) Comparar string." << endl;
        cout << "6) Encontrar un caracter." << endl;
        cout << "7) Invertir." << endl;
        cout << "8) Determinar si es capicua." << endl;
        cout << "9) Quitar vocales." << endl;
        cout << "0) Salir." << endl;
        cout << "Ingresa la opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion)
        {
        case 1:
        {
            string s;
            cout << "Ingrese un string: ";
            getline(cin, s);
            cout << "Numero de vocales: " << contarVocales(s) << endl;
            break;
        }
        case 2:
        {
            string s;
            cout << "Ingrese un string: ";
            getline(cin, s);
            cout << "Longitud: " << longitudString(s) << endl;
            break;
        }
        case 3:
        {
            string s;
            int pos, len;
            cout << "Ingrese un string: ";
            getline(cin, s);
            cout << "Ingrese la posicion de inicio: ";
            cin >> pos;
            cout << "Ingrese la cantidad de caracteres: ";
            cin >> len;
            cin.ignore();
            cout << "Substring: " << extraerParte(s, pos, len) << endl;
            break;
        }
        case 4:
        {
            string s1, s2;
            cout << "Ingrese el primer string: ";
            getline(cin, s1);
            cout << "Ingrese el segundo string: ";
            getline(cin, s2);
            intercambioString(s1, s2);
            cout << "Primer string:  " << s1 << endl;
            cout << "Segundo string: " << s2 << endl;
            break;
        }
        case 5:
        {
            string s1, s2;
            cout << "Ingrese el primer string: ";
            getline(cin, s1);
            cout << "Ingrese el segundo string: ";
            getline(cin, s2);
            if (compararString(s1, s2) == 0)
                cout << "Los strings son iguales." << endl;
            else
                cout << "Los strings son diferentes." << endl;
            break;
        }
        case 6:
        {
            string s;
            char c;
            cout << "Ingrese un string: ";
            getline(cin, s);
            cout << "Ingrese el caracter a buscar: ";
            cin >> c;
            cin.ignore();
            encontrarCaracter(s, c);
            break;
        }
        case 7:
        {
            string s;
            cout << "Ingrese un string: ";
            getline(cin, s);
            cout << "String invertido: " << invertirString(s) << endl;
            break;
        }
        case 8:
        {
            string s;
            cout << "Ingrese un string: ";
            getline(cin, s);
            if (esPalindromo(s) == 1)
                cout << "Es capicua." << endl;
            else
                cout << "No es capicua." << endl;
            break;
        }
        case 9:
        {
            string s;
            cout << "Ingrese un string: ";
            getline(cin, s);
            cout << "Sin vocales: " << quitarVocales(s) << endl;
            break;
        }
        case 0:
            break;
        default:
            cout << "Opcion no valida." << endl;
            break;
        }

    } while (opcion != 0);
}

int contarVocales(string s)
{
    int cont = 0;
    for (int i = 0; i < (int)s.length(); i++)
    {
        char c = s[i];
        if (c=='a'||c=='e'||c=='i'||c=='o'||c=='u'||
            c=='A'||c=='E'||c=='I'||c=='O'||c=='U')
            cont++;
    }
    return cont;
}

int longitudString(string s)
{
    return s.length();
}

string extraerParte(string s, int pos, int len)
{
    if (pos >= 0 && pos < (int)s.length())
        return s.substr(pos, len);
    return "Posicion invalida.";
}

void intercambioString(string &s1, string &s2)
{
    s1.swap(s2);
}

int compararString(string s1, string s2)
{
    return s1.compare(s2);
}

void encontrarCaracter(string s, char c)
{
    bool encontrado = false;
    for (int i = 0; i < (int)s.length(); i++)
        if (s[i] == c)
        {
            cout << "Caracter encontrado en posicion: " << i << endl;
            encontrado = true;
        }
    if (!encontrado)
        cout << "El caracter no fue encontrado." << endl;
}

string invertirString(string s)
{
    int len = s.length();
    for (int i = 0; i < len / 2; i++)
    {
        char aux       = s[i];
        s[i]           = s[len - 1 - i];
        s[len - 1 - i] = aux;
    }
    return s;
}

int esPalindromo(string s)
{
    if (s.compare(invertirString(s)) == 0)
        return 1;
    return 0;
}

string quitarVocales(string s)
{
    string resultado = "";
    for (int i = 0; i < (int)s.length(); i++)
    {
        char c = s[i];
        if (c!='a'&&c!='e'&&c!='i'&&c!='o'&&c!='u'&&
            c!='A'&&c!='E'&&c!='I'&&c!='O'&&c!='U')
            resultado += s[i];
    }
    return resultado;
}

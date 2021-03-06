// queue::push/pop

#include <iostream>
#include <list>
#include <fstream>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include "Planeta.h"
#include "Evaluador.h"
#include "NodoBinario.h"

using namespace std;
int formato = 25;

//Escribe los datos del objeto mascota dado en un archivo binario con el nombre dado en la posicion dada
//Nota: Se deben poder agregar varias mascotas en un solo archivo
void escribir(string nombre_archivo, Planeta*planeta, int posicion)
{
    ofstream out(nombre_archivo.c_str(), ios::in);
    out.seekp(posicion*formato);
    out.write(planeta->nombre.c_str(), 10);
    int x = planeta->habitantes;
    out.write((char*)&x, 4);
    double l = planeta->diametro;
    out.write((char*)&l, 8);
    out.write(&planeta->categoria, 1);
    out.close();
}

//Devuelve una mascota previamente escrita (con la funcion escribir()) en un archivo binario con nombre dado en la posicion dada
//Nota: Se deben poder leer varias mascotas de un solo archivo
Planeta* leer(string nombre_archivo, int posicion)
{
    ifstream in(nombre_archivo.c_str());
    in.seekg(posicion*formato);
    char* n = new char[10];
    string no;
    int habitantes;
    double diametro;
    char tipo;

    in.read(n,10);
    no = n;
    in.read((char*)&habitantes, 4);
    in.read((char*)&diametro, 8);
    in.read(&tipo, 1);
    Planeta *p = new Planeta(no, habitantes, diametro, tipo);
    return p;
}

//Devuelve el primer valor fue ingresado en mi_pila (dada)
//Nota: devuelve el valor mas viejo
string getFondo(stack<string> mi_pila)
{
    string resultado;
    int y = mi_pila.size();
    for(int x = 0; x<y; x++){
        resultado = mi_pila.top();
        mi_pila.pop();
    }
    return resultado;
}

//Devuelve el ultimo valor que fue ingresado en mi_cola (dada)
//Nota: devuelve el valor mas nuevo
char getUltimo(queue<char> mi_cola)
{
    char resultado;
    int y = mi_cola.size();
    for(int x = 0; x<y; x++){
        resultado = mi_cola.front();
        mi_cola.pop();
    }
    return resultado;
}

//Dado una lista, devuelve un vector que contenga los datos de la lista en el mismo orden
vector<int> convertirAVector(list<int> mi_lista)
{
    vector<int> mi_vector;

    for(list<int>::iterator i = mi_lista.begin(); i != mi_lista.end(); i++){
        mi_vector.push_back((*i));
    }

    return mi_vector;
}

//Dado un numero, devuelve un mapa que contenga su tabla de multiplicacion
//Ejemplo:
//Dado num = 5
//Devuelve el siguiente mapa
//{1=>5,2=>10,3=>15,4=>20,5=>25,6=>30,7=>35,8=>40,9=>45,10=>50}
map<int,int> getTabla(int num)
{
    map<int,int> mi_mapa;
    for(int x = 1; x<=10; x++)
        mi_mapa[x] = num*x;
    return mi_mapa;
}

void insertarSet(set<string> *mi_set, set<string> de_set){
    for (set<string>::iterator i = de_set.begin(); i != de_set.end(); i++){
        (*mi_set).insert((*i));
    }
}

//Dado un arbol con raiz dada, devuelve un set que contenga todos los valores almacenados en el arbol
//Nota los valores estan almacendados en el atributo valor en la clase NodoBinario
set<string> getValores(NodoBinario* raiz)
{
    set<string> mi_set;
    if(raiz!=NULL){
        mi_set.insert(raiz->valor);
        set<string> der = getValores(raiz->hijo_der), izq = getValores(raiz->hijo_izq);
        insertarSet(&mi_set, der);
        insertarSet(&mi_set, izq);
    }
    return mi_set;
}

//Dado un arbol con raiz dada, busca el nodo que contenga el valor buscado (dado) y lo reemplaza con la variable reemplazo (dada)
//Nota los valores estan almacendados en el atributo valor en la clase NodoBinario
void buscarYReemplazar(NodoBinario* raiz, string buscado, string reemplazo)
{
    if(raiz!=NULL){
        if (raiz->valor==buscado){
            (raiz->valor=reemplazo);
            return;
        }
        buscarYReemplazar(raiz->hijo_der, buscado, reemplazo);
        buscarYReemplazar(raiz->hijo_izq, buscado, reemplazo);
    }

}

int main ()
{
    //Funcion evaluadora
    evaluar();
    return 0;
}


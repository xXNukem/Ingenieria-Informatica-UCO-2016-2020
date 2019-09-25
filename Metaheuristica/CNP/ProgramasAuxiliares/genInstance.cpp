#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
using namespace std;
int N = 1;
double density = 0.3;
void genMatrix(ofstream &file);

int main(int argc, char ** argv){
    srand(time(NULL));
    if(argc != 3){
        cout << "Error numero parametros: ./genInstance N NombreFichero"<<endl;
        return -1;
    }
    ofstream file(argv[2]);;
    if(!file.is_open()){
        cout<<"No ha sido posible generar el fichero"<<endl;
        return -1;
    }
    N = atoi(argv[1]);
    //cout << "Inserte la densidad de aristas del grafo --> ";
    //cin >> density;
    genMatrix(file);
    file.close();
    cout << "Fichero generado con exito"<<endl;
    return 0;
}


void genMatrix(ofstream &file){
    double _prob = 0.0;
    file << N << " " << density<<endl; // Export NumNodes and graph density
    for(int i = 0; i < N; i++)
    {
        for(int j = i+1; j <= N; j++){
            _prob  = (((double)rand()) / RAND_MAX);
            if(_prob > density){
                file <<  1;
            }
            else{
                file << 0;            
            }
            file << " ";
        }
        file << endl;
    }
}

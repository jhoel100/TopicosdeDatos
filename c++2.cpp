#include <iostream>
#include <fstream>
#include <vector>
#include <cmath> 
#include <time.h>

using namespace std;

int main() {
    string nombreArchivo = "ratings.csv";
    ifstream archivo(nombreArchivo.c_str());
    string palabra;

		int persona_i=1;
		int persona_j=77;

		vector<float> fila1(193886, 0.0);
		vector<float> fila2(193886, 0.0);

    getline(archivo, palabra);

		int userId;
		int movieId;
		float rating;
		float timestamp;

    while (getline(archivo, palabra,',')) {
				userId=stoi(palabra, nullptr);
				getline(archivo, palabra,',');
				movieId=stoi(palabra, nullptr);
				getline(archivo, palabra,',');
				rating=stof(palabra, nullptr);
				getline(archivo, palabra,'\n');
				timestamp=stof(palabra, nullptr);

				if(persona_i==userId){
					fila1[movieId-1]=rating;
				}
				if(persona_j==userId){
					fila2[movieId-1]=rating;
				}

    }

	  clock_t t_ini, t_fin;
	  double secs;

		float xy=0;
		float x=0;
		float y=0;
		float xx=0;
		float yy=0;
		t_ini = clock();

		for(int i=0;i<193886;i++){
	    xy=xy+fila1[i]*fila2[i];
	    x=x+fila1[i];
	    y=y+fila2[i];
	    xx=xx+fila1[i]*fila1[i];
	    yy=yy+fila2[i]*fila2[i];
		}

		float r=(xy-((x*y)/193886))/(sqrt(xx-(x*x/193886))*sqrt(yy-(y*y/193886)));
		t_fin = clock();
		cout<<r<<endl;
 		secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;
  	printf("%.16g milisegundos\n", secs * 1000.0);
}

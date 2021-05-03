#include <iostream>
#include <fstream>
#include <vector>
#include <cmath> 
#include <time.h>

using namespace std;

float cosine(vector<float> fila1,vector<float> fila2,float umbral){
    float xy=0;
    float xx=0;
    float yy=0;
		float ang;

    for(int i=0;i<fila1.size();i++){
        if(fila1[i] != -1 && fila2[i]!= -1){
            if(fila1[i]>umbral && fila2[i]>umbral){
                xy=xy+fila1[i]*fila2[i];
                xx=xx+fila1[i]*fila1[i];
                yy=yy+fila2[i]*fila2[i];
						}
				}
		}    
    
		if(xx==0 || yy==0){
        ang=-1;
		}
    else{
        ang=xy/(sqrt(xx)*sqrt(yy));
		}
    return ang;
}

float pearson(vector<float> fila1,vector<float> fila2,float umbral){
    float xy=0;
    float x=0;
    float y=0;
    float xx=0;
    float yy=0;
    int n=0;
		float r;

    for(int i=0;i<fila1.size();i++){
        if(fila1[i]!= -1 && fila2[i]!= -1 ){
            if(fila1[i]>umbral && fila2[i]>umbral){
                n=n+1;
                xy=xy+fila1[i]*fila2[i];
                x=x+fila1[i];
                y=y+fila2[i];
                xx=xx+fila1[i]*fila1[i];
                yy=yy+fila2[i]*fila2[i];
						}
				}
		}

    if(n==0){
        r=-1;
		}else{
        if(sqrt(xx-(x*x/n))==0 || sqrt(yy-(y*y/n))==0){
            r=-1;
				}else{
            r=(xy-((x*y)/n))/(sqrt(xx-(x*x/n))*sqrt(yy-(y*y/n)));
				}
		}
    return r;
}

float manhathan(vector<float>& row1,vector<float>& row2,float& umbral){
    float distance = 0.0;
    for(int i=0;i<row1.size();i++){
        if(row1[i]!= -1 && row2[i]!= -1){
            if(row1[i]>umbral && row2[i]>umbral){
                distance = distance + abs(row1[i] - row2[i]);
						}
				}
		}
    return distance;
}

float euclidean(vector<float> row1,vector<float> row2,float umbral){
    float distance = 0.0;
    for(int i=0;i<row1.size();i++){
        if(row1[i]!= -1.0 && row2[i]!= -1.0){
            if(row1[i]>umbral && row2[i]>umbral){
                distance += pow((row1[i] - row2[i]),2);
						}
				}
		}
    return sqrt(distance);
}

//QuickSort(arr,0,n-1);
int Particion(float arreglo[], int inicio, int fin)  
{  
	 float pivote=arreglo[fin];
	 int i=inicio-1;

	 float auxiliar;	 

	 for(int j=inicio;j<fin;j++){
			if(arreglo[j]>=pivote){
				i=i+1;
				auxiliar=arreglo[i];
				arreglo[i]=arreglo[j];
				arreglo[j]=auxiliar;
			}
	 }
	 auxiliar=arreglo[i+1];
	 arreglo[i+1]=arreglo[fin];
	 arreglo[fin]=auxiliar;
	return i+1;
	
}  

void QuickSort(float arreglo[], int inicio, int fin) 
{  
	if(inicio<fin){
		int medio=Particion(arreglo,inicio,fin);
		QuickSort(arreglo,inicio,medio-1);
		
		QuickSort(arreglo,medio+1,fin);
	}
}

void get_vecino_euclidean(int i,int nro_personas,float dis[],vector<vector<float>> dataset,float umbral,int vecinos){
		cout<<i+1<<": ";
		for(int j=0;j<nro_personas;j++){
			dis[j] = euclidean(dataset[i],dataset[j],umbral);
			/*if(dis[j]>0){
					  cout<<dis[j]<<" ";
			}*/
		}
		QuickSort(dis,0,nro_personas-1);
		for(int j=0;j<vecinos;j++){
			cout<<dis[j]<<" ";
		}
		cout<<endl;
}

void get_vecino_manhathan(int i,int nro_personas,float dis[],vector<vector<float>> dataset,float umbral,int vecinos){
		cout<<i+1<<": ";
		for(int j=0;j<nro_personas;j++){
			dis[j] = manhathan(dataset[i],dataset[j],umbral);
			/*if(dis[j]>0){
					  cout<<dis[j]<<" ";
			}*/
		}
		QuickSort(dis,0,nro_personas-1);
		for(int j=0;j<vecinos;j++){
			cout<<dis[j]<<" ";
		}
		cout<<endl;
}

void get_vecino_pearson(int i,int nro_personas,float dis[],vector<vector<float>> dataset,float umbral,int vecinos){
		cout<<i+1<<": ";
		for(int j=0;j<nro_personas;j++){
			dis[j] = pearson(dataset[i],dataset[j],umbral);
			/*if(dis[j]>0){
					  cout<<dis[j]<<" ";
			}*/
		}
		QuickSort(dis,0,nro_personas-1);
		for(int j=0;j<vecinos;j++){
			cout<<dis[j]<<" ";
		}
		cout<<endl;
}

void get_vecino_cosine(int i,int nro_personas,float dis[],vector<vector<float>> dataset,float umbral,int vecinos){
		cout<<i+1<<": ";
		for(int j=0;j<nro_personas;j++){
			dis[j] = cosine(dataset[i],dataset[j],umbral);
			/*if(dis[j]>0){
					  cout<<dis[j]<<" ";
			}*/
		}
		QuickSort(dis,0,nro_personas-1);
		for(int j=0;j<vecinos;j++){
			cout<<dis[j]<<" ";
		}
		cout<<endl;
}

int main() {
    string nombreArchivo = "ratings.csv";
    ifstream archivo(nombreArchivo.c_str());
    string palabra;

		int nro_peliculas=193609;
		int nro_personas=610;

		vector<vector<float>> dataset(nro_personas,vector<float> (nro_peliculas,0));

		for(int i=0;i<nro_personas;i++){
			dataset[i].reserve(nro_peliculas);
		}

		for(int i=0;i<nro_personas;i++){
			for(int j=0;j<nro_peliculas;j++){
				dataset[i][j]= (-1);
			}
		}

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

				dataset[userId-1][movieId-1]=rating;
    }

		int row0=1;
		float umbral=0;
		float distance=0;
/*
		for(int i=0;i<nro_personas;i++){
			distance = manhathan(dataset[row0-1],dataset[i],umbral);
			if(distance>0){
				    cout<<distance<<" ";
			}
		}
		cout<<"Completado"<<endl;

		row0=1;
		umbral=2;

		for(int i=0;i<nro_personas;i++){
			distance = euclidean(dataset[row0-1],dataset[i],umbral);
			if(distance>0){
				    cout<<distance<<" ";
			}
		}
		cout<<"Completado"<<endl;


		row0=1;
		umbral=2;

		for(int i=0;i<nro_personas;i++){
			distance = pearson(dataset[row0-1],dataset[i],umbral);
			if(distance>0){
				    cout<<distance<<" ";
			}
		}
		cout<<"Completado"<<endl;


		row0=1;
		umbral=2;

		for(int i=0;i<nro_personas;i++){
			distance = cosine(dataset[row0-1],dataset[i],umbral);
			if(distance>0){
				    cout<<distance<<" ";
			}
		}
		cout<<"Completado"<<endl;
*/

		int vecinos=3;
		float dis[nro_personas];
		int i=0;
		get_vecino_cosine(i,nro_personas,dis,dataset,umbral,vecinos);
		get_vecino_pearson(i,nro_personas,dis,dataset,umbral,vecinos);
		get_vecino_manhathan(i,nro_personas,dis,dataset,umbral,vecinos);
		get_vecino_euclidean(i,nro_personas,dis,dataset,umbral,vecinos);
}

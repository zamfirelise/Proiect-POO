#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include<fstream>
#include <iomanip>
using namespace std;

//Aplicatie pentru gestiunea costurilor produselor la o patiserie unde se produc diferite produse, 
//pentru care se consuma diferite materiale (cod material, denumire, preț unitar, cantitate).
//Aplicația permite calculul pretului de cost pentru fiecare produs, determinarea produsului cu costul cel mai mare, respectiv cel mai mic
class Material
{
private:
	string denumire_material;
	float pm;			//pret material
	static int nrObiecte; // SUNT COMUNE TUTUROR OBIECTELOR !!!!
	int cod_material;
public:


	int get_cod_material()
	{
		return cod_material;
	}

	void set_cod_material(const int cod_material)
	{
		this->cod_material = cod_material;
	}

	string get_denumire_material()
	{
		return denumire_material;
	}

	void set_denumire_material(string denumire_material)
	{
		this->denumire_material = denumire_material;
	}

	float get_pm()
	{
		return pm;
	}

	void set_pm(float pm)
	{
		this->pm = pm;
	}


	Material()			//constructor implicit
	{
		cout << "Apel constructor implicit Material:" << endl << "    ";
		nrObiecte++;
		cod_material = nrObiecte;
		denumire_material = "necunoscut";
		pm = 0;
	}

	Material(string denumire_material, float pm)	//constructor cu parametri
	{
		cout << "Apel constructor cu parametri Material:" << endl << "    ";
		nrObiecte++;
		cod_material = nrObiecte;
		this->denumire_material = denumire_material;
		this->pm = pm;
	}

	~Material()
	{
		cout << "Destructor material "<<nrObiecte <<" cu numele "<<denumire_material<<"." << endl;
		nrObiecte--;
	}
	friend istream& operator>>(istream& consola, Material& m);
};
int Material::nrObiecte = -1;
istream& operator>>(istream& consola, Material& m) {
	cout << "Introduceti numele materialului:"<<endl;
	consola >> m.denumire_material;
	cout << "Introduceti pretul materialului:" << endl;
	consola >> m.pm;
	m.nrObiecte++;
	m.cod_material = m.nrObiecte;
	cout << endl;
	return consola;
}


//VEZI CURSUL DE PE 5 DECEMBRIE. FOARTE UTIL AICI

class Produs_Patiserie
{
private:		
	string nume_prod;			//numele produsului
	int nr_mat;			//nr ingrediente folosite pt realizarea unui produs
	Material* mat;
	float* cm;//vectorul cu cantitatile folosite din fiecare material pentru fabricarea acelui produs; respecta ordinea ingredientelor din vectorul anterior

public:

	Produs_Patiserie()		//constructor implicit 
	{
		cout << "Apel constructor implicit Produs:" << endl << "     ";
		nume_prod = "Necunoscut"; 
		nr_mat = 0;
		cm = nullptr;
	}
	Produs_Patiserie(string nume, int nr_mat, float* cantitati)
	{
		cout << "Apel constructor cu parametri Produs: " << endl<< "     ";
		this->nume_prod = nume;
		this->nr_mat = nr_mat;
		cm = new float [nr_mat];
		for (int i = 0; i < nr_mat; i++)
		{
			cm[i] = cantitati[i];
		}
	}

	~Produs_Patiserie() {
		cout << "Destructor Produs_Patiserie cu numele " << nume_prod << endl;
		if(cm!=nullptr)
			delete[] cm;
		if(mat!=nullptr)
			delete[] mat;
	}
	string get_nume_prod()
	{
		return nume_prod;
	}

	int get_nr_mat()
	{
		return nr_mat;
	}

	void set_nr_mat(const int nr_mat)
	{
		this->nr_mat = nr_mat;
	}

	float* get_cm()
	{
		return cm;
	}

	void set_cm(float* cm)
	{
		this->cm = new float[nr_mat];
		for (int i = 0; i < nr_mat; i++)
			this->cm[i] = cm[i];
	}

	/*float Pret_Produs(float* pm, float* cm)
	{
		int s = 0;
		for (int i = 0; i < nr_mat; i++)
			s = s + pm[i] * cm[i];
		return s;
	}
	
	float valoare_material(float pret, float cantitate)	
	{
		return pret * cantitate;
	}*/

	
	friend istream& operator>>(istream& consola, Produs_Patiserie& p);
};
istream& operator>>(istream& consola, Produs_Patiserie& p)
{
	cout << "Cum se numeste produsul?" << endl;
	consola >> p.nume_prod;
	cout << "     Cate ingrediente sunt folosite pentru realizarea acestuia?" << endl;
	consola >> p.nr_mat;
	cout << "\nAcestea sunt:" << endl;
	for (int i = 0; i < p.nr_mat; i++)
	{
		cout << "Ingredientul " << i << ": ";
		consola >> p.mat[i];
		cout << ", folosit in cantitatea ";
		consola >> p.cm[i];
		cout << "." << endl;
	}
	return consola;
}

int main()
{
	Produs_Patiserie p0;
	cout << "Produsul are denumirea " << p0.get_nume_prod() << " si " << p0.get_nr_mat() << " ingrediente."<<endl;
	float preturi0[] = {1,3,4};
	float cantitati0[] = { 0.2,1.0,1.0 };
	int coduri0[] = { 0,1,2 };
	Produs_Patiserie  p1("covrig", 3, cantitati0);
	float* cantitati = p1.get_cm();
	cout << "Produsul p are denumirea " << p1.get_nume_prod() << ", " << p1.get_nr_mat() << " ingrediente, ";
	cout << "folosite in cantitatile "<<cantitati[0];
	for (int i = 1; i < p1.get_nr_mat(); i++)
		cout << ", " << cantitati[i];
	cout << ".\n\n";
	
	Material m;
	cout << "Materialul " << m.get_denumire_material() << " are codul " << m.get_cod_material() << " si pretul " << m.get_pm()<<"." << endl;
	Material m1("faina", 4);
	cout << "Materialul " << m1.get_denumire_material() << " are codul " << m1.get_cod_material() << " si pretul " << m1.get_pm() << "." << endl<<endl;
	Material m3;
	cin >> m3;

	Produs_Patiserie p2;
	cin >> p2;
	
	return 0;
}


//REZOLVATE
//constructorul implicit pentru ambele clase
//getteri pentru ambele clase
//setteri pentru ambele clase
// ATRIBUTE - CONSTRUCTORI - DESTRUCTOR - METODE
//S1
//de ce se apeleaza un constructor in altul la clasa Material???
//apel constructor cu parametri la Material
//id=static
//destructori
//apel constructor cu parametri la Produse



// modificare test

//NEREZOLVATE
//supraincarcare >> 
//id=nr pozitiv, mai mare cu 1 fata de id-ul ultimului produs/material inregistrat		vezi S5
//calcul cel mai scump produs
//calcul cel mai ieftin produs
//foloseste fisiere
//supraincarcare operatori?
//
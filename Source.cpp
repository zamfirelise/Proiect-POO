#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <iomanip>
using namespace std;

//Aplicatie pentru gestiunea costurilor produselor la o patiserie unde se produc diferite produse, 
//pentru care se consuma diferite materiale (cod material, denumire, preț unitar, cantitate).
//Aplicația permite calculul pretului de cost pentru fiecare produs, determinarea produsului cu costul cel mai mare, respectiv cel mai mic
class Material
{
private:
	
	string denumire_material;
	float pm, cm;			//pret material, cantitate material
	/*static*/ int cod_material;

public:
	

	int get_cod_material()
	{
		return cod_material;
		//return Material::cod_material;
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
		this -> pm = pm;
	}

	float get_cm()
	{
		return cm;
	}

	void set_cm(float cm)
	{
		this->cm = cm;
	}


	Material()			//constructor implicit
	{
		cout << "Apel constructor implicit Material:" << endl << "    ";
		Material::cod_material++;
		denumire_material = "necunoscut";
		pm = 0;
		cm = 0;
	}

	Material(string denumire_material, float pm, float cm)				//constructor cu parametri
	{
		cout << "Apel constructor cu parametri Material:" << endl << "    ";
		Material::cod_material++;		
		this->denumire_material = denumire_material;
		this->pm = pm;
		this->cm = cm;
	}

	float valoare_material(float pret, float cantitate)	
	{
		return pret * cantitate;
	}
};


			//VEZI CURSUL DE PE 5 DECEMBRIE. FOARTE UTIL AICI

class Produs_Patiserie
{
private:		
	string nume_prod;			//numele produsului
	int nr_mat;					//nr ingrediente folosite pt realizarea unui produs
	float* pm;					//vectorul cu preturile materialelor folosite la fabricarea unui produs
	int* codm;					//vectorul cu codurile materialelor folosite la fabricarea unui produs
	float* cm;					//vectorul cu cantitatile folosite din fiecare material pentru fabricarea acelui produs; respecta ordinea ingredientelor din vectorul anterior
	Material* mat;

public:

	Produs_Patiserie()		//constructor implicit 
	{
		cout << "Apel constructor implicit Produs:" << endl << "     ";
		nume_prod = "Necunoscut";
		nr_mat = 0;
		pm = nullptr;
		codm = nullptr;
		cm = nullptr;
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

	float* get_pm()
	{
		return pm;
	}

	void set_pm(float* pm)
	{
		this->pm = new float[nr_mat];
		for (int i = 0; i < nr_mat; i++)
			this->pm[i] = pm[i];
	}

	int* get_codm()
	{
		return codm;
	}

	void set_codm(int* codm)
	{
		this->codm = new int[nr_mat];
		for (int i = 0; i < nr_mat; i++)
			this->codm[i] = codm[i];
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
	}*/

	
	Produs_Patiserie(string nume, int nr_mat, float* preturi, float* cantitati, int* coduri)//:nume_prod(nume)
	{
		cout << "Apel constructor cu parametri Produs: " << endl;
		this->nume_prod = nume;
		this->nr_mat = nr_mat;
		pm = new float [nr_mat];
		cm = new float [nr_mat];
		codm = new int [nr_mat];
		for (int i = 0; i < nr_mat; i++)
		{
			pm[i] = preturi[i];
			cm[i] = cantitati[i];
			codm[i] = coduri[i];
		}
	}
	
};

int main()
{
	Produs_Patiserie p/*, p1("covrig", 3, {1,3,4}, {0.2,1,1},{0,1,2})*/;
	cout << "Produsul p are denumirea " << p.get_nume_prod()<< ", "<< p.get_nr_mat() << " ingrediente, "<< p.get_codm()<<", cu preturile "<<p.get_pm()<<", folosite in cantitatile "<<p.get_cm()<<"."<<endl<<endl;
	
	//cout << "Produsul p1 are denumirea " << p1.get_nume_prod() << ", " << p1.get_nr_mat() << " ingrediente, " << p1.get_codm() << ", cu preturile " << p1.get_pm() << ", folosite in cantitatile " << p1.get_cm() << "." << endl;
		
	Material m, m1("faina", 4, 1), m2("drojdie", 2,0.1);
	cout << "Materialul " << m.get_denumire_material() << " are codul " << m.get_cod_material() << " a fost folosit in cantitatea " << m.get_cm() << " si are pretul " << m.get_pm()<<"."<<endl<<endl;
	cout << "Materialul " << m1.get_denumire_material() << " are codul " << m1.get_cod_material() << " a fost folosit in cantitatea " << m1.get_cm() << " si are pretul " << m1.get_pm() << "." << endl;
	cout << "Materialul " << m2.get_denumire_material() << " are codul " << m2.get_cod_material() << " a fost folosit in cantitatea " << m2.get_cm() << " si are pretul " << m2.get_pm() << "." << endl;

	


	
	//char* Cel_mai_scump()
	{

	}

	//char* Cel_mai_ieftin()
	{

	}


	return 0;
}


//REZOLVATE
//constructorul implicit pentru ambele clase
//getteri pentru ambele clase
//setteri pentru ambele clase
//S1


// modificare test

//NEREZOLVATE
//apel constructor cu parametri la ambele clase
//de ce se apeleaza un constructor in altul la clasa Material???
//id=nr pozitiv, mai mare cu 1 fata de id-ul ultimului produs/material inregistrat		vezi S5
//id=static
//calcul cel mai scump produs
//calcul cel mai ieftin produs
//foloseste fisiere
//supraincarcare operatori?
//
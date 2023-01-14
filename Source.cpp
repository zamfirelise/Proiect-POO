#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
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
		cout << "Apel constructor implicit Material:" << endl;
		nrObiecte++;
		cod_material = nrObiecte;
		denumire_material = "necunoscut";
		pm = 0;
	}

	Material(string denumire_material, float pm)	//constructor cu parametri
	{
		cout << "Apel constructor cu parametri Material:" << endl;
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
	friend ostream& operator<<(ostream& afisare, Material& m)
	{
		afisare << "\nSupraincarcare operator afisare material:\n\tMaterialul " << m.cod_material << " are denumirea " << m.denumire_material << " si pretul " << m.pm << endl;
		return afisare;
	}
	friend istream& operator>>(istream& consola, Material& m);
};
int Material::nrObiecte = -1;
istream& operator>>(istream& consola, Material& m) {
	cout << "\tIntroduceti numele materialului:"<<endl;
	consola >> m.denumire_material;
	cout << "\tIntroduceti pretul materialului:" << endl;
	consola >> m.pm;
	m.nrObiecte++;
	m.cod_material = m.nrObiecte;
	//cout << endl;
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
		mat = nullptr;
	}
	Produs_Patiserie(string nume, int nr_mat, float* cantitati, Material* mat)			//CEVA E GRESIT AICI, IN FOR
	{
		cout << "Apel constructor cu parametri Produs: " << endl;
		this->nume_prod = nume;
		this->nr_mat = nr_mat;
		cm = new float [nr_mat];
		for (int i = 0; i < nr_mat; i++)
		{
			cm[i] = cantitati[i];
			//this->mat[i] = mat[i];
			cout << "\tMaterialul "<<i<<" adaugat." << endl;
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

	Produs_Patiserie& operator<<(Material& m)
	{
		mat[nr_mat++] = &m;
		return *this;
	}

	friend ostream& operator<<(ostream& afisare, Produs_Patiserie& p)
	{
		if (p.nr_mat > 0)
		{
			afisare << "\nSupraincarcare operator Afisare Produs:" << endl << "\tProdusul " << p.nume_prod << " contine " << p.nr_mat << " materiale: " << endl;
			for (int i = 0; i < p.nr_mat; i++)
			{
				afisare << i + 1 << ". " << p.mat[i] << " in cantitatea " << p.cm[i] << endl;
			}
		}
		else afisare << "\tProdusul nu are materiale!";
		return afisare;
	}
	friend istream& operator>>(istream& consola, Produs_Patiserie& p);
};
istream& operator>>(istream& consola, Produs_Patiserie& p)
{
	cout << "Cum se numeste produsul?" << endl;
	consola >> p.nume_prod;
	cout << "\tCate ingrediente sunt folosite pentru realizarea acestuia?" << endl;
	consola >> p.nr_mat;
	cout << "\nAcestea sunt:" << endl;
	for (int i = 0; i < p.nr_mat; i++)
	{
		cout << "\tIngredientul " << i << ": ";
		consola >> p.mat[i];
		cout << ", folosit in cantitatea ";
		consola >> p.cm[i];
		cout << "." << endl;
	}
	return consola;
}

int main()
{
	//Produs_Patiserie p0;
	//cout << "\tProdusul are denumirea " << p0.get_nume_prod() << " si " << p0.get_nr_mat() << " ingrediente." << endl;
	//cout << "SUPRAINCARCARE\n" << p0 << endl;
	//float preturi1[] = {1,3,4};
	//float cantitati1[] = { (float)0.2, (float)1.0, (float)1.0 };
	//int coduri1[] = { 0,1,2 };
	//Material m;
	//Material m1("faina", 4);
	//Material m3, m4;
	//cin >> m3;
	//Material ingrediente[] = { m1, m3, m4 };
	////Produs_Patiserie  p1("covrig", 3, cantitati1, ingrediente);
	////float* cantitati = p1.get_cm();
	////cout << "\nSUPRAINCARCARE prod cu param\n" << p1 << endl;
	////cout << "\tProdusul p1 are denumirea " << p1.get_nume_prod() << ", " << p1.get_nr_mat() << " ingrediente, folosite in cantitatile "<<cantitati[0];
	////for (int i = 1; i < p1.get_nr_mat(); i++)
	//	//cout << ", " << cantitati[i];
	////cout << ".\n"; //afisare simpla produs creat prin constructor cu parametri
	////Material m;
	////Material m1("faina", 4);
	////Material m3, m4;
	////cin >> m3;//citire material fara parametri cu operator supraincarcat


	//Produs_Patiserie p2;
	//cin >> p2;
	//cout << p0;//afisare produs fara parametri cu operator supraincarcat
	
//PROBA CONSTRUCTOR CU PARAMETRI PRODUS
	float cantitati1[] = { (float)0.2, (float)1.0, (float)1.0 };
	Material m0("apa", 0.3), m1("faina", 4), m2("drojdie", 1.3);
	Material ingrediente[] = { m0, m1, m2 };
	Produs_Patiserie  p1("covrig", 3, cantitati1, ingrediente);
	cout << p1;




	return 0;
}


//REZOLVATE
//constructorul implicit pentru ambele clase
//constructorul cu parametri la ambele clase
//getteri, setteri pentru ambele clase
//ATRIBUTE - CONSTRUCTORI - DESTRUCTOR - METODE
//S1
//de ce se apeleaza un constructor in altul la clasa Material???
//id=static
//destructori
//apel constructor cu parametri la Produse
//id=nr pozitiv, mai mare cu 1 fata de id-ul ultimului produs/material inregistrat		vezi S5

//3.01.2023
//pot afisa SI citi informatii despre unul sau mai multe Materiale (cu parametri sau fara) atat prin getteri, cat si prin operatorul de afisare Supraincarcat
//supraincarcare << material fara param
//supraincarcare >> material
//PRODUS
//supraincarcare << produs fara param
//prod fara param<< prin getteri

//14.01.2023
//


// modificare test

//NEREZOLVATE
//cum stie operatorul de afisare supraincarcat pentru produsul cu parametri care e lista de ingrediente a produsului? unde initializez vectorul de materiale si cu ce?
//supraincarcare << produs cu param
//supraincarcare >> produs
//Nu poate citi TOATE materialele necesare pentru prepararea unui produs!!!
//calcul cel mai scump produs
//calcul cel mai ieftin produs
//foloseste fisiere
//supraincarcare operator afisare produs cu parametri

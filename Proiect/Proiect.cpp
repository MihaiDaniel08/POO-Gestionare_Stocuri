#define _CRT_SECURE_NO_WARNINGS
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

class Ingredient {
	char* nume;
	int cantitate;

	static int cantitateMaxima;

public:

	Ingredient() {
		this->nume = nullptr;
		this->cantitate = 0;

	}

	Ingredient(const char* nume, int cantitate) {

		if (strlen(nume) > 0) {
			this->nume = new char[strlen(nume) + 1];
			strcpy(this->nume, nume);
		}
		else
			this->nume = nullptr;
		if (cantitate > 0) this->cantitate = cantitate;
		else this->cantitate = 0;


	}

	Ingredient(const Ingredient& i) {


		this->nume = new char[strlen(i.nume) + 1];
		strcpy(this->nume, i.nume);
		this->cantitate = i.cantitate;

	}

	Ingredient& operator=(const Ingredient& i) {

		if (this != &i) {

			delete[] this->nume;
			this->nume = nullptr;
			this->nume = new char[strlen(i.nume) + 1];
			strcpy(this->nume, i.nume);
			this->cantitate = i.cantitate;


		}
		return *this;

	}

	char* getNume() {
		return this->nume;
	}

	int getCantitate() {
		return this->cantitate;
	}

	void setCantitate(int cantitate) {
		if (cantitate >= 0)this->cantitate = cantitate;
	}

	void setNume(const char nume[]) {
		if (strlen(nume) > 0) strcpy(this->nume, nume);
	}

	static int getCantitateMaxima() {
		return Ingredient::cantitateMaxima;
	}

	static void setCantitateMaxima(int cant) {
		if (cant > 10) Ingredient::cantitateMaxima = cant;
	}

	friend ostream& operator<<(ostream& out, const Ingredient& i) {

		out << "\n------------------------------------------";

		if (i.nume != nullptr)
			out << "\nNume: " << i.nume;
		else out << "\nNume: -";

		out << "\nCantitate: " << i.cantitate;

		out << "\n------------------------------------------";
		return out;
	}

	friend istream& operator>>(istream& in, Ingredient& i) {

		delete[] i.nume;
		i.nume = nullptr;

		cout << "\n------------------------------------------";

		cout << "\nNumele: ";
		string buffer;
		getline(in, buffer);
		i.nume = new char[buffer.size() + 1];
		strcpy(i.nume, buffer.data());

		cout << "\nCantitatea: "; in >> i.cantitate;


		cout << "\n------------------------------------------";
		return in;

	}

	//pre-incrementare
	Ingredient& operator++() {
		if (this->cantitate < Ingredient::cantitateMaxima)
			this->cantitate++;
		return *this;
	}

	//post-incrementare
	Ingredient operator++(int) {
		Ingredient copie = *this;
		if (this->cantitate < Ingredient::cantitateMaxima)
			this->cantitate++;
		return copie;
	}

	Ingredient& operator+(int stocSuplimentar) {
		if (stocSuplimentar > 0) {
			this->cantitate += stocSuplimentar;
			if (this->cantitate > Ingredient::cantitateMaxima)
				this->cantitate = Ingredient::cantitateMaxima;
		}
		return *this;

	}

	bool operator==(const Ingredient& i) {

		if (strcmp(this->nume, i.nume) == 1)
			return 0;
		else if (this->cantitate != i.cantitate)
			return 0;
		else return 1;
	}

	bool operator>(const Ingredient& i) {
		if (this->cantitate < i.cantitate)
			return 0;
		else return 1;
	}

	~Ingredient() {

		if (this->nume != nullptr) {
			delete[] this->nume;
			this->nume = nullptr;
		}

	}
};



class Reteta {

	Ingredient* ingrediente;
	int numarIngrediente;
	string numePreparat;
	int* cantitati;

public:

	Reteta() {
		this->ingrediente = nullptr;
		this->numarIngrediente = 0;
		this->numePreparat = "-";
		this->cantitati = nullptr;
	}

	Reteta(Ingredient* ingrediente, int numarIngrediente, string numePreparat, int* cantitati) {

		if (numePreparat.length() > 0)this->numePreparat = numePreparat;
		else this->numePreparat = "-";

		if (numarIngrediente > 0) this->numarIngrediente = numarIngrediente;
		else this->numarIngrediente = 0;

		if (this->numarIngrediente > 0 && ingrediente != nullptr) {

			this->ingrediente = new Ingredient[this->numarIngrediente];
			for (int i = 0; i < this->numarIngrediente; i++)
				this->ingrediente[i] = ingrediente[i];
		}
		else this->ingrediente = nullptr;

		if (this->numarIngrediente > 0 && cantitati != nullptr) {
			this->cantitati = new int[this->numarIngrediente];
			for (int i = 0; i < this->numarIngrediente; i++)
				this->cantitati[i] = cantitati[i];
		}
		else this->cantitati = nullptr;

	}

	Reteta(const Reteta& r) {

		this->numePreparat = r.numePreparat;
		this->numarIngrediente = r.numarIngrediente;
		if (this->numarIngrediente > 0 && r.ingrediente != nullptr) {

			this->ingrediente = new Ingredient[this->numarIngrediente];
			for (int i = 0; i < this->numarIngrediente; i++)
				this->ingrediente[i] = r.ingrediente[i];
		}
		else this->ingrediente = nullptr;
		if (this->numarIngrediente > 0 && r.cantitati != nullptr) {
			this->cantitati = new int[this->numarIngrediente];
			for (int i = 0; i < this->numarIngrediente; i++)
				this->cantitati[i] = r.cantitati[i];
		}

	}

	Reteta& operator=(const Reteta& r) {

		if (this != &r) {

			delete[] this->ingrediente;
			this->ingrediente = nullptr;
			delete[] this->cantitati;
			this->cantitati = nullptr;

			this->numePreparat = r.numePreparat;
			this->numarIngrediente = r.numarIngrediente;
			if (this->numarIngrediente > 0 && r.ingrediente != nullptr) {

				this->ingrediente = new Ingredient[this->numarIngrediente];
				for (int i = 0; i < this->numarIngrediente; i++)
					this->ingrediente[i] = r.ingrediente[i];
			}
			else this->ingrediente = nullptr;
			if (this->numarIngrediente > 0 && r.cantitati != nullptr) {
				this->cantitati = new int[this->numarIngrediente];
				for (int i = 0; i < this->numarIngrediente; i++)
					this->cantitati[i] = r.cantitati[i];
			}
		}
		return *this;

	}

	string getNumePreparat() {
		return this->numePreparat;
	}

	Ingredient* getIngrediente() {
		return this->ingrediente;
	}

	int getNumarIngrediente() {
		return this->numarIngrediente;
	}

	int* getCantitati() {
		return this->cantitati;
	}

	void setNumePreparat(string numePreparat) {
		if (numePreparat.length() > 0)this->numePreparat = numePreparat;
	}

	void setIngredienteNumarIngredienteSiCantitati(int numarIngrediente, int* cantitati, Ingredient* ingrediente) {
		if (numarIngrediente > 0) this->numarIngrediente = numarIngrediente;

		if (this->numarIngrediente > 0 && ingrediente != nullptr) {

			this->ingrediente = new Ingredient[this->numarIngrediente];
			for (int i = 0; i < this->numarIngrediente; i++)
				this->ingrediente[i] = ingrediente[i];
		}

		if (this->numarIngrediente > 0 && cantitati != nullptr) {
			this->cantitati = new int[this->numarIngrediente];
			for (int i = 0; i < this->numarIngrediente; i++)
				this->cantitati[i] = cantitati[i];
		}
	}

	explicit operator int() {

		int numarTotalStocuri = 0;

		for (int i = 0; i < this->numarIngrediente; i++)
			numarTotalStocuri += this->cantitati[i];

		return numarTotalStocuri;

	}


	friend ostream& operator<<(ostream& out, const Reteta& r) {

		out << "\n-----------------Reteta-------------------";

		out << "\nPreparat: " << r.numePreparat;
		out << "\nNumar ingrediente: " << r.numarIngrediente;
		out << "\nIngredientele: ";

		if (r.ingrediente != nullptr && r.numarIngrediente > 0) {
			out << endl;
			for (int i = 0; i < r.numarIngrediente; i++)
				out << r.ingrediente[i].getNume() << " ";
		}
		else
		{
			out << "-";
		}
		out << "\nCantitatile ingredientelor: " << endl;
		if (r.cantitati != nullptr && r.numarIngrediente > 0) {
			for (int i = 0; i < r.numarIngrediente; i++)
				out << r.cantitati[i] << " ";
		}
		else
		{
			out << "-";
		}

		out << "\n------------------------------------------";
		return out;
	}

	friend istream& operator>>(istream& in, Reteta& r) {

		delete[] r.ingrediente;
		r.ingrediente = nullptr;
		delete[] r.cantitati;
		r.cantitati = nullptr;

		cout << "\nNumele preparatului: "; getline(in, r.numePreparat);

		cout << "Numarul de ingrediente: "; in >> r.numarIngrediente;

		if (r.numarIngrediente > 0) {
			r.ingrediente = new Ingredient[r.numarIngrediente];
			cout << "Ingredientele: ";
			for (int i = 0; i < r.numarIngrediente; i++) {
				cin.ignore();
				cout << "\n" << i + 1 << ": "; in >> r.ingrediente[i];
			}
		}
		else r.ingrediente = nullptr;

		if (r.numarIngrediente > 0) {

			r.cantitati = new int[r.numarIngrediente];
			cout << "Cu cantitatile: ";
			for (int i = 0; i < r.numarIngrediente; i++) {
				cout << "\n" << i + 1 << ": "; in >> r.cantitati[i];
			}
		}
		else  r.cantitati = nullptr;

		return in;

	}


	~Reteta() {
		if (this->ingrediente != nullptr) {
			delete[] this->ingrediente;
			this->ingrediente = nullptr;
		}
		if (this->cantitati != nullptr) {
			delete[] this->cantitati;
			this->cantitati = nullptr;
		}

	}


};


class Meniu {

	Reteta* preparate;
	int numarPreparate;

public:

	Meniu() {
		this->preparate = nullptr;
		this->numarPreparate = 0;
	}

	Meniu(Reteta* preparate, int numarPreparate) {

		if (numarPreparate > 0) this->numarPreparate = numarPreparate;
		else
			this->numarPreparate = 0;

		if (this->numarPreparate > 0 && preparate != nullptr) {
			this->preparate = new Reteta[this->numarPreparate];
			for (int i = 0; i < this->numarPreparate; i++)
				this->preparate[i] = preparate[i];
		}
		else
			this->preparate = nullptr;

	}

	Meniu(const Meniu& m) {
		if (numarPreparate > 0) this->numarPreparate = m.numarPreparate;
		else
			this->numarPreparate = 0;

		if (this->numarPreparate > 0 && m.preparate != nullptr) {
			this->preparate = new Reteta[this->numarPreparate];
			for (int i = 0; i < this->numarPreparate; i++)
				this->preparate[i] = m.preparate[i];
		}
		else
			this->preparate = nullptr;
	}

	Meniu& operator=(const Meniu& m) {
		if (this != &m) {
			delete[] this->preparate;
			this->preparate = 0;
			if (numarPreparate > 0) this->numarPreparate = m.numarPreparate;
			else
				this->numarPreparate = 0;

			if (this->numarPreparate > 0 && m.preparate != nullptr) {
				this->preparate = new Reteta[this->numarPreparate];
				for (int i = 0; i < this->numarPreparate; i++)
					this->preparate[i] = m.preparate[i];
			}
			else
				this->preparate = nullptr;

		}
		return *this;
	}

	int getNumarPreparate() {
		return this->numarPreparate;
	}

	Reteta* getPreparate() {
		return this->preparate;
	}

	void setPreparateSiNumarPreparate(int numarPreparate, Reteta* preparate) {
		if (numarPreparate > 0) this->numarPreparate = numarPreparate;

		if (this->numarPreparate > 0 && preparate != nullptr) {
			this->preparate = new Reteta[this->numarPreparate];
			for (int i = 0; i < this->numarPreparate; i++)
				this->preparate[i] = preparate[i];
		}
	}

	friend ostream& operator<<(ostream& out, const Meniu& m) {

		out << "\n-----------------Meniul-------------------";

		out << "\nNumar preparate: " << m.numarPreparate;
		out << "\nPreparatele: ";
		if (m.preparate != nullptr && m.numarPreparate > 0) {

			out << endl;
			for (int i = 0; i < m.numarPreparate; i++)
				out << "-" << m.preparate[i].getNumePreparat() << endl;

		}
		else
		{
			out << "-";
		}
		out << "\n------------------------------------------";
		return out;
	}


	~Meniu() {
		delete[] this->preparate;
		this->preparate = 0;
	}


};

class Comanda {
	int numarComanda;
	Reteta* preparate;
	int nrPreparate;

public:

	Comanda() {
		this->numarComanda = 0;
		this->preparate = nullptr;
		this->nrPreparate = 0;
	}

	Comanda(Reteta* preparate, int nrPreparate, int numarComanda) {
		if (nrPreparate > 0)this->nrPreparate = nrPreparate;
		else this->nrPreparate = 0;

		if (numarComanda > 0)this->numarComanda = numarComanda;
		else this->numarComanda = 0;

		if (this->nrPreparate > 0 && preparate != nullptr) {
			this->preparate = new Reteta[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++) {
				this->preparate[i] = preparate[i];
			}
		}
		else this->preparate = nullptr;
	}

	Comanda(const Comanda& c) {
		this->nrPreparate = c.nrPreparate;
		this->numarComanda = c.numarComanda;

		if (this->nrPreparate > 0 && c.preparate != nullptr) {
			this->preparate = new Reteta[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++) {
				this->preparate[i] = c.preparate[i];
			}
		}
		else this->preparate = nullptr;
	}

	Comanda& operator=(const Comanda& c) {
		if (this != &c) {
			delete[] this->preparate;
			this->preparate = nullptr;

			this->nrPreparate = c.nrPreparate;
			this->numarComanda = c.numarComanda;

			if (this->nrPreparate > 0 && c.preparate != nullptr) {
				this->preparate = new Reteta[this->nrPreparate];
				for (int i = 0; i < this->nrPreparate; i++) {
					this->preparate[i] = c.preparate[i];
				}
			}
			else this->preparate = nullptr;
		}
		return *this;
	}

	int getNumarComanda() {
		return this->numarComanda;
	}

	int getNumarPreparate() {
		return this->nrPreparate;
	}

	Reteta* getPreparate() {
		return this->preparate;
	}

	void setPreparateSiNumarPreparate(int nrPreparate, Reteta* preparate) {
		if (nrPreparate > 0)this->nrPreparate = nrPreparate;

		if (this->nrPreparate > 0 && preparate != nullptr) {
			this->preparate = new Reteta[this->nrPreparate];
			for (int i = 0; i < this->nrPreparate; i++) {
				this->preparate[i] = preparate[i];
			}
		}
	}

	void setNumarComanda(int numarComanda) {
		if (numarComanda > 0)this->numarComanda = numarComanda;
	}

	friend ostream& operator<<(ostream& out, const Comanda& c) {

		out << "\n**************COMANDA****************";

		out << "\nNumarul comenzii: " << c.numarComanda;
		out << "\nNumarul preparatelor este: " << c.nrPreparate;
		out << "\nPreparatele sunt: \n";
		for (int i = 0; i < c.nrPreparate; i++)
			out << "-" << c.preparate[i].getNumePreparat() << endl;

		out << "\n*************************************";
		return out;
	}

	~Comanda() {
		if (this->preparate != nullptr) {
			delete[] this->preparate;
			this->preparate = nullptr;
		}
	}
};

class Restaurant {

	Ingredient* stoc;
	int nrStocuri;
	Comanda* listaComenzi;
	int nrComenzi;
	Meniu meniu;
	string nume;
	const int CUI;

public:

	Restaurant(int CUI) : CUI(CUI) {
		this->nrStocuri = 0;
		this->nrComenzi = 0;
		this->stoc = nullptr;
		this->listaComenzi = nullptr;
		this->meniu = Meniu();
		this->nume = "-";

	}

	Restaurant(Ingredient* stoc, int nrStocuri, Comanda* listaComenzi, int nrComenzi, Meniu meniu, string nume, int CUI) : CUI(CUI) {

		if (nrStocuri > 0)this->nrStocuri = nrStocuri;
		else this->nrStocuri = 0;

		if (nrComenzi > 0) this->nrComenzi = nrComenzi;
		else this->nrComenzi = 0;

		if (nume.length() > 0)this->nume = nume;
		else this->nume = "-";

		this->meniu = meniu;

		if (this->nrStocuri > 0 && stoc != nullptr) {
			this->stoc = new Ingredient[this->nrStocuri];
			for (int i = 0; i < this->nrStocuri; i++) {
				this->stoc[i] = stoc[i];
			}
		}
		else this->stoc = nullptr;

		if (this->nrComenzi > 0 && listaComenzi != nullptr) {
			this->listaComenzi = new Comanda[this->nrComenzi];
			for (int i = 0; i < this->nrComenzi; i++) {
				this->listaComenzi[i] = listaComenzi[i];
			}
		}
		else this->listaComenzi = nullptr;

	}

	bool verificareStoc(Comanda c) {

		Reteta* copiePreparate = c.getPreparate();
		int nrPreparate = c.getNumarPreparate();

		for (int t = 0; t < nrPreparate; t++) {

			Ingredient* copieIngrediente = copiePreparate[t].getIngrediente();
			int nrIngr = copiePreparate[t].getNumarIngrediente();
			int* cantitati = copiePreparate[t].getCantitati();

			for (int i = 0; i < nrIngr; i++) {
				string ingrDeCautat = copieIngrediente[i].getNume();

				for (int j = 0; j < this->nrStocuri; j++) {
					if (ingrDeCautat == this->stoc[j].getNume()) {
						if (this->stoc[j].getCantitate() - cantitati[i] < 0)
							return 0;

					}
				}
			}
		}
		return 1;
	}


	void inregistrareComanda(Comanda c) {

		Reteta* copiePreparate = c.getPreparate();
		int nrPreparate = c.getNumarPreparate();

		for (int t = 0; t < nrPreparate; t++) {

			Ingredient* copieIngrediente = copiePreparate[t].getIngrediente();
			int nrIngr = copiePreparate[t].getNumarIngrediente();
			int* cantitati = copiePreparate[t].getCantitati();

			for (int i = 0; i < nrIngr; i++) {
				string ingrDeCautat = copieIngrediente[i].getNume();

				for (int j = 0; j < this->nrStocuri; j++) {
					if (ingrDeCautat == this->stoc[j].getNume()) {
						this->stoc[j].setCantitate(this->stoc[j].getCantitate() - cantitati[i]);
					}
				}
			}

		}


	}

	Restaurant(const Restaurant& r) : CUI(r.CUI) {
		if (nrStocuri > 0)this->nrStocuri = r.nrStocuri;
		else this->nrStocuri = 0;
		if (nrComenzi > 0) this->nrComenzi = r.nrComenzi;
		else this->nrComenzi = 0;
		if (nume.length() > 0)this->nume = r.nume;
		else this->nume = "-";
		this->meniu = r.meniu;
		if (this->nrStocuri > 0 && r.stoc != nullptr) {
			this->stoc = new Ingredient[this->nrStocuri];
			for (int i = 0; i < this->nrStocuri; i++) {
				this->stoc[i] = r.stoc[i];
			}
		}
		else this->stoc = nullptr;
		if (this->nrComenzi > 0 && r.listaComenzi != nullptr) {
			this->listaComenzi = new Comanda[this->nrComenzi];
			for (int i = 0; i < this->nrComenzi; i++) {
				this->listaComenzi[i] = r.listaComenzi[i];
			}
		}
		else this->listaComenzi = nullptr;
	}

	Restaurant& operator=(const Restaurant& r) {
		if (this != &r) {
			if (this->stoc != nullptr) {
				delete[] this->stoc;
				this->stoc = nullptr;
			}
			if (this->listaComenzi != nullptr) {
				delete[] this->listaComenzi;
				this->listaComenzi = nullptr;
			}
			if (nrStocuri > 0)this->nrStocuri = r.nrStocuri;
			else this->nrStocuri = 0;
			if (nrComenzi > 0) this->nrComenzi = r.nrComenzi;
			else this->nrComenzi = 0;
			if (nume.length() > 0)this->nume = r.nume;
			else this->nume = "-";
			this->meniu = r.meniu;
			if (this->nrStocuri > 0 && r.stoc != nullptr) {
				this->stoc = new Ingredient[this->nrStocuri];
				for (int i = 0; i < this->nrStocuri; i++) {
					this->stoc[i] = r.stoc[i];
				}
			}
			else this->stoc = nullptr;
			if (this->nrComenzi > 0 && r.listaComenzi != nullptr) {
				this->listaComenzi = new Comanda[this->nrComenzi];
				for (int i = 0; i < this->nrComenzi; i++) {
					this->listaComenzi[i] = r.listaComenzi[i];
				}
			}
			else this->listaComenzi = nullptr;

		}
		return *this;
	}

	void afisareStoc() {
		cout << "\n###############STOCURI################";

		cout << "\n\nLista ingrediente si cantitati:\n";
		for (int i = 0; i < this->nrStocuri; i++)
			cout << "-" << this->stoc[i].getNume() << " " << this->stoc[i].getCantitate() << endl;


		cout << "\n\n#######################################";
	}

	Ingredient* getStoc() {
		return this->stoc;
	}

	int getNumarStocuri() {
		return this->nrStocuri;
	}
	Comanda* getListaComenzi() {
		return this->listaComenzi;
	}

	int getNumarComenzi() {
		return this->nrComenzi;
	}

	Meniu getMeniu() {
		return this->meniu;
	}

	string getNume() {
		return this->nume;
	}

	void setStocSiNumarStocuri(int nrStocuri, Ingredient* stoc) {

		if (nrStocuri > 0)this->nrStocuri = nrStocuri;

		if (this->nrStocuri > 0 && stoc != nullptr) {
			this->stoc = new Ingredient[this->nrStocuri];
			for (int i = 0; i < this->nrStocuri; i++) {
				this->stoc[i] = stoc[i];
			}
		}
	}

	void setComenziSiNumarComenzi(int nrComenzi, Comanda* listaComenzi) {
		if (nrComenzi > 0) this->nrComenzi = nrComenzi;

		if (this->nrComenzi > 0 && listaComenzi != nullptr) {
			this->listaComenzi = new Comanda[this->nrComenzi];
			for (int i = 0; i < this->nrComenzi; i++) {
				this->listaComenzi[i] = listaComenzi[i];
			}
		}
	}

	void setNume(string nume) {
		if (nume.length() > 0)this->nume = nume;
	}

	void setMeniu(Meniu meniu) {
		this->meniu = meniu;
	}

	friend ostream& operator<<(ostream& out, const Restaurant& r) {

		out << "\n*-*-*-*-*-*-*-*-*-*RESTAURANT*-*-*-*-*-*-*-*-*-*-*";

		out << "\nNumele restaurantului: " << r.nume;
		out << "\nCUI-ul restaurantului: " << r.CUI;
		out << "\nNumarul de stocuri: " << endl;
		for (int i = 0; i < r.nrStocuri; i++) {
			out << "-" << r.stoc[i].getNume() << endl;
		}
		out << "\nNumarul de comenzi: " << r.nrComenzi;

		out << "\nID-ul comenzilor: " << endl;
		for (int i = 0; i < r.nrComenzi; i++) {
			out << "-" << r.listaComenzi[i].getNumarComanda() << endl;
		}

		out << "\n*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-";
		return out;
	}

	void operator[](int maxim) {

		for (int i = 0; i < this->nrStocuri; i++) {
			this->stoc[i].setCantitate(maxim);
		}
	}

	void operator!() {
		for (int i = 0; i < this->nrStocuri; i++) {
			this->stoc[i].setCantitate(0);
		}
	}

	~Restaurant() {
		if (this->stoc != nullptr) {
			delete[] this->stoc;
			this->stoc = nullptr;
		}
		if (this->listaComenzi != nullptr) {
			delete[] this->listaComenzi;
			this->listaComenzi = nullptr;
		}
	}

};


int Ingredient::cantitateMaxima = 100;


Ingredient operator+(int stocSuplimentar, Ingredient i) {
	return i + stocSuplimentar;
}


int main()
{
	//SETUP

	Ingredient i1;

	Ingredient i2("morcov", 5);
	Ingredient i3("carne", 4);
	Ingredient i4("rosie", 4);
	Ingredient i5("ceapa", 10);
	Ingredient i6("ardei", 7);
	Ingredient i7("patrunjel", 4);

	Ingredient i8("oua", 12);
	Ingredient i9("cascaval", 20);
	Ingredient i10("sare", 100);
	Ingredient i11("piper", 100);
	Ingredient i12("bacon", 15);
	Ingredient i13("paine", 4);

	Ingredient i14("mere", 10);
	Ingredient i15("faina", 3);
	Ingredient i16("lapte", 7);
	Ingredient i17("vanilie", 3);
	Ingredient i18("drojdie", 6);
	//Ingredient i19();

	Ingredient i20("cartofi", 10);
	Ingredient i21("ulei", 3);



	Ingredient j1[] = { i2,i3,i4,i5,i6,i7 };
	Ingredient j2[] = { i8,i9,i10,i11,i12,i13 };
	Ingredient j3[] = { i8,i14,i15,i16,i17,i18 };
	Ingredient j4[] = { i20,i21 };


	int cant1[] = { 2,2,2,1,1,1 };
	int cant2[] = { 3,4,2,1,2,1 };
	int cant3[] = { 1,1,2,3,1,1 };
	int cant4[] = { 4,1 };

	Reteta r1(j1, 6, "ciorba", cant1);
	Reteta r2(j2, 6, "mic_dejun", cant2);
	Reteta r3(j3, 6, "placinta_cu_mere", cant3);
	Reteta r4(j4, 2, "cartofi_prajiti", cant4);

	Reteta r[] = { r1,r2,r3,r4 };

	Reteta comanda1[] = { r1,r4 };
	Reteta comanda2[] = { r2 };
	Reteta comanda3[] = { r3 };
	Reteta comanda4[] = { r1,r2,r3,r4 };
	Reteta comanda5[] = { r1,r2,r3 };

	Comanda c1(comanda1, 2, 1);
	Comanda c2(comanda2, 1, 2);
	Comanda c3(comanda3, 1, 3);
	Comanda c4(comanda4, 4, 4);
	Comanda c5(comanda5, 3, 5);

	Comanda c[] = { c1,c2,c3,c4,c5 };
	Ingredient stoc[] = { i2,i3,i4,i5,i6,i7,i8,i9,i10,i11,i12,i13,i14,i15,i16,i17,i18,i20,i21 };
	Meniu m(r, 4);


	Restaurant restaurant(stoc, 19, c, 5, m, "Sete si Foame", 123456789);

	//FINAL SETUP


	cout << "\nLista comenzi:";
	cout << "\ncmd - permite plasarea unei comenzi daca exista intredientele disponibile";
	cout << "\nmeniu - afiseaza meniul cu toate retetele disponibile la restaurant";
	cout << "\nafisstoc - afiseaza lista cu toate ingredientele din stoc ";
	cout << "\nlistacomenzi - afiseaza lista comenzilor ce pot fi folosite in program";
	cout << "\nexit - opreste programul";
	cout << "\n\nATENTIE! Dupa selectarea comenzii cmd veti fi intrebat cate produse doriti sa comandati. ";
	cout << "\n         Raspunsul va fi de la 1 la 3, programul avand capacitatea de a plasa o comanda ";
	cout << "\n         cu maxim 3 atribute. Formatul comanzii cmd va fi urmatorul:";
	cout << "\n         ----> cmd <nume_preparat1> <nume_preparat2> <nume_preparat3>";
	cout << "\n         Se vor scrie atatea nume de preparate cate au fost specificate ca se vor ";
	cout << "\n         introduce, exact asa cum sunt scrise in meniu.";
	cout << endl;



	string action;
	string produs1;
	string produs2;
	string produs3;

	int prod;
	int countComenzi = 0;

	while (action != "exit") {

		string command;
		cout << "\nEnter your command: ";

		getline(cin, command);
		stringstream ss(command);
		ss >> action;
		if (action == "cmd") {

			cout << "\nCate produse vrei sa comanzi?\n "; cin >> prod;
			cout << m;
			if (prod == 1) {

				cout << "\nCe vrei sa comanzi: ";
				cin.ignore();
				getline(cin, command);
				stringstream ss(command);
				ss >> action >> produs1;

				countComenzi++;
				Reteta deComandat[4];
				int nrPreparateComandate = 0;

				for (int i = 0; i < 4; i++)
					if (produs1 == r[i].getNumePreparat())
					{
						deComandat[nrPreparateComandate] = r[i];
						nrPreparateComandate++;
					}

				Comanda comandaActuala(deComandat, nrPreparateComandate, countComenzi);

				cout << comandaActuala;

				if (restaurant.verificareStoc(comandaActuala) == 1) {
					restaurant.inregistrareComanda(comandaActuala);
					cout << "\nComanda a fost inregistrata cu succes!";
				}
				else
					cout << "\nStocuri insuficiente pentru comanda dumneavoastra!";
			}
			else if (prod == 2) {
				cout << "\nCe vrei sa comanzi: ";
				cin.ignore();
				getline(cin, command);
				stringstream ss(command);
				ss >> action >> produs1 >> produs2;

				countComenzi++;
				Reteta deComandat[4];
				int nrPreparateComandate = 0;

				for (int i = 0; i < 4; i++) {
					if (produs1 == r[i].getNumePreparat())
					{
						deComandat[nrPreparateComandate] = r[i];
						nrPreparateComandate++;
					}
					if (produs2 == r[i].getNumePreparat())
					{
						deComandat[nrPreparateComandate] = r[i];
						nrPreparateComandate++;
					}


				}
				Comanda comandaActuala(deComandat, nrPreparateComandate, countComenzi);

				cout << comandaActuala;

				if (restaurant.verificareStoc(comandaActuala) == 1) {
					restaurant.inregistrareComanda(comandaActuala);
					cout << "\nComanda a fost inregistrata cu succes!";
				}
				else
					cout << "\nStocuri insuficiente pentru comanda dumneavoastra!";
			}
			else if (prod == 3) {
				cout << "\nCe vrei sa comanzi: ";
				cin.ignore();
				getline(cin, command);
				stringstream ss(command);
				ss >> action >> produs1 >> produs2 >> produs3;

				countComenzi++;
				Reteta deComandat[4];
				int nrPreparateComandate = 0;

				for (int i = 0; i < 4; i++) {
					if (produs1 == r[i].getNumePreparat())
					{
						deComandat[nrPreparateComandate] = r[i];
						nrPreparateComandate++;
					}
					if (produs2 == r[i].getNumePreparat())
					{
						deComandat[nrPreparateComandate] = r[i];
						nrPreparateComandate++;
					}
					if (produs3 == r[i].getNumePreparat())
					{
						deComandat[nrPreparateComandate] = r[i];
						nrPreparateComandate++;
					}

				}
				Comanda comandaActuala(deComandat, nrPreparateComandate, countComenzi);

				cout << comandaActuala;

				if (restaurant.verificareStoc(comandaActuala) == 1) {
					restaurant.inregistrareComanda(comandaActuala);
					cout << "\nComanda a fost inregistrata cu succes!";
				}
				else
					cout << "\nStocuri insuficiente pentru comanda dumneavoastra!";
			}
			else cout << "\nNUMAR GRESIT";
		}
		else if (action == "meniu") {
			cout << m;
		}
		else if (action == "exit") {
			cout << "\nIESIRE ALICATIE";
		}
		else if (action == "afisstoc") {
			restaurant.afisareStoc();
		}
		else if (action == "listacomenzi") {

			cout << "\nLista comenzi:";
			cout << "\ncmd - permite plasarea unei comenzi daca exista intredientele disponibile";
			cout << "\nmeniu - afiseaza meniul cu toate retetele disponibile la restaurant";
			cout << "\nafisstoc - afiseaza lista cu toate ingredientele din stoc ";
			cout << "\nlistacomenzi - afiseaza lista comenzilor ce pot fi folosite in program";
			cout << "\nexit - opreste programul";
			cout << "\n\nATENTIE! Dupa selectarea comenzii cmd veti fi intrebat cate produse doriti sa comandati. ";
			cout << "\n         Raspunsul va fi de la 1 la 3, programul avand capacitatea de a plasa o comanda ";
			cout << "\n         cu maxim 3 atribute. Formatul comanzii cmd va fi urmatorul:";
			cout << "\n         ----> cmd <nume_preparat1> <nume_preparat2> <nume_preparat3>";
			cout << "\n         Se vor scrie atatea nume de preparate cate au fost specificate ca se vor ";
			cout << "\n         introduce, exact asa cum sunt scrise in meniu.";
			cout << endl;
		}
		else
		{
			cout << "Comanda invalida.\n";
		}


	}



	/*TESTARE ELEMENTE INTRODUSE IN PROIECT

		cout << (int)r1;

		cout << endl;
		cout << endl;

		cout << i2.getCantitate();
		i2 + 10;
		cout << endl; cout << i2.getCantitate();

		cout << endl;
		cout << endl;

		if (i2 == i3)
		cout << "EGALE";
		else cout << "INEGALE";

		cout << endl;
		cout << endl;

		if (i2 > i3)
		cout << "i2 e mai mare";
		else cout << "i3 e mai mare";


		cout << restaurant;
		restaurant.afisareStoc();

		cout << "\n*****************************************************************";

		Reteta ret[] = { r4,r3 };
		Comanda cmd(ret, 2, 6);
		cout << cmd;

		restaurant.afisareStoc();
		cout << "\nAVEM STOC DISPONIBIL: " << restaurant.verificareStoc(cmd) << endl;
		restaurant.inregistrareComanda(cmd);
		restaurant.afisareStoc();


		cout << "\n*****************************************************************";
		restaurant.afisareStoc();


		cout << endl;
		cout << endl;

		Ingredient ii("Rucola", 10);
		cout << ii;
		cout << ++ii;
		cout << ii++;
		cout << ii;

		cout << endl;
		cout << endl;

		restaurant.afisareStoc();
		restaurant[Ingredient::getCantitateMaxima()];
		restaurant.afisareStoc();


		cout << "\n=============TESTARE SETTER PENTRU CLASA RESTAURANT=================";

		cout << restaurant;
		Reteta testSetterRestaurant[] = { r1 };
		Comanda testSetter(testSetterRestaurant, 1, 7);
		Comanda tset[] = { testSetter };
		Reteta retetar[] = { r1,r2 };
		Meniu meniuTestSetter(retetar, 2);
		Ingredient tsetter[] = { i2,i3 };
		restaurant.setNume("La Mihaitza Boss");
		restaurant.setComenziSiNumarComenzi(1, tset);
		restaurant.setStocSiNumarStocuri(2, tsetter);
		restaurant.setMeniu(meniuTestSetter);
		cout << restaurant;
		restaurant.afisareStoc();
		cout << "\n=====================================================================";

		cout << endl;
		cout << endl;

		cout << "\nURMEAZA CITIREA UNEI RETETE: \n";

		Reteta rr;
		cout << rr;
		cin >> rr;
		cout << rr;

		cout << "\nAM TERMINAT CITIREA UNEI RETETE\n";
		restaurant.afisareStoc();
		!restaurant;
		restaurant.afisareStoc();

		FINAL TESTARE ELEMENTE INTRODUSE IN PROIECT*/

	return 0;
}


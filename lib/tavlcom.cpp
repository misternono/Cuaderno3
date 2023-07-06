

#include "tavlcom.h"
using namespace std;

TNodoAVL::TNodoAVL() {
	fe = 0;
}

void TNodoAVL::copiarNodo(const TNodoAVL &other) {
	this->fe = other.fe;
    this->item = other.item;
    this->de = other.de;
    this->iz = other.iz;
}

TNodoAVL::TNodoAVL(const TNodoAVL &nodo) {
	copiarNodo(nodo);
}

TNodoAVL::~TNodoAVL() {
	fe = 0;
}

TNodoAVL & TNodoAVL::operator=(const TNodoAVL &node) {
	if (this != &node) {
		this->item = node.item;
		this->de = node.de;
		this->iz = node.iz;
	}

	return *this;
}

///////////
//TAVLCOM//
///////////

TAVLCom::TAVLCom() {
	this->raiz = NULL;
}

void TAVLCom::copiarArbol(const TAVLCom &arbol) {
	if (!arbol.EsVacio()) {
		this->raiz = new TNodoAVL();
		this->raiz->item = arbol.raiz->item;
		this->raiz->iz.copiarArbol(arbol.raiz->iz);
		this->raiz->de.copiarArbol(arbol.raiz->de);
	} else
		this->raiz = NULL;
}

TAVLCom::TAVLCom(const TAVLCom &arbol) {
	this->copiarArbol(arbol);
}

TAVLCom::~TAVLCom() {
	while (!this->EsVacio()) {
		TNodoAVL *aux;
		aux = this->raiz;

		this->raiz->iz.~TAVLCom();
		this->raiz->de.~TAVLCom();

		delete this->raiz;
		this->raiz = NULL;
	}
}

TAVLCom & TAVLCom::operator=(const TAVLCom &arbol) {
	if (this != &arbol) {
		this->~TAVLCom();

		this->copiarArbol(arbol);
	}

	return *this;
}

bool TAVLCom::operator==(const TAVLCom &arbol) const {
	if (this->Inorden() == arbol.Inorden())
		return true;
	else
		return false;
}

bool TAVLCom::operator!=(const TAVLCom &arbol) const {
	return !this->operator ==(arbol);
}

bool TAVLCom::EsVacio() const {
	if (this->raiz)
		return false;
	else
		return true;
}

void TAVLCom::actualizarFE() {

	if (!EsVacio()) {
		raiz->fe = raiz->de.Altura() - raiz->iz.Altura();
		if (!raiz->de.EsVacio())
			raiz->de.actualizarFE();
		if (!raiz->iz.EsVacio())
			raiz->iz.actualizarFE();
	}
}

bool TAVLCom::comprobarFe() {

	if (raiz->de.raiz != NULL) {
		raiz->de.comprobarFe();
	}
	if (raiz->iz.raiz != NULL) {
		raiz->iz.comprobarFe();
	}

	if (raiz->fe == 2) {
		if (raiz->de.raiz->fe == 1 || raiz->de.raiz->fe == 0) {
			reestructurarRR();
		}
		if (raiz->de.raiz->fe == -1) {
			reestructurarRL();
		}
	} else if (this->raiz->fe == -2) {
		if (this->raiz->iz.raiz->fe == 1) {
			reestructurarLR();
		} else if (this->raiz->iz.raiz->fe == -1 || raiz->iz.raiz->fe == 0) {
			reestructurarLL();
		}
	}

	return true;
}

void TAVLCom::reestructurarLL() {
	TNodoAVL *aux = raiz->iz.raiz->de.raiz;
	raiz->iz.raiz->de.raiz = raiz;
	raiz->iz.raiz->fe = 0;
	TNodoAVL *aux2 = raiz->iz.raiz;
	raiz->iz.raiz = aux;
	raiz->fe = 0;
	raiz = aux2;
}

void TAVLCom::reestructurarRR() {
	TNodoAVL *aux = raiz->de.raiz->iz.raiz;
	raiz->de.raiz->iz.raiz = raiz;
	raiz->de.raiz->fe = 0;
	TNodoAVL *aux2 = raiz->de.raiz;
	raiz->de.raiz = aux;
	raiz->fe = 0;
	raiz = aux2;
}

void TAVLCom::reestructurarLR() {
	raiz->iz.reestructurarRR();
	reestructurarLL();
}

void TAVLCom::reestructurarRL() {
	raiz->de.reestructurarLL();
	reestructurarRR();
}

bool TAVLCom::Insertar(const TComplejo &complejo) {
	bool insertado = false;

	if (this->EsVacio()) {
		TNodoAVL *aux = new TNodoAVL();
		aux->item = complejo;
		this->raiz = aux;

		insertado = true;
	} else {
		if (!this->Buscar(complejo)) {
			if (this->mayor(complejo))
				insertado = this->raiz->de.Insertar(complejo);
			else
				insertado = this->raiz->iz.Insertar(complejo);
		}
	}

	if (insertado) {
		this->actualizarFE();
		this->comprobarFe();
	}

	return insertado;
}

bool TAVLCom::mayor(TComplejo complejo) const {
	bool may = false;

	if (complejo.Mod() == this->raiz->item.Mod()) {
		if (complejo.Re() == this->raiz->item.Re()) {
			if (complejo.Im() == this->raiz->item.Im()) //si mod, re e im son iguales -> false
				may = false;
			else {
				if (complejo.Im() < this->raiz->item.Im())
					may = false;
				if (complejo.Im() > this->raiz->item.Im())
					may = true;
				;
			}
		} else {
			if (complejo.Re() < this->raiz->item.Re())
				may = false;
			if (complejo.Re() > this->raiz->item.Re())
				may = true;
		}
	} else {
		if (complejo.Mod() < this->raiz->item.Mod())
			may = false;
		if (complejo.Mod() > this->raiz->item.Mod())
			may = true;
	}

	return may;
}

bool TAVLCom::Buscar(const TComplejo &complejo) const {
	if (!EsVacio()) {
		if (this->raiz->item == complejo)
			return true;
		else {
			if (this->raiz->iz.Buscar(complejo)
					|| this->raiz->de.Buscar(complejo))
				return true;
			else
				return false;
		}
	}

	return false;
}

bool TAVLCom::Borrar(const TComplejo &complejo) {
	bool borrado = false;
	borrado = BorrarAux(complejo);
	if (!EsVacio()) {
		actualizarFE();
		comprobarFe();
	}
	return borrado;
}

TComplejo TAVLCom::maxIzq(const TAVLCom &arbol) {
	return (arbol.raiz->de.raiz != NULL) ?
			maxIzq(arbol.raiz->de) : arbol.raiz->item;

}

bool TAVLCom::BorrarAux(const TComplejo &complejo) {

	if (!raiz)
		return false;
	if (raiz->item == complejo) {
		if (raiz->de.raiz != NULL && raiz->iz.raiz != NULL) {
			// El mayor de la izquierda
			raiz->item = maxIzq(raiz->iz);
			raiz->iz.Borrar(raiz->item);
			return true;
		} else if (this->esHoja()) {
			if (raiz)
				delete raiz;
			raiz = NULL;
			return true;
		} else {
			// Solo tiene 1 hijo
			if (raiz->iz.raiz != NULL) {
				TNodoAVL *aux = new TNodoAVL((*raiz->iz.raiz));
				(raiz->iz).~TAVLCom();
				raiz = aux;
				return true;
			}
			if (raiz->de.raiz != NULL) {
				TNodoAVL *aux = new TNodoAVL((*raiz->de.raiz));
				(raiz->de).~TAVLCom();
				raiz = aux;
				return true;
			}

		}
	} else {
		return raiz->de.Borrar(complejo) || raiz->iz.Borrar(complejo);
	}
}
int TAVLCom::Altura() const {
	if (!EsVacio()) {
		return 1 + max(raiz->de.Altura(), raiz->iz.Altura());
	} else
		return 0;
}

int TAVLCom::Nodos() const {
	if (!EsVacio()) {
		return 1 + raiz->de.Nodos() + raiz->iz.Nodos();
	} else
		return 0;
}

int TAVLCom::NodosHoja() const {
	if (!EsVacio()) {
		if (!raiz->iz.EsVacio() || !raiz->de.EsVacio()) {
			return raiz->iz.NodosHoja() + raiz->de.NodosHoja();
		} else
			return 1;
	} else
		return 0;
}

TVectorCom TAVLCom::Inorden() const {
	int pos = 1;
	TVectorCom v(this->Nodos());

	this->InordenAux(v, pos);

	return v;
}

TVectorCom TAVLCom::Preorden() const {
	int pos = 1;
	TVectorCom v(this->Nodos());

	this->PreordenAux(v, pos);

	return v;
}

TVectorCom TAVLCom::Postorden() const {
	int pos = 1;
	TVectorCom v(this->Nodos());

	this->PostordenAux(v, pos);

	return v;
}

TComplejo TAVLCom::Raiz() const {
	if (this->EsVacio())
		return TComplejo();
	else
		return this->raiz->item;
}

bool TAVLCom::esHoja() const {
	if (this->raiz->de.EsVacio() && this->raiz->iz.EsVacio())
		return true;
	else
		return false;
}

void TAVLCom::InordenAux(TVectorCom &v, int &x) const {
	if (!this->EsVacio()) {
		if (this->esHoja()) { //Es un nodo hoja
			//Lo añado al vector y acabo recur
			v[x] = this->raiz->item;
			x++;
		} else {
			this->raiz->iz.InordenAux(v, x);
			v[x] = this->raiz->item;
			x++;
			this->raiz->de.InordenAux(v, x);
		}
	}
}

void TAVLCom::PreordenAux(TVectorCom &v, int &x) const {
	if (!this->EsVacio()) {
		if (this->esHoja()) {			//Es un nodo hoja
			//Lo añado al vector y acabo recur
			v[x] = this->raiz->item;
			x++;
		} else {
			v[x] = this->raiz->item;
			x++;
			this->raiz->iz.PreordenAux(v, x);
			this->raiz->de.PreordenAux(v, x);
		}
	}
}

void TAVLCom::PostordenAux(TVectorCom &v, int &x) const {
	if (!this->EsVacio()) {
		if (this->esHoja()) {				//Es un nodo hoja
			//Lo añado al vector y acabo recur
			v[x] = this->raiz->item;
			x++;
		} else {
			this->raiz->iz.PostordenAux(v, x);
			this->raiz->de.PostordenAux(v, x);
			v[x] = this->raiz->item;
			x++;
		}
	}
}

ostream & operator<<(ostream &salida, TAVLCom &arbol) {
	salida << arbol.Inorden();

	return salida;
}
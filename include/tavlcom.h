/*
 * tavlcom.h
 *
 *  Created on: 06/05/2014
 *      Author: jorge
 */

#ifndef TAVLCOM_H_
#define TAVLCOM_H_

#include "tvectorcom.h"
//using namespace std;
class TNodoAVL;

class TAVLCom {
	friend class TNodoAVL;
	friend std::ostream & operator<<(std::ostream &, TAVLCom &);

public:
	TAVLCom();
	TAVLCom(const TAVLCom &);
	~TAVLCom();
	TAVLCom & operator=(const TAVLCom &);

	bool operator==(const TAVLCom &) const;
	bool operator!=(const TAVLCom &) const;
	bool EsVacio() const;
	bool Insertar(const TComplejo &);
	bool Buscar(const TComplejo &) const;
	bool Borrar(const TComplejo &);
	int Altura() const;
	int Nodos() const;
	int NodosHoja() const;
	TVectorCom Inorden() const;
	TVectorCom Preorden() const;
	TVectorCom Postorden() const;
	TComplejo Raiz() const;
	TComplejo maxIzq(const TAVLCom &);

private:
	TNodoAVL *raiz;

	void copiarArbol(const TAVLCom &);
	void InordenAux(TVectorCom &, int &) const;
	void PreordenAux(TVectorCom &, int &) const;
	void PostordenAux(TVectorCom &, int &) const;
	bool esHoja() const;
	void actualizarFE();
	bool mayor(TComplejo) const ;
	bool comprobarFe();
	void reestructurarLL();
	void reestructurarLR();
	void reestructurarRL();
	void reestructurarRR();
	bool BorrarAux (const TComplejo &);
};

class TNodoAVL {
	friend class TAVLCom;
public:
	TNodoAVL();
	TNodoAVL(const TNodoAVL &);
	~TNodoAVL();
	TNodoAVL & operator=(const TNodoAVL &);

private:
	TComplejo item;
	TAVLCom iz, de;
	int fe;

	void copiarNodo(const TNodoAVL &);
};

#endif /* TAVLCOM_H_ */
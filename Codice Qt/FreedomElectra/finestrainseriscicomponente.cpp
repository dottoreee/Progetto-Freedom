#include "finestrainseriscicomponente.h"

FinestraInserisciComponente::FinestraInserisciComponente(DatabaseComponenti* d, Cliente* c, SalaCompressori* s ,QDialog *parent):QDialog(parent), db(d), cl(c), sala(s){
    this->setWindowTitle("Finestra Inserisci Componenti");
    this->setMinimumSize(340,340);

    // new
    layoutSfondo=new QVBoxLayout(this);
    layoutDatiComponente = new QGridLayout();
    layoutBottoni = new QHBoxLayout();
    boxDatiComponente = new QGroupBox(this);
    boxBottoni = new QGroupBox(this);
    comboBoxTipo = new QComboBox();
    labelTipo = new QLabel("Tipo:");
    labelMarca=new QLabel("Marca:");
    labelModello = new QLabel("Modello:");
    labelAnno = new QLabel("Anno:");
    labelPressione = new QLabel("Pressione (Bar):");
    labelPortata_Capacita = new QLabel("Portata o Capacita (Lt/s):");
    labelCadDiPress = new QLabel("Caduta di pressione (Bar):");
    labelKw = new QLabel("Kw:");
    lineEditMarca = new QLineEdit(this);
    lineEditModello = new QLineEdit(this);
    lineEditAnno = new QLineEdit("2000");
    lineEditAnno->setInputMask("9999");
    lineEditPressione = new QLineEdit("07.0");
    lineEditPressione->setInputMask("xx.x");
    lineEditPortata_Capacita = new QLineEdit("0");
    lineEditCadDiPress = new QLineEdit("0");
    lineEditKw = new QLineEdit("0");
    lineEditKw->setDisabled(true);
    bottoneIndietro=new QPushButton("Torna indietro",this);
    bottoneSalva = new QPushButton("Salva",this);
    bottoneSalva->setDefault(true);

    comboBoxTipo->insertItem(0,"Seleziona il tipo");
    comboBoxTipo->insertItem(1,"Compressore On-Off");
    comboBoxTipo->insertItem(2,"Essiccatore On-Off");
    comboBoxTipo->insertItem(3,"Compressorie Vel variable");
    comboBoxTipo->insertItem(4,"Essiccatore Vel variabile");
    comboBoxTipo->insertItem(5,"Impianto");
    comboBoxTipo->insertItem(6,"Filtro");
    comboBoxTipo->insertItem(7,"Serbatoio");

    // associazione box e layout
    layoutSfondo->addWidget(boxDatiComponente);
    layoutSfondo->addWidget(boxBottoni);
    boxDatiComponente->setLayout(layoutDatiComponente);
    boxBottoni->setLayout(layoutBottoni);

    // associazione a layoutDatiComponente
    layoutDatiComponente->addWidget(labelTipo,0,0);
    layoutDatiComponente->addWidget(comboBoxTipo,0,1);
    layoutDatiComponente->addWidget(labelMarca,1,0);
    layoutDatiComponente->addWidget(lineEditMarca,1,1);
    layoutDatiComponente->addWidget(labelModello,2,0);
    layoutDatiComponente->addWidget(lineEditModello,2,1);
    layoutDatiComponente->addWidget(labelAnno,3,0);
    layoutDatiComponente->addWidget(lineEditAnno,3,1);
    layoutDatiComponente->addWidget(labelPressione,4,0);
    layoutDatiComponente->addWidget(lineEditPressione,4,1);
    layoutDatiComponente->addWidget(labelPortata_Capacita,5,0);
    layoutDatiComponente->addWidget(lineEditPortata_Capacita,5,1);
    layoutDatiComponente->addWidget(labelCadDiPress,6,0);
    layoutDatiComponente->addWidget(lineEditCadDiPress,6,1);
    layoutDatiComponente->addWidget(labelKw,7,0);
    layoutDatiComponente->addWidget(lineEditKw,7,1);

    // associazione a layoutBottoni
    layoutBottoni->addWidget(bottoneIndietro);
    layoutBottoni->addWidget(bottoneSalva);

    this->setLayout(layoutSfondo);

    lineEditMarca->setDisabled(true);
    lineEditModello->setDisabled(true);
    lineEditAnno->setDisabled(true);
    lineEditCadDiPress->setDisabled(true);
    lineEditPortata_Capacita->setDisabled(true);
    lineEditPressione->setDisabled(true);
    lineEditKw->setDisabled(true);

    connect(bottoneIndietro,SIGNAL(clicked()),this,SLOT(torna()));
    connect(bottoneSalva,SIGNAL(clicked()),this,SLOT(salva()));
    connect(comboBoxTipo,SIGNAL(currentIndexChanged(int)),this,SLOT(sbloccaLineEdit()));
}

void FinestraInserisciComponente::sbloccaLineEdit(){
    if (comboBoxTipo->currentIndex()==0){
        lineEditMarca->setDisabled(true);
        lineEditModello->setDisabled(true);
        lineEditAnno->setDisabled(true);
        lineEditCadDiPress->setDisabled(true);
        lineEditPortata_Capacita->setDisabled(true);
        lineEditPressione->setDisabled(true);
        lineEditKw->setDisabled(true);
    }
    else
        if (comboBoxTipo->currentIndex()!=5 && comboBoxTipo->currentIndex()!=6 && comboBoxTipo->currentIndex()!=7){
            lineEditMarca->setDisabled(false);
            lineEditModello->setDisabled(false);
            lineEditAnno->setDisabled(false);
            lineEditCadDiPress->setDisabled(false);
            lineEditPortata_Capacita->setDisabled(false);
            lineEditPressione->setDisabled(false);
            lineEditKw->setDisabled(false);
        }
        else{
            lineEditMarca->setDisabled(false);
            lineEditModello->setDisabled(false);
            lineEditAnno->setDisabled(false);
            lineEditCadDiPress->setDisabled(false);
            lineEditPortata_Capacita->setDisabled(false);
            lineEditPressione->setDisabled(false);
            labelKw->setDisabled(true);
            lineEditKw->setDisabled(true);
        }
}

int FinestraInserisciComponente::calcolaIdComponente() const{
    if (db->isEmpty()==true)
        return 1;
    else{
        int idesatto;
        bool trovato=false;
        for (DatabaseComponenti::Iteratore cit=db->begin(); !trovato && cit!=db->end(); cit++){
            trovato=true;
            idesatto = (*cit)->getIdComponente();
        }
        return (idesatto+1);
    }
}

void FinestraInserisciComponente::salva(){

    string marca = lineEditMarca->text().toStdString();
    string modello = lineEditModello->text().toStdString();
    int anno = lineEditAnno->text().toInt();
    float pressione = lineEditPressione->text().toFloat();
    float portataCapacita = lineEditPortata_Capacita->text().toFloat();
    float cdp = lineEditCadDiPress->text().toFloat();
    int kw = lineEditKw->text().toInt();
    int idComponente = calcolaIdComponente();

    bool inserito;

    FinestraInserisciComponente::sbloccaLineEdit();

    if (lineEditMarca->text()!=""){
        if (comboBoxTipo->currentIndex()==1 || comboBoxTipo->currentIndex()==2){
            if (comboBoxTipo->currentIndex()==1){
                Componente* a = new OnOff(marca, modello, anno, pressione, portataCapacita, cdp, kw,true,cl,sala,idComponente);
                inserito = db->inserisciComponente(a);
                sala->aggiungiComponente(a);
            }
            else{
                Componente* a = new OnOff(marca, modello, anno, pressione, portataCapacita, cdp, kw,false,cl,sala,idComponente);
                inserito = db->inserisciComponente(a);
                sala->aggiungiComponente(a);}
        }
        else if (comboBoxTipo->currentIndex()==3 || comboBoxTipo->currentIndex()==4){
            if (comboBoxTipo->currentIndex()==3){
                Componente* a = new VelocitaVariabile(marca, modello, anno, pressione, portataCapacita, cdp ,kw,true,cl,sala,idComponente);
                inserito = db->inserisciComponente(a);
                sala->aggiungiComponente(a);}
            else{
                Componente* a = new VelocitaVariabile(marca, modello, anno, pressione, portataCapacita, cdp ,kw,false,cl,sala,idComponente);
                inserito = db->inserisciComponente(a);
                sala->aggiungiComponente(a);}
        }
        else if (comboBoxTipo->currentIndex()==5){
            Componente* a = new Impianto(marca, modello, anno, pressione, portataCapacita,cdp,cl,sala,idComponente);
            inserito = db->inserisciComponente(a);
            sala->aggiungiComponente(a);
        }
        else if (comboBoxTipo->currentIndex()==6){
            Componente* a = new Filtro(marca, modello, anno, pressione, portataCapacita,cdp,cl,sala,idComponente);
            inserito = db->inserisciComponente(a);
            sala->aggiungiComponente(a);
        }
        else if (comboBoxTipo->currentIndex()==7){
            Componente* a = new Serbatoio(marca, modello, anno, pressione, portataCapacita,cdp,cl,sala,idComponente);
            inserito = db->inserisciComponente(a);
            sala->aggiungiComponente(a);
        }
        else
            inserito=false;
        QMessageBox messageBox(this);
        if (inserito) {
            messageBox.setText("Componente inserito con successo!");
            messageBox.exec();
            this->close();
        }
        else {
            messageBox.setText("Compilare i campi.");
            messageBox.exec();
        }
    }
    else {
        QMessageBox messageBox(this);
        messageBox.setText("Inserire una marca non vuota.");
        messageBox.exec();
    }
}

void FinestraInserisciComponente::torna(){
    this->close();
}

#include "finestraclienteselezionato.h"

FinestraClienteSelezionato::FinestraClienteSelezionato(DatabaseClienti* d, DatabaseComponenti* db, Cliente* c, QDialog *parent):QDialog(parent), dbc(d), dbComp(db), cl(c){
    this->setWindowTitle("Finestra Cliente Selezionato");
    this->showMaximized();

    // new layout e groupbox
    layoutSfondo=new QVBoxLayout(this);
    layoutCliente= new QGridLayout();
    layoutBottoni= new QHBoxLayout();
    layoutTabella = new QVBoxLayout();
    boxCliente = new QGroupBox(this);
    boxTabella = new QGroupBox(this);
    boxBottoni = new QGroupBox(this);

    // new label e lineEdit
    labelTitolo=new QLabel("Cliente Selezionato:");
    labelTitoloTabella= new QLabel("Sale Compressori:", this);
    labelRagioneSociale=new QLabel("Ragione Sociale:",this);
    lineEditRagioneSociale=new QLineEdit(QString::fromStdString(c->getRagioneSociale()));
    lineEditRagioneSociale->setDisabled(true);
    labelPIva=new QLabel("Partita Iva:",this);
    lineEditPIva=new QLineEdit(QString::fromStdString(c->getPIva()));
    lineEditPIva->setDisabled(true);
    labelTelefono=new QLabel("Telefono:",this);
    lineEditTelefono=new QLineEdit(QString::fromStdString(c->getTelefono()));
    lineEditTelefono->setDisabled(true);
    labelFax=new QLabel("Fax:",this);
    lineEditFax=new QLineEdit(QString::fromStdString(c->getFax()));
    lineEditFax->setDisabled(true);
    labelEmail=new QLabel("Email:",this);
    lineEditEmail=new QLineEdit(QString::fromStdString(c->getEmail()));
    lineEditEmail->setDisabled(true);
    labelStabilimento=new QLabel("Stabilimento:",this);
    lineEditStabilimento=new QLineEdit(QString::fromStdString(c->getStabilimento()));
    lineEditStabilimento->setDisabled(true);
    labelVia=new QLabel("Via:",this);
    lineEditVia=new QLineEdit(QString::fromStdString(c->getIndirizzo().getVia()));
    lineEditVia->setDisabled(true);
    labelCitta=new QLabel("Citta:",this);
    lineEditCitta=new QLineEdit(QString::fromStdString(c->getIndirizzo().getCitta()));
    lineEditCitta->setDisabled(true);
    labelCap=new QLabel("CAP:",this);
    lineEditCap=new QLineEdit(QString::fromStdString(c->getIndirizzo().getCap()));
    lineEditCap->setDisabled(true);
    labelProvincia=new QLabel("Provincia:",this);
    lineEditProvincia=new QLineEdit(QString::fromStdString(c->getIndirizzo().getProvincia()));
    lineEditProvincia->setDisabled(true);
    labelKwStabilimento = new QLabel("Kw tot stab.");
    lineEditKwStabilimento = new QLineEdit("0");
    lineEditKwStabilimento->setDisabled(true);

    // new tabella
    tabellaSale=new QTableWidget(0,7);
    tabellaSale->setColumnWidth(0,150);
    QStringList header;
    header=QStringList() << "Nome" << "Stabilimento" << "Tipo Impianto" << "Kw Totali" << "Portata Effettiva (Lt/s)" << "Pressione Richiesta (Bar)" << "Portata Richiesta (Bar)";
    tabellaSale->setHorizontalHeaderLabels(header);
    QHeaderView* q=tabellaSale->horizontalHeader();
    q->setStretchLastSection(true);
    tabellaSale->setHorizontalHeader(q);
    tabellaSale->setColumnWidth(0,250);
    tabellaSale->setColumnWidth(1,200);
    tabellaSale->setColumnWidth(2,200);
    tabellaSale->setColumnWidth(3,100);
    tabellaSale->setColumnWidth(4,150);
    tabellaSale->setColumnWidth(5,150);
    tabellaSale->setColumnWidth(6,100);

    // new bottoni
    bottoneModificaDatiCliente= new QPushButton("Modifica anagrafica cliente",this);
    bottoneInserisciNuovaSala=new QPushButton("Inserisci nuova Sala Compressori",this);
    bottoneConfiguraSala= new QPushButton("Visualizza",this);
    bottoneEliminaSala= new QPushButton("Elimina",this);
    bottoneIndietro=new QPushButton("Torna indietro",this);

    // associazioni box e layout
    boxCliente->setLayout(layoutCliente);
    boxBottoni->setLayout(layoutBottoni);
    boxTabella->setLayout(layoutTabella);
    layoutSfondo->addWidget(labelTitolo);
    layoutSfondo->addWidget(boxCliente);
    layoutSfondo->addWidget(boxTabella);
    layoutSfondo->addWidget(tabellaSale);
    layoutSfondo->addWidget(boxBottoni);

    // associazion label e linedit a layoutCliente
    layoutCliente->addWidget(labelRagioneSociale,0,0);
    layoutCliente->addWidget(labelStabilimento,1,0);
    layoutCliente->addWidget(labelPIva,2,0);
    layoutCliente->addWidget(lineEditRagioneSociale,0,1);
    layoutCliente->addWidget(lineEditStabilimento,1,1);
    layoutCliente->addWidget(lineEditPIva,2,1);

    layoutCliente->addWidget(labelTelefono,0,2);
    layoutCliente->addWidget(labelFax,1,2);
    layoutCliente->addWidget(labelEmail,2,2);
    layoutCliente->addWidget(lineEditTelefono,0,3);
    layoutCliente->addWidget(lineEditFax,1,3);
    layoutCliente->addWidget(lineEditEmail,2,3);

    layoutCliente->addWidget(labelVia,0,4);
    layoutCliente->addWidget(labelCitta,1,4);
    layoutCliente->addWidget(labelCap,2,4);
    layoutCliente->addWidget(lineEditVia,0,5);
    layoutCliente->addWidget(lineEditCitta,1,5);
    layoutCliente->addWidget(lineEditCap,2,5);

    layoutCliente->addWidget(labelProvincia,0,6);
    layoutCliente->addWidget(lineEditProvincia,0,7);
    layoutCliente->addWidget(labelKwStabilimento,1,6);
    layoutCliente->addWidget(lineEditKwStabilimento,1,7);
    layoutCliente->addWidget(bottoneModificaDatiCliente,2,6,1,2);

    // associazione tabella a layoutTabella
    layoutTabella->addWidget(labelTitoloTabella);
    layoutTabella->addWidget(tabellaSale);

    // associazioni sul layoutBottoni
    layoutBottoni->addWidget(bottoneConfiguraSala);
    layoutBottoni->addWidget(bottoneEliminaSala);
    layoutBottoni->addWidget(bottoneInserisciNuovaSala);
    layoutBottoni->addWidget(bottoneIndietro);

    this->setLayout(layoutSfondo);

    riempiTabellaSale();
    aggiornaKwStabilimento();

    connect(bottoneInserisciNuovaSala,SIGNAL(clicked()),this,SLOT(apriFinestraInserisciSala()));
    connect(bottoneConfiguraSala,SIGNAL(clicked()),this,SLOT(apriFinestraConfiguraSala()));
    connect(bottoneIndietro,SIGNAL(clicked()),this,SLOT(torna()));
    connect(bottoneModificaDatiCliente,SIGNAL(clicked()),this,SLOT(apriModificaAnagraficaCliente()));
    connect(tabellaSale,SIGNAL(cellDoubleClicked(int,int)), this,SLOT(apriFinestraConfiguraSala()));
    connect(bottoneEliminaSala,SIGNAL(clicked()), this,SLOT(elimina()));
}

void FinestraClienteSelezionato::aggiornaKwStabilimento(){
    int kw_parziale=0;
    for(unsigned int it=0;it<cl->getSala().size();++it){
        kw_parziale += cl->getSala(it).getKwTot();
    }
    lineEditKwStabilimento->setText(QString::number(kw_parziale));
}

//metodo privato riempiTabellaSale
void FinestraClienteSelezionato::riempiTabellaSale() {
    int row = tabellaSale->rowCount();
    for (unsigned int i= 0; i<cl->getSala().size();++i) {
        tabellaSale->setRowCount(row+1);

        QTableWidgetItem* itemNome= new QTableWidgetItem (QString::fromStdString(cl->getSala(i).getNome()));
        tabellaSale->setItem(row, 0, itemNome);
        itemNome->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        QTableWidgetItem* itemStabilimento= new QTableWidgetItem (QString::fromStdString(cl->getStabilimento()));
        tabellaSale->setItem(row, 1, itemStabilimento);
        itemStabilimento->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        QTableWidgetItem* itemImpianto= new QTableWidgetItem (QString::fromStdString(cl->getSala(i).getImpianto()));
        tabellaSale->setItem(row, 2, itemImpianto);
        itemImpianto->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        QTableWidgetItem* itemKwTot= new QTableWidgetItem (QString::number(cl->getSala(i).getKwTot()));
        tabellaSale->setItem(row, 3, itemKwTot);
        itemKwTot->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        QTableWidgetItem* itemLtMin= new QTableWidgetItem (QString::number(cl->getSala(i).getPortataTot()));
        tabellaSale->setItem(row, 4, itemLtMin);
        itemLtMin->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        QTableWidgetItem* itemPressRic= new QTableWidgetItem (QString::number(cl->getSala(i).getPressioneRichiesta()));
        tabellaSale->setItem(row, 5, itemPressRic);
        itemPressRic->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);

        QTableWidgetItem* itemPortRic= new QTableWidgetItem (QString::number(cl->getSala(i).getPortataRichiesta()));
        tabellaSale->setItem(row, 6, itemPortRic);
        itemPortRic->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        ++row;
    }
}

void FinestraClienteSelezionato::apriFinestraInserisciSala(){
    FinestraInserisciSala finInsSala(dbc,cl);
    finInsSala.exec();
    tabellaSale->clearContents();
    tabellaSale->setRowCount(0);
    riempiTabellaSale();
}

void FinestraClienteSelezionato::apriFinestraConfiguraSala() {
    if(!(tabellaSale->selectedItems().isEmpty())){
        SalaCompressori* s;
        int riga = tabellaSale->currentRow();
        s = &(cl->getSala(riga));
        FinestraConfiguraSala finConfSala(dbc,dbComp,cl,s);
        finConfSala.exec();
        tabellaSale->clearContents();
        tabellaSale->setRowCount(0);
        riempiTabellaSale();
        aggiornaKwStabilimento();
    }
}


void FinestraClienteSelezionato::apriModificaAnagraficaCliente() {
    ModificaAnagraficaCliente modAnaCli(dbc,cl);
    modAnaCli.exec();
    // aggiorna anagrafica cliente nella finestra
    lineEditRagioneSociale->setText(QString::fromStdString(cl->getRagioneSociale()));
    lineEditCap->setText(QString::fromStdString(cl->getIndirizzo().getCap()));
    lineEditCitta->setText(QString::fromStdString(cl->getIndirizzo().getCitta()));
    lineEditEmail->setText(QString::fromStdString(cl->getEmail()));
    lineEditFax->setText(QString::fromStdString(cl->getFax()));
    lineEditPIva->setText(QString::fromStdString(cl->getPIva()));
    lineEditProvincia->setText(QString::fromStdString(cl->getIndirizzo().getProvincia()));
    lineEditStabilimento->setText(QString::fromStdString(cl->getStabilimento()));
    lineEditTelefono->setText(QString::fromStdString(cl->getTelefono()));
    lineEditVia->setText(QString::fromStdString(cl->getIndirizzo().getVia()));
}

void FinestraClienteSelezionato::elimina(){
    if (tabellaSale->currentItem()!= 0){
        int rigaSel=tabellaSale->currentRow();
        SalaCompressori* a=&(cl->getSala(rigaSel));

        vector<Componente*>::const_iterator it=a->getComponenti().end();
        int i=0;

        for(;it!=a->getComponenti().begin() && a->getComponenti().size()>0;--it){
            Componente* r=*dbComp->cercaComponente(a->getComponente(i)->getIdComponente());
            dbComp->rimuoviComponente(*r);
            delete r;
            a->getComponenti().pop_back();

            i++;
        }

        cl->rimuoviSala(rigaSel);
        tabellaSale->clearContents();
        tabellaSale->setRowCount(0);
        riempiTabellaSale();
    }

}

void FinestraClienteSelezionato::torna(){
    this->close();
}

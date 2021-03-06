#include "modificaanagraficacliente.h"

ModificaAnagraficaCliente::ModificaAnagraficaCliente(DatabaseClienti* d, Cliente* c, QDialog* parent): QDialog(parent), dbc(d), cl(c){
    this->setWindowTitle("Finestra Modifica Anagrafica Cliente");
    this->setMinimumSize(420,340);

    layoutSfondo=new QVBoxLayout(this);
    boxInfoCliente=new QGroupBox("Info cliente",this);
    layoutInfoCliente=new QGridLayout();
    boxBottoni=new QGroupBox(this);
    layoutBottoni=new QHBoxLayout();

    labelRagioneSociale=new QLabel("Ragione Sociale:",this);
    lineEditRagioneSociale=new QLineEdit(QString::fromStdString(c->getRagioneSociale()));
    labelPIva=new QLabel("Partita Iva:",this);
    lineEditPIva=new QLineEdit(QString::fromStdString(c->getPIva()));
    labelTelefono=new QLabel("Telefono:",this);
    lineEditTelefono=new QLineEdit(QString::fromStdString(c->getTelefono()));
    labelFax=new QLabel("Fax:",this);
    lineEditFax=new QLineEdit(QString::fromStdString(c->getFax()));
    labelEmail=new QLabel("Email:",this);
    lineEditEmail=new QLineEdit(QString::fromStdString(c->getEmail()));
    labelStabilimento=new QLabel("Stabilimento:",this);
    lineEditStabilimento=new QLineEdit(QString::fromStdString(c->getStabilimento()));
    labelVia=new QLabel("Via:",this);
    lineEditVia=new QLineEdit(QString::fromStdString(c->getIndirizzo().getVia()));
    labelCitta=new QLabel("Citta:",this);
    lineEditCitta=new QLineEdit(QString::fromStdString(c->getIndirizzo().getCitta()));
    labelCap=new QLabel("CAP:",this);
    lineEditCap=new QLineEdit(QString::fromStdString(c->getIndirizzo().getCap()));
    labelProvincia=new QLabel("Provincia:",this);
    lineEditProvincia=new QLineEdit(QString::fromStdString(c->getIndirizzo().getProvincia()));

    bottoneIndietro=new QPushButton("Torna indietro",this);
    bottoneSalva=new QPushButton("Salva",this);

    // label e lineedit sinistra
    layoutInfoCliente->addWidget(labelRagioneSociale,0,0);
    layoutInfoCliente->addWidget(lineEditRagioneSociale,1,0);
    layoutInfoCliente->addWidget(labelPIva,2,0);
    layoutInfoCliente->addWidget(lineEditPIva,3,0);
    layoutInfoCliente->addWidget(labelTelefono,4,0);
    layoutInfoCliente->addWidget(lineEditTelefono,5,0);
    layoutInfoCliente->addWidget(labelFax,6,0);
    layoutInfoCliente->addWidget(lineEditFax,7,0);
    layoutInfoCliente->addWidget(labelEmail,8,0);
    layoutInfoCliente->addWidget(lineEditEmail,9,0);

    // label e lineedit destra
    layoutInfoCliente->addWidget(labelStabilimento,0,1);
    layoutInfoCliente->addWidget(lineEditStabilimento,1,1);
    layoutInfoCliente->addWidget(labelVia,2,1);
    layoutInfoCliente->addWidget(lineEditVia,3,1);
    layoutInfoCliente->addWidget(labelCitta,4,1);
    layoutInfoCliente->addWidget(lineEditCitta,5,1);
    layoutInfoCliente->addWidget(labelCap,6,1);
    layoutInfoCliente->addWidget(lineEditCap,7,1);
    layoutInfoCliente->addWidget(labelProvincia,8,1);
    layoutInfoCliente->addWidget(lineEditProvincia,9,1);

    boxInfoCliente->setLayout(layoutInfoCliente);
    boxBottoni->setLayout(layoutBottoni);
    layoutSfondo->addWidget(boxInfoCliente);
    layoutSfondo->addWidget(boxBottoni);
    layoutBottoni->addWidget(bottoneIndietro);
    layoutBottoni->addWidget(bottoneSalva);

    this->setLayout(layoutSfondo);

    connect(bottoneIndietro,SIGNAL(clicked()),this,SLOT(torna()));
    connect(bottoneSalva,SIGNAL(clicked()),this,SLOT(salva()));
}

void ModificaAnagraficaCliente::torna(){
    this->close();
}

void ModificaAnagraficaCliente::salva(){
    if(lineEditRagioneSociale->text()!="" && lineEditPIva->text()!="" &&
            lineEditTelefono->text()!="" && lineEditFax->text()!="" && lineEditEmail->text()!="" && lineEditStabilimento->text()!="" &&
            lineEditVia->text()!="" && lineEditCitta->text()!="" && lineEditCap->text()!="" && lineEditProvincia->text()!=""){

        if (lineEditRagioneSociale->isUndoAvailable() || lineEditStabilimento->isUndoAvailable()){

            string ragsoc = lineEditRagioneSociale->text().toStdString();
            string stab = lineEditStabilimento->text().toStdString();

            bool inseribile=true;
            for (unsigned int i=0;i<dbc->getDatabase().size() && inseribile;i++){
                if(ragsoc == dbc->getCliente(i).getRagioneSociale() && stab==dbc->getCliente(i).getStabilimento()){
                    inseribile=false;
                    QMessageBox messageBox(this);
                    messageBox.setText("Cliente gia presente");
                    messageBox.exec();
                }
            }
            if (inseribile==true){
                cl->setRagioneSociale(lineEditRagioneSociale->text().toStdString());
                cl->setTelefono(lineEditTelefono->text().toStdString());
                cl->setEmail(lineEditEmail->text().toStdString());
                cl->setFax(lineEditFax->text().toStdString());
                cl->setPIva(lineEditPIva->text().toStdString());
                cl->setStabilimento(lineEditStabilimento->text().toStdString());
                Indirizzo i;
                i.setVia(lineEditVia->text().toStdString());
                i.setCitta(lineEditCitta->text().toStdString());
                i.setProvincia(lineEditProvincia->text().toStdString());
                i.setCap(lineEditCap->text().toStdString());
                cl->setInd(i);

                dbc->saveClienti(DatabaseClienti::Json);
                QMessageBox messageBox(this);
                messageBox.setText("Dati aggiornati correttamente");
                messageBox.exec();
                this->close();
            }
        }
        else{
            cl->setTelefono(lineEditTelefono->text().toStdString());
            cl->setEmail(lineEditEmail->text().toStdString());
            cl->setFax(lineEditFax->text().toStdString());
            cl->setPIva(lineEditPIva->text().toStdString());

            Indirizzo i;
            i.setVia(lineEditVia->text().toStdString());
            i.setCitta(lineEditCitta->text().toStdString());
            i.setProvincia(lineEditProvincia->text().toStdString());
            i.setCap(lineEditCap->text().toStdString());
            cl->setInd(i);

            dbc->saveClienti(DatabaseClienti::Json);
            QMessageBox messageBox(this);
            messageBox.setText("Dati aggiornati correttamente");
            messageBox.exec();
            this->close();
        }
    }
    else{
        QMessageBox messageBox(this);
        messageBox.setText("Compilare tutti i campi");
        messageBox.exec();
    }
}

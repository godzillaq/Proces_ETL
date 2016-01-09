drop table if exists Produkt cascade;
create table Produkt
(
KodProduktu integer primary key not null,
Marka character varying(100),
Model character varying(100),
RodzajUrz character varying(70),
DodUwagi character varying(2000)
);

drop table if exists Opinia cascade;
create table Opinia
(
IdProdukt integer not null REFERENCES Produkt ON DELETE CASCADE,
Autor character varying(100),
Opinia character varying(10000),
Wady character varying(2000),
Zalety character varying(2000),
LGwiazdek character varying(50),
Data timestamp ,--character varying(200),
PolecNPolec character varying(200),
PrzydatnaOpiniaPr character varying(200),
IleOsOcPrzydatnosc character varying(200),
Primary Key(Autor, Data, IdProdukt),
CONSTRAINT Opinia_Produkt_fk FOREIGN KEY(IdProdukt) REFERENCES Produkt(KodProduktu)
);

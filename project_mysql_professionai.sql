-- Data exploration. First I see each table, printing their fields
select * from banca.cliente;
select * from banca.conto;
select * from banca.tipo_conto;
select * from banca.tipo_transazione;
select * from banca.transazioni;

-- Point 1: clients' age
create temporary table banca.point_1 as select id_cliente, timestampdiff(year, data_nascita, current_date()) as eta from banca.cliente;
select * from banca.point_1;

-- Points 2 and 4: number of exiting transactions and total exiting amount of money
create temporary table banca.points_2_4 as 
(
select 
conto.id_cliente, COUNT(transazione.importo) numero_transazioni_uscita, sum(transazione.importo) importo_uscita
from banca.conto conto

left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans >= 3
group by conto.id_cliente);

select * from banca.points_2_4;

-- Points 3 and 5: number of entering transactions and total entering amount of money
create temporary table banca.points_3_5 as
(
   select 
conto.id_cliente, COUNT(transazione.importo) numero_transazioni_entrata, sum(transazione.importo) importo_entrata
from banca.conto conto

left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans < 3
group by conto.id_cliente);

select * from banca.points_3_5;

-- Point 6: total number of bank account per id_client
create temporary table banca.point_6 as
(
    select 
    cliente.id_cliente, COUNT(conto.id_conto) AS numero_conti
from
    banca.cliente cliente
        left join
    banca.conto conto on cliente.id_cliente = conto.id_cliente
group by cliente.id_cliente);
select * from banca.point_6;

-- Point 7: number of bank accounts per type
-- base accounts
create temporary table banca.point_7_base as
(
SELECT 
    cliente.id_cliente, COUNT(conto.id_conto) AS numero_conti_base
FROM
    banca.cliente cliente
        LEFT JOIN
    banca.conto conto ON cliente.id_cliente = conto.id_cliente AND conto.id_tipo_conto = 0
GROUP BY cliente.id_cliente, conto.id_tipo_conto
);
select * from banca.point_7_base;

-- business accounts
create temporary table banca.point_7_business as
(
    SELECT 
    cliente.id_cliente, COUNT(conto.id_conto) AS numero_conti_business
FROM
    banca.cliente cliente
        LEFT JOIN
    banca.conto conto ON cliente.id_cliente = conto.id_cliente AND conto.id_tipo_conto = 1
GROUP BY cliente.id_cliente, conto.id_tipo_conto
);
select * from banca.point_7_business;

-- private accounts
create temporary table banca.point_7_private as
(
    SELECT 
    cliente.id_cliente, COUNT(conto.id_conto) AS numero_conti_privati
FROM
    banca.cliente cliente
        LEFT JOIN
    banca.conto conto ON cliente.id_cliente = conto.id_cliente AND conto.id_tipo_conto = 2
GROUP BY cliente.id_cliente, conto.id_tipo_conto
);
select * from banca.point_7_private;

-- family accounts
create temporary table banca.point_7_family
(
    SELECT 
    cliente.id_cliente, COUNT(conto.id_conto) AS numero_conti_famiglie
FROM
    banca.cliente cliente
        LEFT JOIN
    banca.conto conto ON cliente.id_cliente = conto.id_cliente AND conto.id_tipo_conto = 3
GROUP BY cliente.id_cliente, conto.id_tipo_conto
);
select * from banca.point_7_family;

-- Joining all the subtables in the point_7 table

create temporary table banca.point_7 as
(
	select base.id_cliente, base.numero_conti_base, business.numero_conti_business,
    privati.numero_conti_privati, famiglie.numero_conti_famiglie
    from banca.point_7_base base
	inner join
    banca.point_7_business business
    on base.id_cliente = business.id_cliente
    inner join 
    banca.point_7_private privati
    on privati.id_cliente = business.id_cliente
    inner join
    banca.point_7_family famiglie
    on privati.id_cliente = famiglie.id_cliente
);

select * from banca.point_7;


-- Point 8-9: number of operations per type

create temporary table banca.stipendio
(
select conto.id_cliente, count(transazione.importo) n_transazioni_stipendio
from banca.conto conto
left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans = 0
group by conto.id_cliente
);
select * from banca.stipendio;

create temporary table banca.pensione
(
select conto.id_cliente, count(transazione.importo) n_transazioni_pensione
from banca.conto conto
left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans = 1
group by conto.id_cliente
);

select * from banca.pensione;

create temporary table banca.dividendi
(
select conto.id_cliente, count(transazione.importo) n_transazioni_dividendi
from banca.conto conto
left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans = 2
group by conto.id_cliente
);

select * from banca.dividendi;

create temporary table banca.amazon
(
select conto.id_cliente, count(transazione.importo) n_transazioni_amazon
from banca.conto conto
left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans = 3
group by conto.id_cliente
);

select * from banca.amazon;

create temporary table banca.mutuo
(
select conto.id_cliente, count(transazione.importo) n_transazioni_mutuo
from banca.conto conto
left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans = 4
group by conto.id_cliente
);
select * from banca.mutuo;

create temporary table banca.hotel
(
select conto.id_cliente, count(transazione.importo) n_transazioni_hotel
from banca.conto conto
left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans = 5
group by conto.id_cliente
);
select * from banca.hotel;

create temporary table banca.aereo
(
select conto.id_cliente, count(transazione.importo) n_transazioni_aereo
from banca.conto conto
left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans = 6
group by conto.id_cliente
);
select * from banca.aereo;


create temporary table banca.supermercato
(
select conto.id_cliente, count(transazione.importo) n_transazioni_supermercato
from banca.conto conto
left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans = 7
group by conto.id_cliente
);
select * from banca.supermercato;


create temporary table banca.points_8_9
(
	select stipendio.id_cliente, stipendio.n_transazioni_stipendio, pensione.n_transazioni_pensione,
    dividendi.n_transazioni_dividendi, amazon.n_transazioni_amazon, mutuo.n_transazioni_mutuo, 
    hotel.n_transazioni_hotel, aereo.n_transazioni_aereo, supermercato.n_transazioni_supermercato
    from banca.stipendio stipendio
    inner join banca.pensione pensione
    on stipendio.id_cliente = pensione.id_cliente
    inner join banca.dividendi dividendi
    on pensione.id_cliente = dividendi.id_cliente
    inner join banca.amazon amazon
    on dividendi.id_cliente = amazon.id_cliente
    inner join banca.mutuo mutuo
    on amazon.id_cliente = mutuo.id_cliente
    inner join banca.hotel hotel
    on mutuo.id_cliente = hotel.id_cliente
    inner join banca.aereo aereo
    on hotel.id_cliente = aereo.id_cliente
    inner join banca.supermercato
    on aereo.id_cliente = supermercato.id_cliente
);

select * from banca.points_8_9;

-- Point 10: Exiting amount of money per bank account type
create temporary table banca.importo_uscita_base
(
select 
conto.id_cliente,  case when sum(transazione.importo) is null then 0
 else sum(transazione.importo) end importo_uscita_base
from banca.conto conto

left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans >= 3 and conto.id_tipo_conto = 0
group by conto.id_cliente
);
select * from banca.importo_uscita_base;

create temporary table banca.importo_uscita_business
(
select 
conto.id_cliente,  case when sum(transazione.importo) is null then 0
 else sum(transazione.importo) end importo_uscita_business
from banca.conto conto

left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans >= 3 and conto.id_tipo_conto = 1
group by conto.id_cliente
);
select * from banca.importo_uscita_business;

create temporary table banca.importo_uscita_privati
(
select 
conto.id_cliente,  case when sum(transazione.importo) is null then 0
 else sum(transazione.importo) end importo_uscita_privati
from banca.conto conto

left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans >= 3 and conto.id_tipo_conto = 2
group by conto.id_cliente
);
select * from banca.importo_uscita_privati;

create temporary table banca.importo_uscita_famiglie
(
select 
conto.id_cliente,  case when sum(transazione.importo) is null then 0
 else sum(transazione.importo) end importo_uscita_famiglie
from banca.conto conto

left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans >= 3 and conto.id_tipo_conto = 3
group by conto.id_cliente
);
select * from banca.importo_uscita_famiglie;

create temporary table banca.point_10
(
	select base.id_cliente, base.importo_uscita_base, business.importo_uscita_business, 
    privati.importo_uscita_privati, famiglie.importo_uscita_famiglie
    from banca.importo_uscita_base base
    inner join
    banca.importo_uscita_business as business
    on base.id_cliente = business.id_cliente
    inner join
    banca.importo_uscita_privati privati
    on business.id_cliente = privati.id_cliente
    inner join
    banca.importo_uscita_famiglie famiglie
    on privati.id_cliente = famiglie.id_cliente
);

select * from banca.point_10;

-- Point 11: entering amount of money per type of bank account
create temporary table banca.importo_entrata_base
(
select 
conto.id_cliente,  case when sum(transazione.importo) is null then 0
 else sum(transazione.importo) end importo_entrata_base
from banca.conto conto

left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans >= 3 and conto.id_tipo_conto = 0
group by conto.id_cliente
);
select * from banca.importo_entrata_base;

create temporary table banca.importo_entrata_business
(
select 
conto.id_cliente,  case when sum(transazione.importo) is null then 0
 else sum(transazione.importo) end importo_entrata_business
from banca.conto conto

left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans >= 3 and conto.id_tipo_conto = 1
group by conto.id_cliente
);
select * from banca.importo_entrata_business;

create temporary table banca.importo_entrata_privati
(
select 
conto.id_cliente,  case when sum(transazione.importo) is null then 0
 else sum(transazione.importo) end importo_entrata_privati
from banca.conto conto

left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans >= 3 and conto.id_tipo_conto = 2
group by conto.id_cliente
);
select * from banca.importo_entrata_privati;

create temporary table banca.importo_entrata_famiglie
(
select 
conto.id_cliente,  case when sum(transazione.importo) is null then 0
 else sum(transazione.importo) end importo_entrata_famiglie
from banca.conto conto

left join banca.transazioni transazione
on conto.id_conto = transazione.id_conto and transazione.id_tipo_trans >= 3 and conto.id_tipo_conto = 3
group by conto.id_cliente
);
select * from banca.importo_entrata_famiglie;

create temporary table banca.point_11
(
	select base.id_cliente, base.importo_entrata_base, business.importo_entrata_business, 
    privati.importo_entrata_privati, famiglie.importo_entrata_famiglie
    from banca.importo_entrata_base base
    inner join
    banca.importo_entrata_business as business
    on base.id_cliente = business.id_cliente
    inner join
    banca.importo_entrata_privati privati
    on business.id_cliente = privati.id_cliente
    inner join
    banca.importo_entrata_famiglie famiglie
    on privati.id_cliente = famiglie.id_cliente
);

select * from banca.point_11;

select * from banca.point_10;

create temporary table banca.complete_extraction
(
	select point_1.id_cliente, point_1.eta, points_2_4.numero_transazioni_uscita, points_2_4.importo_uscita,
    points_3_5.numero_transazioni_entrata, points_3_5.importo_entrata, point_6.numero_conti, point_7.numero_conti_base,
    point_7.numero_conti_business, point_7.numero_conti_privati, point_7.numero_conti_famiglie, points_8_9.n_transazioni_stipendio,
    points_8_9.n_transazioni_pensione, points_8_9.n_transazioni_dividendi, points_8_9.n_transazioni_amazon, points_8_9.n_transazioni_mutuo,
    points_8_9.n_transazioni_hotel, points_8_9.n_transazioni_aereo, points_8_9.n_transazioni_supermercato, point_10.importo_uscita_base,
    point_10.importo_uscita_business, point_10.importo_uscita_privati, point_10.importo_uscita_famiglie, point_11.importo_entrata_base,
    point_11.importo_entrata_business, point_11.importo_entrata_privati, point_11.importo_entrata_famiglie
    from banca.point_1 point_1 
    inner join banca.points_2_4 points_2_4 
    on point_1.id_cliente = points_2_4.id_cliente
    inner join banca.points_3_5 points_3_5
    on points_2_4.id_cliente = points_3_5.id_cliente
    inner join banca.point_6 point_6
    on points_3_5.id_cliente = point_6.id_cliente
    inner join banca.point_7 point_7
    on point_6.id_cliente = point_7.id_cliente
    inner join banca.points_8_9 points_8_9
    on point_7.id_cliente = points_8_9.id_cliente
    inner join banca.point_10 point_10
    on point_10.id_cliente = points_8_9.id_cliente
    inner join banca.point_11 point_11
    on point_11.id_cliente = point_10.id_cliente
    
);

select * from banca.complete_extraction;

Exzerpt Nafe 2005
-----------------

1. Einleitung

2. Indexierung von XML-Dokumenten

- Kapitelinhalt: "Indexierungsmethoden für Textdaten" (S. 9)

2.1 Data-Guides

2.2 Tries

2.3 PATRICIA-Tries 

- Auch: "PT-Baum"
- "PATRICIA": "Practical Algorithm To Retrieve Information Coded In Alphanumeric"
- "alphanumerisch": Zahlen und Buchstaben 
- Sollen Probleme bisheriger Tries beheben -> in jedem Knoten wird ein Offset von zu überspringenden Buchstaben u. evtl. der Index des nächsten relevanten Buchstaben gespeichert
- Weitere Variante: Präfixbaum (speichert übersprungene Buchstabensequenz; speichert keine kompletten Datensätze in den Blättern; "einen Pfad von der Wurzel bis zum Blatt zu verfolgen ergibt automatisch das gespeicherte Wort", S. 13) -> vermeidet Probleme der PATIRCIA-Trees

2.4 Index Fabric

- Bisher: PT-Bäume können leicht entarten; minimale u. maximale Pfadlänge können parallel auftreten 
- Daher jetzt: Index Fabric 
	* "Indexart, die auf PT-Bäumen aufsetzt, aber nicht" deren Probleme aufweist (S. 13)
	* Findet jeden Datensatz in höchstens drei Plattenzugriffen 
	* "Unterstützt mehrere verschiedene Zugriffspfade auf" eine Datei (S. 13)
	* Funktionsweise: "Aufteilung des Baumes auf Blöcke"; Einführung einer horizontalen Ebenenhierarchie "neben der vertikalen Baumstruktur" -> führt zu "ausbalancierte[r] Sicht auf den zugrunde liegenden (unbalancierten) PT-Baum und ein Überspringen mehrerer Knoten in diesem" (S. 13; vgl. S. 13f. ff. Details u. Bsp.)

2.5 Bitindizes

2.6 Histogramme

2.7 Textkompression

3. Routing von Anfragen

- Kapitelinhalt: "Verfahren zum Routing von Anfragen in P2P-Netzen" (S. 9)

3.3 Inhaltsbasiertes Anfrage-Routing in Baumnetzen

- Prinzip: "Grundlage dieses Algorithmus' ist ein baumstrukturiertes P2P-Netz. Er beschreibt das approximative Indexieren von Knoten- und Teilbauminhalten sowie das Routen von Queries basierend auf diesen Indizes" (S. 28)
- Die Anfragen sollen abhängig vom Inhalt der Knoten-Repositories möglichst effizient durchs Netz geroutet werden (so wenige Hosts wie möglich, so viele wie nötig) 
- Dazu werden die Hosts indexiert (vgl. Kap. 2.5): 
	1. Jeder Host hat mit hoher W'keit eine eindeutige Signatur
	2. Verfügt ein Host über Kindknoten, verknüpft er deren Signaturen mit seiner eigenen (logisches ODER)
- Beim Routing erstellt der anfragende Host eine Signatur für die Anfrage -> natürlich müssen dieselben Hashfunktionen wie bei der Indexierung verwendet werden 
- Zwei Fehlerquellen: Falsch Positive sowie Aggregation von Suchwörtern
- Probleme bei diesem Verfahren: 
	1. Ungeeignet für sich häufig ändernde Inhalte (statischer Index wird einmal generiert)
	2. Knoteneintritt und -austritt nicht vorgesehen 

3.4 Histogramm-Routing

- "Histogramm": "graphische Darstellung der Häufigkeitsverteilung metrisch skalierter Merkmale" (vgl. https://de.wikipedia.org/wiki/Histogramm)
- Prinzip: Jeder Host hat zwei Indizes: lokaler Index + Routing-Index für jeden Nachbarn 
- Indizes beruhen auf Histogrammen; Hosts mit ähnlichem Inhalt werden geclustert 

4. Ansatz zur Umsetzung eines Prototypen

- Kapitelinhalt: "Designentscheidungen und der konzeptionelle Aufbau eines Prototypen" (S. 9)

4.1 Indexierung 

- Untersuchung der vorgestellten Ansätze auf ihre Eignung: 
	1. Data-Guides (DG)
	2. Standard-Tries
	3. PATRICIA-Tries -> geringer Speicherplatzbedarf
	4. Bitindizes -> noch geringerer Speicherverbrauch bei geeigneter Hashfkt. 
	5. Histogramme 
- Entscheidung hier: Zweistufiger Index mit 1. Stufe Bitindex, 2. Stufe Histogrammindex

4.1.1. Bitindex

- Details und Schritte z. Erstellung des Index vgl. S. 37-42
- Zusammenfassung: "Das Alphabet hat eine Mächtigkeit von 11, und somit wird die Wertemenge (und auch jeder Bitindex) eine Größe von 14.641 haben." (S. 42)

4.1.2. Histogrammindex 

- Z. Erstellung eines Histogramms muss Wissen über den Definitionsbereich des zu indexierenden Attributes vorhanden sein -> hier dient aber der schon bekannte (berechnete) Bitindex aus Kap. 4.1.1 als Grundlage 
- Verfahren: "Der lokale Index wird durch ein Histogramm mit [A^3 (A ist die Mächtigkeit des zu Grunde liegenden Alphabets)] Buckets repräsentiert. In jedem Bucket wird die Anzahl der im zugehörigen Abeschnitt des Bitindexes auf eins gesetzten Bits angegeben." (S. 43)

5. Umsetzung des Prototypen

6. Ergebnisse

7. Schlussbetrachtung

- Ziel: Indexierungsverfahren, "mit dessen Hilfe es möglich ist, gezielt Anfragen durch dezentralisierte, unstrukturierte P2P-Netzwerke zu routen" (S. 65)
- Vorgehensweise: Dreistufiger Index
	1. "Erstellung einer eindeutigen Signatur für das Repositorium" (S. 65)
	2. "Generierung eines Histogramms über die Verteilung einzelner Bits in der Signatur" (S. 65)
	3. "Indizes aus der zweiten Stufe" (der Netznachbarn) 
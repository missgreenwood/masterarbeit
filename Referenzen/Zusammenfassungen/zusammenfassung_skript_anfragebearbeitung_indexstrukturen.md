Exzerpt Skript Anfragebearbeitung und Indexstrukturen 
-----------------------------------------------------

1.5 Indexstrukturen 

- "Um Anfragen und Operationen efifzient druchführen zu können, setzt die interne Ebene des Datenbanksystems geeignete Datenstrukturen und Speicherungsverfahren (Indexstrukturen) ein." (S. 6)
- Index/Directory: "Strukturinformation zur Zuordnung von Suchschlüsseln und zur Organisation der Datei" (S. 7, Datei: Die gesamte Datenstruktur, sprich Suchbaum/Array/...)
	* Unterscheide zw. Directoryseiten und Datenseiten 
- Klassen: 
	1. Datenorganisierende Strukturen -> hier zentral: "Organisiere die Menge der tatsächlich auftretenden Daten (Suchbaumverfahren)" (S. 6)
	2. Raumorganisierende Strukturen -> "Organisiere den Raum, in den die Daten eingebettet sind (dynamische Hashverfahren)" (S. 6)
	3. Hybride Strukturen -> "Kombination beider Vorgehensweisen (Hash-Bäume)" (S. 6)

1.6 Allgemeine Anforderungen an Indexstrukturen 

	1. "Effizentes Suchen" (S. 7) -> "Eine Anfrage sollte [...] mit Hilfe der Indexstruktur möglichst schnell zu der Seite oder den Seiten hingeführt werden, wo sich die gesuchten Datensätze befinden" (S. 7)
	2. "Dynamisches Einfügen, Löschen und Verändern von Datensätzen" (S. 7) -> "Das Einfügen, Löschen und Verändern von Datensätzen darf [...] nur lokale Änderungen bewirken" (S. 7)
	3. "Ordnungserhaltung" -> hier am wichtigsten[!]
	4. "Hohe Speicherplatzausnutzung" (S. 7) 
	5. "Implementierbarkeit, Nutzen des Implementieraufwandes" (S. 7)

4. Raumorganisierende Strukturen zur Primärschlüsselsuche

- Jetzt: Dynamische Hashverfahren z. Primär- und Sekundärschlüsselsuche; d.h. Organisation des Raums, in den die Daten eingebettet sind

4.1 Hashverfahren 

- "Ziel: Gleichmäßige Verteilung der Schlüssel über den Adressraum" (S. 43) 
- für DBS: Hashverfahren müssen möglichst dynamisch sein! 

4.2 Klassifizierung 

4.3 Verfahren mit Directory

4.4 Verfahren ohne Directory

4.5 Partielle Erweiterungen

4.6 Ordnungserhaltung

- "Wichtige Eigenschaft von Indexstrukturen (vgl. 1. Kapitel): lokale Ordnungserhaltung" (S. 55) 
- "Datensätze mit Schlüsseln, die in der Ordnung aufeinander folgen, sollten in der gleichen Seite gespeichert werden" (S. 55)
- "Suchbäume wie z.B. B-Bäume sind (lokal) ordnungserhaltend" (S. 43)
- "Lineares Hashing ist mit den bisherigen Hashfunktionen nicht ordnungserhaltend" (S. 55) 
- Daher jetzt: Ordnungserhaltendes lineares Hashing/eindimensionales Interpolationsverfahren (vgl. S. 55f.) -> also evtl. interessant: Eindimensionale dynamische Hashverfahren, aber vermutlich sind Suchbäume generell besser/sinnvoller?   
Exzerpt Skript AlgoDat 2 
------------------------

1. Mehrwegbäume

- "Ausgangspunkt: Binäre Suchbäume (balanciert)" (S. 6)
- Jetzt: "Index-Datenstruktur f. schnellere Suche" (S. 6)
- "Grundoperationen: Suchen, Einfügen, Löschen" (S. 6) 

	a. m-Wege-Suchbaum
	
	* Def. vgl. S. 7
	* Eigenschaften: 
		1. Die Einträge D_i in den Knoten können Daten oder Zeiger auf die Daten repräsentieren
		2. "Direkter Index: eingebettete Daten (weniger Einträge pro Knoten; kleineres m)" (S. 6)
		3. "Indirekter Index: nur Verweise; erfordert separaten Zugriff auf Daten zu dem Schlüssel" (S. 6)  
		4. "Die Schlüssel in den inneren Knoten besitzen zwei Funktionen. Sie identifizieren Daten(sätze) und sie dienen als Wegweiser in der Baumstruktur" (S. 7)
		5. m-Wege-Suchbaum i.A. nicht ausgeglichen 
		6. Es gelten die Ungleichungen: 
			(1) 	x ∈ K(P_0): x < K_1
			(2) 	x ∈ K(P_i): K_i < x < K_{i+1} für i = 1,...,b-1
 			(3)		x ∈ K(P_b): K_b < x
 		7. #Knoten: (m^h - 1)/(m-1)
 		8. Höhe: log_m(n+1) ≤ h ≤ n

	b. B-Baum

	* Def. vgl. S. 9, informell: 
		(1) 	"Eine Seite darf höchstens voll sein." (S. 10)
		(2)		"Jede Seite (außer der Wurzel) muss mindestens halb voll sein. Die Wurzel enthält mindestens einen Schlüssel." (S. 10)
		(3)		"Der Baum ist, was die Knotenstruktur angeht, vollständig ausgeglichen." (S. 10) 
	* geordneter Binärbaum: "Ein Binärbaum b heißt geordnet, wenn b leer ist oder wenn [...] für alle nichtleeren Teilbäume t von b gilt: Der Schlüssel von t ist größer (oder gleich) als alle Schlüssel des linken Teilbaums von t und kleiner (oder gleich) als alle Schlüssel des rechten Teilbaums von t" (Vgl. http://www.pst.ifi.lmu.de/Lehre/fruhere-semester/wise-09-10/infoeinf/zentraluebung_09/zentraluebung_09.pdf)
	* Eigenschaften: 
		1. "In jedem Knoten stehen in aufsteigender Ordnung mit" K_1 < ... < K_b (S. 10)
		2. "Jeder Schlüssel hat eine Doppelrolle als Identifikator eines Datensatzes und als Wegweiser im Baum" (S. 10)
		3. "Die Klassen τ(k,h) sind nicht alle disjunkt" (S. 10)
		4. Höhe: 	h = 0 											falls n = 0
					log_(2k+1)(n+1) ≤ h ≤ log_(k+1)((n+1)/2) + 1 	sonst
		5. Falls Wurzel oder ein Blattknoten überläuft: Split! (Details vgl. S. 11)
		6. "Bei B-Bäumen ist das Wachstum von den Blättern zur Wurzel hin gerichtet" (S. 11)
		7. Löschen in B-Bäumen: "Die B-Baum-Eigenschaft muss wiederheigestellt werden, wenn die Anzahl der Elemente in einem Knoten kleiner als k wird" -> "Ausgleich mit Elementen aus einer Nachbarseite oder [...] Konkatenation [...] mit einer Nachbarseite" (S. 13)

	c. B*-Baum

	* Def.: Vgl. S. 15
	* Eigenschaften: 
		1. "Hauptunterschied zu B-Baum: in inneren Knoten wird nur die Wegweiser-Funktion ausgenutzt[, Information] wird in den Blattknoten abgelegt" (S. 15)
		2. "Für einige K_i ergibt sich eine redundante Speicherung. Die inneren Knoten bilden also einen Index, der einen schnellen direkten Zugriff zu den Schlüsseln gestattet" (S. 15)
		3. höherer Verzweigungsgrad, geringere Höhe 
		4. "Durch Verkettung aller Blattknoten lässt sich eine effiziente sequentielle Verarbeitung erreichen, die beim B-Baum einen [...] Durchlauf in symmetrischer Ordnung erforderte" -> "für den praktischen Einsatz wichtigste Variante des B-Baums" (S. 15)
		5. Höhe: 	1 + log_(2k+1) (n/2k*) ≤ h* ≤ 2 + log_(k+1) (n/2k*)		falls h* ≥ 2
		6. "B*-Baum entspricht einer geketteten sequentiellen Datei von Blättern, die einen Indexteil besitzt, der selbst ein B-Baum ist. Im Indexteil werden insbesondere beim Split-Vorgang die Operationen des B-Baums eingesetzt" (S. 17)

	* Verallgemeinerte Überlaufbehandlung: 
		1. "Standard (m=1): Überlauf führt zu zwei halb vollen Seiten" (S. 19)
		2. "m<1: Verbesserung der Belegung" (S. 19) 
		3. "Speicherplatzbelegung als Funktion des Split-Faktors" (S. 20)


	d. Schlüsselkomprimierung, Präfix-B-Baum

		* "Zeichenkomprimierung ermöglicht weit höhere Anzahl von Einträgen pro Seite (v.a. bei B*-Baum)" (S. 20)
		* Präfixkomprimierung vs. Suffixkomprimierung
		* "Präfix-B-Bäume: Verwendung minimaler Separatoren (Präfixe) in inneren Knoten" (S. 20)

	e. 2-3-Baum, binärer B-Baum

		* B-Bäume als Hauptspeicher-Datenstruktur -> "möglichst kleine Knoten wichtiger als hohes Fan-Out" (S. 22)
		* Daher jetzt: 2,3-Baum
		* Def. vgl. S. 22
		* Wichtige Eigenschaften: 
			1. "2-3-Baum ist ein balancierter B-Baum" (S. 22)
			2. "ähnliche Laufzeitkomplexität wie AVL-Baum" (S. 22)
			3. "schlechte Speicherplatzausnutzung (besonders nach Höhenänderung)" (S. 22)

		* Daher jetzt: Binäre B-Bäume -> "Verbesserte Speicherplatzausnutzung gegenüber 2-3-Bäumen durch Speicherung der Knoten als gekettete Listen Mit einem oder zwei Elementen" (S. 22)
	
	f. Digitalbäume

		* Eigenschaften: 
			1. "Zerlegung des Schlüssels - bestehend aus Zeichen eines Alphabets - in Teile" (S. 23)
			2. "Aufbau des Baumes nach Schlüsselteilen" (S. 23)
			3. "Suche im Baum durch Vergleich von Schlüsselteilen" (S. 23)  
		
		* "Spezielle Implementierung des Digitalbaumes: Trie" (S. 23)
		
		* Daher jetzt: "PATRICIA-Baum (Practical Algorithm To Retrieve Information Coded In Alphanumeric)" (S. 25)
		* Eigenschaften: 
			1. "Binärdarstellung für Schlüsselwerte -> binärer Digitalbaum" (S. 25)
			2. "Speicherung der Schlüssel in den Blättern" (S. 25)
			3. "innere Knoten speichern, wieviele Zeichen (Bits) beim Test zur Wegeauswahl zu überspringen sind" (S. 25)
			4. "Vermeidung von Einwegverzweigungen" (S. 25)
		* Vorteile: 
			1. Speichereffizient
			2. gut für "variabel lange Schlüssel und (sehr lange) Binärdarstellungen von Schlüsselwerten" (S. 25)
		* Nachteil: "Bei jedem Suchschlüssel muss die Testfolge von der Wurzel beginnend ganz ausgeführt werden" (S. 25)

		* Daher jetzt: Präfix- bzw. Radix-Baum -> "(Binärer) Digitalbaum als Variante des PATRICIA-Baumes" (S. 26)
		* Eigenschaften: 
			1. "Speicherung variabel langer Schlüsselteile in den inneren Knoten, sobald sie sich als Präfixe für die Schlüssel des zugehörigen Unterbaums abspalten lassen" (S. 26)
			2. "komplexere Knotenformate und aufwendigere Such- und Aktualisierungsoperationen" (S. 26)
			3. "erfolglose Suche lässt sich oft schon in einem inneren Knoten abbrechen" (S. 26)

- Zusammenfassung
	1. Mehrwegbaum: "breite Bäume geringer Höhe[,] Bezugsgröße [...] Seite als Transporteinheit zum Externspeicher[,] Seiten werden immer größer (S. 26)
	2. B- und B*-Baum gewährleisten balancierte Struktur unabh. v. Schlüsselmenge u. Einfügereihenfolge, wichtigste Unterschiede vgl. S. 26
	3. Digitale Suchbäume: "V"erwendung von Schlüsselteilen", "Unterstützung von Suchvorgängen u.a. bei langen Schlüsseln variabler Länge" (S. 27), wichtigste Realisierungen: PATRICIA-Baum, Radix-Baum 
Exzerpt Yang2002
----------------

0. Abstract

- Motivation: Joinanfragen auf multidimensionalen spatialen Daten ("k-closest pairs", "nearest neighbor joins")
- Daher jetzt: Neue Indexstruktur f. versch. Join-Anfragen -> "b-Rdnn-tree" (S. 140)
- Basiert auf "Rdnn-tree for the reverse nearest neighbor queries" (S. 140)
- Besonders effektiv f. "k-closest pair"-Anfragen, v. a. ggü. früheren Implementierungen wie R*-Baum
- Achtung, möglicherweise nicht relevant, da Fokus: "handling of spatial and multidimensional data" (S. 140)
 
1. Introduction 

- Wichtige Anfragen (auf multidimensionalen spatialen Daten): "point location, range, nearest neighbor, reverse nearest neighbor" (S. 140)
- Hier: 
	1. "(Distance-based) Spatial Joins" (S. 140) 
	* Wichtigste/effizienteste Algorithmen basieren auf: R-Bäumen, Seed-Bäumen, Breadth-First-approach 
	2. "k Closest nearest neighbor pairs" (S. 140)
	3. "k Closest pairs"

- Für mich also höchstens wichtig, da keine mehrdimensionalen Objekte, keine relationale Datenbank, keine Joinoperationen über mehrere Tabellen: Alternative Indexstrukturen 
- Jetzt: "bichromatic Rdnn-Tree [...] to solve the closest pair join problem" (S. 141) 
	* verwendet Information über die nächsten Nachbarn, um Suchpfade abzuschneiden 
	* für mich evtl. interessant: "the index structure is also very efficient on [...] closest nearest neighbor pairs, and all pairs nearest neighbor" (S. 141)

2. Problem Definitions and Existing Algorithms

- Kapitelinhalt: Problemdefinitionen, bisherige Algorithmen u. Lösungsansätze

2.1 Problem Definitions

- Fokus: "nearest neighbor related problems" (S. 141): "Given two data sets S and T and a query point in one data set S, one can search the nearest neighbor of a point in p ∈ S in the other data set T" (auch "bichromatic nearest neighbor search", S. 141)
- Def. (Bichromatic Nearest Neighbor Query): Vgl. S. 141
- Def. (k Closest NN Pairs Query): Vgl. S. 141; informell: "the k-closest NN pair problem with respect to a data set is to find k points in the data set that have smaller nearest neighbor distances than any other points in the same data set" (S. 141)
- Def. (k-Closest Pair Join): Vgl. S. 141
- Illustration d. Unterschiede (Grafik) zw. "k Closest Pair" vs. "k Closest NN Pair": Vgl. S. 141 -> Beachte: Sind nicht notwendigerweise identisch, da: "the closest NN pairs is always with respect to one of the data set involved. For that set, each object can only appear in the result once. For closest pairs queries, there is no such restriction", S. 141
- Unterschiede zw. "k Closest Pair" vs. "k Closest NN Pair" in Anwendungen: Vgl. Kap. 1
- "k Closest Pair" u. "k Closest NN Pair" sind jedoch eng miteinander verbunden, vgl. Theorem 2.1 (S. 142): Besagt, dass jedes "Closest Pair" in den "k-closest NN pairs" enthalten ist 

2.2 Existing Algorithms

- 2 wichtige Algorithmen: "incremental distance join algorithms" v. Hjaltason u. Samet/"algorithms based on the R-tree family" v. Corral et al. (S. 142)
- im Prinzip geht es hier aber immer um den Vergleich von Elementen zweier Mengen; ich möchte aber Aussagen über Elemente aus EINER Menge treffen (hier nämlich das Ziel: "new indexing scheme for join queries over multiple data sets", S. 142)

3. The Index Structure and Algorithms

- Kapitelinhalt: Vorstellung d. neuen Datenstruktur (bRdnn-Tree)

3.1 Proposed Index Structure: bichromatic Rdnn-Tree (bRdnn-Tree)

- Grundidee: Verwende Lösung des k-closest NN pair-Problems, um k-closest pairs zu finden (vgl. Theorem 2.1)
- Wichtigster Aspekt: Die Information über das NN pair wird dynamisch im Baum gespeichert 
- Beruht auf dem Rdnn-Baum, der das "Reverse Nearest Neighbor Problem" löst (S. 143)
- "Reverse nearest neighbor problem (RNN)" (S. 143): Für einen Punkt p aus S, finde "a collection of points in S that have p as their nearest neighbor" (S. 143)
- Prinzip: 
	* 2 Mengen R und S, für jede wird ein Baum berechnet ("Red tree"/"Blue tree", S. 143)
	* "For a point p in R, N N_S(p) denotes its nearest neighbors in data set S, and R N N_S(p) its reverse nearest neighbors in S" (S. 143)
	* Blätter in den beiden Bäumen enthalten Einträge der Form (pt, dnn): pt ist ein Datenpunkt, dnn ist die Distanz zwischen dem NN-Paar bezüglich pt (also die Distanz von pt zu seinem NN-Paar im anderen Baum)
	* innere Knoten in beiden Bäumen enthalten Einträge der Form (ptr, Rect, max_dnn, min_dnn): ptr ist die Adresse eines Kindknotens; falls ptr auf ein Blatt verweist, ist Rect das MBR aller Punkte im Blattknoten/falls ptr auf einen weiteren inneren Knoten verweist, ist Rect das MBR aller MBRs im Kindknoten; max_dnn/min_dnn sind die maximale/minimale Distanz jedes Punktes zu seinem NN in der anderen Menge

3.2 Algorithms

- Insertion and Deletion (vgl. S. 143)
- Spatial Join (vgl. S. 144)
- k Closest NN Pairs (vgl. S. 144)
- k Closest Pairs (vgl. S. 144)
- Laufzeiten werden leider nicht angegeben!

4. Experimental results

- Nur Vergleich von k-closest pair query mit früher vorgestellten Algorithmen (da nur hier ein Vergleich der Implementierungen möglich ist)
- Tests wurden ausgeführt auf: "uniformely distributed data, clustered data, as well as real geographical 2D data" (S. 145)
- Def. d. Kosten (f. Suche): Durchschnittliche #Blattknoten-Zugriffe  

4.1 Uniformely distributed data sets (= 100% Überschneidung)

- Besser als die früher vorgestellten Lösungen (DFS mit R*-Baum, Heap-Algo. mit R*-Baum) - sogar, wenn diese einen Seitenpuffer von 10 oder 80 Seiten erhalten 
- "When k is small, our algorithm is most beneficial" (S. 145)
- Der R*-Baum wird vor allem übertroffen, da: "by storing the nearest neighbor distance, our method can prune each bRdnn-Tree index separately at high level" (S. 145)
- Der vorgestellte Algo. ist auch robust ggü. der Bufferkapazität

4.2 2D clustered data sets

4.3 2D Real data set

4.4 Index maintenance

- Aber höhere Kosten im bRdnn-Baum ggü. R*-Baum: Indexpflege, z.B. Einfügung
- Vgl. S. 148, Tabelle 3 f. Kostenübersicht 

4.5 Is an index worthwile?

	1. Statische Datensätze: Ergebnis vorberechnen und in Tabelle abspeichern 
	* Falls obere Schranke f. k gegeben: Ergebnisse bis zu dieser Schranke vorberechnen und in Tabelle abspeichern ist weit billiger als Index! (Bsp. vgl. S. 149)
	* Ebenfalls für kleine Datensätze
	* Erst für sehr große Datensätze lohnt sich ein Index, weil die Kosten f. eine verschachtelte Schleife dann schneller wachsen als die Indexberechnung (hier: Datensätze mit bis zu 3000000 Datenpunkten)
	* Indexberechnung/Einfügung in bRdnn-Baum erfordert hier: Reverse NN-Suche und Einfügen des Punkts im korrespondierenden Baum 
	
	2. Dynamische Datensätze
	* Auch hier ist Vorberechnen möglich -> beim Einfügen eines neuen Datenpunkts muss dann ein Datensatz sequenziell gelesen werden (zum Update der Tabelle)
	* Ohne Index: Beim Einfügen eines neuen Datenpunkts müssen paarweise die Distanzen von jedem neuen Punkt zur jedem Punkt in der Tabelle berechnet werden 
	* Auch hier wird bei großen Datensätzen der Index sehr viel billiger als sequenzieller Scan ohne Index (= Vergleich mit Tabellenwerten) -> Index v. a. f. große Datensätze wichtig!

- Zusammenfassung: "in a relatively static environment with a relatively small data set, it is appropriate to use the naive nested-loop algorithm and cache the closest pairs. However, in a dynamic environment or with large amount of data, it is preferable to use the bRdnn-tree" (S. 148)

5. Conclusion and future work 

	1. Zusammenfassung: 
	* Vorstellung des bRdnn-Baums für Join-Queries
	* Indexstruktur speichert die NN-Distanz f. jeden Datenpunkt 
	* Liefert Pruning-Methode f. zahlreiche Anfragen (k-nächste Paare, k-NN-Paare)
	* Index ist robust sowohl f. unterschiedliche Verteilungen der Daten als auch begrenzte Ressourcen [?]

	2. Zukünftige Arbeiten
	* Wie kann man den Index schneller erstellen? 
	* bulk-loading: "a way to load data (typically into a database) in 'large chunks'" (vgl. http://stackoverflow.com/questions/4462074/what-does-bulk-load-mean)

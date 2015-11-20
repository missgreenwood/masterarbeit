Exzerpt Hellerstein1994
-----------------------

0. Abstract

- RD-Baum: Indexstruktur f. mengenwertige Attribute/"an adaption of the R-Tree that exploits a natural analogy between spatial objects and sets" (S. 2)
- R-Baum (englisch R-tree): "in Datenbanksystemen verwendete mehrdimensionale (räumliche) dynamische Indexstruktur. Ähnlich wie bei einem B-Baum handelt es sich hier um eine balancierte Indexstruktur." (Quelle: https://de.wikipedia.org/wiki/R-Baum)
- Also f. mich evtl. interessant: Wie werden die mengenwertigen Schlüssel (= "record elements of type set-of-x", S. 2) organisiert? ("A particular engineering difficulty arises in representing the keys in an RD-Tree", S. 2)
- Im Prinzip wird hier eine Abstraktionsebene tiefer gearbeitet: Bloom-Filter-Repräsentation von Mengen bzw. ihrer Schlüssel/Indizes ist nicht vorgegeben, sondern eine von vielen möglichen -> Es wäre also höchstens zu prüfen, ob eines der vorgeschlagenen Verfahren dazu geeignet ist, die Bloom-Filter selbst besser zu organisieren. Da die Organisation der Mengen aber durch die RD-Bäume gegeben ist, die für Geodaten/Mengeninklusion optimiert sind, vermutlich nicht!

1. Introduction

- "In this paper we describe the RD-Tree, an index structure for sets. The RD-Tree is a variant of the R-Tree, a popular access method for spatial data [...]. RD stands for 'Russian Doll', which describes the transitive containment relation that is fundamental to the tree structure" (S. 2)

1.2 Related Work

- "[S]ignature file techniques": Test auf Teilmengen-Eigenschaft (S. 4) -> "Signatures provide a way to quickly resolve a comparison of two specific sets, while the RD-Tree is an access method that guides the DBMS to the appropriate data" (S. 4)

3. Representation of Keys

- Kriterien für die Repräsentation von Schlüsseln: 
	
	1. Größe
	2. Vollständigkeit
	3. Berechnungsaufwand

3.1 Complete Representation 

- "The first class of representations considered define the bounding set of a set to be exactly the same as the set itself" (S. 7)
	* Vorteil: Keinerlei Verlust
	* Nachteil: Evtl. zu groß/Berechnungsaufwand f. grundlegende Mengenoperationen zu hoch 
- Einfachster Ansatz: Mengen direkt als Knoten des RD-Baums darstellen -> Nachteil: Die Schlüssel werden schnell zu groß, da sie Mengenvereinigungen darstellen ("Even if the base sets are all small, their union may be large, and keys in higher levels of the tree represent unions of many sets", S. 8)
- "fan-out"/"fanout": Ausfächerung, Ausgangsverzweigung
- Zwei Lösungsansätze hierfür: 
	
	1. Schlüssel außerhalb vom RD-Baum speichern, Zeiger auf den Schlüssel in jedem Baum-Eintrag mit abspeichern 
	* Nachteil: Mengenoperationen werden teuer
	2. Falls Universum der Basiselemente klein und feste Größe: Repräsentiere Mengen als Bitmap 
	* Vorteil: Feste Schlüsselgröße, billige (bitweise) Mengenoperationen   
	* Nachteil: Kein Einfügen neuer Elemente möglich!

- Daher jetzt Abwandlung des Bitmap-Ansatzes: 

3.2. Bloom Filters and Signatures 

- Vorteile: Feste Schlüsselgröße, billige Mengenoperationen 
- "A more sophisticated technique is to use signatures [...]. Every element has a signature, which is a pattern of bits in the bitmap that are set when the element is present" (S. 8) -> hier nicht wichtig!

3.3 Rangesets

- Die Schlüssel eines RD-Baums werden jetzt als "rangesets" (S. 9) repräsentiert 

3.4 Combined Representations

- Weitere Möglichkeiten: 
	
	* RD-Tree mit Kombination aus unterschiedlichen Repräsentationen
	* Mehrere Repräsentationen für jeden Schlüssel: "A key for an entry could consist of a hint, in the form of one of the approximate bounding sets described above, together with a pointer to the complete set description" (S. 10); bei der Suche wird dann nur bei einer positiven Antwort für den "hint" überhaupt weiter gemacht 

4. Inverted RD-Trees

5. Proposed Performance Study

6. Conclusion 

- "The performance of an RD-Tree in a domain is likely to depend on the correlation factor of elements in the domain" (S. 12)

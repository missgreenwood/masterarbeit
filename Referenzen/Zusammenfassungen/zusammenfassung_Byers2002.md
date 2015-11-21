Zusammenfassung Byers2002 _(referenziert in AMBIENCE)_
------------------------------------------------------

0. Abstract

- Ziel: Neue, effiziente u. einfache Datenstrukturen z. Approximation v. Mengenabgleich -> "useful standalone primitive for peer-to-peer networks and a natural subroutine in methods for exact reconciliation" (S. 1)
- "reconciliation": "Abgleich, Ausgleich, Verbindung"
- Beschreibung des "approximate reconciliation problem" [Achtung, wichtig!]: "peers A and B respectively have subsets of elements S_A and S_B of a large universe U. Peer A wishes to send a short message M to peer B with the goal that B should use M to determine as many elements in the set S_B - S_A as possible. [...] we focus on the situation where a single message M is sent" (S. 1)
- Erster Ansatz mit Bloom-Filtern -> dienen als Benchmark für "performance tradeoffs bewtween message size, accuracy and computation time" (S. 1)
- Dann Einführung einer neuen Datenstruktur: "approximation reconciliation trees" (S. 1) -> kombiniert "Patricia tries", "Merkle trees" u. Bloom-Filter (S. 1)
- Außerdem Vgl. d. unterschiedl. Datenstrukturen u. ihrer Performance

1. Introduction

- Exakter Mengenabgleich m. nahezu optimalen Rechenzeiten: Vgl. z.B. Minsky, Y., and Trachtenberg, A.. Practical set reconciliation. Tech. Perp. BU ECE 2002-01, Boston University, 2002.
- Hier jedoch: Approximativer Mengenabgleich, Ziel: "determine a large fraction of the set difference between the parties" (S. 1) -> bessere Rechenzeiten 
- Verfahren: Nur eine Kommunikationsrunde ("communication round", S. 1)
- Motivation: 
	1. Schnelle Abschätzung für spätere exakte Berechnung -> reduziert #Elemente bereits vorab drastisch 
	2. P2P-Anwendungen -> z.B. Abgleich von Musikdatenbanken ("song list") zw. Peers, "subroutine for informed content delivery of large data files protected with erasure-resilient codes" (S. 2, vgl. Byers, J., Considine, J., Mitzenmacher, M., and Rost, S.. Informed content delivery across adaptive overlay networks. IN Proc of ACM SIGCOMM '02 (August 2002).)
- Unterschied zu früheren Arbeiten: nur eine Kommunikationsrunde, Approximation ("one round protocols reconciling differences between very large sets", S. 2)
- Außerdem: Trennen von Preprocessing- und Mengenabgleichskosten ("carefully separate preprocessing costs from teh costs of reconciliation", S. 3) -> reconciliation immer in Echtzeit!
- Resultat: "while we account for all costs, we focus on minimizing the work done once peer A has sent its message to peer B" (S. 3)

2. Bloom Filters for Approximate Reconciliation 

- effektive Lösung bei vielen Unterschieden
- dient aber hier nur zum Vergleich/als Benchmark für effizientere/elegantere Lösungen bzw. diffizilere Probleme
- Grundlagen Bloom-Filter werden wiederholt/vorgestellt; wichtig/neu: 
- "The probability of a false positive f depends on the number of bits used per item m/n and the number of hash functions k according to the following equation: f ≈ (1 - e^(-km/n))^k. [...] This false positive rate is minimized by picking k = (ln 2)(m/n) which results in f = (1/2)^((ln 2)(m/n))" (S. 3)
- Definiere Performance-Kriterien: 
	1. #Kommunikationsrunden
	2. Nachrichtengröße
	3. Konstruktionszeit: "for A, the construction time is the time for A to compute the message; for B, the construction time is the time to produce an appropriate representation of S_B" (S. 4)
	4. Reconciliation time: "the time for B to compute the approximation to S_B - S_A given the message from A and an appropriate representation of S_B" (S. 4)
	5. Korrektheit: "the probability that a given element in S_B - S_A is identified by B. Of secondary concern is the correlation between correct identification of elements in S_B - S_A [?]" (S. 4) 
- Ergebnisse: 
	* Kleine Nachrichtengröße bei großer Korrektheit 
	* Weitere Verbesserung durch "compressed Bloom filter"
	* "With a constant number of hash functions and assuming hashes and array accesses are constant time operations, A's construction time is O(|S_A|) to set up the Bloom filter, and B's reconciliation time is O(|S_B|) to find the set difference" (S. 4)
	* Zusammenfassung:

Theorem 1: "There exists a one-round protocol with message size O(|S_A|), construction time O(|S_A|) for A, reconciliation time O(|S_B|), and constant accuracy." (S. 4)

- Nachteile: 
	* Konstruktionszeit O(|S_A|) und Nachrichtengröße O(|S_A|) (können noch gedrückt werden, z.B. durch Pipelining verschiedener Bloom-Filter)
	* Hohe "reconciliation time": "Even when the set difference S_B - S_A is small, every element of S_B must be tested against the filter F_A" (S. 4) -> wird durch den neuartigen Ansatz gelöst!

3. Approximate Reconciliation Trees [ARTs, meine Abk.]

- Ansatz: "for A to send a searchable structure as a message, so that not every element of S_B needs to be tested for membership in S_B - S_A" (S. 5)
- Ergebnisse: 
	* Niedrigere "reconciliation time" -> sublinear zu |S_B|, dafür zusätzliche logarithmische Terme in Konstruktionszeit 
	* Zusammenfassung: 

Theorem 2: "There exists a one-round protocol with message size O(log|S_A|), construction time O(|S_A|log|S_A|) for A, construction time O(|S_B|log|S_B|) for B, reconciliation time O(|S_B - S_A|log|S_B|) (with high probability), and constant accuracy." (S. 5)	

3.1 Prerequisite Data Structures

- Kapitelinhalt: "the data structures upon which ARTs are based" (S. 5)
- Anwendung: Patricia Tries für "structured searching based upon comparable subsets" (S. 5), Merkle Trees z. praktischen Vgl. d. Teilmengen, Bloom-Filter z. kompakten Repräsentation u. "To avoid some complications" (S. 5)

3.1.1 Patricia Tries

- Anwendung: Jeder Peer stellt seine Menge als Patricia Trie dar
- Konstruktion (Umbau einer Menge S aus einem Universum U = {0,...,u-1} in Patricia Trie): "The root (with depth 0) corresponds to the entire subset S. The children correspond to the subsets of S in each half of U; that is, the left child is S ∩ [0, u/2 - 1] and the right child is S ∩ [u/2, u-1]. The rest of the trie is similar; the jth child at depth k corresponds to the set S ∩ [(j-1) * u/2^k, j * u/2^k - 1]. [T]he trie has Θ(u) nodes and depth Θ(log u). [...] However, almost all the nodes in the trie correspond to the same sets [?]. In fact there are only 2|S| - 1 non-trivial nodes [?]. The trie can be collapsed by removing edges between nodes that correspond to the same set, leaving only 2|S|-1 nodes" (S. 5) -> Resultat ist Patricia trie, muss nicht binär sein!
- Jetzt: Mengenunterschiede an Hand von Baumdarstellungen!

	1. Suche auf unkollabierten Bäumen der Größe Θ(u): "If the root of peer A matches the root of peer B, then there are no differences between the sets. Otherwise, [...] peer B [...] recursively considers the children of the root. If x ∈ S_B - S_A, eventually peer B determines that the leaf corresponding to x in its tree is not in the tree for peer A. [...] Assuming nodes in the trie can be compared in constant time, the total work for peer B to find all of S_B - S_A is O(|S_B - S_A|log u), since each discrepancy may cause peer B to trace a path of depth log u." (S. 5)
	* Laufzeit: ~ Tiefe von T_B, aber worst case: Ω(|S_B|)) -> "to avoid this issue with high probability, we hash each element initially before inserting it into the virtual tree" (S.5; wir gehen immer von zufälligen Hashfkt. aus; hier mit einem Range von mind. poly(|S_B|), um Kollisionen zu vermeiden!)
	* Ergebnis: "random Patricia trie" (S. 6) m. n zufälligen Blattwerten (S. 6) u. den Eigenschaften: 
		a. ∅ Blatttiefe: log n + O(1)
		b. "the variance of the depth of a leaf is constant" (S. 6, [?])  
		c. Max. Blatttiefe: log n + √(2 log n) + O(1) (m. hoher W'keit) -> damit konzentriert sich Vtlg. d. Blatttiefen stark um log n
	* Beachte: Kein exakter Knotenvgl. mögl., nur probabilistischer! -> Daher jetzt: Merkle Trees 

	2. Suche auf kollabierten Bäumen: Schwieriger, da das Mapping der Knoten von T_A auf T_B nicht mehr eindeutig ist -> Methoden hierfür später

- Notationen hier (LANDAU-Symbole):
	* f ∈ Θ(g): f wächst genauso schnell wie g
	* f ∈ Ω(g): f wächst nicht wesentlich langsamer als g (Achtung, nur Komplexitätstheorie!)

3.1.2 Merkle Trees

- Prinzip: "method of signing and comparing large databases while allowing fast updates and identifying differences" (S. 6)
- Konstruktion: Merkle tree wird auf dem Patricia trie gebildet durch "associating a value with each node of the underlying tree. At the leaves, the value is obtained by applying a hash function to the element represented by the leaf. The values of the internal nodes of a Merkle tree are then obtained by applying a hash function to the values of their children. Using this construction, the hash of a node is dependent upon all of the elements inits subtree" (S. 6f.) 
- Eigenschaften: "Merkle trees on top of uncollapsed tries give a natural set reconciliation algorithm if the tree and its hashes are sent. [...] While this affords constant time comparisons, it now runs the risk of false positive matches due to hash collisions" (S. 7) -> jedoch nicht mögl. f. die kollabierten Patricia tries bzw. zu aufwändig! 
- Daher jetzt: Kombination m. Bloom-Filtern als dritter Schritt 

3.2 

- Kapitelinhalt: "provide and analyze the basic construction of ARTs" (S. 5)
- Prinzip: "a Bloom filtered representation of the Patricia/Merkle tree combination" (S. 7)
- Konstruktion (Bsp./Grafik vgl. S. 7): 
	1. "Randomization for tree balancing" (S. 7)
	2. Patricia trie 
	3. "Breaking spatial correlation" (S. 7, [?])
	4. "pre-hashed Merkle tree (+= XOR)" (S. 7)
	5. "Internal Bloom filter" (S. 7) 
	6. "Leaf Bloom filter" (S. 7)

- Funktionsweise: "each peer starts by building a Patricia trie of their set along with the associated Merkle tree values. The message A then sends to B is a Bloom filter of the values from the Merkle tree. For B to perform approximate reconciliation, B uses the same recursive algorithm previously used to traverse an uncollapsed trie, to traverse its collapsed Patricia trei T_B" (S. 7)
- Vorteile durch Verwendung des Bloom-Filters z. Zusammenfassung des Merkle-Baums: 
	1. B sucht die Knotenwerte in T_B im Bloom-Filter von A -> d.h. falls irgendein Knoten T_A den gesuchten Wert enthält, wird er mit hoher W'keit gefunden 
	2. Quasi keine Hash-Kollisionen in den Merkle-Bäumen mehr mögl., da der ART große #Bits für jeden Wert im Merkle-Tree verwenden kann -> werden nicht an den anderen Peer geschickt, sondern in Bloom-Filter zusammengefasst
	3. Komplikationen beim Kollabieren d. Bäume werden vermieden
- Nachteile: Ungenauere Resultate d. Vergleiche d. tries, da: Kein Vgl. der Werte d. in den Merkle-Bäumen, sondern Lookup in Bloom-Filter  

5. Korrektheit? 
	* Ignoriere Kollisionen 
	* Wann erhält B ein falsch Positives für ein Element x in  S_B - S_A auf Ebene d im approximation reconciliation tree für S_B? ⟺ Es gibt ein falsch Positives für einen der Knotenwerte auf Ebene d auf dem Pfad von der Wurzel zum Blatt, das x im Bloom-Filter repräsentiert!
	* Geg. Falsch-Positiv-Rate f im von A gesendeten Bloom-Filter: p_x (W'keit, dass B das falsch Positive x als Element aus S_B - S_A identifiziert) = (1 - f)^d
	* Um konstante erwartete Korrektheit zu erzielen: f max. O(a/d) f. die meisten Elemente
	* Da sich m. hoher W'keit Elemente im Baum von B auf Ebene log|S_B| + O(1) befinden: f sollte O(1/log|S_B|) sein -> A sollte Ω(log log|S_B|) Bits pro Element f. den Bloom-Filter verwenden u. Θ(log log|S_B|) Hashfunktionen (um Falsch-Positiv-Rate zu minimieren)
	* Zusammenfassung:

- Theorem 3: "There exists a one-round protocol with message size O(|S_A|log log|S_B|), construction time O(|S_A|log|S_A|log log|S_B|) for A, construction time O(|S_B|log|S_B|) for B, reconciliation time O(|S_B - S_A|log|S_B|log log|S_B|) (with high probability), and constant accuracy" (S. 9, Bew. vgl. S. 9) 
 
3.3 Improvements

- Kapitelinhalt: "Improvements over this basic construction leading to asymptotically better performance"
- Bisher durch ARTs erreicht: schnellere Suche f. kleine #Mengendifferenzen, kein Management v. Baumstrukturen notwendig
- Aber: "incorrect pruning ["Abschneiden"?] from false positives can result in large numbers of differences being overlooked" (S. 9) -> muss gelöst werden durch höhere #Bits pro Element u. höhere Laufzeiten:

3.3.1 Increased Branching Factor

- Verbesserung: Erhöhe den Verzweigungsfaktor der Bäume -> reduziert #Innere Knoten, damit auch W'keit für falsch Positive (da mehr Bits pro Knoten); verringert Tiefe des Baums
- Nachteil: Potenziell höhere Laufzeit 

3.3.2 Correction factors

- Verbesserung: "To double-check that a match is not caused by a false positive in an internal node, we can also check its children" (S. 10, im Merkle-Baum wg. seiner inhärent redundanten Struktur: "If an internal node represents a subset that provides a match between A and B, then each of its children should also match", S. 10) -> verbessert erheblich die Korrektheit
- Nachteil: höhere Laufzeit
- Verallgemeinerung:  

Theorem 4: "There exists a one-round protocol with message size O(|S_A|), construction time O(|S_A|log|S_A|) for A, construction time O(|S_B|log|S_B|) for B, reconciliation time O(|S_B - S_A|log^2|S_B|) (with high probability), and constant accuracy" (S. 10, Beweisskizze u. Herleitung S. 10)

3.3.3 Improved Bit Allocation

- Verbesserung: Unterschiedliche Knotengewichtung -> Knoten nahe der Wurzel bekommen mehr Bits, da ihre falsch Positiven "gefährlicher" sind
- Nachteil: In den Blättern auftauchende falsch Positive können ohnehin nicht durch weiteres Traviersieren des Baumes korrigiert werden; der ART kann also höchstens so korrekt sein wie die Bloom-Filter-Tests seiner Blätter -> ein ART kann nur so korrekt sein wie ein Bloom-Filter derselben Größe 

3.3.4 Leveraging Random Tree Structure

- Verbesserung 1: Weitere Anpassung der ART-Struktur an Hand 3.3.3 -> Verwende separaten Bloom-Filter für jedes Baumlevel mit Θ(h) Bits für jeden Knoten auf Level h 
- Verbesserung 2: Versuche, die größere Korrektheit des Merkle-Baums m. der weniger komplizierten Struktur des Bloom-Filters zu verbinden -> Hybridstruktur
- Konstruktion: 
	1. Die ersten log n - 2 log log n Levels eines beliebigen Baums sind höchstwahrscheinlich vollständig -> keine Rekonstruktion für ART erforderlich
	2. B kann die ersten Levels also direkt durchsuchen -> niedrigere Falsch-Positiv-Rate, höhere Korrektheit 
	3. Erst die unteren Levels werden von B mittels Bloom-Filter getestet
	4. Verwende zusätzlich große #Bits pro Element für die höheren Levels -> niedrigere Falsch-Positiv-Rate, höhere Korrektheit 

3.4 Improved Theoretical Result

- Kapitelinhalt: "final construction"
- Zusammenfassung der Verbesserungen in 
Theorem 2: "There exists a one-round protocol with message size O(|S_A|), construction time O(|S_A|log|S_A|) for A, construction time O(|S_B|log|S_B|) for B, reconciliation time O(|S_B - S_A|log|S_B|) (with high probability), and constant accuracy" (S. 12, Bew. S. 12)

4. Experiments

4.1 Accuracy Experiments

- Vgl. Diagramm 3 (S. 13):
	3(a): Basis-Implementierung, unterschiedl. Werte f. Korrekturfaktor, unterschiedl. Verteilungen d. Bits zw. Blättern u. inneren Knoten 
	3(b): Erhöhe Verzweigungsfaktor von 2 auf 4 -> "dramatic increase in accuracy since the tree depth is halved and the number of internal nodes drops" (S. 11)
	3(c): Explizite Angabe der oberen (vollständigen) Baumlevels -> "definite improvement over the basic approach, but not as much as changing the branching factor" (S. 11)
	3(d): Kombinierter Effekt

4.2 Speed Experiments

- Vgl. Diagramm 4 (S. 14): "We compare Bloom filters against badic ARTs and those with the explicit (complete) top levels, both with correction levels of zero and two" (S. 14); Verzweigungsfaktor ist immer 4; 2 Bloom-Filter f. Blattknoten u. innere Knoten; Bitverteilung f. die Bloom-Filter so gewählt, dass max. Korrektheit erreicht wird 
- Ergebnisse: 
	1. "For small numbers of differences, Bloom filters take significantly longer to reconcile" (S. 14)
	2. "The reconciliation time taken by Bloom filters is roughly constant, but drops slightly as the number of differences increases" (S. 14)
	3. "The reconciliation time for approximate reconciliation trees grows roughly linearly with the number of differences and is initially very small" (S. 14)
	4. Wie bei Bloom-Filtern: "drop in the time to reconcile when nearly all the elements are different" (S. 14)
	5. ARTs mit höheren Korrekturfaktoren sind erwartungsgemäß langsamer; nur minimaler Unterschied bei expliziter Angabe der oberen (vollst.) Baumlevels; bei kleiner #Mengenunterschiede jedoch schon  
	6. Korrekturfaktor 2: "ARTs are faster if the number of differences is fewer than 2% of |S_B|. Without correction, they are faster if the number of differences is fewer than 30% of |S_B|, but at the cost of significantly decreased accuracy" (S. 14)
- Trend trotz kleiner Unterschiede: "for small numbers of differences, approximate reconciliation trees are faster, but their advantage deteriorates as the correction level increases" (S. 15)

5. Conclusions 

- Vorstellung von approx. Mengenabgleich als Primitiv für P2P-Anwendungen 
- Vorstellung von ARTs mit minimierter Abgleichszeit ggü. Bloom-Filter-Ansatz, praktischer Nachweis d. Wirksamkeit 
Exzerpt Bayardo2007
-------------------

0. Abstract

- Gegeben: Große Menge dünn verteilter Vektordaten in hochdimensionalem Raum 
- Problemstellung: Finde alle Paare mit Ähnlichkeitswert über einer bestimmten Schwelle (Ähnlichkeitsmaß: z.B. Kosinusdistanz)
- Lösung: Einfacher Algorithmus basierend auf neuer Indexstruktur und Optimierung, ohne Näherungsverfahren oder komplexes Parameter-Tuning
- "We show the approach efficiently handles a variety of datasets across a wide setting of similarity thresholds, with large speedups over previous state-of-the-art approaches" (S. 131)

1. Introduction 

- Anwendungsszenarien (Bsp.): 

	1. "Query refinement for web search" (S. 131)
	2. "Collaborative filtering" (S. 131)

- Allerdings: Alles Szenarien für sehr große Datenmengen!
- Heute i.d.R.: Näherungsverfahren -> hohe Fehlerraten/exakte Lösungen, aber in DBMS-Framework!   
- Hier stattdessen: Keine DBMS-Integration, Fokus rein auf Performance 

2. Problem Statement

	1. "Given a set of real-valued vectors V [...] of fixed dimensionality m, a similarity function sim(x,y) and a similarity threshold t, we wish to compute the set of all pairs (x,y) and their similarity values sim(x,y) such that x,y ∈ V and sim(x,y) ≥ t" (S. 131)
	2. Ähnlichkeitsfunktion sei kommutativ
	3. v_i sind nichtnegativ

- Zunächst nur für Einheitsvektoren + Kosinusdistanz

- Terminologie: 

	1. "unit vector in a normed vector space": "a vector (often a spatial vector) of length 1" (vgl. https://en.wikipedia.org/wiki/Unit_vector)
	2. Kosinusdistanz f. 2 Einheitsvektoren x,y ist ihr Kreuzprodukt, d.h. dot(x,y) = Σ_i x[i] * y[i]
	3.  "sparse vector representation for a vector x": "the set of all pairs (i, x[i]) such that x[i] > 0 over all i = 1...m" (S. 131, auch: "features")
	4. "size of a vector x": "|x|, [...] the number of such pairs" (S. 131)
	5. hingegen Länge ("length"/"magnitude") eines Vektors x: ||x|| (S. 131)
	6. "inverted list representation of [a] set [of sparse vectors V]": "m lists I_1, I_2, ..., I_m (one for each dimension), where list I_i consists of all pairs (x,w) such that vector x is in V, x[i] = w, and w is non-zero" (S. 132)
	7. "maxweight(x) [for a vector x]": "the maximum value x[i] over all i" (S. 132)
	8. "maxweight_i(V) [for a set of sparse vectors V]": "the maximum value x[i] over all vectors x in the dataset V" (S. 132)

3. Related Work

- "The all-pairs similarity search problem is a generalization of the well-known nearest neighbor problem in which the goal is to find the nearest neighbors of a given point query" (S. 132)
- Lösungsansätze mit Näherungsverfahren: Reduktion d. Dimensionalität und/oder Länge d. Input-Vektoren 
- Das Problem wird in der DB-Community allgemein als "similarity join problem" bezeichnet (S. 132) -> zwei Ansätze: "inverted list solutions" u. "signature based solutions" (S. 132)

4. Algorithms

- Kapitelinhalt: Algorithmus + Einschränkung auf Kosinusdistanz/Portierung auf Binärdaten/Erweiterung auf Daten im Sekundärspeicher   
- Annahme: Vektoren u. Indexstrukturen sind im Hauptspeicher

4.1 A Basic Inverted Index-Based Approach

	1.  Naiver Ansatz: "employing an IR system to build an inverted list index of the input vectors, and issuing each input vector as if it were a query to find the set of matching documents. Matching documents could then be filtered according to the similarity threshold, or the IR system itself could be modified to return only documents that meet the threshold" (S. 132)
	* Jedoch ineffizient: 
		a. Berechnung von (x,y) und (y,x), obwohl Ähnlichkeitsmaß kommutativ 
		b. Berechnung des gesamten "inverted list index" vor jeglichem Output (S. 132)
		c. Index und Vektoren müssen im Hauptspeicher liegen 

	2. Verbesserung: Berechne Index dynamisch [vgl. Sarawagi2004], speichere Gewichte der Vektoren im invertierten Index mit ab -> "Score accumulation can then be applied to compute the similarity function using the inverted index structure alone" (S. 132)

	3. Verwende Heap als Datenstruktur, wenn nur die n ersten Ergebnisse von Interesse sind -> "only the initial portion of many lists may need to be accessed" (S. 132)
	* Jedoch nicht anwendbar, wenn alle Antworten (bis zu einer bestimmten Schwelle) gefunden werden sollen
	* Lösungsansatz hier: "scan each [inverted list] individually and accumulate scores in a hash-based map" (S. 132)

	=> Ergebnis: "All-Pairs-0" (vgl. S. 133 Fig. 1): "the top-level function scans the dataset and incrementally builds the inverted lists. The Find-Matches-0 subroutine scans the inverted lists to perform score accumulation. We call any vector y that is added to the weight accumulation map a candidate vector for x, and the vector pair (x,y) a candidate pair. The algorithm checks the score of each candidate pair, and adds the pair in the result set if it meets the threshold" (S. 132)

4.2 Exploiting the Threshold During Indexing

- Schwellwert kann verwendet werden, um Kandidatenpaare einzugrenzen 
- Vermeide Aufbau des gesamten invertierten Index (wie z.B. [Sarawagi2004]) -> hier stattdessen: "exploit the threshold to reduce the amount of information indexed in the first place" (S. 132)

=> Ergebnis: "All-Pairs-1" (vgl. S. 133 Fig. 2): "The main loop function now iterates over features from most to least frequent, and avoids indexing any vector features until a particular condition is met. The result is to index just enough of the least frequent features to ensure that any vector y that has the potential of meeting the similarity threshold given x must be identified as a candidate of x during matching" (S. 133, Details vgl. ebd.)

- Verbesserung: Viel schneller als All-Pairs-0, da drastische Reduzierung d. max. Größe d. invertierten Listen 
- Korrektheitsbeweis: Vgl. S. 133

4.3 Exploiting a Specific Sort Order

- Voraussetzung aus 4.2: "All-Pairs-1 [...] indexes enough of each vector y to guarantee that y is produced as a cadidate when matched against any other vector x in the dataset such that x and y satisfy the similarity threshold" (S. 133, Korrektheit von All-Pairs-1)
- Jetzt: Korrektheit erfüllt, aber weitere Einschränkung d. Kandidatenmenge -> "a vector y must be produced as a candidate only when matched against those vectors that follow it in the order in which the dataset is processed" (S. 133)

=> Ergebnisse: "All-Pairs-2" (vgl. S. 134 Fig. 3a): "The ordering over the vectors guarantees any vector x that is produced after a vector y has a lower maximum weight. Significantly fewer features of each vector can now be indexed while still guaranteeing candidacy of a vector when matched against those that follow it in th iteration order" (S. 134)

- Details u. Korrektheitsbeweis vgl. S. 134

4.4 Exploiting the Threshold During Matching

- Voraussetzung aus 4.1: "indirectly exploit the similarity threshold to reduce candidate pairs by virtue of the partially indexed vectors" (S. 134)
- Jetzt: Bessere Ausnutzung des Ähnlichkeits-Schwellwerts (zweimal ohne, einmal mit geordnetem Datensatz): 

	1. "as we iterate over the features of x, we eventually get to the point where if a vector has not already been identified as a candidate of x, then there is no way it can meet the score threshold"	
	2. Berechne nicht das gesamte Skalarprodukt über x und y' ("partial candidate vector"), sondern Schranke
	3. "for a vector x, [...] any vector y that satisfies the similarity score threshold must meet the [...] minimum size constraint: |y| ≥ t/maxweight(x)" (S. 135)

	=> Ergebnis: "Find-Matches-2" (vgl. S. 134 Fig. 3b): 
	1. "keep[...] track of such a point by maintaining an upperbound remscore on the score attainable between x and any vector y that shares none of the 'already processed' features" (S. 134)
	2. "only explicitely computes the dot product should the upperbound meet the threshold" (S. 134)
	3. Entferne jeden Vektor aus dem Index, der Minimalgröße nicht erfüllt

- Details vgl. S. 134f. 

4.5 Specializations for Binary Vector Data

- Man könnte die bisher vorgestellten Algorithmen direkt verwenden, indem man die Inputs auf Einheitslänge normalisiert und auf den resultierenden gewichteten Vektoren arbeitet
- Jedoch hier: Vermeide komplizierte Berechnungen + weitere Optimierungen möglich 
- Bsp.: "If the vectors are binary, there is no need to store vector weights within the inverted index as long as we can get at the vector sizes in order to appropriately compute the similarity function" (S. 135)
=> Ergebnis: "All-Pairs-Binary" (vgl. S. 135 Fig. 4): 

	1. "all vectors that fail to meet the minimum size constraint appear at the front of the list" (S. 135) -> alle diese Vektoren können sofort entfernt/übersprungen werden 
	2. für alle weiteren Vektorenpaare (x,y), deren Kosinusähnlichkeit über einem best. Schwellenwert t liegt, wird folgender "minsize constraint" ausgenutzt: |y| ≥ |x|*t^2 (S. 136)

- Details u. Korrektheitsbeweis vgl. S. 135

4.6 Extensions for Disk Resident Data

- nur interessant für Datensätze, die nicht im Hauptspeicher gehalten werden können, also wahrscheinlich eher uninteressant
- Lösungsansatz: "have the algorithm index newly encountered vectors only up to the point where further indexing would exceed available memory" (S. 136) -> vergleichbar der "block nested loop strategy employed by database systems for out-of-core table joins" (S. 136)

5. Experiments

- 3 Datensätze, alle Implementierungen in C++ mit "standard template library vector class for inverted lists and most other structures" (S. 136)
- außerdem Klassen von Google: "dense_hash_map" ("performing score accumulation in Find-Matches") und "dense_hash_set" ("signature matching", S. 136)
- Im Folgenden Beschreibung der Datensätze

5.1 Datasets 

	1. QSC: "the 5 million most frequent queries that were submitted to the Google search engine [...] during one week" (S. 136)
	2. Orkut: "the Orkut social network, in which each user is represented by a binary vector over the space of all users" (S. 136) 
	3. DBPL: "snapshot of the DBLP data" (S. 137)

- Es wurden immer sortierte Datensätze verwendet
- Schwellwert f. Ähnlichkeitsmaß: Zwischen 0.5 und 0.9

5.2 Comparison of Inverted List-Based Approaches

- Vergleich von All-Pairs mit "another inverted-list based approach, ProbeOpt-sort" (S. 137)
- Varianten von All-Pairs wurden verwendet, die nicht auf sortierten Datensätzen beruhen (wg. Vergleichbarkeit m. ProbeOpt-sort)

=> Ergebnis: All-Pairs immer deutlich besser als ProbeOpt-sort (mind. Faktor 2)
- Speedup wg. nur teilweiser Indexierung jedes Eingabevektors u. "hash-based score accumulation in place of queue-based merging" (S. 137)
- Weitere Verbesserungen durch Ausnutzen der sortierten Datensätze (bis Faktor 22)

5.3 Comparison with Signature-Based Methods

- Vergleich von All-Pairs mit "two signature-based methods for finding all similar pairs: LSH and PartEnum" (S. 137)
- LSH (Locality Sensitive Hashing): "well-known approximate algorithm for the problem" (S. 138)
- PE (Part Enum): "another signature based algorithm that like All-Pairs is guaranteed to generate all pairs that satisfy the similarity threshold" (S. 138); Verwendet Konversion von Jaccard-Distanz zu Hammingabstand! (S. 138)
- Vergleich von AllPairs mit PartEnum und LSH unter Verwendung von Jaccard-Distanz und Kosinusähnlichkeit: Vgl. S. 139 Fig. 9

=> Ergebnis: All-Pairs ist immer deutlich schneller: 
	1. LSH: Faktor 16-700 bei Kosinusähnlichkeit, mind. eine Größenordnung b. Jaccard-Distanz
	2. PE: Faktor 2-15 b. Kosinusähnlichkeit, Faktor 1.3-6 b. Jaccard-Distanz  

6. Other Similarity Measures

- Kapitelinhalt: Verallgemeinerung d. Ergebnisse f. andere Ähnlichkeitsmetriken
- Algo. kann auch für andere Ähnlichkeitsmaße angewendet werden, z.B. Jaccard mit binären Eingabevektoren! 
- notwendige Anpassungen: "For an indexed vector y and any vector x following it in the ordering (|x|≥|y|) [...] we [...] only need to show that the unindexed portion of the vector y [...] contributes an amount to the similarity score that alone is not enough to meet the threshold" (S. 139) -> "Find-Matches-Binary" muss angepasst werden bzgl. "similarity score, upperbound the similarity score, and compute a monotone minimum size constraint on candidate vectors" (S. 139)
- Ergebnisse f. All-Pairs-Algo. m. anderen Ähnlichkeitsmaßen: Vgl. S. 140 Fig. 10 -> Jaccard performt immer am besten!!

7. Conclusions and Future Work

- Zentrale Erkenntnisse:
	1. "An inverted list based approach to the problem need not build a complete inverted index over the vector input" (S. 139)
	2. "Appropriately ordering the vectors in addition to the dimensions can vastly reduce the search space" (S. 139)

- Ergebnis: "We aggressively exploited these insights to produce an algorithm, All-Pairs, that is easy to implement and does not require any parameter tuning" (S. 139) -> führt zu drastischen Performance-Steigerungen ggü. vergleichbaren Algorithmen 
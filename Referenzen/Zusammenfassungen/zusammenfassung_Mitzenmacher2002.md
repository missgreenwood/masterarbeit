Zusammenfassung Mitzenmacher2002 _(referenziert in AMBIENCE)_
-------------------------------------------------------------

0. Abstract

- Ziel: Optimierte Bloom-Filter für beschränkte Nachrichtengröße -> komprimierte Bloom-Filter "compressed Bloom filters" (S. 604)
- Beispielanwendung: "sharing web cache information" (S. 604): "proxies do not share the exact contents of their caches, but instead periodically broadcast Bloom filters representing their cache" (S. 604) -> Optimierungsmöglichkeiten durch komprimierte Bloom-Filter: Falsch-Positiv-Rate f, #Übertragene Bits, Rechenaufwand pro Lookup
- Nachteil/Kosten: Rechenzeit/-aufwand f. Kompression u. Dekompression u. höherer Speicherplatz f. unkomprimierte Form    
- Kompression u. Dekompression: z.B. einfache arithmetische Codierung 

1. Introduction

- Bloom-Filter sind randomisiert, da zufällig ausgewählte Hashfkt. verwendet werden!
- Bloom-Filter sind von Vorteil v. a. in verteilten Systemen: "where systems need to share information about what data they have available" (S. 604)
- Bsp. f. Bloom-Filter in verteilten Anwendungen: Squid, OceanStore etc. 
- Hier: Bloom-Filter 
	1. Als Datenstruktur -> Optimierung Falsch-Positiv-Rate (möglichst niedrig)
	2. Als Nachricht zw. Proxies -> Optimierung Nachrichtengröße (möglichst klein)
- Ziel: Verbesserte Performance durch reduzierte Nachrichtengröße, reduzierte Falsch-Positiv-Rate und/oder reduzierten Rechenaufwand pro Lookup
- Fokus: "Our paper underscores an important general principle for distributed algorithms: when using a data structure as a message, one should consider the parameters of the data structure with both of these roles in mind. If transmission size is important, tuning the parameters so that compression can be used effectively may yield dividends" (S. 605)

2. Compressed Bloom Filters: Theory

- Kapitelinhalt: Problembeschreibung als Optimierungsproblem 

2.1 Bloom filters 

- neue/wichtige Aspekte: "Bloom filters are highly effective even if m = cn for a small constant c, such as c = 8. An alternative approach if more bits are available is to simply sash each item into Θ(log n) bits and send a list of hash values. Bloom filters can allow significantly fewer bits to be sent while still achieving good false positive rates" (S. 605)

2.2 Compressed Bloom filters

- Bisher: Optimierung der #Hashftk. als Funktion von m und n ("optimiziation [...] of the number of hash functions k[,] based on the assumption that we wish to minimize the failure of a false positive as a function of the array size m and the number of objects n", S. 605)
- Jetzt: Optimierung der #Hashfkt. als Funktion d. Übertragungsgröße -> "Therefore we choose our parameters to minimize the failure probability after using compression" (S. 606)
- Für den bisherigen optimierten Bloom-Filter wird durch Kompression nichts gewonnen, da: "Under our assumption of good random hash functions, the bit array appears to be a random string of m =#s and 1's, with each entry being 0 or 1 independently with probability 1/2" (S. 606) -> daher jetzt: wähle k so, dass mit W'keit p = 1/3 jeder der Einträge im Bitarray m 1 ist, ermöglicht Kompression u. reduziert Übertragungsgröße
- Frage: "[Does] this compression gain[...] us anything, or [...] would [we] have been better off simply using a smaller number of bits in our array and optimizing for that size"? (S. 606) 
- Annahme: Lookup erst nach Dekompression 
- Daher erster Ansatz: "split the Bloom filter into several pieces, and compress each piece. To look up a bit would only require decompressing a certain peice of the filter instead of the entire filter, reducing the amount of memory required" (S. 606) -> unpraktikabel, falls viele Lookups in versch. Teilen notwendig werden
- 4 Metriken: 
	1. Rechenzeit/#Hashfkt. k
	2. Fehlerwahrscheinlichkeit/Falsch-Positiv-Rate f 
	3. Unkomprimierte Filtergröße/#Arraybits m 
	4. Übertragungsgröße/Komprimierte Filtergröße z
- Problembeschreibung: "given n and z, choose m and k to minimize f subject to mH(p) ≤ z" (S. 606) -> "One possibility is to choose m = z and k = (ln 2) * (m/n) so that p = 1/2; this is the original optimized Bloom filter. Hence we can guarantee that f ≤ (0.6185)^(z/n)" (S. 606)
- Das ist jedoch die schlechteste Möglichkeit, wenn Kompression erlaubt ist, da: 
	1. Formuliere f als Fkt. von p, also f = (1 - p)^(-(z ln p)/(nH(p)))
	2. Ziel: Minimiere β = f^(n/z)
	3. Ermittle Maximum für β: β ist maximal gdw γ = ((p/(ln(1-p))) + ((1-p)/ln p)) ist minimal (warum [?])
	4. Ermittle dγ/dp und setze dγ/dp = 0 ⟹ p = 1/2
	5. Ermittlung von f'' und einsetzen liefert p = 1/2 ist globales Maximum, d.h. "the maximum probability of a false positve using a compressed Bloom filter occurs when p = 1/2, or equivalently k = (ln k) * (m/n)" (S. 606)

- Wichtiges Ergebnis hier: "the number of hash functions that minimizes the false positive rate without compression in fact maximizes the false positive rate with compression" (S. 606)
- Für Grenzwertbetrachtung bei minimalem β: p strebt gegen 0 oder 1 -> "β goes to 1/2 in both limiting cases, and we can in theory achieve a false positive rate arbitrarily close to (0.5)^(z/n) by letting the number of hash functions go to 0 or infinity" (S. 607, Erklärung vgl. S. 607) 
- In der Realität sind 0 oder unendl. viele Hashfkt. nat. nicht machbar! Stattdessen Optimierung #Hashfkt. f. komprimierten Bloom-Filter: Setze k < ln 2 * (m/n) (wird nicht erklärt...)
- Andere (denkbare) Optimierungsmöglichkeit: Wähle f fest, optimiere z ⟹ z = m ln 2 -> bedeutet ca. 30% Speicherplatzersparnis
- Ergebnisse: 
	 1. "compression is a viable means of improving performance" (S. 607)
	 2. "because the compressed Bloom filter allows us another performance metric, it provides more flexibility than the standard original Bloom filter" (S. 607)
	 3. "compressed Bloom filters use a smaller number of hash functions, so [...] lookups are more efficient" (S. 607)

3. Compressed Bloom Filters: Practice

- Kapitelinhalt: Praxisaspekte (Kompressionsschemata, tatsächliche Performance etc.)
- Zusätzliche praxisrelevante Aspekte: 
	1. Beschränktes m 
	2. Kompressionsoverhead
	3. Kompressionsvariabilität: Größe der komprimierten Bloom-Filter sollen Paketgröße im Netzwerk nicht überschreiten; Kompressionsperformance ist vom Input abh. (z.B. ist es schlecht, wenn n vorher nicht bekannt ist)
	4. Hashing-Performance
- Hashing-Aspekte werden hier nicht weiter behandelt -> Annahmen: 
	1. "in practice we suspect that using standard universal families of hash functions [vgl. J. L. Carter and M. N. Wegman. Universal classes of hash functions. Journal of Computer and System Sciences, 18, pages 143-154, 1979 sowie L. Fan, P. Cao, J. Almeida, and A. Broder. Summary cache: A scalable wide-area Web cache sharing protocol. In Proceeding of SIGCOMM ’98, 1998. Extended version available as Technical Report 1361, Computer Sciences Department, Univ. of Wisconsin-Madison, February 1999] or MD5 [vgl. Ramakrishna1989] will be suitable" (S. 607)
	2. "in situations where hashing performance is not sufficiently random, we expect that compressed Bloom filters will still generally outperform the uncompressed Bloom filter" (S. 607) -> jedoch ergibt sich folgendes Problem: Schwache Hashfunktionen können zu Bitarrays führen, die sich nicht so gut komprimieren lassen wie erwartet!

- Hier verwendetes Kompressionsverfahren: Arithmetic coding ("for a random m bit string where the bit values are independent and each bit is 0 with probability p and 1 with probablity 1-p, arithmetic coding compresses the string to near mH(p) bits with high probability, with the deviation from the average having a Chernoff-like bound", S. 608)
- Andere Kompressionsschemata wie Lauflängenkodierung wären auch denkbar 
- Vorgehensweise Kompression:
	1. Wähle max. unkomprimierte Größe m 
	2. Designe komprimierten Bloom-Filter an Hand Kap. 2, verwende etwas kleinere Kompressionsgröße als gewünscht (z.B. 0.99z wg. Kompressionsvariabilität -> "with this desgin, the compressed filter should be within the desired size range with high probability", S. 608)
- Behandlung von Sonderfällen mit schlechtem Kompressionsverhalten: Verwende multiple Filtertypen, im Zweifelsfall den Standard-Bloom-Filter

3.1 Examples

- Die Variationen der Konfigurationen richten sich im Wesentlichen nach L. Fan, P. Cao, J. Almeida, and A. Broder. Summary cache: A scalable wide-area Web cache sharing protocol. In Proceeding of SIGCOMM ’98, 1998. Extended version available as Technical Report 1361, Computer Sciences Department, Univ. of Wisconsin-Madison, February 1999: 
	1. Max. 8 Transmissionsbits pro Element
	2. Max. 16 Transmissionsbits pro Element
	3. Max. 4 Transmissionsbits pro Element
	4. Max. f ≈ 0.02
	5. Max. f ≈ 0.00045
- Verwendetes Kompressionsverfahren (Bibliothek/Implementierung: Vgl. J. Carpinelli, W. Salomonsen, A. Moffat, R. Neal, and I. H. Witten. Source code for arithmetic coding, Version 1. Available at http://www.cs.mu.oz.au/~alistair/arith_coder/. March 1995 sowie A. Moffat, R. Neal, and I. H. Witten. Arithmetic coding revisited. ACM Transactions on Information Systems, 16(3):256-294, July 1998.)
- Ergebnisse der unterschiedlichen Kombinationen: Vgl. S. 408; entsprechen den theoretischen Vorüberlegungen 
- "to bear out": bekräftigen, bestätigen 

4. Delta Compression 

- Jetzt: Nicht die ganzen Bloom-Filter sollen übertragen werden, sondern nur, was sich in der Zwischenzeit geändert hat ("representations of the changes between the updated filter and the old filter", S. 610)
- Berechnung der Differenzen durch XOR, dann Kompression wie zuvor
- Bsp.: "one may decide that updates should be broadcast whenever 5% of the underlying array bits have changed; in this case, the compressed size of the delta would be roughly mH(0.05)" (S. 610)
- Versuchsaufbau/Problembeschreibung analog zu vorher ("we consider the case where our goal is to minimize the false positive rate f while maintaining a specific size for the delta", S. 610) 
	1. "We send a delta whenever a fraction c of the n entries of the set have changed" (S. 610)
	2. Damit sind n und z fest, m und k können frei gewählt werden 
	3. Sei q: W'keit, dass Deltabit nach Änderung von c * n Elementen = 1 ist, also q = 2p(1 - e^(-cnk/m)) = 2p(1 - p^c)
	4. Wie vorher: z = mH(q)
	5. Wie vorher: Sei p W'keit, dass ein Bit im Bloom-Filter = 0 ist, also p = e^(-kn/m))
	6. Wie vorher: Formuliere f als Fkt. von p (vgl. Abschnitt 2.2)
	7. Wie vorher: Ziel: Minimiere β (vgl. Abschnitt 2.2) -> Aber Symmetrie von Standard- u. komprimiertem Bloom-Filter besteht nicht mehr: "The value of β still appears to be minimizid as p ⟶ 1 for any c < 1/2, but a simple formal proof appears challenging" (S. 411)
- Für Grenzwertbetrachtung bei minimalem β: p strebt 1 -> "β ⟶ (1/2)^(1/2c), so f approaches (0.5)^(z/2cn)" (S. 611, Erklärung vgl. S. 611) 
- Ergebnisse (Details vgl. S. 611 sowie Tabellen 6 und 7, S. 611): 
	* "using compressed Bloom filters in conjunction with delta compression can yield even greater performance gains" (S. 410)
	* m oder k können ggü. Standard- und komprimiertem Bloom-Filter deutlich reduziert werden (wie zuvor: entweder f fest oder z fest, vgl. Abschnitt 3.1)
	* Bei kleinerem c weitere Verbesserungen 

5. Counting Bloom Filter

- In Fan2000 werden auch "counting Bloom filters" beschrieben, diese werden dort aber nicht übertragen
- Auch für "counting Bloom filters" könnten mit Kompression erhebliche Performance-Gewinne erzielt werden: "Our optimization approach for finding appropriate parameters can be extended to this situation, and arithmetic coding remains highly effective" (S. 611)
- Es ist anzunehmen, dass auch andere Bloom-Filter-Varianten von Kompression und arithmetic encoding profitieren! 

6. Conclusions

- Ergebnisse: 
	1. Kompression verbessert Performance von Bloom-Filtern
	2. Proof of Concept/Paradigma von Datenstruktur als Nachrichtenformat in verteilter Anwendung 
	3. Fokus auf Minimierung/feste Nachrichtengröße -> andere Parameter müssen sich hieran orientieren 

- Offene Fragen (zum Zeitpkt. der Veröffentlichung!): 
	1. Gute zufällige Hashfkt. werden vorausgesetzt 
	2. Kein Proof of Concept in kompletter Anwendung 

8. Appendix: Mathematical Details

- V.a. Herleitung: "the size of a compressed Bloom filter is very close to mH(p) with high probability" (S. 612)
Zusammenfassung Broder2004 _(referenziert in AMBIENCE)_
-------------------------------------------------------

0. Abstract

- Zentrale Def. Bloom-Filter: "a simple space-efficient randomized data structure for representing a set in order to support membership queries" (S. 485)
- Ziel des Papers: "survey the ways in which Bloom filters have been used and modified in a variety of network problems, with the aim of providing a unified mathematical and practical framework for understanding them and stimulating their use in future applications" (S. 485)

1. Introduction 

- Inhalte des Papers: Math. Beschreibung von Bloom-Filtern; Vorstellung von vier Netzwerk-relevanten Anwendungsmöglichkeiten: 
	1. "Collaborating in overlay and peer-to-peer networks" (S. 486): "summarizing content to aid collaborations in overlay and peer-to-peer networks" (S. 486, hier zentral!)
	2. "Resource routing" (S. 486) -> evtl. wichtig?
	3. "Packet routing" (S. 486)
	4. "Measurement" (S. 485): "tool for measurement infrastructures used to create data summaries in routers or other network devices" (S. 486)
- Gemeinsamkeit dieser Anwendungen: "The Bloom filter principle" (S. 486) ->"Wherever a list or set is used, and space is at a premium, consider using a Bloom filter if the effect of false positives can be mitigated." (S. 486)

2. Bloom Filters: Mathematical Preliminaries

2.1 Standard Bloom Filters 

- Zentrale math. Def. Bloom-Filter: "A Bloom filter for representing a set S = {x_1,x_2,...,x_n} of n elements os described by an array of m bits, initially all set to 0. A Bloom filter uses k independent hash functions h_1,...,h_k with range {1,...,m}. For mathematical convenience, we [assume] that these hash functions map each item in the universe to a random number uniform [?] over the range {1,...,m}. For each element x ∈ S, the bits h_i(x) are set to 1 for 1 ≤ i ≤ k. A location can be set to 1 multiple times, but only the first change has an effect. To check if an item y is in S, we check whether all h_i(y) are set to 1. If not, then clearly y is not a member of S If all h_i(y) are set to 1, we assume that y is in S, although we are wrong with some probability. Hence, a Bloom filter may yield a fase positive[. W]e will [...] assume from now on that kn < m." (S. 487)
- Falsch-Positiv-Rate: 
	* Formel vgl. S. 487 bzw. Schönfeld2012, Werner2015
	* Wahrscheinlichkeit, dass ein bestimmtes Bit nach dem Einfügen aller Elemente aus S in den Bloom-Filter ein Nullbit ist: p = e^(-kn/m) (Näherungswert/Approximation)
	* ρ: Verhältnis Nullbits zu allen Bits nach dem Einfügen [?]
	* Wahrscheinlichkeit für falsch Positive in Abh. von ρ: (1 - ρ)^k ≈ (1 - p')^k ≈ (1 - p)^k (Formel vgl. S. 487 bzw. Schönfeld2012, Werner2015) 
- Heutzutage wird hauptsächlich MD5 als Haschfkt. verwendet 

- Optimierung #Hashfkt. (vgl. S. 488f.): 
	* Minimiere f als Fkt. von k durch Ableiten 
	* f = exp(k ln(1 - e^(-kn/m))) -> andere Schreibweise für f; f ist Wahrscheinlichkeitsdichtefkt. für die #Nullbits 
	* p (approximierte W'keit für ein Nullbit) = 1/2, falls f (approximierte Falsch-Positiv-Rate) minimal; nicht abhängig von der Approximation [?] -> damit ist auch p' (tatsächliche W'keit für ein Nullbit) = 1/2, falls f' (tatsächliche Falsch-Positiv-Rate) 
	* Generell: p, f, g sind asymptotische Approximationen für p', f', g'
	* Beachte: Die tatsächliche #Nullbits einer Instanziierung muss nicht gleich p oder p' sein, da Ergebnis des Hashings: "Indeed, p' simply represents the expected fraction of 0 bits in the array. If the number of 0 bits in the array is substiantially less than expected, then the probability of a false positive will be higher thatn the quantity f that we computed", S. 489; Beweis vgl. M. Mitzenmacher. “Compressed Bloom Filters.” IEEE/ACM Transactions on Networking 10:5 (2002), 604—612.) 

- Schranken für #Nullbits: 
	* Anwendung von AZUMA-HOEFFDING-Ungleichung, CHERNOFF-Schranken u. neg. Abhängigkeit ergeben: "while on any specific Bloom filter the fraction of 0 bits may not be exactly p', with high probability it will be very close to p' for large arrays, which justifies the use of p' (and p) in our analyses above" (S. 490; vgl. 489f. f. Quellenangaben d. Beweise)

2.2 A Lower Bound

- Motivation: Wie groß muss m sein, um alle n-elementigen Teilmengen abbilden zu können mit Falsch-Positiv-Anteil von max. ϵ und ohne falsch Negative
- Ableitung einer unteren Schranke für m: "We say that an m-bit string s accepts an element x of the universe if s = F(X) for some X containing x; that is, there is some set in the universe containing x for which s is the representative string. Intuitively, if s accepts x, then given s we should conclude that the set that generated s contains x, and if s rejects x, we can be sure that the set that generated x does not contain s. Consider a specific set X of n elements. Any string s that is used to represent X must accept every element x of X [...], but it may also accept ϵ(u-n) other elements of the universe while maintaining a false positive rate of at most ϵ. Each string s therefore accepts at most n + ϵ(u-n) elements." (S. 490)
- Es ergibt sich m ≥ n log_2(1/ϵ) für ein Repräsentationsschema mit durch ϵ beschränkter Falsch-Positiv-Rate (Herleitung vgl. S. 490)
- In Kombination mit f minimiert (vgl. S. 489) ergibt sich für f ≤ ϵ: m ≥ n log_2 e * log_2(1/e) (vgl. S. 491)
- Man kann also auch sagen: Speicherkomplexität eines Bloom-Filters ist ein Faktor von log_2 e der asymptotischen unteren Schranke ([?], S. 491)
- Für konstanten Speicheraufwand ergibt sich: Bei n*j Bits für das Array liegt die Falsch-Positiv-Rate eines optimalen Bloom-Filters bei ungefähr (0.6185)^j, untere Schranke f. Falsch-Positiv-Rate liegt bei (0.5)^j (vgl. S. 491)
- Optimierungen: "compressed Bloom filters" (S. 491, vgl. Kap. 2.6), perfektes Hashing -> aber höherer Rechenaufwand + weniger flexibel!

2.3 Hashing vs. Bloom Filters 

- Generelle Erklärung von Hashing: Vgl. S. 491
- "Bloom filters can be interpreted as a natural generalization of hashing that allows more interesting tradeoffs between the number of bits used per set element and the probability of false positives" (S. 491; ein Bloom-Filter mit nur einer Hashfunktion ist äquivalent zu normalem Hashing!)
- Bloom-Filter werden aber nur in der Praxis angewandt, weil für eine theoretische Betrachtung i.d.R. die Fehlerrate approximativ "verschwinden" müsste 

2.4 Standard Bloom Filter Tricks

	1. Vereinigung der Bloom-Filter zweier Mengen durch OR
	2. Dynamische Reduktion eines Bloom-Filters: OR auf den beiden Hälften
	* "When hashing to do a lookup, the highest order bit can be masked" ([?], S. 492)
	3. Approximation des Schnitts der Bloom-Filter zweier Mengen (Herleitung vgl. S. 491, [?]) -> gegeben |S_1|, |S_2|, k und m, lässt sich |S_1| ∩ |S_2| abschätzen
	* Ebenso, wenn |S_1|, |S_2| nicht gegeben (da sich #Nullbits um den Erwartungswert m(1 - 1/m)^(k|S|) verdichtet/"strongly concentrated", S. 491)
	* Resultierende Formel vgl. S. 492
	* "inner product": Skalarprodukt/inneres Produkt; für zwei Vektoren a, b: a * b = a_1 * b_1 + ... + a_n * b_n (das Ergebnis ist ein Skalar!)

2.5 Counting Bloom Filters 

- Löschen aus Bloom-Filter ist nicht möglich
- Was machen wir also, wenn sich die Elemente der Mengen ändern? Vgl. L. Fan, P. Cao, J. Almeida, and A. Z. Broder. “Summary Cache: A Scalable Wide-Area Web Cache Sharing Protocol.” IEEE/ACM Transactions on Networking 8:3 (2000), 281—293: Verwende Zähler im Array statt 0/1-Bits
- Vermeide Zähler-Overflow durch entsprechend große Zähler -> i.d.R. sind 4 Bit pro Zähler ausreichend (Herleitung und Schranken vgl. S. 493f.), da gilt: P(max_i c(i) ≥ 16) ≤ 1.37 * 10^(-15) * m
- 2 Interpretationen können daraus abgeleitet werden: 
	1. "a counting Bloom filter that represents t different sets of at most n items during its history overflows with probability at most 1.37 * 10^(-15) * mt" (S. 494)
	2. "when there are m ln 2 total counter increments spread over m counters, then with high probabilty the maximum counter value is O(log m) and hence only O(log log m) bits are necessary for each counter" (S. 494)
- Beachte: Overflows können nat. zu falsch Negativen führen!

2.6 Compressed Bloom Filters

- Auf den ersten Blick ist durch Kompression eines Bloom-Filters (z.B. zum Verbreiten über ein Netzwerk) nichts zu gewinnen, da: Mit optimalem k und Hashfunktionen mit gutem Zufallsverhalten ist die W'keit für ein Bit, 0 oder 1 zu sein, gleich 1/2 -> nicht optimiert darstellbar durch Kompression 
- Man könnte aber den Bloom-Filter auch erst nach der Kompression optimieren bzw. mit einem anderen Constraint: "Suppose instead that we optimize the false positive rate of the Bloom filter under the constraint that the number of bits to be sent after compression is z, but the size m of the array in its uncompressed form can be larger" (S. 494) -> "It turns out that using a larger, but sparser, Bloom filter can yield the same false positive rate with a smaller number of transmitted bits" (S. 494)
- Alternativen: Gleiche #übertragener Bits, aber niedrigere Falsch-Positiv-Rate oder weitere Tradeoffs (dazwischen)
- Bsp. vgl. S. 495: "Using at most sixteen bits per element after copression, a bigger but sparser Bloom filter can reduce the false positive probability" 

3. Historical Applications

3.1 Dictionaries
3.2 Databases

4. A Sample Network Application: Distributed Caching

- Einführung: Bloom-Filter wurden in "Summary Cache" verwendet, eine Anwendung zum "Web cache sharing" (S. 496): "In their setup, web proxies cooperate in the following way: on a cache miss, a proxy attempts to determine if another proxy cache holds the desired WEb page; if so, a request is made to that proxy rather than trying to obtain that page from the Web" (S. 496)
- In diesem Szenario broadcasten die Proxies periodisch nicht die Inhalte ihrer Caches, sondern eine Bloom-Filter-Repräsentation -> führt bei falsch Positiven im schlimmsten Fall zu einem Delay, wenn eine angefragte Seite doch nicht im Cache eines bestimmten Proxys vorhanden ist
- "succinct": "prägnant, knapp, bündig"
- Diese Technik wird auch im Open Source-Webproxy Squid verwendet 
- Die Technik kann optimiert werden durch Verwendung von Counting Bloom Filters, "delta compression" (S. 497) und Compressed Bloom Filters
- "delta compression": "Delta-Kodierung oder auch Differenzspeicherung ist eine Möglichkeit der Datenkompression. Sie dient der platzsparenden Speicherung korrelierter Daten wie zum Beispiel sequenzieller Daten (= Daten die in mehreren Versionen vorliegen), also der sogenannten Dekorrelation." (vgl. https://de.wikipedia.org/wiki/Delta-Kodierung)

5. Applications: P2P/Overlay Networks

- Frühe P2P-Anwendung mit Bloom-Filtern: "in the context of a desktop web browsing assistant called Vistabar" (S. 497)

5.1 Moderate-Sized P2P Networks

- Viele P2P-Netzwerke verwenden DHT, um Objekte zu lokalisieren (Vorteile: Skalierbarkeit in großen Netzwerken; P2P-Netzwerke, in denen Knoten häufig das Netzwerk verlassen oder dazukommen)
- Daher: Bloom-Filter eher für kleinere und robustere Netzwerke geeignet: "While keeping a list of objects stored at every other node in a peer-to-peer system may be prohibitive, keeping a Bloom filter for every other node may be tractable" (S. 497); "[i]mplementation challenges include how frequently filters need to be updated" (S. 498)
- 2 Beispielimplementierungen werden kurz vorgestellt und Quellen genannt

5.2 Approximate Set Reconciliation for Content Delivery

- Weiteres P2P-Anwendungsszenario: Verwende Bloom-Filter für "approximate set reconciliation problems" zw. einzelnen Peers -> könnte evtl. wichtig sein: "The authors also consider an alternative data structure that uses Bloom filters, but allows for faster determination of elements in S_A - S_B when the difference is small" (S. 498 bzw. Byers2002)

5.3 Set Intersection for Keyword Searches

- Ähnliche Anwendung wie in 5.2, doch soll nicht die Differenz, sondern die Schnittmenge zweier Mengen mittels Bloom-Filter bestimmt werden -> evtl. noch interessanter: "The approach is essentially the same as for database joins. [...] The Bloom filter approach allows S_A ∩ S_B to be determined with fewer bits transmitted than A sending the entire set S_A. Reynolds and Vahdat describe how using this approach for set intersection allows for efficient distributed inverted kyword indices for keyowrd search in an overlay network over a peer-to-peer architecture. [...] To handle conjunctive queries involving multiple nodes, the set intersection methods above are used to reduce the amount of information that needs to be sent to determine the appropriate documents" (S. 499 bzw. P. Reynolds and A. Vahdat. “Efficient Peer-to-Peer Key- word Searching.” In Middleware 2003: ACM/IFIP/USENIX International Mid- dleware Conference, Rio de Janeiro, Brazil, June 16—20, 2003, Proceedings, Lec- ture Notes in Computer Science 2672, pp. 21—40. New York: Springer, 2003.)

6. Applications: Resource Routing

6.1 A Basic Routing Protocol

- Zunächst generelle Vorstellung eines "resource discovery service", der von Czerwinski et al. 1999 vorgestellt wurde (S. 499)
- "[The] rather straighforward routing protocol becomes more interesting if the resource lists are represented by Bloom filters. The property that a union of Bloom filters can be obtained by ORing the corresponding individual Bloom filters allows easy creation of unified resource lists" (S. 599)
- Im Folgenden werden weitere Routing-Ansätze vorgestellt, die diesem Ansatz folgen: 

6.2 Resource Routing on P2P Networks

- "attenuated Bloom filter": "In the array for each edge, there is a Bloom filter for each distance d, up to some maximum value, so that the dth Bloom filter in the array keeps track of files reachable via d hops through the overlay network along that edge" (S. 500; diese spezielle Implementierung ist sicher nicht wichtig, aber vllt. die Idee/das Bloom-Filter-Array? Referenz: )

6.3 Geographic Routing 

7. Applications: Packet Routing

- "We examine how Bloom filters can be used to aid early detection of forwarding loops, to find heavy flows for the Stochastic Fair Blue queue management scheme, and to potentially speed up the forwarding of multicast packets" (S. 501) -> hier wahrsch. alles nicht so wichtig!

7.1 Detecting Loops in Icarus

7.2 Queue Management: Stochastic Fair Blue

7.3 Multicast

- Hier Idee: Parallelisierung d. Vergleiche (S. 502; vgl. B. Grönvall. “Scalable Multicast Forwarding.” Available from World Wide Web (www.acm.org/sigcomm/ccr/archive/2002/jan02/CCR-SC01-Posters/BjornGronvall.ps), 2002.)

8. Applications: Measurement Infrastructure

- Wahrscheinlich hier auch nicht wichtig: "how to provide a reasonable measurement infrastructure" (S. 503)

8.1 Recording Heavy Flows

8.2 IP Traceback

9. Recent Work

- Neue Ansätze: 
	1. "[S]pectral Bloom filters" (S. 504, vgl. S. Cohen and Y. Matias. “Spectral Bloom Filters.” In Proceedings of the 2003 ACM SIGMOD International Conference on the Management of Data, pp. 241—252. New York: ACM Press, 2003)
	2. Behandlung von Multimengen (vgl. ebd. sowie C. Estan and G. Varghese. “New Directions in Traffic Measurement and Accounting.” ACM SIGCOMM Computer Communication Review (Proceedings of the 2002 SIGCOMM Conference) 32:4 (2002), 323—336) 
	3. Verwendung von nur paarweise unabhängige Hashfunktionen -> leicht zu implementieren u. effizient, vgl. G. Cormode and S. Muthukrishnan. “An Improved Data Stream Summary: The Count-Min Sketch and its Applications.” In LATIN 2004: Theoretical Informatics, edited by M. Farach-Colton, pp. 29—38. New York: ACM Press, 2004
	4. "[S]pace-code Bloom filter" (S. 505, vgl. A. Kumar, J. Xu, L. Li, and J. Wang. “Space-Code Bloom Filter for Efficient Traffic Flow Measurement.” In Proceedings of the 2003 ACM SIGCOMM Conference on Internet Measurement, pp. 167—172. New York: ACM Press, 2003)
	5. "Bloomier filter" (S. 505, vgl. B. Chazelle, J. Kilian, R. Rubinfeld, and A. Tal. “The Bloomier Filter: An Efficient Data Structure for Static Support Lookup Tables.” In Proceedings of the Fifteenth Annual ACM-SIAM Symposium on Discrete Algorithms, pp. 30—39. Philadelphia: SIAM, 2004) -> vermutlich nicht wichtig


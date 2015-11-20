Zusammenfassung Agarwal2006
---------------------------

0. Abstract

- Inhalt: Approximation #Mengendifferenzen auf verschiedenen Hosts, minimale Kommunikation ("approximating the number of differences between sets held on remote hosts using minimum communication", S. 1)
- Anwendung u.a.: "content delivery networks" (S. 1)
- Es wird gezeigt, dass z. Lösung dieses Problems nur in etwa so viel Kommunikation notwendig ist wie zur Bestimmung der Differenzen selbst -> hier aber nicht wichtig
- Ergebnis: Heuristische Lösung mit "counting Bloom filter" (S. 1) 
- "Heuristik": "Lehre, Wissenschaft von den Verfahren, Probleme zu lösen; methodische Anleitung, Anweisung zur Gewinnung neuer Erkenntnisse" (duden.de)
- Außerdem: Analytische Schranken f. die Protokollperformance, experimentelle Untermauerung der Überlegenheit ggü. bisherigen Approximationen 

I. Introduction 

- Prinzipiell andere Motivation: Datenkonsistenz zw. Remote-Hosts
- Formale Problembeschreibung: "given two hosts A and B with data sets S_A and S_B repectively, we wish to approximate the size of mutual difference S_A ⨁ S_B ≙ (S_A - S_B) ∪ (S_B - S_A)" (S. 2)
- Ziele: 
	1. Minimierung Kommunikation zw. Hosts
	2. Minimierung Rechenaufwand z. Bestimmung d. Differenzen 

A. Organization 

II. Preliminaries 

- Kapitelinhalt: "baseline information-theoretic analysis of the difference approximation problem", "existing protocols for difference approximation", "review traditional Bloom filters" (S. 2)

A. Information-theoretic bounds

1) Tools	
	1. Ergebnis von Yao (vgl. A. C. Yao, “Some complexity questions related to distributive computing,” in Proceedings of the 11th Annual ACM Symposium on Theory of Computing, 1979, pp. 209–213): "based on a two-way communication model[,] two remote users with data X ∈ M and Y ∈ N respectively alternate, sending each other one bit at a time, with the goal of computing a given deterministic function f(X,Y). [...] at least log_2(d(f)) - 2 bits of communication are needed to correctly communicate f, with d(f) being the minimum number of monochromatic rectangles needed to partition f on M x N [?]" (S. 2)
	
	2. Ergebnis von Orlitsky und Roche (vgl. A. Orlitsky and J. R. Roche, “Coding for computing,” IEEE Transactions on Information Theory, vol. 47, pp. 903–917, March 2001): "remote users have random variables X and Y. In this one-way communication model, X repeatedly sends (as one block) an instance of his variable to the second user, who then attempts to compute f(X,Y) with respect to instances of its own random variable, with vanishing block error probability. [...] the number of bits that must be transmitted per block for this model is given by the graph entropy [...] of the characteristic graph [...] of function f, namely H_G(X|Y) ≙ min I(W;X|Y)" (S. 3, auch Erklärungen d. Variablen u. Verweise)

	* Def. charakteristischer Graph einer Funktion f: "a graph whose vertices are the support set of X and edges (x,x') are such that ∃y with p(x,y),p(x',y) > 0 and f(x,y) ≠ f(x',y)" (S. 3, Bed. [?]) 

2) Results
	* "All the algorithms discussed in this paper compute the approximate number of differences between sets on remote hosts" (S. 3)
	* Exakte Berechnung von Mengenunterschieden erfordert mind. so viel Kommunikation wie enthaltene Information (da Mengendifferenz Spezialfall von Mengengleichheit) 
	
Lemma II.1: "approximating differences within an additive constant also requires much communication" (S. 3, vgl. S. 3f. f. exakte Formulierung u. Bew.); "We can deduce a stronger result under the model of Orlitzky and Roche, essentially showing that one cannot efficiently approximate set difference in many cases. This result is based on the following lemma generalizing a similar result" (S. 4, vgl. J. Körner and K. Marton, “Random access communication and graph entropy,” in IEEE Transactions on Information Theory, vol. 34, pp. 312–314.)
	
Lemma II.2: "Let q_G(P) denote the probability that two vertices, chosen independently with distribution P, do not form an edge in G. Then H_G(X|Y) ≥ log(1/q_G(P))" (vgl. S. 4, Bew. vgl. S. 4f.) -> "Lemma II.2 is tight enough to show that difference approximation typically requires communication of the same size as the sets being compared" (S. 4)

- Hier anscheinend: 
	"Ω": "asymptotische obere Schranke" (LANDAU-Notation) 
	"o": "asymptotisch gegenüber g vernachlässigbar" (LANDAU-Notation)
	"U": "Vereinigungsmenge"

Theorem II.3: "Consider two sets X,Y ⊆ U generated independently, with elements chosen with probability p. Then a one-way communication algorithm approximating differences within an additive error o(|U|) requires at least Ω(|U|) bits of communication" (S. 5, Bew. vgl. S. 5) -> kann trivialerweise generalisiert werden: 

Corollary II.4: "Any algorithm on remote sets X,Y ⊆ U" returning an approximation f(X,Y) with f_1(X ⨁ Y) ≤ f(X,Y) ≤ f_2(X ⨁ Y) for some functions F_1, f_2 such that 
	∃c > 0 
	f_1(x) > f_2(x)
	∀ x > c|U|
	requires at least Ω(|U|) bits of one-way communication" (S. 6, [?])

B. Existing solutions

- Wir haben gesehen: Approximation oder gar exakte Berechnung der Mengendifferenz erfordert immer viel Kommunikation -> daher jetzt: heuristische Techniken!
- Guter Überblick über bestehende Approximationstechniken: J. Byers, J. Considine, M. Mitzenmacher, and S. Rost, “Informed content delivery across adaptive overlay networks,” ACM SIGCOMM, August 2002. 
	1. Naiver Ansatz: "random sampling" (S. 6) -> hohe Fehlerrate, niedrige Auflösung ([?], "resolution", S. 6)
	2. "min-wise sketches" (S. 6) -> verwendet für Dokumente!

C. Bloom filter basics

III. Wrapped filter approximation 

- Kapitelinhalt: Lösung der Autoren, nämlich "a wrapped filter approximation based on the counting Bloom filter" (S. 2)
- "wrapped filters hold condensed set membership information with more precision than a Bloom filter" (S. 7) -> höhere Kommunikationskosten, werden aber durch bessere Performance aufgewogen!
- "As we show later, wrapped filters often provide a more accurate approximation of set difference per communicated bit than traditional Bloom filters" (S. 6)

A. Wrapping

- "wrapped filters" werden ähnlich wie Bloom-Filter konstruiert: "A wrapped filter W_S of a set S = {s_1,s_2,s_3,...,s_n} is first initialized with all zeroes, and then set elements are added to the filter by incrementing locations in W(S) corresponding to k independent hashes h_i(·) of these elements. More precisely, we increment W_S[h_j(s_i)] for each set element s_i ∈ S and hash function h_j in order to construct the wrapped filter W_S" (S. 7) -> Generalisierung des Bloom-Filters: man kann wrapped filter in Bloom-Filter umbauen, indem man alle Nicht-Null-Einträge in Einsen umwandelt 
- Das wird hier als Bloom-Filter-Eigenschaft bezeichnet: "Host A can use this Bloom filter property of a wrapped function to determine [S_A - S_B] by inspecting B's wrapped filter W_S_B; [...] all elements of S_A that do not fit the Bloom filter can be considered to be in S_A - S_B" (S. 7)
- "Conversely, the unwrapping algorithm in Section III-B allows us to approximation [S_B - S_A] from the same wrapped filter, giving an overall approximation for the mutual difference [S_A ⨁ S_B]" (S. 7)
- "wrapped filters" haben Löschoperation, aber: "The prize for this feature is that each entry can now take any of kn values [...], requiring a worst-case of m log(kn) bits of storage memory and communication for a filter of size m" (S. 7f., hingegen Bloom-Filter: max. m Bits Kommunikation!)
- Kann jedoch i.d.R. reduziert werden auf log(kn/m) Speicher-Overhead ggü. Bloom-Filter

B. Unwrapping

- Host A kann einen wrapped filter unwrappen, um [S_B - S_A] zu approximieren -> wird hier beschr. in Protokoll 1 (vgl. S. 8)
- 2 Vorteile eines wrapped filter liegen im Unwrapping-Algo.: 
	1. "the total weight of the wrapped filter (i.e., Σ_{s_i ∈ S} W_S_B(s_i)) decreases as each set element is unwrapped" -> damit sinkt auch die W'keit f. falsch Positive insgesamt -> "better overall approximate", vgl. Abschnitt IV (S. 8)
	2. Kompensation von falsch Positiven: "when a false positive is unwrapped, it prevents (at least) one other non false positive element from being unwrapped" (S. 8, warum[?])

IV. Analysis and Performance

- Kapitelinhalt: Analyse der Korrektheit d. Lösung, namentlich der W'keit f. falsch Positive

A. False Positive Statistics

- Auch bei wrapped filters besteht W'keit f. falsch Positive im Unwrapping-Prozess: "A false positive occurs when the hash values h_i(s) of an element s fit into the W_S_B despite the fact that s ∉ S_B" (S. 9, analog z. Def. f. Bloom-Filter)
- 2 negative Effekte von falsch Positiven: 
	1. "they can reduce the overall set differnece approximation by inappropriately reducing the weight of the wrwpped filter" (S. 9, wie/warum[?])
	2. "a false positive can prevent a valid set element [...] from fitting in the resulting filter by reducing to zero [...] one of the hash locations of the valid element" (S. 9, wie/warum[?])
- "residue": Nachlass, Abfall, Rest
- 3 Möglichkeiten für Unwrapping, mit versch. Auswirkungen auf die Approximation: 
	1. Zuerst Elemente aus S_A ∩ S_B
	2. Andere Fälle können durch eine binomiale obere Schranke abgeschätzt werden
	3. Schranke für "φ false positives occurring during a random unwrapping": vgl. S. 9

B. Effect of false positives

- "the decrease in weight of the wrapped filter will be linear in the number of unwrapping iterations", an Hand folgender Theoreme:

Theorem IV.1: "Consider a k-hash wrapped filter W with initial false positve probability p_f being (uniformely) randomly unwrapped. Then each unwrappingiteration decreases the expected weight of W by (k(|S_A|-d)/|S_A|), assuming that p_f << 1 and given d = |S_A - S_B|" (S. 10, Bew. vgl. S. 10) -> "determines (in expectation) the probability of error at any iteration of the decoding algorithm, and it is left as an open problem how to compute and correct for this bias" (S. 11)

Lemma IV.2: "deterministic bounds on the effects of a false positive" (S. 11), genauer: "Each false positive will contribute an error of ε to our approximation, with -1 ≦ ε ≦ k-1" (S. 11)

- führt zu verbesserter Performance ggü. Bloom-Filter, aber nur in manchen Fällen und wird nur experimentell gezeigt!

C. Wrapped filter size and compression 

- Tradeoff: Ausgleich zw. Korrektheit der wrapped filter-Approximation (m möglichst groß) und Kommunikationsoverhead (m möglichst klein) -> "It is possible to generalize the tradeoff analysis [...] to lower bound the size of a compressed wrapped filter" (S. 11):

Theorem IV.3: "The compressed size of a length m wrapped filter with k hash functions encoding n elements is (asymptotically) at most 1.42(1 - 1/m) kn + 0.12m bits" (S. 11, Bew. S. 11f.)

V. Experimental comparisons

- Kapitelinhalt: Experimenteller Vergleich der entwickelten Lösung m. bestehenden Verfahren 
- Grafische Darstellung: Vergleich von random sampling, min-wise sketches, Standard-Bloom-Filter, wrapped filter bzgl. der Approximation der Mengenunterschiede (vgl. Argawal2006b: 8)
- Ergebnisse: "the standard Bloom filter and wrapped filter approaches are very similar for filter sizes that are large relative to hosts sets. For smaller filters, Bloom filters generally provide a lower (and less accurate) approximation than wrapped filters [...]. Random sampling [...] is quite inaccurate unless almost all the samples are transmitted; both minwise sketches and random sampling have a high standard deviation compared to Bloom and wrapped filters" (S. 13)

VI. Conclusions

- Kapitelinhalt: "Conclusions and directions for future work" (S. 2)
- Ergebnisse: Kommunikationsaufwand zur Approximation von Mengendifferenzen generell proportional z. #Elemente ("amount of information between the sets", S. 13)
- Daher heuristische Methoden notwendig/angemessen; neuartiger Ansatz: "a Bloom filter known as a wrapped filter, whose data structure is also known as a counting Bloom filter" (S. 13)
- Neuerung: "our novel decoding algorithm for the wrapped filter allows it to be generally more accurate than the standard Bloom filter for the same communication complexity" (S. 13); außerdem ist das Verfahren nicht interaktiv und leicht wartbar (Einfügen/Löschen von Elementen); Encoding-/Decoding-Verfahren können ebenfalls effizient berechnet werden (wo[?])
- "All these qualities make wrapped filters particularly suitable for the many network applications where there is a need to quickly and efficiently measure the consistency of distributed information" (S. 13)

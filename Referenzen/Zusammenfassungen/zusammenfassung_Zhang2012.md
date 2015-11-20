Zusammenfassung Zhang2012
-------------------------

0. Abstract

- Problemstellung: "Simultaneous query in wireless networks, where multiple nodes activate Orthogonal Frequency-Division Multiplexing (OFDM) subcarriers to announce control information" (S. 3340)
- Hier v.a. interessant: "Analog Bloom Filter (ABF)" (S. 3340)  

1. Introduction 

- Am wichtigsten ist die simultane Query; typischerweise antworten viel weniger Knoten, als im Netzwerk enthalten sind: "The simultaneous query mechanism amortizes the overhead over all nodes and achieves better efficiency" (S. 3340)
- Existierende Mechanismen für simultane Queries basieren alle auf OFDM: "existing query schemes assign dedicated subcarriers to the nodes" (S. 3440)
- Das wird auch hier verwendet, jedoch: "novel query method inspired by the Bloom filter (ABF)" (S. 3440)
- "The existing method is basically a linear scan and is very conservative because every node is allocated with dedicated resources including time and the usage of subcarriers although many nodes are idle" (S. 3340)
- Es ist auch die Rede von "Digital Bloom Filter (DBF)" [sind das die klassischen?] (S. 3340)
- Ergebnis: ABF kann die Queryzeit signifikant verkürzen 

2. Related Work

- Hier lediglich behandelt: "the unique problems when the inputs are real values with possible errors, which are very different from the inputs to the typical Bloom filter" (S. 3441)

3. Analog Bloom Filter for Binary Detection 

- Kapitelinhalt: "binary node state detection with ABF" (S. 3340)
- Unterschiede DBF/ABF: 
	1. Digitalisiertes/analoges Inputsignal 
	2. Keine Fehlerbehandlung für Inputwerte/Es gibt Fehlerbehandlung

A. Complexity Analysis

B. The ABF Binary Detection Algorithm

- Wichtigste Aspekte: 
	1. 2 Präprocessing-Schritte: 
		a. "marks a node v_i as idle if none of the subcarriers in Ω_i has power level greater than μ + 4σ" (S. 3342)
		b. 
	2. "basically a belief propagation algorithm" (S. 3342)

C. Parameter Selection and Subcarrier Assignments

D. Multiple Antennas

4. Multi-bit queries

- Kapitelinhalt: "multi-bit detection with ABF" (S. 3341)

A. A Simple Query Scheme with ECC

B. Combining ECC with a Novel Signaling Scheme

C. An Example Code 

5. Evaluations 

- Kapitelinhalt: "ABF with simulations" (S. 3341)

A. Binary Detection 

B. Multi-bit Detection 

6. Reducing the Number of Responders 

- Kapitelinhalt: "techniques to reduce the number of responders" (S. 3341)

A. Silencing the Known Active Nodes

B. Dividing the Subcarrier into Multiple Frequency Slots

7. Conclusion

- Weniger relevantes Paper!
- Ergebnisse:
	* Problemstellung: "supporting simultaneous query where nodes activate random OFDM subcarriers as the responses to the query" (S. 3446)
	* Lösungen: 
		1. "Analog Bloom Filter (ABF) which exploits the fact that the number of nodes that should respond to the query is usually much smaller than the number of associated nodes" -> "nodes [...] share subcarriers to reduce [...] query response time" (S. 3446)
		2. "algorithm to detect the binary states of the nodes based on belief propagation" (S. 3446)
		3. "error correction codes", "novel signaling scheme [for] multi-bit queries" (S. 3446)
		4. Simulation 
		5. ABF hat ähnliche oder bessere Performance als "existing collision-free query schemes with much less query time" (S. 3446)
Zusammenfassung Qiao2014
------------------------

0. Abstract 

- Bewertung v. Bloom-Filter-Performance an Hand v. 3 Kriterien: 
	1. Query-Overhead
	2. Speicherkomplexität
	3. Falsch-Positiv-Rate
- "In this paper, we study Bloom-1, a data structure that performs membership check in one memory access, which compares favorably with the k memory accesses of a standard Bloom filter" (S. 93)
- Außerdem: Vgl. v. Bloom-1, Bloom-g u. Bloom-α -> "allowing performance tradeoff between membership query overhead and false positive ratio" (S. 93)
- Ergebnisse: Weniger Speicherzugriffe, kleinere o. gleiche #Hashbits, kleinere o. vergleichbare Falsch-Positiv-Rate mit den neuen Datenstrukturen (u. in praktischen Szenarien); Durchführung praktischer Experimente

1. Introduction 

- Anwendungsfälle v. Bloom-Filtern: 
	1. Lookup in Routingtabellen
	2. "online traffic measurement" (S. 93)
	3. P2P-Systeme: Vgl. Reynolds2003
	4. "cooperative caching": Vgl. Fan2000
	5. Firewall-Design 
	6. "intrusion detection"
	7. Bioinformatik
	8. Query-Processing in Datenbanken 
	9. Stream-Computing
	10. Verteilte Speichersysteme: Vgl. Hao2007
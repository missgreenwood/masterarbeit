I. Indexstrukturen

	1. Baumstruktur für Bloom-Filter (Grundlage: Sakuma2011)

	a. Implementieren: 
		i. Baumstruktur auf EINEM Host

			* Bloomfilter zufällig erzeugen 
			* Baumstruktur aufbauen
			* Ausgeben 

			
			// Generate 100 unique instances of Bloom filter
			// The address of a message is defined to be a small set of strings represented as a Bloom filter of previuosly known configuration
			// Use subset and similarity queries to select messages

		ii. Verwaltung d. Bloom-Filter im Baum (Einfügen, Löschen, Nachbarinformationen, Lookup von Informationen, Update-Propagierung)

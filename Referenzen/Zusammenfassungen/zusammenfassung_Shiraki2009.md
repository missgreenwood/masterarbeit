Zusammenfassung: Shiraki2009
----------------------------

0. Abstract

- Inhalt: P2P-Methode zur Suche von Nutzern basierend auf Bewegungsmeldungen ("P2P user search method based on movement records that can be automatically obtained by location detection services", S. 177)
- Bewegungsmeldungen ("movement records") werden dabei als Sequenz aus Paaren von "spot-ID" (SA. 177) und Zeit gespeichert (für jeden Nutzer in einem Peer)
- Anwendung v. Bloom-Filtern: Bloom-Filter wird auf alle Paare eines Nutzers angewendet -> ein Bloom-Filter bildet das Bewegungsverhalten jedes Nutzers ab
- Suche von Nutzern: AND/OR-Suchmethode basierend auf "Bloom Finger Table (BFT)" (S. 177) -> Erweiterung einer Routingtabelle eines "Chord DHT"-Systems ([?], S. 177), bietet effiziente Suche nach Nutzern basierend auf Ortssequenz (mit oder ohne Angabe von Zeitstempeln)
- Außerdem Ziel: #Nachrichten für die Nutzersuche reduzieren -> Zuweisung von peer-ID für BFT an Hand einer geografischen Stütze ("foothold", S. 177) 
- Nutzer, die denselben Ort besuchen, werden dadurch auf der Routingtabelle näher beeinander platziert -> reduziert nachgewiesenerweise #Nachrichten gegenüber naivem Ansatz ("existing P2P retrieval method", S. 178)

1. Introduction 

- Verwendung der aktuellen Position der Nutzer an Hand GPS, "ubiquitous networks" ([?], S. 177) -> Fokus auf Bewegungssequenz! ("location-based information services that utilize movement records", S. 177)
- Bsp.: "a messaging service for people that attended to the same conference" (S. 177) -> erfordert 
- Def. Bloom-Filter: "a simple space-efficient randomized data structure for representing a set in order to support membership queries" (S. 177)/"probabilistische Datenstruktur, mit deren Hilfe sehr schnell festgestellt werden kann, welche Daten in einem Datenstrom schon einmal vorgekommen sind und welche erstmals auftreten. Hierzu wird mit einer geeigneten Zahl von Hash-Funktionen ein 'Fingerabdruck' des gelesenen Datensatzes in einer einzeiligen Hashtabelle hinterlassen." (https://de.wikipedia.org/wiki/Bloomfilter)
- Suchmethoden mit Bloom-Filtern für P2P-Netzwerke: "Bloom Finger Table", "Chord" (S. 177)
- Hier vorgestellt: Suchverfahren basierend auf Bewegungsmeldungen ("movement records", S. 177), erweitert BFT
- 2 Bloom-Filtern werde verwendet: besuchte Spot-IDs + korrespondierende Zeitstempel -> werden konkateniert, Suche von Nutzern kann dadurch inkl. o. exkl. Zeitstempel erfolgen 
- Reduzierung der #Nachrichten durch Assoziation von Nutzern mit Peer-IDs -> dadurch werden Nutzer, die sich am selben Ort befinden, im Chord-Netzwerk näher beeinander platziert 

2. Bloom Finger Table (BFT)

- Zur Realisierung der Nutzersuche wird hier Erweiterung von BFT erweitert, was wiederum Chord erweitert
- Prinzip von BFT: Anwendung von Bloom-Filter auf Finger Table von Chord; "To search multiple elements, a combined Bloom Filter of the elements is generated. Then the query is forwarded to the peer in the Finger Table when the Bloom Filter of the query is included in the corresponding Bloom Filter. [...] If the Bloom Filter of the peer is included by the Bloom Filter of the query, the peer is matched to the query However, all elements have to be tested again on the peer since the testing by Bloom Filter has false positive." (S. 178)
- Genaues Verfahren [?]

3. User Search Method Based on Movement Records 

3.1 Movement Record Management on BFT
- Prinzip: Auf jede Spot-ID und den korrespondierenden Zeitstempel werden voneinander unabhängige Bloom-Filter angewendet, diese werden dann zu einem Bloom-Filter konkateniert -> das Ergebnis bezeichnet einen "movement record" (S. 178)
- Diese Bloom Filter-Struktur wird auf BFT angewendet wie in 2. beschrieben -> realisiert die Nutzer-Suche basierend auf diesen records
- Wenn Zeitstempel bei der Suche vernachlässigt werden können/sollen, wird der untere Teil des Bloom-Filters bei der Suche einfach ignoriert 

3.2 AND Search 
- Prinzip: Anfrage nach allen Peer-IDs der Peers, die ALLE spezifizierten Ort/Zeitstempel-Paare (movement records) enthalten 
- Bsp.: Suche nach Nutzer, die einem bestimmten Pfad (zu einem bestimmten Zeitpunkt) gefolgt sind 
- Realisierung: Auf die ursprüngliche BFT wird nach mehreren movement records gesucht -> diese werden dazu mit OR verknüpft (falls nur nach Orten, nicht aber nach Zeitstempeln gesucht werden soll, wird der untere Teil des Filters wie in 3.1 ignoriert) 

3.3 OR Search 
- Prinzip: Anfrage nach allen Peer-IDs der Peers, die EINES der spezifizierten Ort/Zeitstempel-Paare (movement records) enthalten 
- Bsp.: Suche nach Nutzern, die irgendeinen der bestimmten Pfade (zu einem bestimmten Zeitpunkt) zurückgelegt haben 
- Realisierung: Bloom-Filter werden für jedes gesuchte Element generiert und zu einer Query konkateniert -> der Bloom-Filter jedes Peers wird nach jedem Element durchsucht

3.4 Geographical Assignment of Peer-IDs
- In Chord werden Peer-IDs zufällig vergeben -> würde dieses Verfahren hier angewendet, würde die oben beschriebene Suche an unnötig viele Nutzer weitergeleitet ([?])
- Jetzt jedoch: Vergabe von Peer-IDs basierend auf einer geografischen Stütze/Ankerpunkt ("foothold", S. 179) -> näher beeinander liegende Peer-IDs haben nun tendenziell mehr besuchte Orte gemeinsam -> Bloom-Filter der BFTs sind gleich -> ODER-Verknüpfung der Bloom-Filter ist gleich -> Anfragen werden an weniger Peers weiter geleitet, reduziert # weitergeleiteter Nachrichten im Netzwerk! 

4. Evaluation

4.1 Setup 
- Ergebnisse wurden verglichen mit Multikey Skip Graph Methode (MKSG, existierendes P2P-Anfrageverfahren)  
- Setup (ausgewählte Details): Zeitstempel werden als Unixtime vergeben; "The query includes 5 movement records and 5 % of the peers have the movement records in the AND search and 10 % of the peers have the movement records in the OR search." (S. 181)

4.2 Simulation Result
- Für AND Search: Ohne geographische Stütze sind die Ergebnisse fast identisch mit MKSG (# weitergeleiteter Nachrichten im Netzwerk), mit geografischer Stütze Reduzierung um 56% reduziert
- Für OR Search: Mit oder ohne geografische Stütze Reduzierung um 64% gegenüber MKSG, weitere leichte Reduzierung mit geografischer Stütze

5. Conclusion

- Zusammenfassung: "Bloom Filter-based user search method based on movement records in the P2P architecture. By applying Bloom Finger Table and geographical peer-ID assignment, the number of messages is vastly reduced compared to the naive implementation" (S. 181)


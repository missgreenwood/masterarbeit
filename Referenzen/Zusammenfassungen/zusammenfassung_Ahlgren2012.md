Zusammenfassung Ahlgren2012 _(referenziert in AMBIENCE)_
--------------------------------------------------------

0. Abstract 

- Ansatz des informationszentrischen Netzwerkens ("information-centric networking (ICN)", S. 26)
- Beinhaltet: "in-network caching, multi-party communication through replication, [...] interaction models decoupling senders and receivers" (S. 26)
- Ziel: Bessere Netzwerkstruktur als Adressbasierung, Fokus auf "content distribution and mobility" (S. 26)
- Inhalt des Papers: Survey d. existierenden ICN-Architekturen m. den Komponenten "named data objects, naming and security, API, routing and transport, [...] caching" (S. 26), Vorteile von ICN i. A.

1. Introduction

- Entwicklung von Internetarchitekturen basierend auf benannten Datenobjekten ("named data objects (NDOs)", S. 26) wg. Skalierbarkeit u. Effizienz = ICN
- Bsp. f. NDOs: Webseiten, Videos, Dokumente
- Hingegen heutige Netzwerke: "host-centric" (S. 26) -> "communication is based on named hosts, for example, web servers, PCs, [...]" (S. 26)
- "leverage": "Einfluss, Hebel"
- Ziel aller ICN-Varianten: Effiziente u. zuverlässige Verteilung von Informationen durch Bereitstellen einer allgemeinen Kommunikationsplattform -> war bisher nur in P2P-Netzwerken u. proprietären Netzwerken möglich

- ICN-Varianten: 
	1. Data-Oriented Network Architecture (DONA)
	2. Content-Centric Networking (CCN)/Named Data Networking (NDN, vgl. www.named-data.org)
	3. Publish-Subscribe Internet Routing Paradgim (PSIRP)/Publish-Subscribe Internet Technology (PURSUIT, vgl. www.fp7-pursuit.eu)
	4. Network of Information (NetInf)/Scalable and Adaptive Internet Solutions (SAIL, vgl. www.sail-project.eu)

- Ziele/Gemeinsamkeiten: Effizienterer Zugriff auf und Verteilung von Inhalten; Management von Unterbrechungen u. "flash crowd effects" (S. 26)
- "Communication is driven by receivers requesting NDOs. Senders make NDOs available to receivers by publising the objects" (S. 26)
- Caching wird zentral; Integrität von Datenobjekten hängt am Objekt, nicht am veröffentlichenden Host 
- Hier: "information", "data" u. "content" synonym (S. 26) 

2. The Information-Centric Networking Approach 

- Kapitelinhalt: ICN-Hauptkomponenten, Vorteile von ICN

- ICN-Hauptkomponenten: 
	1. "Named Data Objects" (NDOs, S. 27)
	* Hauptabstraktion von ICN, Def.: "all types of objects that we store in and access via computers[;] independent of location, storage method, application program, and transportation method" (S. 27)
	* zwei identische Kopien eines NDO werden als gleichwertig betrachtet
	* Granularität von NDOs: Pakete <-> ganze Objekte 
	* Netzwerkperspektive: benannte Datenblöcke ohne Semantik
	* ICN-Perspektive: "information abstraction model including multiple representations [...] for the same object" (S. 27, Bsp.: unterschiedl. Mediencodierungen o. Aufnahmen eines Musikstücks)
	* NDOs können Metadaten haben

	2. "Naming and Security" (S. 27)
	* "Naming data objects is as important for ICN as naming hosts is for today's internet" (S. 27) -> nur so kann Zuverlässigkeit/Sicherheit in einem informationszentrischen Netzwerk gewährleistet werden 
	* Anforderungen an Namen: unterschiedliche NDOs müssen eindeutige Namen haben ("unique", S. 27); verifizierbare Bindung NDO/Name ("name-data integrity", S. 27) -> sichert Authentizität von NDOs ("object authenticity", S. 27); Herkunft eines Objekts muss deutlich werden ("provenance", d.h. wer hat das Objekt erstellt/veröffentlicht, S. 27)
	* Sicherheitsmechanismen für Namen/Namensräume: durch Kryptographie und entsprechende Namenskonventionen 
	* 2 Namenskonventionen ("naming schemes"): flach vs. hierarchisch 
	* Flacher Namensraum: Nicht-hierarchisch, nicht für Menschen lesbar, selbst-zertifizierend ohne PKI, Publisher-Feld kann z. Aggregation v. Routinginformationen verwendet werden 
	* Hierarchischer Namensraum: Analog z. heutigen URLs, für Menschen lesbar, Hierarchiewurzel ist Publisher-Präfix, benötigt PKI

	3. API
	* Definiert Anfrage und Auslieferung ("request and delivering", S. 28) von NDOs 
	* Funktionsweise: "The source/producer makes an NDO available to others by publishing it to the network" (publish/register; i.d.R. synchrone, einmalige Operation, S. 28); "A client/consumer asks for an NDO by name" (get/interest/request/find/subscribe, S. 28)
	* Beide Operationen verwenden Namen des Objekts als zentralen Parameter 
	* Es kann weitere Parameter geben wie z.B. Ortspräferenz (z.B. im CURLING-Ansatz)

	4. "Routing and Forwarding" (S. 28)
	* 2 Ansätze für aggregierbare und nicht aggregierbare Namensräume: Mit "name resolution service (NRS)" (S. 28) vs. direkt  
	* 2 Phasen: "Routing of NDO requests"/"Routing of NDO back" (S. 28) 
	* Ansatz mit NRS: "stores bindings from object names to topology-based locators pointing to corresponding storage locations" (S. 28); 3 Phasen: 
		a) Route Request zum zuständigen NRS-Knoten, wo Objektname in ein oder mehrere Quelladressen übersetzt wird 
		b) Route Request zu Quelladresse(n)
		c) Route Daten von Quelle(n) zum Requester
	* Direkter Ansatz: 2 Phasen:
		a) Route Request vom Requester direkt zu Quelladresse(n) 
		b) Route Daten von Quelle(n) zum Requester

	5. "Caching" (S. 28) 
	* Alle Knoten können Caches haben 
	* Alle Knoten mit Kopie eines NDO im Cache können Anfrage beantworten 
	* Kombination von "caching at the network edge" (wie z.B. bei P2P-Overlay)/"in-network caching" (wie z.B. bei "transparent web caches", S. 28)
	* Das Caching ist generisch -> anwendungsunabhängig, wird auf alle Content-Provider angewendet 

- Vorteile des ICN-Ansatzes: 
	1. Skalierbare und kosteneffiziente Verteilung
	* Wichtigste Entwicklungen/Ansätze hierbei: P2P, CDN ("content distribution networks", S. 28) 
	* Lösungsansatz ICN: "architecturally sound way of addressing these requirements that does not require individual amendments for specific domains and architectures" (S. 28)

	2. "Persistent and Unique Naming" (S. 29)
	* Heute: URIs werden i.d.R. mittels DNS zu einer IP-Adresse auf einem spezifischen Webserver aufgelöst -> fehleranfällig 
	* Heute: Ein- und dasselbe Objekt kann als verschiedene Objekte erscheinen, falls mehrere URIs darauf verweisen -> uneindeutig
	* Lösungsansatz ICN: Persistente und einzigartige Namenskonvention für NDOs, Dienstmodell entkoppelt consumer/producer 

	3. "Security Model" (S. 29)
	* Heute: Sicherheitsmechanismen schützen den Kanal, auf dem Netzwerkkommunikation stattfindet (Transportschicht) -> Client muss Server vertrauen!
	* Lösungsansatz ICN: Sicherstellung von "name-data integrity" u. Authentizität (Sicherung des Datenursprungs) (u. ermöglicht dadurch "ubiquitous caching", S. 28)

	4. "Mobility and Multihoming" (S. 29)
	* Heute: Host-basierte Netzwerke erschweren Mobilität und "multihoming", da EZE-Verbindungen verwendet werden 
	* Lösungsansatz ICN: Keine EZE-Verbindungen, Management fällt weg 

	5. Unterbrechungstoleranz 
	* Heute: Bei EZE-Verbindungen werden Anwendungs-Protokollsessions an Transportsessions gebunden -> diese sind störanfällig, dann ist auch die Anwendungssitzung futsch 
	* Eigentlich aber: "Many applications do not require seamless communication with end-to-end paths" (S. 29)
	* Lösungsansatz ICN: "better reliability and better performance by leveraging optimized hop-by-hop transport and in-network caching" (S. 29)

3. Overview of Information-Centric Network Architectures 

- Kapitelinhalt: Vorstellung der 4 ICN-Ansätze auf abstrakter Ebene 
	1. Data-Oriented Network Architecture (DONA)
		a) Publish: 
		* NDOs werden von Quellen ins Netzwerk gestellt 
		* Zur Datenverbreitung autorisierte Knoten melden sich bei der "resolution infrastructure" an, die aus "resolution handlers (RHs)" besteht (S. 30) 
		b) Subscribe: 
		* Requests werden an Hand des Namens zur passenden RH geroutet -> hierarchisch, "anycast name resolution" (S. 30), ermöglicht "clean support for network-imposed middleboxes (e.g., firewalls, proxies)" (S. 30)
		* Daten werden entweder auf demselben Pfad oder einen direkte(re)n Pfad an den Requester geschickt 
		* Register-Befehle haben Ablaufzeit
		c) Sonst noch wichtig: 
		* Content provider u. Objekte können sich generell registrieren 
		
	2. Content-Centric Networking (CCN) 
		a) Publish:
		* NDOs werden von Knoten veröffentlicht
		* Zur Information über Datenlokalisierung werden Routingprotokolle verwendet -> Aggregation, hierarchische Namenskonvention 
		* Sicherheit durch Public Key-Verschlüsselung (PKIs, Web of Trust)
		b) Subscribe: 
		* Requests werden zu einer "publisher location" weitergeleitet 
		* Router halten "pending interest table" (PIT, S. 30) -> verhindert mehrfaches Weiterleiten von Anfragen, ermöglicht Request-Aggregation 
		* Unterstützt "on-path caching" (S. 30): "NDOs a CCN router receives [...] can be cached so that subsequent received requests for the same object can be answered from that cache" (S. 30)
		c) Sonst noch wichtig: 
		* Aus Knotensicht: request/response-Balance!
		* Knoten können versch. Strategien z. Schnittstellenauswahl u. "requests (re)transmission pace" (S. 30) einsetzen 
		* Erweiterung von CCN durch NDN (greedy Routing, Topologie-unabhängige Namenskonvention)

	3. Publish-Subscribe Internet Routing Paradigm (PSIRP)
		a) Publish: 
		* NDOs werden von Quellen ins Netzwerk gestellt (wie 1. DONA)
		b) Subscribe:
		* publications/subscriptions werden über Rendezvous-System gematcht: Subscription request spezifiziert "scope identifier" (SI, S. 31) und "rendezvous identifier" (RI, S. 31), beide zusammen benennen gewünschtes NDO; die Identifier werden in ein Matching-Verfahren eingespeist -> liefert "forwarding identifier" (FI, S. 31)
		* FI wird an NDO-Quelle gesendet, diese beginnt mit dem Weiterleiten der Daten 
		* FI ist Bloom-Filter: Router verwenden ihn zur Auswahl der Schnittstellen, an die ein NDO weiter geleitet werden soll (beachte: es gibt nat. falsch Positive -> NDO wird u.U. an Schnittstellen weiter geleitet, die nicht zu Empfängern führen)
		c) Sonst noch wichtig: 
		* "The forwarding ientifiers (Bloom Filters in LIPSIN) are not names for NDOs; they are transient and identify a path from the publisher to the subscriber" (S. 32)

	4. Network of Information (NetInf)
		a) Publish:
		* Entweder: NDOs werden von Quellen ins Netzwerk gestellt durch Anmeldung eines Namens/"locator binding" bei NRS (S. 31)
		* Oder: Zur Information über Datenlokalisierung werden Routingprotokolle verwendet (wie 2. CCN)
		b) Subscribe: 		 
		* 2 Modelle zum Empfang von NDOs: "name resolution" vs. "name-based routing" (S. 31) 
		* Sobald eine Kopie (des angefragten NDOs) gefunden wird, werden die Daten zum Subscriber weiter geleitet 
		c) Sonst noch wichtig:
		* Das bedeutet: "name resolution" und "name-based routing" werden vereint -> "hybrid resolution/routing approach whrer a global resolution system provides mappings in the form of routing hints that enable aggregation of routing information" (S. 31) 

4. Design Choices and Trade-Offs 

- Kapitelinhalt: Detaillierte Diskussion der vorgestellten Ansätze bzgl. "naming and security, API, name resolution and routing, caching, transport, [...] mobility" (S. 31)
- Übersicht (Schaubild): Vgl. S. 34

4.1 Naming and Security for Data Objects
4.2 Application Programming Interface
4.3 Name Resolution and Routing
- "Information abstraction model": Nur im ICN-Designpattern NetInf vorhanden, das bedeutet: NDOs werden nicht nur als Datenblöcke betrachtet, sondern bekommen eine Semantik -> ermöglicht z.B. verschiedene Bitmuster für verschiedene Repräsentationsformen eines Objekts zu vergeben (S. 34)
- "Routing aggregation" (S. 34): Varianten sind "Publisher/explicit" (DONA), "Publisher" (CCN, NetInf) und "Scope/explicit" (PSIRP, S. 34) -> das bedeutet: 
	1. Publisher: Namenskonvention hat Publisher-Präfix als Wurzel -> ermöglicht Aggregation von Routinginformationen 
	2. Explicit: Namensbasiertes Routing
	3. Scope: Veröffentlichung eines NDO gehört zu einem bestimmten Scope -> führt zum Rendezvous-System
- "Routing of NDO" (S. 34): Hier wird nur von TSIRP ein Bloom-Filter verwendet ("Source routing using Bloom filter", S. 34), alle anderen Ansätze verwenden den umgekehrten Anfragepfad oder direkte IP-Verbindung 
- Funktionsweise in TSIRP ("zFilters", S. 33): "[A] Bloom filter describing the rout is built by the rendezvous point and used to forward packets from the selected source to the destination. The Bloom filter is attached to the packet itself, and it contains all names of the links that have to be followed. The Bloom filter approach allows packet length to be traded off against wasting network resources. A large Bloom filter gives fewer false positives, thsu resulting in less packets being forwarded on links without any receiver" (S. 33)

4.4 Caching
- Generell Unterstüzung von "in-network storage", teilweise (CCN, NetInf) auch "request aggregation" (kann als Form des Caching betrachtet werden, S. 34)  

4.5 Transport
- 2 Aspekte: 
	1. Zentraler request/response-Mechanismus
	2. Funktionen des Transportprotokolls (Ressourcenteilung, Flusssteuerung-/kontrolle, "congestion control" (S. 35), Zuverlässigkeit)
- Hier wiederum: Zentrale Funktion in TSIRP wird mit Bloom-Filtern realisiert ("PSIRP's basic forwarding mechanism is based on Bloom filters as described earlier", S. 35)

4.6 Mobility
- 3 Arten von Mobilität im Zusammenhang mit ICNs: 
	1. Client mobility
	2. Content mobility
	3. Network mobility: Ein ganzes Netzwerk bewegt sich, z.B. in einem Zug!

5.  Conclusion 

- "incentive": Anreiz, Ansporn 
- Bisheriger Stand (2012): Zusammengefasst in Tabelle auf S. 34
- Zukünftige Herausforderungen: 
	1. Skalierbarkeit
	2. Schutz der Privatsphäre
	3. Rechtliche Aspekte
	* U. a. "ubiquituous caching" -> mich interessieren zwar nicht die rechtlichen Aspekte, aber könnte trotzdem wichtig sein 
	4. (Weiter-)Entwicklung ("deployment", S. 36)
	* Quellen für Standards: S. References (S. 36)
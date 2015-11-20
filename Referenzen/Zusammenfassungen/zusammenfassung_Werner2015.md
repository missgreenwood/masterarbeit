Zusammenfassung: Werner2015
---------------------------

0. Abstract 

* Thema: Context-awareness in mobilen Anwendungen, kombiniert mit persönlichen Daten aus sozialen Netzwerken
* Schlüsselwort Context-awareness! -> treibt Personalisierung voran 
* Jetzt: Verwenden von persönlichen Informationen zur Modifizierung/Modellierung des Graphs (des sozialen Netzwerks)
* Neues Paradigma: "context-centric online social networking in which the social graph structure is derived from context-information alone" (S. 1) 
* Anwendung: Context-zentriertes Netzwerk, basiert auf WiFi-Ortsinformationen und geohash-basierten GPS-Informationen, verwendet spezielle Metadaten-Konstruktion 
* Außerdem: Location-based service, beruht auf Metadaten-Modell, zeigt Nutzung von räumlicher und zeitlicher Awareness ("spatial and temporal awareness", S. 1) 

I. Introduction

- Context-awareness: Nutzung von Kontextinformationen als Informationsquelle für Anwendungen und Netzwerke -> Anpassung von Anwendungen an die aktuellen Nutzerbedürfnisse, bessere Dienstqualität 
- Prinzip: Anwendung ist auf den Nutzer abgestimmt und passt sich dessen aktuellen Bedürfnissen an; ermöglicht komplexe Interaktionen zwischen Nutzern und Anwendungen
- Context-awareness bezogen auf Nutzer = "personalization" (S. 1) -> kann auch verwendet werden z. Verbesserung der Dienstqualität des Netzwerks (z.B. in Sensornetzen: Batteriestand, Energieverbrauch; in sozialen Netzwerken: Ort ("location", S. 1), soziale Umgebung ("social ambience", S. 1))  
- Neue Kommunikationsmuster im Internet in den letzten Jahrzehnten v.a. wegen sozialer Online-Netzwerke -> werden von klass. adressbasiertem Routing nicht gut unterstützt
- Führt zum Paradigma des "information-centric networking" (S. 1): Netzwerk organisiert sich an Hand von Informationsverbreitung, nicht an Hand von Zielen/Quellen 
- Ziel des vorliegenden Papers: "adaption from user context information for context-aware online social networks" -> führt zum Paradigma "context-centric online social networks" (S. 1): Kommunikation beruht nicht mehr auf Online-Freundschaft, sondern allein auf Kontext-Ähnlichkeit!
- Ziele/Features dieser Netzwerke: 
	* improve privacy (S. 1)
	* simplify targeted communication in larger and dynamic social groups defined from context (S. 1)
	* daher bessere Kommunikation als in Freundschafts-basierten sozialen Online-Netzwerken 
- Design u. Implementierung eines solchen Beispiel-Netzwerks: AMBIENCE -> verwendet "specific meta data construction" (S. 1), nicht gebunden an bestimmten Typ von Kontextinformationen 


II. Background

- Kapitelinhalt: "short overview of context-awareness and [...] definitions of semi-constant and quasi-random context", Einführung von "information-centric networking", Bloom-Filter, "the central observation of how Bloom filters bitsets can be compared using a variant of the Jaccard distance between sets" (S. 1)

- Def. "context-cetric online social networks": "context-aware, information-centric online social networks in which information dissemination is tightly bound to context similarity" (S. 1)
- Dazu notwendiger Hintergrund: "context-aware computing, the paradigm of information-centric networks", Bloom-Filter, "paradigm of online social networks" (S. 2) 
- Neuerung: "Bloom filter allows for blind calculation of set similarity" (S. 2)

A. Context Awareness

- Def. Kontext nach Dey und Abowd: 
"Context is any information that can be used to characterize the situation of an entity. An entity is a person, place or object that is considered relevant to the interactoinbetween a user and an application including the user and application themselves." (S. 2, zitiert nach Gregory D Abowd, Anind K Dey, Peter J Brown, Nigel Davies, Mark Smith, and Pete Steggles. Towards a better understanding of context and context-awareness. In Handheld and ubiquitous computing, pages 304–307. Springer, 1999.) -> anwendungszentrierte Perspektive
- Jedoch hier: "context-centric networking" (S. 2), daher konkretere/erweiterte Def. von "context": 
"Context is any information that can be used to infer aspects of the surroundings of an entity in a way, in which some applications may have interest. Surroundings include all information that could possibly impact the behaviour of the entity." (S. 2)
- "Context awareness" erstmals verwendet von Bill Schilit, Norman Adams, and Roy Want. Context-aware computing applications. In Mobile Computing Systems and Applications, 1994. WMCSA 1994. First Workshop on, pages 85–90. IEEE, 1994: "paradigm for research in ubiquitous and pervasive computing" (S. 2)
- "pervasive": allgegenwärtig, durchdringend
- Heute: v. a. location-based services (LBS, "most prominent example of context-aware applications", S. 2) 
- Einteilung von Kontextinformationen in "context atoms" und "higher-level context" (Klassen, S. 2)
- "Context atoms": Informationen aus Sensordaten, z.B. Gerätebeschleunigung, Helligkeit, WiFi-Signalstärke (S. 2)
- "Higher-level context": Aggregation von atomarer Informationen 
- Hier: 2 Klassen von Kontextinformationendefiniert: "Semi-constant context information" vs. "quasi-random context information" (S. 2) 
- "Semi-constant context information": "context information with a limited rate of change", wird aus "semi-constant context variables" wie "location" gewonnen (S. 2)
- Beachte: Auch semikonstante Kontextvariablen wie Druck, Feuchtigkeit, Luftverschmutzung liefern atomare Kontextinformationen / Nutzeraktivität liefert auch Informationen für "higher-level context" (S. 2)
- "However, this information can be used as a key element for establishing preference based context similarity, allowing for fine-grained detection of communities and sub-communities within groups" (S. 2)
- "Quasi-Random context information": "context information for which it is impossible (or hardly possible) to infer the actual context information without measurements at the same location and situation", Bsp.: "secure key extraction from surroundings" (S. 2)
- diese Techniken ermöglichen das Entschlüsseln von Nachrichten nur für Entitäten, die sich zur selben Zeit am selben Ort befunden haben ("geo-encryption scheme", S. 2)
- "it is worth noting, that such a geo-encryption scheme does not lead to a cryptosystem in which only nearby users are able to decrypt data" (S. 2) -> man kann einen ortsbasierten Schlüssel auch entfernten Nutzern zugänglich machen!

B. Information-centric Networks

- Das Internet ist heute EZE-basiert/adressbasiert
- Alternative Ansätze: P2P-/"content delivery"-Netzwerke als "overlay" (S. 2f.) 
- Neue Nomenklaturen für informationszentrierte Netzwerke: Nicht mehr URI, da keine Datenmobilität unterstützt -> wird heute durch "redirection" gelöst (S. 3)
- Daher jetzt 3 Blöcke: Def. der Informationsobjekte ("information objects", S. 3) u. ihrer Repräsentationen, ortsunabhängige Nomenklatur ("naming scheme", S. 3) inkl. Sicherheitsmechanismen u. API
- Herausforderungen f. informationszentrierte Netzwerke, teilw. ungelöst: "naming, scalability, security, privacy, mobility and object localization" (S. 3)
- Metadaten ("metadata", S. 3): werden zw. Knoten ausgetauscht, um Netzwerkdienste bereitzustellen 
- Was sind Metadaten? "a representation of the contents of an information object suitable for concisely describing the information object content" (S. 3)
- "concise": prägnant, präzise
- Metadaten können sein: "size, content type, hash value and other technical details directly calculated from the information objects[sic!] data block as well as semantically meaningful information" (S. 3)
- Metadaten für informationszentrierte Netzwerke müssen unterstützen: "aggregation, merge and distributed reconciliation" (S. 3)
- "reconciliation": Abgleich 
- Aggregation: "calculate a summarizing metadata representation out of a set of objects" (S. 3) -> "aggregated metadata"
- "in the sequel": im Folgenden 
- Aggregierte Merge-Operation ("aggregated merge operation", S. 3): "calculate the aggregated metadata of the union of two sets out of the aggregate metadata of the individual sets" (S. 3)
- Mengenvergleich/Erkennung von Mengendifferenzen ("set reconciliation", S. 3): "an algorithm [...] which efficiently calculates a list of information objects that two nodes do not have in common based on the aggregated metadata of the two sets of objects each node have in their cache" (S. 3)
- "set reconciliation problem": "the problem of synchronizing unordered data" (https://en.wikipedia.org/wiki/Data_synchronization)
-> Diese Fragestellungen rund um "information object metadata" werden häufig mittels Bloom-Filtern angegangen (S. 3)

C. Bloom Filter

- Def. Bloom Filter: "probabilistic data structure describing sets" (S. 3)
- Form: Bitarray fester Länge, basiert auf Berechnung einer festen Anzahl von Hashfunktionen des Informationsobjekts, die positive Werte kleiner als die Länge des Bitarrays annehmen. 
- Die Hashwerte werden verwendet, um die Bits zu setzen, wenn ein Informationsobjekt zum Filter hinzugefügt wird
- Die Hashwerte werden verwendet, um Queries auf dem Filter auszuführen (ob ein Objekt darin enthalten ist)
- Bloom-Filter erfüllen Aggregation, Merge und Mengenvergleich! 
- Hier wichtig: Über den Nullanteil ("fraction of zeros", S. 3) eines Bloom-Filters (#Nullbits/#Bits) lässt sich #Elemente eines Bloom-Filters abschätzen (Formel vgl. S. 3, lt. Wikipedia wird der natürliche Logarithmus verwendet, vgl. https://en.wikipedia.org/wiki/Bloom_filter)
- Vereinigung zweier Bloom-Filter berechnen: OR -> #Elemente zweier vereinigter Bloom-Filter abschätzen: Nullanteil d. Vereinigung in die obige Formel einsetzen 
- #Elemente zweier geschnittener Bloom-Filter abschätzen: Formel vgl. S. 3

- Approximation d. Jaccard-Distanz zweier Mengen: Vgl. S. 3, wird später verwendet in V.
- 2 Varianten von Bloom-Filtern hier wichtig: "counting Bloom filter" und "time-decaying Bloom filter" (S. 4) -> die Bits werden durch Integer-Zähler ersetzt
- "Counting Bloom filter": Zähler werden beim Einfügen eines Elements um 1 erhöht -> liefert obere Schranke für #Einfügungen eines best. Elements (aber nat. zu hohe Schätzungen mögl. wegen Hash-Kollisionen)
- "Time-decaying Bloom filter": Zähler werden beim Einfügen eines Elements um einen festen Wert r #Runden erhöht, die das Element im Filter vorhanden sein soll; in jeder Runde werden alle Zellen mit pos. Werten um 1 dekrementiert 

D. Distributed Online Social Networks 

- Def. "social network site" nach Boyd und Ellison: Vgl. Nicole B Ellison et al. Social network sites: Definition, history, and scholarship. Journal of Computer-Mediated Communication, 13(1):210–230, 2007.
- Jedoch hier weiter gefasst: Def. "social network site" als "web-based services that allow individuals to (1) construct a public or semi-public profile within a bounded system, (2) articulate a list of other users with whom they share a connection, and (3) view and traverse their list of connections and those made bay others within their system" (S. 4)
- Normalerweise zentrale Datenstruktur in "social network site": "social graph" (S. 4)
- Außerdem: "interaction graph" (S. 4) -> spiegelt besser das darunterliegende soziale Netzwerk wider, Kanten nur bei echter Interaktion 
- "social network pollution" (S. 4): Verbindungen zw. Profilen/Identitäten ohne echte Interaktion 
- Architektur sozialer Online-Netzwerke: Häufig Client-Server mit zentralem logischen Server/Dienst, aber mehreren physischen Servern -> Nachteile z.B. SPOF, Verletzung der Privatsphäre, mangelndem Schutz von Nutzerdaten, Sicherheitsrisiken, Datenmissbrauch z.B. zu Werbezwecken  
- Daher: "distributed online social networks" (S. 4)
- Architektur Verteilter sozialer Online-Netzwerke: Keine zentrale Entität, Netzwerkfunktionalität realisiert als P2P zwischen Nutzern -> Nachteil: "permanente profile availability and efficient distributed search" weitaus komplexer/schwieriger zu realisieren! (S. 4)

III. CONTEXT-CENTRIC ONLINE SOCIAL NETWORKS 

- Kapitelinhalt: "the novel paradigm of context-centric online social networks" (S. 1)
- Motivation: "providing adaptive networks using the information-centric networking paradigm" (S. 4)
- Voraussetzungen: Adaption funktioniert am besten kontextbasiert; Kommunikation in sozialen Online-Netzwerken kann von Kontext und Informationsbewusstsein ("information awareness", S. 4) profitieren 
- Def. "Context-Aware Online Social Network": "[A]n online social network in which the edges in the social graph are annotated with context variables and in which it is made possible to share information based on context similarity." (S. 4)
- Def. "Context-Centric Online Social Network": "[A]n online social network in which the edges of the social graph are defined from context information and context matching algorithms. An edge between two profiles exists for a fixed information object if and only if the two profiles share the relevant context as defined by the publisher." (S. 4)
- Nachteil: Informationsfluss kann stark eingeschränkt sein, wenn nur die Nutzer überhaupt das Informationsobjekt weiterleiten dürfen, die dessen Restriktionen erfüllen 
- Vorteil: Keinerlei "social network pollution" (S. 4)

IV. TOWARDS A CONTEXT-CENTRIC ONLINE SOCIAL NETWORK

- Kapitelinhalt: "a metadata format for context-centric online social networks" inkl. Beispielszenarien (S. 1)
- Ziel: Kontextzentrische Funktionalität für den Prototypen, Datenstrukturen für die notwendigen verteilten Operationen 
- Grundlage: Bloom-Filter
- Aber: Erste Version mit CS-Architektur!
- Am wichtigsten: Metadaten-Management! (vgl. folgenden Abschnitt)

A. Metadata in Context-Centric Networks 

- Verwendung von Bloom-Filtern zur Generierung der Metadaten -> Repräsentation der Kontextinformationen als Menge von String-Labels, die mittels einer sicheren Hashfkt. in einen Bloom-Filter eingegeben werden
- Ergebnis: 
	1. Typenlose Repräsentation der Informationen ("Typeless Representation", S. 5)
	2. Blinde Teilmengen-Operationen ("Blind Subset Operation", S. 5): Ohne Kenntnis des Inhalts, der von den Metadaten beschrieben wird, können mit geringer Fehlerwahrscheinlichkeit Teilmengen bestimmt werden [?]
	3. Ungefähre Jaccard-Ähnlichkeit ("Approximate Jaccard Similarity"): Ohne Kenntnis des Inhalts, der von den Metadatan beschrieben wird, kann die (Jaccard-)Distanz zwischen zwei Filtern approximiert werden
- Diese Eigenschaften ermöglichen neuartiges Addressierungsschema -> Die Adresse einer Nachricht wird als kleine Menge von Strings interpretiert, die von einem Bloom-Filter (mit bekannter Konfiguration) repräsentiert werden: "We can address a single message to a small subset of strings [?] and select messages from a database based on the Jaccard set similarity of these sets of strings or based on the subset relation." (S. 5)
- Beispiele für Widerspiegelung von Kontext/Kontextähnlichkeit durch dieses Adressierungsschema: 
	1. "Spatial awareness inside buildings" -> Binde Nachricht an Menge von MAC-Adressen/Wi-Fi access points -> ermöglicht "location-limited publication" und "location-based ranking" von Nachrichten (S. 5)
	2. "Geospatial awareness based on coordinates" (S. 5) -> Verwende Z-Kurven-Codierung beschränkter Länge (analog zu Geohashes), um Nachricht an Ort zu binden -> Client kann beliebige spatiale Queries innerhalb dieses Frameworks bilden, Grid-Geohashes [?] benachbarter Zellen können leicht berechnet werden (analog zu "GeoCookie", vgl. Peter Ruppel and Axel Küpper. Geocookie: a space-efficient represen- tation of geographic location sets. Journal of Information Processing, 22(3):418–424, 2014.)
	3. "Activity information" (S. 5) -> Füge Strings einer vorher festgelegten Menge von Labels zum Filter hinzu 
- Das Framework ist damit komplett allgemein gehalten; Einschränkungen sind lediglich Query-Typen sowie Repräsentation von stetigen Variablen 

B. Group Messages and Epoch-based Privacy

- Erinnerung: Kontext-Situationen werden also als kleine Mengen von Strings zusammengefasst und durch Bloom-Filter repräsentiert
- Wähle sichere kryptografische Hashfunktionen -> Original-Strings können nicht zurück verfolgt werden -> Schutz der Privatsphäre
- Jedoch: Replay-Angriffe (Wiedereinspielen von Filtern) leicht möglich: "Each user that has once been in a specific context situation is able to calculate the associated filter and make targeted queries." (S. 5) -> Problem bzgl. Privatsphäre, da Angreifer in unbegrenzter Zeit Datenbank von realistischen Filtern aufbauen und damit die erhoffte Kontext-Basierung des Systems umgehen kann (er wendet Filter von Kontexten an, in denen er sich zum jetzigen Zeitpunkt aber nicht befindet!)
- Lösungsansatz: Verwende zufällige Präfix-Strings zur Einschränkung der Nutzer, die gerichtete kontextbasierte Query ausführen können, auf ausgewählte Gruppe: "By choosing a prefix for the hash functions and using cryptographic hash functions, we can model access control on the contents of the data structure without hiding the approximate number of elements for any filter and the expected set similarity for two filters created using the same prefix." (S. 5)
- Gruppen können sein: 
	1. "group of users": Teilen ein gemeinsames, geheimes Präfix (S. 5)
	2. "time epochs": Von der Plattform wird jedem Zeitintervall ein besimmter String zugeordnet, der allen Nachrichten vorangestellt werden muss; nur Nutzer, die diesen (bzw. das Zeitintervall) kennen, können die zugehörigen Informationen erhalten (S. 5)
	3. "spatially limited time epoch": Analog für zeitliche + räumliche Einschränkung; nur Nutzer, die sich in einem bestimmten Zeitraum an einem bestimmten Ort aufgehalten haben, erhalten das Präfix und können die zugeordneten Informationen erhalten (S. 5)

V. AMBIENCE: A CONTEXT-CENTRIC ONLINE SOCIAL NETWORK PROTOTYPE

- Kapitelinhalt: "our prototypical implementation of the ideas presented in this paper" (S. 1)/"proof of concept" (S. 6)
- Ziel: Funktionsfähiger Prototyp eines kontextzentrierten sozialen Online-Netzwerks
- Prinzip: CS-Architektur mit zwei Client-Komponenten z. Veröffentlichen u. Empfangen von Nachrichten (basierend auf Ähnlichkeit) 
- Server: Speichert u. managt Liste v. Paaren aus Bloom-Filter + Multimedia-Nachricht; bietet Schnittstelle zum Anfragen ("querying", S. 6) der k ähnlichsten Bloom-Filter/der k ähnlichsten Bloom-Filter, die einen bestimmten anderen Bloom-Filter enthalten 
- Client: 
	1. Subscription-Teil: Pflegt regelmäßig einen "time-decaying Bloom filter" (S. 6) u. fragt Liste bei Server an: beschränkte #Elemente, geordnet nach Zeit, Angabe d. geschätzten Jaccard-Ähnlichkeit (in der Anwendung wird Ähnlichkeit über eine farbige Sidebar dargestellt: Je dunkler der Hintergrund einer Nachricht, desto größer die Ähnlichkeit mit der Anfragequery -> Ranking von Zeit und Ähnlichkeit können dadurch gleichzeitig dargestellt werden)
	2. Veröffentlichungs-Teil: Funktioniert analog (verwendet denselben Bloom-Filter [?])  
- Filter können im Client gespeichert u. mit Namen versehen werden -> funktioniert wie "channel subscription" (S. 6); man kann dann in der Anwendung mit Klicken auf den Filter die ähnlichsten Nachrichten eines bestimmten Zeitfensters (in der Vergangenheit) erhalten
- Ergebnis: System funktionierte im Wesentlichen wie erwartet, doch Channel-Management sowie "tradeoff" von Relevanz, Zeit [?] u. #Nachrichten erweist sich als kompliziert!

VI. CONCLUSION 

- Ergebnisse: Einführung des Paradigmas "Kontext-zentriertes soziales Online-Netzwerk"; Metadaten-Ansatz z. tatsächlichen Konstruktion solcher Netzwerke als informationszentrierte Netzwerke; Beispielimplementierung "Ambience" 
- Ambience: Nutzer können Textnachrichten austauschen, die nach zeitlicher Aktualität und Kontextähnlichkeit ausgewählt werden 
- Zukünftige Arbeiten: 
	1. Sicherheit und Schutz der Privatsphäre im System
	2. Kontextzentrierter Verschlüsselungsmechanismus -> Inhalt der Nachrichten soll jetzt auch geschützt werden 

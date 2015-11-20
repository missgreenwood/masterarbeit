Zusammenfassung Sarwat 2012 _(referenziert in AMBIENCE)_
--------------------------------------------------------

0. Abstract 

- Ziel: Präsentation von Sindbad, ein Location-basiertes OSN
- Drei neue Dienste: "location-aware news feed, location-aware recommender, and location-aware ranking" (S. 649) -> berücksichtigen soziale u. spatiale Relevanz
- Im Fokus: Skalierbarkeit u. Effizienz -> dazu werden die Dienste in die "query processing engine" von PostgreSQL gekapselt
- "Usage and internal funcionality of Sindbad, implemented with PostgreSQL and Google Maps API, are demonstrated through user (i.e. web/phone) and system analyzer GUI interfaces, respectively" (S. 649)

1. Introduction

- Unterschied zu bestehenden ONS: Location-awareness ("within every aspect of social interaction and functionality", S. 649)
- Unterschied auch zu bestehenden location-based ONS (i.e. Facebook Places, Foursquare): "these networks are atrictly built for mobile devices, and only allow users to receive messages about the whereabouts of their friends" (S. 649) - hingegen Sindbad: Verbindung von traditionellem ONS und "location-based social scenarios (e.g., friend news posts with spatial extents, location-influenced recommendations)" (S. 649)
- Features von Sindbad: 
	1. "[S]patial messages" (S. 649)
	2. Bewertung von "(spatial) objects" (S. 649)
	3. "Location-aware news feed module[:] GeoFeed" (S. 649) 
	4. "Location-aware recommender module[:] LARS" (S. 649)
	5. "Location-aware ranking module that efficiently selects the top-k relevant objects" (entweder von 3. oder 4., S. 649)
- PostgreSQL: Open Source-DBMS
- Technische Realisierung: v.a. basierend auf PostgreSQL -> liefert Skalierbarkeit und "early pruning techniques" (S. 649); außerdem RESTful Web-API
- "prune": abschneiden, beschneiden 
- Anwendung wird an Web- und Smartphone-App demonstriert, die auf Sindbad aufsetzt
- "the system internals are demonstrated through an administrator-like interface that shows the differnet system parameters as well as general statistics about Sindbad" (S. 649f.)

2. Sindbad architecture

- 3 Module (S. Abschnitt 1): "location-aware news feed (GeoFeed), location-aware ranking, location-aware recommender (LARS)" (S. 650)
- 3 Datentypen werden gespeichert: "spatial messages, user profiles, [...] spatial rankings" (S. 650)
- Kommunikation zw. Sindbad und Außenwelt über RESTful Web-API-Interface ("Sindbad API Functions", S. 650) -> "facilitates building a wide variety of applications [...] on top of Sindbad" (S. 650)
- 5 Input-Arten durch API-Interface: 
	1. "Profile update" (S. 650)
	2. "[N]ew message" (S. 650) -> "The message is deemed relevant to only those users who are located within its spatial range" (S. 650)
	3. "[N]ew rating" (S. 650) 
	4. "Location-aware news feed query" (S. 650) -> "Once a [...] user logs on to the system, a location-aware news feed query is fired to retrieve the relevant news feed, i.e., messages posted by the user's firends that have spatial extents covering the location of the requesting user" (S. 650)
	5. "Location-aware news feed query" (S. 650)

3. Location-aware news feed

- Kapitelinhalt: GeoFeed
- Konzept: "abstract the location-aware news feed problem into one that evaluates a set of location-based point queries against each friend in a user's friend list that retrieves the set of messages issued that overlap with the querying user's location" (S. 650)
- 3 Ansätze zur Auswertung jeder "location based query" (S. 650):
	1. "spatial pull approach" (S. 650)
	2. "spatial push approach" (S. 650) -> bestes Zeitverhalten, daher für Sindbad verwendet 
	3. "shared push approach" (S. 650)
- Größte Herausforderung: Wann welchen Ansatz verwenden? -> in Sindbad wird Tradeoff zw. mehr System-Overhead ("spatial push approach") und höherer Antwortzeit ("spatial pull approach") je nach Situation (Profil, User, Query) hergestellt und demensprechend entweder 1. oder 2. verwendet 

4. Location-aware recommender

- Kapitelinhalt: LARS
- Normale Ratingsysteme ignorieren Location (Netflix etc.)
- Filtertechnik in LARS (vgl. G. Adomavicius and A. Tuzhilin. Toward the Next Generation of Recommender Systems: A Survey of the State-of-the-Art and Possible Extensions. TKDE, 17(6):734–749, 2005.) -> "collaborative existing filtering technique that utilizes only the ratings located in R [range]" (S. 651)
- auch hier müssen zwei kontradiktorische Faktoren vereinbart werden: Skalierbarkeit u. Lokalität ("locality", S. 651)  
- Details zu LARS: Vgl. J. J. Levandoski, M. Sarwat, A. Eldawy, and M. F. Mokbel. LARS: A Location-Aware Recommender System. In ICDE, 2012.

5. Location-aware ranking

- Kapitelinhalt: "location-aware ranking module" (S. 651) -> "ranking the results coming out of the location-aware news feed module and location-aware recommender module, based on the user's preferences" (S. 651)

6. Demonstration scenario 

- Sindbad in Kombination mit Foursquare-Accounts, Integration von Google Maps

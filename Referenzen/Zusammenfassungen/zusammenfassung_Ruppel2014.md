Zusammenfassung Ruppel2014 _(referenziert in AMBIENCE)_
-------------------------------------------------------

0. Abstract

- Ziel: Neue Methode "that allows a user agent to compute a compact browser cookie-like character string (called Geocookie) for a third party, whereby for any given geographic location the third party can either infer that the location is definitely not covered by the Geocookie, or it can inter that the location is probably covered by the Geocookie, depending on whether the user agent has or has not included the location befoehand" (S. 418)
- Verwendete Technik: Erweiterung von Bloom-Filtern u. Verbindung mit Geohashes
- Anwendungsszenarien: "whenever a user agent wants to inform a third party about a set of visited locations such that the third party can compile a result that either favors or excludes these locations" (S. 418)
- Unterschied zu bisherigen Techniken: Bessere Privacy und Security, da keine Session-Cookies auf serverseitige gespeicherte Bewegungskurven ("location trajectories", S. 418) gemappt werden, sondern Einweg-Checkfunktion 
- Inhalt des Papers: "formal definition for Geocookies together with a discussion on practical applications and embedding into HTTP headers" (S. 418)

1. Introduction

- Normalerweise/bisher: "Information retrieval for location-based applications often involves the filtering and processing of datasets on the basis of user-dependent trajectories and sets of visited places, respectively" (S. 418)
- Generelle Problembeschreibung: "given a set L = {l_1, l_2,, ..., l_n} of geographic location elements and a location element p, determine whether there is at least one elemntin L that covers p" (S. 419) -> wird heute i.d.R. mit beliebiger spatialer DB ausgeführt 
- Problemstellungen: 
	1. p und L nicht auf demselben System
	2. Erkennung von Ähnlichkeiten/weiteren Faktoren (z.B. nur bestimmte Entfernung, d.h. "at least one element in L which is apart from p no more than a given distance d", S. 419)
	3. Große #L, hohe Checkrate
	4. Charakterisierung u. Portabilität v. "location sets" (S. 419)
- Klass. Problemstellung f. 
	1. "location-dependent messaging" (S. 419): "deliver messages to recipients only at certain locations, possibly considering additional contextual constraints" (S. 419)
	2. "geofencing application" (S. 419): "trigger events based on the entering, leaving, staying or the recurrence of mobile targets in vcertain geographical regions, called geofences" (S. 419)
- Standardisiertes Geodaten-Format: GPS Exchange Format (XML-basiert)
- Wichtigstes Ziel: Nicht nur standardisiertes Geodaten-Format u. Nutzbarkeit f. unterschiedlichste Anwendungen, sondern v.a. kompakte Datenstruktur für skalierbare Menge von "location elements" -> Anwendungsfälle: 
	1. L wird häufig zw. Parteien ausgetauscht
	2. L wird häufig gegen andere l gematcht
	3. L wird häufig um weitere l's erweitert 
- Klass. Bloom-Filter muss erweitert werden um: "take into account matches as a result of being covered by other location elements or because of their spatial proximity to the element under consideration" (S. 419)
- Also Ziel: "novel combination of existing Bloom filter and location hashing approaches that allows to efficiently evaluate spatial containment of a geographic locatoin in a set of previously collected locations" (S. 419)
- Anwendungsfälle: "both native and web-based LBS applications that rely on filtering geographic locations in order to compile their responses" (S. 419) 

2. Geocookies

- Kapitelinhalt: "fundamentals of the data structure and [description of] how location elements can be added and tested" (S. 419)
- Ansatz: Kombination aus Bloom-Filter und Geohashes (vgl. Gustavo Niemeyer. Geohash, http://geohash.org.), d.h. natürlich: "Once a location element has been added to the Geocookie, it cannot be removed, and an increasing number of elements in the Geocookie will increase the false positive rate of membership tests"
- Folgerung: "Geocookies are not intended for perfect checks on geographic object, but rather for various optimization purposes in the domain of location data queries" (S. 419)
- location elements l_i werden sind Polygonzüge, d.h. auch Punkte können dargestellt werden 
- 2 Operationen auf Geocookie: add(l) und isCovered(l)
- Eigenschaften von L im Geocookie: monoton wachsend, divers, möglicherweise überlappend, approximativ

2.1 Adding Locations to the Geocookie

- Besonderheit i. Vgl. zu klass. Bloom-Filtern: "it is not only required to recognize an exact area, but also to test whether a given location is inside a previously stored area" (S. 419) -> verwendet Approximation, d.h. es wird Exaktheit ggü. Effizienz eingebüßt
- Methode: Geohash -> "approximate and process geographic locations within the geocookie" (S. 419)
	1. Methode kann vergröbert werden, indem man Zeichen am Ende des Hashes abschneidet 
	2. Zwei Hashes mit demselben Präfix zeigen i.d.R. auf dieselbe Region 
	3. Akkuratheit des Geohashes hängt von seiner Länge ab
- Verbesserungen/Spezifika für Geocookie: 
	1. Verwende Maximallänge f. gemeinsame Präfixe -> Vielzahl von nahe beeinander liegenden Locations cluttern nicht den Bloom-Filter 
	2. Verwende Minmallänge f. gemeinsame Präfixe -> große Gebiete werden ausreichend abgedeckt: "raster the overlarge location element l into many smaller rectangular fragments whose size equals the size of the rectangles that are represented by Geohashes with the minimum allowable length cp_min" (S. 420)
- Vor dem Einfügen des angepassten location elements in den Bloom-Filter wird Check durchgeführt, ob es schon von einem bereits darin enthaltenen Element abgedeckt ist 
- Wähle praktischerweise cp_min nicht zu klein, d.h. auf jeden Fall > 3!

2.2 Testing for Coverage

- Ziel: Ist das location element l schon von einem Element im Geocookie abgedeckt?
- Schritte: 
	1. Berechne gemeinsames Präfix cp(l) wie in 2.1 unter Berücksichtigung von cp_min, cp_max, l_mbr. Falls der resultierende Geohash zu kurz ist, werden mehrere längere Geohashes f_1, ..., f_m wie in 2.1 berechnet
	2. Klass. Bloom-Filter-Check auf jedem Geohash 
	3. Falls Check false ergibt, d.h. der Geohash ist nicht im Geocookie enthalten, kann der Geohash trotzdem schon durch eine größere Fläche abgedeckt sein -> alle Präfixe pre_i(cp(l)) müssen einzeln getestet werden 

2.3 False Positives and Location Coverage

- |L| kann kleiner sein als #eingefügter Elemente in den Bloom-Filter, weil evtl. Elemente mit zu kurzen Präfixen beim Einfügen gesplittet wurden -> "therefore the proportion f of location fragmentation needs to be considered, which is defined as the ratio between the number of Geohashes and the number of distinct location elements" (S. 420)
- W'keit für falsch positives Element im Geocookie also: P_fp = (1 - (1 - 1/m)^(knf))^k, wobei 
	* m: #Arraylänge des Geocookies
	* k: #unabh. Hashfunktionen 
	* n: #Elemente, die bereits in Geocookie eingefügt wurden 
- Außerdem muss Überdeckungsverhältnis berücksichtigt werden: "coverage ratio c ≥ 1 of a location element and its resulting Geohash bounding boxes", def. als "fraction between the area covered by the Geohash approximation and the area covered by the location" (S. 420) -> kann nicht aus Geocookie extrahiert werden, muss man daher vorher im Additionsprozess berechnen
- Falls das gewünschte c nicht durch die aktuelle Präfixlänge erreicht wird, muss Geohash-Raster erhöht werden!
- Geocookie wird als voll erklärt, wenn vorher def. #Elemente eingefügt wurden (damit Falsch-Positiv-Rate nicht zu hoch wird!)
- Wahl der Hashfunktionen? -> MurmurHashes, SHA1 (z.B. "fixed-length snippets of SHA-512", S. 421)
	1. Voneinander unabhängig 
	2. schnell
	3. einheitl. Vtlg. ("uniform distribution", S. 421)

2.4 Related Work 

	1. Klass. Bloom-Filter
	2. Counting Bloom filters
	3. Komprimierte Bloom-Filter 
	4. Spektrale Bloom-Filter

- Lassen sich alle nicht auf Geodaten anwenden! 
- Der hier vewendete Ansatz ist daher neuartig (Kombination von location hashing und Bloom-Filtern)

3. Geocookies for Location Data Processing 

- Kapitelinhalt: "use cases and [...] numbers for the utilization of the approach within HTTP" (S. 419)

3.1 Types of Geocookies

	1. Browser Geocookies: Werden verwendet, um location sets an normalen HTTP-Request anzuhängen -> vgl. Abschnitt 3.4
	2. Local Geocookies
	3. Hierarchical Geocookies: "[S]eparate multiple layers of location granularity in an application context" (S. 422)
	4. Public Geocookies
	5. Concealed Geocookies: "[C]ontain either additional artificial location elements or are configured with a high false positive rate, which both disguises the actual set of locations of interest" (S. 422)

3.2 General Privacy Considerations

- 3 wichtige Ansätze bzgl. location privacy:
	1. Privacy Policies
	2. Datenabstraktion 
	3. Identifier-Abstraktion 
- Außerdem: k-Anonymität
- Privacy-Eigenschaften von Geocookie gehören zu 2.!
- Aber: Nicht k-Anonymität, sondern plausible Abstreitbarkeit ("plausible deniability", S. 422, Erklärung S. 422)

3.3 Distance-based Testing

- Jetzt: Auch Distanzparameter d wird in Lookup-Funktion integriert -> "" 

3.4 HTTP embedding

4. Discussion 

- "The presented approach aims at application scenarios that benefit from fast coverage checks and which at the same time are tolerant towards a certain false-positive rate" (S. 423) -> muss an die jeweilige Anwendung angepasst werden, also vllt. für uns nicht so günstig?!
- Zentral: Anpassung der minimalen u. maximalen Länge d. Geohash-Präfixe; ebenso Differenz zw. beiden ("defines how coarse-grained large location elemnts will be mapped", S. 423)
- Falls wenig Unterschiede in den Polygonen: Setze cp_min = cp_max, um #Elemente im Geocookie zu minimieren 
- Zukünftige Herausforderung, noch ungelöst: Zeitstempel für Locations -> Unterstützung von Anwendungen mit zeitlicher Ordnung der Elemente

5. Conclusions

- Ergebnis: kompakte Repräsentation geografischer location sets
- Eigenschaften/Vorteile: 
	1. "polygonal location elements can be maintained and tested for coverage" (S. 423)
	2. "the granularity of stored location elements can be adjusted by defining upper and lower bounds for the Geohashes" (S. 423)
	3. "false positive rate for coverage checks can be computed and adjusted in advance" (S. 423)
	4. Unterstützung unterschiedlicher Anwendungsfälle wie Übergeben von location sets in Browser-Requests, "speeding up local lookups on location elements or sharing fixed location sets that act as filters for location-based queries" (S. 423)
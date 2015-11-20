Zusammenfassung Sakuma2011
--------------------------

0. Abstract 

- In verteilten Systemen: Bloom-Filter flexibler als DHT, da Lookup für ein oder mehrere keywords möglich ("lookup of data in distributed systems", S. 316)
- Ring von Bloom-Filtern: "Chord filter" (S. 316) -> Nachteil: "the node in the ring must maintain many filters corresponding to the number of nodes" (S. 316)
- Stattdessen jetzt:
	1. "tree structured Bloom filter" (S. 316)
	2. Evaluation der Performance des Query-Forwarding
	3. "similarity-based tree management method" -> "effective to reduce the cost of reconstruction of the tree" (S. 316)
	4. Evaluation: Vergleich mit existierenden Filtermethoden (bzgl. Filtergröße u. durchschnitt. #Hops b. Query-Forwarding) 
	5. Simulation d. "tree reconstruction cost" (S. 316)

1. Introduction 

- Lookup v. Daten in P2P-Netzwerken mit DHT
- OR, AND-Operationen auf Bloom-Filtern 
- Attenuated Bloom-Filter: "each node manages a table of the Bloom filters" (S. 316)/"standard Bloom filter combined with d layers" (S. 318)
- Chord-Algorithmus: wird in DHT verwendet sowie in attenuated Bloom-Filtern zum Query-Forwarding
- Neue Methoden: 
	1. Lookup-Methode f. Bloom-Filter, basierend auf B-Baum -> Query-Forwarding liegt in O(log_m N) ggü. Chord-Algo. (O(log_2 N)), #verwaltete Bloom-Filter liegt in O(1) ggü. Chord-Algo. (O(log_2 N))
	2. Baum-Management-Methode -> basiert auf Ähnlichkeit v. Bloom-Filtern ("similarity of Bloom filter", S. 316), reduziert Rekonstruktionskosten f. Baum 

2. Related works

2.1 Bloom filter

- OR-Operation: Kombination zweier oder mehrerer Bloom-Filter 

2.2 Bloom filter with the Chord structure

- DHT mit Bloom-Filtern: 
	* "In usual distributed hash table (DHT), a content ID is generated from one or some key words, and the content is added to the node corresponding to the content ID according to the P2P protocol of each DHT" (S. 317); "key word of contents is represented in the Bloom filter" (S. 317) -> ermöglicht Vergleich von Bloom-Filtern basierend auf P2P-Protokoll
	* Jeder Knoten generiert einen Bloom-Filter aus allen Schlüsselwörtern der Inhalte, die bei ihm gespeichert sind -> "Node Bloom filter [...] (NBf)" (S. 317)
	* Damit kann bei jedem Knoten Lookup nach Schlüsselwörtern durchgeführt werden; Lookup aller NBfs ist aber ineffizient -> deswegen weiterer Bloom-Filter aus allen NBfs "of all nodes in the finger table within the range of each search path" (S. 317) -> "Finger Bloom filter [...] (FBf)" (S. 317)
	* Der FBf enthält damit alle Schlüsselwörter aller Suchpfade!
	* Beim Lookup von Daten wird der Bloom-Filter der Query generiert und mit der Finger table des Knoten verglichen; die Querx wird weitergeleitet an den Knoten, der den Query-Filter enthält
	* Dabei müssen Ranges festgelegt werden, damit sich Suchbereiche nicht überlappen 

2.3 Attenuated Bloom Filter

- Prinzip: Standard-Bloom-Filter mit d Schichten -> "A certain node stores information on the presence of the content in the surrounding nodes in the attenuated Bloom filter. In the (i+1)th layer of this filter, information on all nodes in i hops has been consolidated. In the first layer, information on the site itself is stored" (S. 318)
- Funktionsweise:
	* Der attenuated Bloom filter wird regelmäßig mit allen Nachbarknoten ausgetauscht und die entsprechenden Schichten werden mit OR verknüpft
	* "the link to which the filter is received is managed" -> "Therefore, whether the searched filter exists can be specified" (S. 318), ebenso die Richtung
- Vorteil: Niedrigere Kosten als 2.2, weil das Netzwerk nicht strukturiert werden muss
- Nachteil: Keine obere Schranke f. Query-Forwarding
 
3. Bloom filter based on the tree structure

- Kapitelinhalt: "Bloom filter management method based on a B-tree" (S. 316)

3.1 B-tree structure

- Prinzip: Jeder Knoten managt den verteilten B-Baum 
- Funktionsweise: 
	* Knoten im B-Baum heißt logischer Knoten 
	* IDs der phyischen Knoten werden in den Blättern des B-Baums gespeichert
	* Innere Knoten: Zweiginformationen, Versionsnr. d. Informationen 
	* Informationsmanagement f. den B-Baum über physische Knoten; jeder physische Knoten hat partielle Informationen über den B-Baum
	* Jeder physische Knoten managt die Information für seinen Zweig sowie Informationen über die Geschwisterknoten 
	* Also für N physische Knoten: B-Baum der Höhe ~ log_m N, m-facher Baum [was wird mit m bezeichnet?]; "Each physical node has information on th enumber of nodes proportional to log_m N" (S. 319, [?])
	* Der Knoten mit der kleinsten ID in der internen Knoten-Information heißt repräsentativeer Knoten; er managt die Informationen des korrespondierenden internen Knoten (vgl. Fig. 4 S. 319)

3.2 Management of the tree

3.2.1 Participation method 

	1. "participation request": endet beim "representative node of the lowest internal node which is the appropriate to manage the new node" (S. 319) 
	* Falls dort Platz im Array: Der neue Knoten wird ins Array integriert
	* Andernfalls: Der interne Knoten muss sich um den Split kümmern (notfalls bis zur Wurzel)
	2. "notification of change information": wird vom repräsentativen Knoten des höchsten Knoten in der Baumstruktur ausgeführt, der von der Änderung betroffen ist 
	* als Multicast an die betroffenen Knoten 
	* Situation: "the update has been generated concurrently by another process when the version number of the node has already been changed"; "after the interruption, the participation processing is executed again" (S. 319, [?])

3.2.2 Secession method

	1. "secession request": wird an den repräsentativen Knoten des niedrigsten internen Knoten gesendet, an dem der ausscheidende Knoten hängt (S. 319)
	* Falls dort #Elemente ≥ m/2: Knoten-ID wird aus Array gelöscht  
	* Andernfalls: Element vom Bruderknoten wird geholt; falls immer noch Underflow, werden die beiden Knoten verschmolzen (notfalls bis zur Wurzel)
	2. "notification of change information": analog zu 3.2.1 

3.3 Management of the Bloom filter 

- Management d. physischen Knoten: 
	* Jeder physische Knoten verwaltet einen konsolidierten Bloom-Filter ("consolidated", S. 319) für die Indexinformationen 
	* Ein höherer innerer Knoten hat zudem "a consolidated Bloom filter which consolidates the bloom filter of the node of the subordinate position based on the structure of the B-tree" (S. 319) -> damit hat der Wurzelknoten die konsolidierten Filter aller Knoten 
- Informationen über die konsolidierten Bloom-Filter und die Baumstruktur werden sowohl an physische als auch an Baumknoten weiter gegeben 
- Management d. Baumknoten: 
	* Jeder repräsentative Knoten hat konsolidierten Bloom-Filter des korrespondierenden physischen Knotens sowie Bloom-Filter der untergeordneten Filter (vgl. Fig. 5 S. 320) 

3.3.1 Management of Bloom filters of leaf node

- Bei Änderung des konsolidierten Filters in einem Blattknoten wird diese Information zum repräsentativen Knoten des höchsten inneren Knoten nach oben propagiert  
- Dieser informiert den repräsentativen Knoten des Geschwisterknotens und untergeordneten Knoten durch Multicast

3.3.2 Management of joining node

- "The representative node of the internal node which accomodates the new node computes the change of consolidated Bloom filter when there is new participation in B-tree" (S. 320); gleiches Verfahren wie 3.3.1 für Geschwisterknoten und untergeordneten Knoten 

3.3.3 Management of secession of the node

- Verfahren analog zu 3.3.2

3.4 Method of looking up data

4. Similarity-based tree management

- Kapitelinhalt: "similarity-based tree management method" (S. 316)
- Häufige Umstrukturierungen der B-Bäume werden teuer -> daher jetzt: Baum-Management, das auf Ähnlichkeit d. Bloom-Filter aufbaut: "similar Bloom filters are grouped and managed as the child node of one internal node" (S. 321)

4.1 Similarity of Bloom filter

- Def. "Ähnlichkeit": #1-Bits > #0-Bits (falls #1-Bits gleich, wird der Filter umgekehrt und die #0-Bits mit AND verglichen)

4.2 Node join

- Ein neuer Filter kommt zu dem Knoten, mit dem er die größte Ähnlichkeit hat (vom Wurzelnoten nach unten bis zum niedrigsten inneren Knotenlevel)

4.3 Division of the internal node

- Falls #Kindknoten > m, muss innerer Knoten geteilt werden: "[T]he similarity of the each child node and the new node is calculated. After that, (m+1)/2-1 nodes which has the high similarity are seleceted. One group is composed of the new node and the selected nodes, and other group is composed of the rest" (S. 322) 

4.4 Node Leave

- Falls #Kindknoten < m/2, muss ein innerer Knoten einen Kindknoten vom Bruderknoten nehmen -> wird über Ähnlichkeit ausgewählt

5. Evaluation 

- Kapitelinhalt: "Comparison between the previous method and our method" (S. 316) 
- #Schritte im Query-Forwarding: entpricht Baumhöhe, also O(log_m N)
- Change-, Add- und Delete-Operationen: O(log_m N)
- Management: 
	* durchschnittl. #Bloom-Filter, die ein Knoten managen muss: O(1) 
	* Gesamtanzahl zu managender Bloom-Filter: O(N))
	* durchschnittl. #Bloom-Filter, die ein repräsentativer Knoten managen muss: O(m) (da ~ N/m repräsentative Knoten)
- Vergleich mit Chord-Algo.: Tab. 2 S. 322
- Durchschnittl. Forwarding-Zeit f. Query kann ggü. Chord im besten Fall um ~ 25% reduziert werden -> "shows that the performance of the proposal method improves the lookup efficiency"
- Rekonstruktionskosten können m. ähnlichkeitsbasiertem Ansatz ggü. naivem Ansatz um 9-16% reduziert werden 

6. Conclusions

- Zusammenfassung/Ergebnisse: 
	1. "management method of the Bloom filter with B-tree structure for information retrieval"
	* Vorteil: obere Schranke f. #Schritte Query-Forwarding
	* Nachteil: Baumstruktur muss aufgebaut werden 
	* "Since a B-tree is used to manage Bloom filters, the height of the tree changes dynamically in proportion to the number of nodes" (S. 323) -> Gesamtanzahl Bloom-Filter hängt von Knotenanzahl im B-Baum ab, kann also niedriger sein als in Bloom-Filter mit fester Ringstruktur -> besser für Query-Processing!
	2. Ähnlichkeitsbasierte B-Baum-Managementmethode
	* Evaluation durch #Rekonstruktionen -> werden durch Methode reduziert -> gut für Netzwerk mit häufigem join/leave von Knoten 
	3. Repräsentative Knoten managen Maintenance-Informationen u. propagieren die Queries 
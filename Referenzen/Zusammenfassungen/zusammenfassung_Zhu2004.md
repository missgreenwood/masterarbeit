Zusammenfassung Zhu2004
-----------------------

0. Abstract 

- "An efficient and distributed scheme for file mapping or file lookup scheme [for] decentralizing metadata management within a group of metadata servers" (S. 165) -> also evtl. nicht relevant!
- "[N]ovel technique [...] to map file names to the servers holding their metadata": "Hierarchical Bloom Filter Arrays" ("HBA", S. 165)

1. Introduction 

2. Related Work and Comparisons of Decentralization Schemes

3. Architectural Considerations and Design Objectives 

- Fokus: "scalability and flexibility aspects of metadata management" (S. 167) -> also u.a. geringer Metadata-Management-Overhead 

4. Hierarchical Bloom Filter Arrays 

4.2 Hierarchical Bloom Array Design 

4.2.1 Pure Bloom Filter Array (PBA) Approach

- Erster Ansatz: Metadaten jeder Datei werden als Bloom-Filter repräsentiert, alle Bloom-Filter werden in Array gespeichert -> für mich: Metadaten entsprechen einer Nachricht; jetzt muss man schauen, ob für die Organisation d. Bloom-Filter was Neues dabei ist 

4.2.2 Hierarchical Bloom Filter Array (HBA) Approach

- Ziel ggü. PBA: "reduce memory overhead while achieving a competitively high hit rate" (S. 169)
- Interessante Grundlage (aber evtl. Zufall!): "a small fraction of files absorb most of the I/O activities" (S. 169)
- Jetzt: "[E]ach metadata server maintains a LRU [...] list that caches names of recently visited files whose metadata is stored on that metadata server. Each Bloom filter at the first level [...] represents all the files cached in the LRU list of the corresponding metadata server" (S. 169) -> aber trotzdem nicht wichtig für mich!
## Stundenliste

Mi, 09.09. (3 h 30 min)
- Papers lesen, Besprechung

So, 27.09. (1 h 30 min)
- Papers lesen + zusammenfassen, Recherche

Di, 29.09. (2 h)
- Recherche

Mi, 01.10. (3 h 30 min)
- Recherche, Papers lesen + zusammenfassen

Fr, 09.10. (4 h 45 min)
- Papers besorgen, lesen + zusammenfassen
- Schauen, was aus dem Probekapitel wichtig ist

Sa, 10.10. (5 h 30 min)
- Recherche, Papers lesen + zusammenfassen 

So, 11.10. (3 h 15 min)
- Recherche, Papers lesen + zusammenfassen 

Mo, 12.10. (4 h)
- Papers lesen + zusammenfassen 

Di, 13.10. (3 h 45 min)
- Recherche, Papers lesen + zusammenfassen

Do, 15.10. (4 h 30 min)
- Recherche, Papers lesen + zusammenfassen, Terminabsprache Mirco

Fr, 16.10. (7 h 15 min)
- Recherche, Papers lesen + zusammenfassen, Terminabsprache Mirco

Sa, 17.10. (6 h 15 min)
- Papers lesen und zusammenfassen 

So, 18.10. (6 h)
- Recherche, Papers lesen + zusammenfassen

Mi, 21.10. (9 h 30 min)
- Recherche, Papers lesen + zusammenfassen

Do, 22.10. (2 h 30 min)
- Entwurf Exposé, Papers lesen und zusammenfassen

Fr, 23.10. (2 h 15 min)
- Entwurf Exposé, Papers lesen und zusammenfassen

Sa, 07.11. (3 h 15 min)
- Recherche, Entwurf Exposé

So, 08.11. (4 h)
- Recherche, Papers lesen und zusammenfassen, Versionskontrolle, Entwurf Exposé

Mi, 11.11. (1 h 45 min)
- Papers lesen und zusammenfassen, Versionskontrolle, Entwurf Exposé

Fr, 13.11. (4 h 15 min)
- Papers lesen und zusammenfassen, Versionskontrolle, Entwurf Exposé

So, 15.11. (1 h)
- Papers lesen und zusammenfassen, Versionskontrolle, Entwurf Exposé

Di, 17.11. (30 min)
- Papers lesen und zusammenfassen, Versionskontrolle, Entwurf Exposé

Mi, 18.11. (4 h 15 min)
- Papers lesen und zusammenfassen, Versionskontrolle, Entwurf Exposé

Do, 19.11. 
- Termin mit Zweitbetreuer

Fr, 20.11. (1 h 15 min)
- Papers lesen und zusammenfassen, Versionskontrolle, Entwurf Exposé 

Sa, 21.11. (45 min)
- Entwurf Exposé 

So, 22.11. (4 h 30 min)
- Entwurf Exposé

Mo, 23.11. (3 h 15 min)

Di, 24.11. (4 h 15 min)

Mi, 25.11. (3 h)

Mo, 30.11. (1 h)

Di, 08.12. (1 h 45 min)
- Recherche, Treffen vorbereiten

Mi, 09.12. (2 h 30 min)
- Recherche, Treffen vorbereiten, Literaturverzeichnis einheitlich

Sa, 12.12. (45 min)
- Recherche, Treffen vorbereiten 

So, 13.12. (4 h
- Recherche, Treffen vorbereiten

Mo, 14.12. (4 h)
- Recherche, Treffen vorbereiten

Do, 07.01. (1 h 45 min)
- Cassandra lokal installieren + testen

Fr, 08.01. (3 h)
- Cassandra + Stress-Tool testen

So, 10.01. (3 h 45 min)
- Präsentation vorbereiten, Terminabsprache, Titel 


## TODO

1. Wie arbeitet Cassandra stress tool? 

2. Bisherige Quellen in Ausarbeitung: Ahlgren2012, Broder2004, Byers2002, Hellerstein1994, Mitzenmacher2002, Ruppel2014, Sakuma2011, Shiraki2009, Skript Anfragebearbeitung, Werner2015, Yang2002, Skript ADS2, Nafe2005, Bayardo2007, Werner2015

3. Antrittsvortrag

4. Notizen Stand in Ausarbeitung 

"1. Du hattest ja die Idee, Cassandra bzw. das Cassandra stress tool für die Evaluation meiner Implementierungen der Indexstrukturen und Algorithmen zum Mengenvergleich einzusetzen. Dazu hatten wir zwei Möglichkeiten in Betracht gezogen: 

a) Meine Daten in Cassandra bringen und das stress tool darauf anwenden 
b) Das stress tool rausziehen und für meine Implementierungen anwenden/umschreiben 

Prinzipiell ist der Quellcode von beidem (Cassandra/stress tool) frei verfügbar. Das Prinzip von Cassandra ist zwar eine verteilte Datenbank, aber man kann natürlich auch nur einen Knoten spezifizieren. Die Bloom-Filter werden in Cassandra werden für index scans auf den SSTables eingesetzt, nicht aber für range scans. Das stress tool testet Geschwindigkeit von Einfügen und Löschen von Datensätzen in einer Cassandra-Datenbank. Alles, was mit dem Verteilen und Spiegeln der Daten auf unterschiedliche Knoten zu tun hat, kann ich vernachlässigen, d.h. alles, was das Einfügen von Datensätzen in Cassandra betrifft. Ich würde mich also auf die Lookup-Funktion in Cassandra beschränken sowie auf die Organisation der Daten, die mit meinen angedachten Indexstrukturen natürlich ganz anders aussehen muss als in Cassandra. Bei mir sind außerdem die Bloom-Filter selbst die Daten, die möglichst gut organisiert/möglichst schnell gefunden werden sollen. 

Damit würde ich also vier Teilbereiche ausmachen, die man zwar kombinieren kann, aber nicht vermischen sollte: 

1. Indexstrukturen mit Bloom-Filtern als Datensätzen
2. Algorithmen zum Mengenvergleich auf Bloom-Filtern
3. Evaluation mit Cassandra
4. Evaluation mit Cassandra stress tool  

Punkt 3 ist mE nur für Punkt 2 relevant. D.h. ich könnte also versuchen, die Daten (die Bloom-Filter selbst) ohne Anpassungen in Cassandra zu bringen, den Lookup-Algorithmus verändern und das dann mit dem stress tool evaluieren. Punkt 1 hat mit der Organisation der Daten in Cassandra überhaupt nichts zu tun. D.h. ich würde nur das stress tool nehmen ohne die Datenbank und die Daten anders organisieren. ich würde also einmal die Code-Basis von Cassandra und einmal die des stress tools nehmen und für meine Anwendungsfälle umschreiben. 

Die Bloom-Filter werden in Cassandra anders verwendet als bei mir, wenn ich das richtig sehe. Der Schwerpunkt von Cassandra ist außerdem gerade die verteilte Datenbank, was bei mir keine Rolle spielt. Ich würde also Cassandra und das stress tool eher als Codebasis sehen, damit ich von irgendwas Existierendem und Funktionierendem ausgehen kann. Ich werde mir bis Dienstag den Code noch genauer anschauen. Was ich dann bald bräuchte, sind die aktuell verwendeten Testdaten bzw. Zugang zum Server. "

5. Wie kann ich bestehende Algorithmen u. Indexstrukturen umbauen?

6. Wie werden Bloom Filter in Cassandra generiert/eingesetzt?

7. Wie bringe ich meine Daten in Cassandra? 

8. Titelvorschlag (bisher: "Optimierung von Indexstrukturen und Algorithmen zum Mengenvergleich für Bloom-Filter in einem kontext-zentrierten sozialen Online-Netzwerk")


## TODO Ausarbeitung 

- Anpassen in main.tex: \lmutitle, \lmudeadline, \input{text/appendix}, \input{listoffigures}, \input{listoftables}, \input{lstlistoflistings}, \include{text/abstract}, further chapters, Erklärung zum eigenständigen Arbeiten, Tabellen/Bilder/Programmcode (vgl. introduction.tex)

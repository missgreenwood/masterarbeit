Zusammenfassung: Schnell2013
----------------------------

0. Zusammenfassung
- Inhalt: "Einführende Übersicht über technische Lösungen für die datenschutzgerechte Zusammenführung personenbezogener Daten in Deutschland" /Beschreibung zweier "neuere[r] Verfahren zur Zusammenführung personenbezogener Datenbanken, die die Identität der Person nicht erkennbar werden lassen" (S. 1)

1. Einleitung 

2. Verknüpfung personenbezogener Datenbanken
- "Record-Linkage": "Verknüpfung unterschiedlicher Datenbanken zur Untersuchung neuer Fragestellungen" (S. 3)

3. Verknüpfung personenbezogener Datenbanken in Deutschland 
- Variante 1: "Datentreuhänder" für das Record-Linkage verwenden, um die personenbezogenen Daten zu schützen (S. 5)

4. Anonyme Verknüpfung von Datenbanken
- Erweiterung: Treuhänder soll Identifikatoren nicht kennen! Dazu werden Identifikatoren durch Datengeber mit Hashfkt. (wie MD5, SHA-1) verschlüsselt ("keyed HMACs" = "keyed Hashed Message Authentification Codes" -> der Hash wird zusätzlich mit Passwort versehen)

5. Anonyme und fehlertolerante Datenverknüpfungsmethoden 
- Hier kommen jetzt die Bloom-Filter zum Einsatz: In der Medizin werden offensichtlich bisher v.a. phonetische Codes verwendet, was zu Problemen führt (hier nicht weiter relevant) -> "Privacy Preserving Record Linkage"/"PPRL" (S. 7): Methoden z. "fehlertolerante[n] und anonyme[n] Datenverknüpfung" (S. 7)
- Verfahren z. Vergleich von Namen mittels Bloom-Filtern: "Safelink" (S. 8)
- Prinzip: Namen werden in Bigramme aufgeteilt und mit mehreren, unabhängigen HMACs in Bloom-Filter eingefügt
- Verwendetes Ähnlichkeitsmaß: Dice-Koeffizient (Ähnlichkeit zweier Namen := #Anteil gemeinsamer Bigramme * 2/#Bigramme)
- "Für Safelink werden alle Identifikatoren einzeln in einen eigenen Bloom-Filter gespeichert" (S. 8)
- "Die Bigrammähnlichkeit der beiden Namen [...] wird durch die Ähnlichkeit der Bloom-Filter [...] approximiert" (S. 9)  
- Ergebnis: "fehlertolerante Verknüpfung zweier Datenbanken durch eine Forschungsgruppe oder eine Drittpartei bei vollständiger Anonymität der Identifikatoren" (S. 19)
- Entscheidender Faktor: "Zahl der Hash-Funktionen im Verhältnis zur Länge der Bloom-Filter: Je höher die Zahl der Hash-Funktionen, desto sicherer wird der Bloom-Filter gegenüber einem Angriff" (S. 9); andererseits "verringert sich die Güte der Approximation der Bigramm-Ähnlichkeit" bei großer Anzahl Hashfunktionen 
- Sicherheitsrisiken wurden minimiert durch Abbildung aller personenbezogenen Variablen ("Identifikatoren", S. 9) "mit unterschiedlicher Anzahl von HMACs und unterschiedlichen auf den gleichen Bloom-Filter" (S. 9) = "cryptographic longterm key" (S. 10) 
- Problem des Verfahrens: Hohe Fallzahlen -> Rechenaufwand ist nicht zu bewältigen 
- Lösungsansätze: Verfahren müssen gefunden werden, die mit Sicherheit die ähnlichsten Paare auch dann finden, wenn man nur die ähnlichsten Paare vergleicht [?], (S. 13) 
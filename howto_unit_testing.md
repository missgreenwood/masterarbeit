Howto unit testing 
------------------

I. Testfälle 

	1. 	Null-Fälle
	2. 	Bereichstests (range)
	3. 	Grenzfälle (edge cases)
	4. 	Fehlerfälle (failure cases)
	5. 	Wahrscheinlichste Ausführungspfade

II. googletest in XCode-Projekt einbinden

	1. 	Neues Target "Tests" erstellen (File -> New -> Target)
	2. 	Für Target "Tests" setzen (Targets -> Test markieren -> Build Settings): 
		Library search paths: /usr/local/lib
		User header search paths: /usr/local/include
		Other linker flags: -lgtest

III. Testfälle für alle Methoden erstellen

	0. 	Neue Header-Datei in src erstellen (New File -> Header File -> Next -> Save As: example.hpp, Group: src, Targets: src) -> alle zu testenden Methoden müssen darin deklariert sein 

	1. 	In Testprogramm: 
		TEST () {...} (vgl. https://github.com/google/googletest, https://github.com/google/googletest/blob/master/googletest/docs/Primer.md)

	2. 	main-Methode in Testprogramm erstellen:

		int main(int argc, char *argv[]) {
			::testing::InitGoogleTest(&argc, argv);
			return RUN_ALL_TESTS(); 
		}  

	 

IV. Tests ausführen 

	2.	Zu testende Header-Dateien in Testprogramm einbinden
	2. 	gtest-Library in Testprogramm einbinden (#include "gtest/gtest.h")
	3. 	Scheme "Tests" auswählen (Product -> Schemes -> Tests)
	4. 	Build and run (cmd + b)

	


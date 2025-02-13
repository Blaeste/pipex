#!/bin/bash

# Compilation de pipex
make re

# Création des fichiers de test
echo -e "Hello World\n42 School\nGrep this line" > infile.txt
touch outfile.txt expected_output.txt

# Fonction pour comparer les résultats
compare_outputs() {
    diff outfile.txt expected_output.txt > /dev/null
    if [ $? -eq 0 ]; then
        echo "✅ Test OK: $1"
    else
        echo "❌ Test FAIL: $1"
        echo "Diff:"
        diff outfile.txt expected_output.txt
    fi
}

echo "================== TESTS PIPEX =================="

# 🟢 Test 1 : Commande simple (cat)
./pipex infile.txt "cat" "wc -l" outfile.txt
cat infile.txt | wc -l > expected_output.txt
compare_outputs "cat | wc -l"

# 🟢 Test 2 : Commande avec arguments
./pipex infile.txt "grep 42" "wc -w" outfile.txt
grep 42 infile.txt | wc -w > expected_output.txt
compare_outputs "grep 42 | wc -w"

# 🟢 Test 3 : Commande avec PATH
./pipex infile.txt "/bin/ls -l" "wc -l" outfile.txt
/bin/ls -l infile.txt | wc -l > expected_output.txt
compare_outputs "/bin/ls -l | wc -l"

# 🟠 Test 4 : Fichier d'entrée inexistant
./pipex nonexistent.txt "cat" "wc -l" outfile.txt
if [ $? -ne 0 ]; then echo "✅ Test OK: infile inexistant"; else echo "❌ Test FAIL: infile inexistant"; fi

# 🟠 Test 5 : Commande invalide
./pipex infile.txt "invalidcommand" "wc -l" outfile.txt
if [ $? -ne 0 ]; then echo "✅ Test OK: Commande invalide"; else echo "❌ Test FAIL: Commande invalide"; fi

# 🟠 Test 6 : Permission refusée sur infile
chmod 000 infile.txt
./pipex infile.txt "cat" "wc -l" outfile.txt
if [ $? -ne 0 ]; then echo "✅ Test OK: Permission refusée"; else echo "❌ Test FAIL: Permission refusée"; fi
chmod 644 infile.txt

# 🟠 Test 7 : Permission refusée sur outfile
chmod 000 outfile.txt
./pipex infile.txt "cat" "wc -l" outfile.txt
if [ $? -ne 0 ]; then echo "✅ Test OK: Permission refusée sur outfile"; else echo "❌ Test FAIL: Permission refusée sur outfile"; fi
chmod 644 outfile.txt

# 🔴 Test 8 : Trop ou pas assez d'arguments
./pipex
if [ $? -ne 0 ]; then echo "✅ Test OK: Pas assez d'arguments"; else echo "❌ Test FAIL: Pas assez d'arguments"; fi

./pipex infile.txt "cat"
if [ $? -ne 0 ]; then echo "✅ Test OK: Pas assez d'arguments"; else echo "❌ Test FAIL: Pas assez d'arguments"; fi

# 🟢 Test 9 : Here_doc (Bonus)
echo "Line1\nLine2\nSTOP\nLine3" | ./pipex here_doc STOP "cat" "wc -l" outfile.txt
echo "Line1\nLine2\nLine3" | wc -l > expected_output.txt
compare_outputs "Here_doc test"

echo "================== FIN TESTS =================="

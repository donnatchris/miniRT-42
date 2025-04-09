#!/bin/bash

SCENE="test_scene.rt"
VALGRIND_LOG="valgrind.log"

# Détection de l'exécutable
if [[ -x ./miniRT_bonus ]]; then
	EXEC="./miniRT_bonus"
elif [[ -x ./miniRT ]]; then
	EXEC="./miniRT"
else
	echo "❌ Aucun exécutable trouvé (miniRT ou miniRT_bonus)."
	exit 1
fi

# Vérifie que la scène existe
if [[ ! -f "$SCENE" ]]; then
	echo "❌ Le fichier de scène '$SCENE' est introuvable."
	exit 1
fi

echo "🚀 Lancement de Valgrind sur $EXEC avec $SCENE..."
valgrind --leak-check=full --show-leak-kinds=all \
	--track-origins=yes --log-file="$VALGRIND_LOG" \
	"$EXEC" "$SCENE"

echo ""
echo "🧠 Résumé Valgrind :"
grep -A10 "HEAP SUMMARY" "$VALGRIND_LOG"

echo ""
echo "📄 Log complet dispo dans : $VALGRIND_LOG"


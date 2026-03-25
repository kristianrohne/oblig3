# oblig3 — INF205

Implementasjon av et **binært søketre** (Binary Search Tree, BST) i Python.

## Beskrivelse

Et binært søketre er en node-basert trestruktur der:
- Hver node har maksimalt to barn (venstre og høyre).
- Alle verdier i venstre deltre er **mindre enn** nodens verdi.
- Alle verdier i høyre deltre er **større enn** nodens verdi.

## Filstruktur

| Fil | Beskrivelse |
|-----|-------------|
| `bst.py` | Implementasjon av `Node`- og `BinarySearchTree`-klassene |
| `test_bst.py` | Enhetstester (pytest) |

## Operasjoner

| Metode | Beskrivelse | Tidskompleksitet (gjennomsnitt) |
|--------|-------------|-------------------------------|
| `insert(value)` | Sett inn en verdi | O(log n) |
| `search(value)` | Søk etter en verdi | O(log n) |
| `delete(value)` | Fjern en verdi | O(log n) |
| `inorder()` | Inorden-traversering (gir sortert rekkefølge) | O(n) |
| `preorder()` | Preorden-traversering | O(n) |
| `postorder()` | Postorden-traversering | O(n) |
| `height()` | Høyden til treet | O(n) |
| `size()` | Antall noder | O(n) |
| `min_value()` | Minste verdi | O(log n) |
| `max_value()` | Største verdi | O(log n) |

## Kjøring

```bash
# Kjør demo
python bst.py

# Kjør tester
pytest test_bst.py -v
```

## Eksempel

```python
from bst import BinarySearchTree

bst = BinarySearchTree()
for v in [50, 30, 70, 20, 40, 60, 80]:
    bst.insert(v)

print(bst.inorder())   # [20, 30, 40, 50, 60, 70, 80]
print(bst.search(40))  # True
print(bst.height())    # 2
bst.delete(50)
print(bst.inorder())   # [20, 30, 40, 60, 70, 80]
```
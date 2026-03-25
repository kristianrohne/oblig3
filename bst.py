"""
INF205 - Oblig 3
Binary Search Tree (BST) implementation in Python.

A Binary Search Tree is a node-based binary tree where:
  - Each node has at most two children (left and right).
  - All values in the left subtree are less than the node's value.
  - All values in the right subtree are greater than the node's value.
"""


class Node:
    """A single node in a Binary Search Tree."""

    def __init__(self, value):
        self.value = value
        self.left = None
        self.right = None

    def __repr__(self):
        return f"Node({self.value})"


class BinarySearchTree:
    """
    Binary Search Tree with standard operations:
      - insert
      - search
      - delete
      - inorder / preorder / postorder traversal
      - height
      - min_value / max_value
    """

    def __init__(self):
        self.root = None

    # ------------------------------------------------------------------
    # Insert
    # ------------------------------------------------------------------

    def insert(self, value):
        """Insert a value into the BST."""
        self.root = self._insert(self.root, value)

    def _insert(self, node, value):
        if node is None:
            return Node(value)
        if value < node.value:
            node.left = self._insert(node.left, value)
        elif value > node.value:
            node.right = self._insert(node.right, value)
        # Duplicate values are ignored
        return node

    # ------------------------------------------------------------------
    # Search
    # ------------------------------------------------------------------

    def search(self, value):
        """Return True if *value* exists in the BST, otherwise False."""
        return self._search(self.root, value)

    def _search(self, node, value):
        if node is None:
            return False
        if value == node.value:
            return True
        if value < node.value:
            return self._search(node.left, value)
        return self._search(node.right, value)

    # ------------------------------------------------------------------
    # Delete
    # ------------------------------------------------------------------

    def delete(self, value):
        """Remove a value from the BST (no-op if the value is absent)."""
        self.root = self._delete(self.root, value)

    def _delete(self, node, value):
        if node is None:
            return None
        if value < node.value:
            node.left = self._delete(node.left, value)
        elif value > node.value:
            node.right = self._delete(node.right, value)
        else:
            # Node to delete found
            if node.left is None:
                return node.right
            if node.right is None:
                return node.left
            # Node has two children: replace with inorder successor
            successor = self._min_node(node.right)
            node.value = successor.value
            node.right = self._delete(node.right, successor.value)
        return node

    # ------------------------------------------------------------------
    # Traversals
    # ------------------------------------------------------------------

    def inorder(self):
        """Return a list of values using inorder (left, root, right) traversal.

        Inorder traversal of a BST yields values in sorted ascending order.
        """
        result = []
        self._inorder(self.root, result)
        return result

    def _inorder(self, node, result):
        if node is not None:
            self._inorder(node.left, result)
            result.append(node.value)
            self._inorder(node.right, result)

    def preorder(self):
        """Return a list of values using preorder (root, left, right) traversal."""
        result = []
        self._preorder(self.root, result)
        return result

    def _preorder(self, node, result):
        if node is not None:
            result.append(node.value)
            self._preorder(node.left, result)
            self._preorder(node.right, result)

    def postorder(self):
        """Return a list of values using postorder (left, right, root) traversal."""
        result = []
        self._postorder(self.root, result)
        return result

    def _postorder(self, node, result):
        if node is not None:
            self._postorder(node.left, result)
            self._postorder(node.right, result)
            result.append(node.value)

    # ------------------------------------------------------------------
    # Height
    # ------------------------------------------------------------------

    def height(self):
        """Return the height of the BST.

        An empty tree has height -1; a single-node tree has height 0.
        """
        return self._height(self.root)

    def _height(self, node):
        if node is None:
            return -1
        return 1 + max(self._height(node.left), self._height(node.right))

    # ------------------------------------------------------------------
    # Min / Max
    # ------------------------------------------------------------------

    def min_value(self):
        """Return the minimum value stored in the BST.

        Raises ValueError if the tree is empty.
        """
        if self.root is None:
            raise ValueError("Tree is empty")
        return self._min_node(self.root).value

    def max_value(self):
        """Return the maximum value stored in the BST.

        Raises ValueError if the tree is empty.
        """
        if self.root is None:
            raise ValueError("Tree is empty")
        return self._max_node(self.root).value

    def _min_node(self, node):
        current = node
        while current.left is not None:
            current = current.left
        return current

    def _max_node(self, node):
        current = node
        while current.right is not None:
            current = current.right
        return current

    # ------------------------------------------------------------------
    # Size
    # ------------------------------------------------------------------

    def size(self):
        """Return the number of nodes in the BST."""
        return self._size(self.root)

    def _size(self, node):
        if node is None:
            return 0
        return 1 + self._size(node.left) + self._size(node.right)

    # ------------------------------------------------------------------
    # Pretty print
    # ------------------------------------------------------------------

    def __str__(self):
        """Return a simple string representation of the BST (inorder)."""
        return f"BST(inorder={self.inorder()})"


# ----------------------------------------------------------------------
# Demo
# ----------------------------------------------------------------------

if __name__ == "__main__":
    bst = BinarySearchTree()

    values = [50, 30, 70, 20, 40, 60, 80]
    print(f"Inserting values: {values}")
    for v in values:
        bst.insert(v)

    print(f"\nInorder traversal (sorted): {bst.inorder()}")
    print(f"Preorder traversal:         {bst.preorder()}")
    print(f"Postorder traversal:        {bst.postorder()}")
    print(f"\nTree height: {bst.height()}")
    print(f"Tree size:   {bst.size()}")
    print(f"Min value:   {bst.min_value()}")
    print(f"Max value:   {bst.max_value()}")

    print("\nSearching:")
    for val in [40, 99]:
        found = bst.search(val)
        print(f"  search({val}) -> {found}")

    print("\nDeleting 30 (node with two children):")
    bst.delete(30)
    print(f"  Inorder after delete: {bst.inorder()}")

    print("\nDeleting 20 (leaf node):")
    bst.delete(20)
    print(f"  Inorder after delete: {bst.inorder()}")

    print("\nDeleting 50 (root node):")
    bst.delete(50)
    print(f"  Inorder after delete: {bst.inorder()}")

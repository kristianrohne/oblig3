"""
Tests for Binary Search Tree (BST) implementation — INF205 Oblig 3.
Run with:  pytest test_bst.py -v
"""

import pytest
from bst import BinarySearchTree, Node


# ---------------------------------------------------------------------------
# Helper
# ---------------------------------------------------------------------------

def build_bst(*values):
    """Return a BST containing the given values (inserted in order)."""
    bst = BinarySearchTree()
    for v in values:
        bst.insert(v)
    return bst


# ---------------------------------------------------------------------------
# Node
# ---------------------------------------------------------------------------

class TestNode:
    def test_node_creation(self):
        node = Node(42)
        assert node.value == 42
        assert node.left is None
        assert node.right is None

    def test_node_repr(self):
        assert repr(Node(7)) == "Node(7)"


# ---------------------------------------------------------------------------
# Empty tree
# ---------------------------------------------------------------------------

class TestEmptyTree:
    def setup_method(self):
        self.bst = BinarySearchTree()

    def test_root_is_none(self):
        assert self.bst.root is None

    def test_inorder_empty(self):
        assert self.bst.inorder() == []

    def test_preorder_empty(self):
        assert self.bst.preorder() == []

    def test_postorder_empty(self):
        assert self.bst.postorder() == []

    def test_height_empty(self):
        assert self.bst.height() == -1

    def test_size_empty(self):
        assert self.bst.size() == 0

    def test_search_empty(self):
        assert self.bst.search(1) is False

    def test_min_raises_on_empty(self):
        with pytest.raises(ValueError):
            self.bst.min_value()

    def test_max_raises_on_empty(self):
        with pytest.raises(ValueError):
            self.bst.max_value()

    def test_delete_empty_is_noop(self):
        self.bst.delete(5)  # should not raise
        assert self.bst.root is None


# ---------------------------------------------------------------------------
# Single-node tree
# ---------------------------------------------------------------------------

class TestSingleNode:
    def setup_method(self):
        self.bst = build_bst(10)

    def test_root_value(self):
        assert self.bst.root.value == 10

    def test_height_single(self):
        assert self.bst.height() == 0

    def test_size_single(self):
        assert self.bst.size() == 1

    def test_search_found(self):
        assert self.bst.search(10) is True

    def test_search_not_found(self):
        assert self.bst.search(99) is False

    def test_min_value(self):
        assert self.bst.min_value() == 10

    def test_max_value(self):
        assert self.bst.max_value() == 10

    def test_inorder_single(self):
        assert self.bst.inorder() == [10]

    def test_preorder_single(self):
        assert self.bst.preorder() == [10]

    def test_postorder_single(self):
        assert self.bst.postorder() == [10]


# ---------------------------------------------------------------------------
# Insert
# ---------------------------------------------------------------------------

class TestInsert:
    def test_insert_multiple(self):
        bst = build_bst(5, 3, 7, 1, 4, 6, 8)
        assert bst.size() == 7

    def test_insert_maintains_bst_property(self):
        bst = build_bst(5, 3, 7, 1, 4, 6, 8)
        values = bst.inorder()
        assert values == sorted(values)

    def test_insert_duplicate_ignored(self):
        bst = build_bst(5, 5, 5)
        assert bst.size() == 1

    def test_insert_ascending_order(self):
        bst = build_bst(1, 2, 3, 4, 5)
        assert bst.inorder() == [1, 2, 3, 4, 5]

    def test_insert_descending_order(self):
        bst = build_bst(5, 4, 3, 2, 1)
        assert bst.inorder() == [1, 2, 3, 4, 5]


# ---------------------------------------------------------------------------
# Search
# ---------------------------------------------------------------------------

class TestSearch:
    def setup_method(self):
        self.bst = build_bst(50, 30, 70, 20, 40, 60, 80)

    def test_search_root(self):
        assert self.bst.search(50) is True

    def test_search_left_subtree(self):
        assert self.bst.search(20) is True

    def test_search_right_subtree(self):
        assert self.bst.search(80) is True

    def test_search_missing(self):
        assert self.bst.search(99) is False

    def test_search_after_insert(self):
        self.bst.insert(45)
        assert self.bst.search(45) is True


# ---------------------------------------------------------------------------
# Delete
# ---------------------------------------------------------------------------

class TestDelete:
    def test_delete_leaf(self):
        bst = build_bst(5, 3, 7)
        bst.delete(3)
        assert bst.search(3) is False
        assert bst.inorder() == [5, 7]

    def test_delete_node_with_one_child(self):
        bst = build_bst(5, 3, 7, 2)
        bst.delete(3)
        assert bst.search(3) is False
        assert bst.inorder() == [2, 5, 7]

    def test_delete_node_with_two_children(self):
        bst = build_bst(50, 30, 70, 20, 40, 60, 80)
        bst.delete(30)
        assert bst.search(30) is False
        values = bst.inorder()
        assert values == sorted(values)
        assert 30 not in values

    def test_delete_root_single_node(self):
        bst = build_bst(10)
        bst.delete(10)
        assert bst.root is None
        assert bst.size() == 0

    def test_delete_root_multiple_nodes(self):
        bst = build_bst(50, 30, 70)
        bst.delete(50)
        assert bst.search(50) is False
        values = bst.inorder()
        assert values == sorted(values)

    def test_delete_missing_value_is_noop(self):
        bst = build_bst(5, 3, 7)
        bst.delete(99)
        assert bst.inorder() == [3, 5, 7]

    def test_delete_reduces_size(self):
        bst = build_bst(5, 3, 7)
        bst.delete(3)
        assert bst.size() == 2


# ---------------------------------------------------------------------------
# Traversals
# ---------------------------------------------------------------------------

class TestTraversals:
    def setup_method(self):
        # Build a balanced BST:
        #       4
        #      / \
        #     2   6
        #    / \ / \
        #   1  3 5  7
        self.bst = build_bst(4, 2, 6, 1, 3, 5, 7)

    def test_inorder(self):
        assert self.bst.inorder() == [1, 2, 3, 4, 5, 6, 7]

    def test_preorder(self):
        assert self.bst.preorder() == [4, 2, 1, 3, 6, 5, 7]

    def test_postorder(self):
        assert self.bst.postorder() == [1, 3, 2, 5, 7, 6, 4]


# ---------------------------------------------------------------------------
# Height & size
# ---------------------------------------------------------------------------

class TestHeightAndSize:
    def test_height_balanced(self):
        bst = build_bst(4, 2, 6, 1, 3, 5, 7)
        assert bst.height() == 2

    def test_height_skewed(self):
        bst = build_bst(1, 2, 3, 4, 5)
        assert bst.height() == 4

    def test_size(self):
        bst = build_bst(4, 2, 6, 1, 3, 5, 7)
        assert bst.size() == 7


# ---------------------------------------------------------------------------
# Min / Max
# ---------------------------------------------------------------------------

class TestMinMax:
    def setup_method(self):
        self.bst = build_bst(50, 30, 70, 20, 40, 60, 80)

    def test_min(self):
        assert self.bst.min_value() == 20

    def test_max(self):
        assert self.bst.max_value() == 80

    def test_min_after_delete(self):
        self.bst.delete(20)
        assert self.bst.min_value() == 30

    def test_max_after_delete(self):
        self.bst.delete(80)
        assert self.bst.max_value() == 70


# ---------------------------------------------------------------------------
# String representation
# ---------------------------------------------------------------------------

class TestStr:
    def test_str(self):
        bst = build_bst(2, 1, 3)
        assert str(bst) == "BST(inorder=[1, 2, 3])"

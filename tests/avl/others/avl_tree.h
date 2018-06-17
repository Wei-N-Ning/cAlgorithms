
#ifndef AVL_TREE_H_
#define AVL_TREE_H_

#include <memory>
#include <cstdlib>

template <class KeyType, class ValueType> class AVLTree {
 private:
  enum CompareResult {
    kMinCmp = -1,
    kEqCmp = 0,
    kMaxCmp = 1
  };

  enum Direction {
    kLeft = 0,
    kRight = 1
  };

 public:

  class Comparable {
   private:
    KeyType key;
    ValueType value;

   public:
    Comparable(KeyType key, ValueType value) : key(key), value(value) {}

    CompareResult Compare(KeyType key) const {
      return (key == this->key) ? kEqCmp
          : ((key < this->key) ? kMinCmp : kMaxCmp);
    }

    KeyType Key() const {
      return key;
    }

    ValueType Value() const {
      return value;
    }

    void SetValue(ValueType v) {
      value = v;
    }
  };

  enum BalanceFactor {
    kE = 0,
    kL = -1,
    kR = 1
  };

  struct Node {
    explicit Node(Comparable* item) :
        item(item),
        balance_factor(kE) {
      children[kLeft] = nullptr;
      children[kRight] = nullptr;
    }

    ~Node() {
        delete item;
        item = nullptr;

        if (Left()) {
            delete Left();
        }
        if (Right()) {
            delete Right();
        }
    }

    bool IsLeftImbalance() const {
      return balance_factor < kL;
    }

    bool IsRightImbalance() const {
      return balance_factor > kR;
    }

    Node* Right() const {
      return children[kRight];
    }

    Node* Left() const {
      return children[kLeft];
    }

    static Direction Opposite(Direction dir) {
      return static_cast<Direction>(1 - static_cast<int>(dir));
    }

    static int RotateOnce(Node*& root, Direction dir) {
      Direction other_dir = Opposite(dir);
      Node* old_root = root;

      int height_change = (root->children[other_dir]->balance_factor == 0)
          ? kHeightNoChange : kHeightChange;

      root = old_root->children[other_dir];

      old_root->children[other_dir] = root->children[dir];
      root->children[dir] = old_root;

      old_root->balance_factor =
          -((dir == kLeft) ?
            --(root->balance_factor) : ++(root->balance_factor));

      return  height_change;
    }

    static int min(int a, int b) {
      return  (a < b) ? a : b;
    }

    static int max(int a, int b) {
      return  (a > b) ? a : b;
    }

    static int RotateTwice(Node*& root, Direction dir) {
      Direction other_dir = Opposite(dir);
      Node* old_root = root;
      Node* old_other_dir_subtree = root->children[other_dir];

      root = old_root->children[other_dir]->children[dir];

      old_root->children[other_dir] = root->children[dir];
      root->children[dir] = old_root;

      old_other_dir_subtree->children[dir] = root->children[other_dir];
      root->children[other_dir] = old_other_dir_subtree;

      root->Left()->balance_factor =
          -max(static_cast<int>(root->balance_factor), 0);
      root->Right()->balance_factor =
          -min(static_cast<int>(root->balance_factor), 0);
      root->balance_factor = 0;

      return kHeightChange;
    }

    static Comparable* Get(KeyType key, Node* root, CompareResult cmp) {
      CompareResult result;
      while (root &&  (result = root->Compare(key, cmp))) {
        root = root->children[(result < 0) ? kLeft : kRight];
      }
      return root ? root->item : nullptr;
    }

    static Comparable* Insert(Comparable* item, Node*& root) {
      int change;
      return Insert(item, root, change);
    }

    static Comparable* Insert(Comparable* item, Node*& root, int& change) { // NOLINT
      if (root == nullptr) {
        root = new Node(item);
        change = kHeightChange;
        return nullptr;
      }

      Comparable* found = nullptr;
      CompareResult result = root->Compare(item->Key());
      Direction dir = (result == kMinCmp) ? kLeft : kRight;

      int increase = 0;
      if (result != kEqCmp) {
        found = Insert(item, root->children[dir], change);
        if (found) {
          return found;
        }
        increase = result * change;
      } else  {
        increase = kHeightNoChange;
        return root->item;
      }

      root->balance_factor += increase;
      change = (increase && root->balance_factor)
          ? (1 - ReBalance(root)) : kHeightNoChange;
      return nullptr;
    }

    static int ReBalance(Node*& root) {
      int height_change = kHeightNoChange;

      if (root->IsLeftImbalance()) {
        if (root->Left()->balance_factor == kR) {
          height_change = RotateTwice(root, kRight);
        } else {
          height_change = RotateOnce(root, kRight);
        }
      } else if (root->IsRightImbalance()) {
        if (root->Right()->balance_factor == kL) {
          height_change = RotateTwice(root, kLeft);
        } else {
          height_change = RotateOnce(root, kLeft);
        }
      }

      return height_change;
    }

    static Comparable* Remove(KeyType key, Node*& root, CompareResult cmp) {
      int change;
      return Remove(key, root, change, cmp);
    }

    static Comparable* Remove(const KeyType key,
                              Node*& root,
                              int& change,
                              CompareResult cmp) {
      if (root == nullptr) {
        change = kHeightNoChange;
        return nullptr;
      }

      Comparable* found = nullptr;
      int decrease = 0;

      CompareResult result = root->Compare(key, cmp);
      Direction dir = (result == kMinCmp) ? kLeft : kRight;

      if (result != kEqCmp) {
        found = Remove(key, root->children[dir], change, cmp);
        if (! found) {
          return found;
        }
        decrease = result * change;
      } else  {
        found = root->item;
        if ((root->Left() == nullptr) &&
            (root->Right() == nullptr)) {
          delete root;
          root = nullptr;
          change = kHeightChange;
          return  found;
        } else if ((root->Left() == nullptr) ||
                   (root->Right() == nullptr)) {
          Node*& toDelete = root;
          root = root->children[(root->Right()) ? kRight : kLeft];
          change = kHeightChange;
          toDelete->children[kLeft] = toDelete->children[kRight] = nullptr;
          delete  toDelete;
          toDelete = nullptr;
          return  found;
        } else {
//          root->item = Remove(key, root->children[kRight],
//                              decrease, kMinCmp);
            delete root;
            root = nullptr;
            return nullptr;
        }
      }
      root->balance_factor -= decrease;

      if (decrease) {
        if (root->balance_factor) {
          change = ReBalance(root);
        } else {
          change = kHeightChange;
        }
      } else {
        change = kHeightNoChange;
      }
      return  found;
    }

    CompareResult Compare(KeyType key, CompareResult cmp = kEqCmp) const {
      switch (cmp) {
        case kEqCmp:
          return item->Compare(key);
        case kMinCmp:
          return  (children[kLeft] == nullptr) ? kEqCmp : kMinCmp;
        default:
          return (children[kRight] == nullptr) ? kEqCmp : kMaxCmp;
      }
    }

    Node* children[2];
    Comparable* item;
    int balance_factor;

   private:
    Node() {}
    Node(const Node& n) {}
    Node & operator=(const Node&) {}
  };

  AVLTree() : root_(nullptr) {
  }

  virtual ~AVLTree() {
    if (root_) {
      delete root_;
      root_ = nullptr;
    }
  }

  Node* Root() const {
    return root_;
  }

  void Add(const KeyType key, const ValueType value) {
    Comparable* item = new Comparable(key, value);
    Comparable* result = Node::Insert(item, root_);
    if (result) {
      result->SetValue(value);
      delete item;
    }
  }

  Comparable* Remove(const KeyType key, CompareResult cmp = kEqCmp) {
    return Node::Remove(key, root_, cmp);
  }

  Comparable* Get(const KeyType key, CompareResult cmp = kEqCmp) const {
    return Node::Get(key, root_, cmp);
  }

  Comparable* GetLowerNearest(const KeyType key) const {
    Node* last_node_lt_key = nullptr;
    Node* n = root_;

    while (n != nullptr) {
      if (n->item->Key() == key) {
        return n->item;
      } else if (n->item->Key() < key) {
        last_node_lt_key = n;
        n = n->Right();
      } else {
        n = n->Left();
      }
    }
    if (last_node_lt_key == nullptr) {
      return nullptr;
    } else {
      return last_node_lt_key->item;
    }
  }

  bool IsBalanced() const {
    if (root_ == nullptr) {
      return true;
    }
    int diff = abs(Height(root_->Left()) - Height(root_->Right()));
    return diff <= 1;
  }

  bool IsEmpty() const {
    return root_ == nullptr;
  }

 private:
  enum HeightEffect {
    kHeightNoChange = 0,
    kHeightChange = 1
  };

  int Height(Node* n) const {
    if (n == nullptr) {
      return 0;
    }
    int l = Height(n->Left());
    int r = Height(n->Right());
    return Node::max(l, r) + 1;
  }

  Node* root_;
};

#endif  // AVL_TREE_H_

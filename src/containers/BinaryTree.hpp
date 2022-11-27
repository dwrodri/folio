#include <functional>
#include <initializer_list>
#include <memory>
namespace folio {

template <typename T>
class BinaryTree {
    struct Node {
        Node* left;
        Node* right;
        T value;
        Node() : left{nullptr}, right{nullptr}, value{} {}
        Node(T val) : left{nullptr}, right{nullptr}, value{val} {}
        Node(Node const& other)
                : left{new Node{}}, right{new Node}, value{other.value} {
            *left = *other.left;
            *right = *other.right;
        }
        ~Node() {
            delete left;
            delete right;
        }
        Node& operator=(Node& other) {
            *left = *other.left;
            *right = *other.right;
            value = other.value;
        }
    };
    Node* root_;
    std::function<bool(T const, T const)> go_left_ = std::less_equal<T>{};

  public:
    BinaryTree<T>() : root_{nullptr} {}

    BinaryTree<T>(T const root_value,
            std::function<bool(T const, T const)> go_left = std::less_equal<T>{})
            : root_{new Node{root_value}}, go_left_{go_left} {}

    BinaryTree<T>(BinaryTree<T> const& other) : root_{nullptr} {
        if (!other.isEmpty()) {
            root_ = new Node{other.root_};
        }
    }

    BinaryTree<T>(std::initializer_list<T> values) : root_{} {
        for (T elem : values) {
            insert(elem);
        }
    }

    ~BinaryTree<T>() { delete root_; }

    /**
     * @brief check if tree has any contents
     *
     * @return true
     * @return false
     */
    bool isEmpty() const { return root_ == nullptr; }

    Node const* root() const { return root_; }
    /**
     * @brief add a new element to the binary tree
     *
     * @param value the value to be inserted
     */
    void insert(T const value) {
        std::function<void(T const, Node**)> traverse = [this, &traverse](T const value,
                                                                Node** current_node) {
            if (*current_node == nullptr) {
                *current_node = new Node(value);
                return;
            } else if (go_left_(value, (*current_node)->value)) {
                if ((*current_node)->left) {
                    traverse(value, &((*current_node)->left));
                } else {
                    (*current_node)->left = new Node{value};
                }
            } else {
                if ((*current_node)->right) {
                    traverse(value, &((*current_node)->right));
                } else {
                    (*current_node)->right = new Node{value};
                }
            }
        };
        traverse(value, &root_);
    }

    /**
     * @brief search for a value in the tree
     *
     * @param key the value to search for
     * @return true the value is in the tree
     * @return false the value is not in the tree
     */
    bool contains(T const key) const {
        std::function<bool(T const, Node const*)> searcher =
                [this, &searcher](T const key, Node const* current_node) {
                    if (!current_node) {
                        return false;
                    } else if (current_node->value == key) {
                        return true;
                    } else if (go_left_(key, current_node->value)) {
                        return searcher(key, current_node->left);
                    } else {
                        return searcher(key, current_node->right);
                    }
                };
        return searcher(key, root_);
    }
};
}  // namespace folio
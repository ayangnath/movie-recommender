#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <vector>


template <typename KeyType, typename ValueType>
class TreeMultimap
{
  public:
    class Iterator
    {
      public:
        Iterator(): m_it(), m_end()
        /**TODO: No matter whether you declare
        other constructors, your TreeMultimap::Iterator MUST have a default constructor that initializes
        an invalid Iterator object (that doesn't refer to any values), so this code can work:*/
        {}

        Iterator(typename std::vector<ValueType>::iterator beg, typename std::vector<ValueType>::iterator end): m_it(beg), m_end(end)
        {
        }

        ValueType& get_value() const
        {
            return *m_it;
        }

        bool is_valid() const
        {
            return m_it != m_end;
        }

        void advance()
        {
            ++m_it;
        }

      private:
        typename std::vector<ValueType>::iterator m_it;
        typename std::vector<ValueType>::iterator m_end;
    };

    TreeMultimap(): m_root(nullptr)
    {}

    ~TreeMultimap()
    {
        destructorHelper(m_root);
    }

    void insert(const KeyType& key, const ValueType& value)
    {
        Node* toInsert = new Node(key, value);
        if(m_root == nullptr)
        {
            m_root = toInsert;
            return;
        }

        Node* cur = m_root;
        while (true)
        {
            if (key == cur->key)
            {
                cur->values.push_back(value);
                delete toInsert;
                return;
            }
            
            
            else if (key < cur->key)
            {
                if (cur->left==nullptr)
                {
                    cur->left = toInsert;
                    return;
                }
                else cur = cur->left;
            }
            else
            {
                if(cur->right==nullptr)
                {
                    cur->right = toInsert;
                    return;
                }
                else cur = cur ->right;
            }
        }
    }

    Iterator find(const KeyType& key) const
    {
        Node* cur = m_root;
        while (cur!=nullptr)
        {
            if (key == cur->key)
                return Iterator(cur->values.begin(), cur->values.end()); //using the vector.begin() and end() to pass into constructor
            else if (key < cur->key)
                cur = cur ->left;
            else cur = cur ->right;
        }
        return Iterator();
    }

  private:
    struct Node
    {
        KeyType key;
        std::vector<ValueType>values;
        Node*left;
        Node*right;
        Node(const KeyType& k, const ValueType&v): key(k), left(nullptr), right(nullptr)
        {
            values.push_back(v);
        }
    };

    Node* m_root;
    void destructorHelper(Node* n)
    {
        if (n==nullptr)
            return;
        destructorHelper(n->left);
        destructorHelper(n->right);
        delete n;
    }
};

#endif // TREEMULTIMAP_INCLUDED

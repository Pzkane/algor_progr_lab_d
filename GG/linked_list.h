#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

namespace PZ
{
    template <typename T>
    struct Node
    {
        T data;
        Node *next;
    };

    template <typename T>
    class Linked_List
    {
        Node<T> *head;
        Node<T> *tail;
        unsigned int nodes_count();
    public:
        Linked_List();
        ~Linked_List();

        Node<T> operator() ();
        Node<T>* begin();
        Node<T>* end();
        void push_front(T value);
        void push_back(T value);
        void pop_front();
        void pop_back();
        bool empty();
        unsigned int size();
        Node<T>* erase(int);
    };

    template <typename T>
    std::ostream &operator << (std::ostream &out, Linked_List<T> &obj)
    {
        return out<<"Linked_List object at "<<&obj;
    }

    template <typename T>
    unsigned int Linked_List<T>::nodes_count()
    {
        unsigned int node_count = 0;

        if (head->data == NULL && head->next == nullptr)
            return node_count;

        Node<T> * tmp = head;
        while (tmp != this->end())
        {
            ++node_count;
            tmp = tmp->next;
        }
        return node_count;
    }

    template <typename T>
    Linked_List<T>::Linked_List()
    {
        head = new Node<T>;
        head->data = NULL;
        head->next = nullptr;
        tail = head;
    }

    template <typename T>
    Linked_List<T>::~Linked_List()
    {
        if (head->next == nullptr) delete head;
        else
        {
            Node<T> *tmp_head = head;
            do
            {
                tmp_head = tmp_head->next;
                head->data = NULL;
                delete head;
                head = tmp_head;
            } while(tmp_head != tail);
            head->data = NULL;
            delete head;
        }
    }

    template <typename T>
    Node<T> Linked_List<T>::operator() ()
    {
        return head;
    }

    template <typename T>
    Node<T>* Linked_List<T>::begin()
    {
        return head;
    }

    template <typename T>
    Node<T>* Linked_List<T>::end()
    {
        return tail->next;
    }

    template <typename T>
    void Linked_List<T>::push_front(T value)
    {
        Node<T> *new_head = new Node<T>;
        new_head->data = value;
        new_head->next = head;
        head = new_head;
    }

    template <typename T>
    void Linked_List<T>::push_back(T value)
    {
        if (head->data == NULL && head->next == nullptr)
        {
            head->data = value;
            return;
        }
        Node<T> *new_node = new Node<T>;
        new_node->data = value;
        new_node->next = nullptr;

        tail->next = new_node;
        tail = new_node;
    }

    template <typename T>
    void Linked_List<T>::pop_front()
    {
        if (head->next == nullptr)
        {
            head->data = NULL;
            return;
        }
        Node<T> *old_head = head;
        head = head->next;
        delete old_head;
    }

    template <typename T>
    void Linked_List<T>::pop_back()
    {
        Node<T> *node = head;
        if (node->next == nullptr)
        {
            head->data = NULL;
            return;
        }
        while(node->next != tail)
            node = node->next;

        Node<T> *to_pop = node->next; // tail
        node->next = nullptr;
        tail = node;
        to_pop->data = NULL;
        delete to_pop;
    }

    template <typename T>
    bool Linked_List<T>::empty()
    {
        if (nodes_count() == 0) return true;
        return false;
    }

    template <typename T>
    unsigned int Linked_List<T>::size()
    {
        return nodes_count();
    }

    template <typename T>
    Node<T>* Linked_List<T>::erase(int position)
    {
        if (position < 0) throw std::runtime_error("Error::PZ::Linked_List::erase: 'position' cannot be less than 0!");
        if (position > this->size()-1) throw std::runtime_error("Error::PZ::Linked_List::erase: 'position' is bigger than size of the list!");
        if (position == 0)
        {
            Node<T> *tmp_head = head;
            head = head->next;
            delete tmp_head;
            return head;
        }

        unsigned int iter = 0;
        Node<T> *prev_node, *curr_node = head;
        do
        {
            prev_node = curr_node;
            curr_node = curr_node->next;
        } while (++iter != position);

        prev_node->next = curr_node->next;
        if (curr_node == this->tail)
            tail = prev_node;
        delete curr_node;
        return prev_node;
    }
}

#endif // LINKED_LIST_H_INCLUDED
